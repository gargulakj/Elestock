#include <QDebug>
#include <QProcess>
#include "SqlConnector.h"

///
/// \brief Maximum size of queue of pending queries.
///
static int MaxQueryQueueSize = 255;

///
/// \brief Path to database data file.
///
static QString DataPath = "/var/lib/mysql/";

///
/// \brief Static mutex for lock multiple access to mysql server.
///
QMutex CSqlConnector::m_ServerLock;

///
/// \brief Constructor of sql connection setting.
///
CSqlConnectorSetting::CSqlConnectorSetting() :
    m_HostName( "" ),
    m_DatabaseName( "" ),
    m_UserName( "" ),
    m_Password( "" ),
    m_SizeLimit( 128 * 1024 ),
    m_UseSizeLimit( true )
{

}

///
/// \brief Copy data from another instance.
/// \param copyFrom Copy from instance.
///
void CSqlConnectorSetting::CopyFrom( const CSqlConnectorSetting& copyFrom )
{
    m_HostName = copyFrom.m_HostName;
    m_DatabaseName = copyFrom.m_DatabaseName;
    m_UserName = copyFrom.m_UserName;
    m_Password = copyFrom.m_Password;
    m_SizeLimit = copyFrom.m_SizeLimit;
    m_UseSizeLimit = copyFrom.m_UseSizeLimit;
}
///
/// \brief Returns true if this and other setting are equal.
/// \param other Other instance for comparision.
/// \return Returns true if this and other setting are equal.
///
bool CSqlConnectorSetting::IsEqual( const CSqlConnectorSetting& other )
{
    bool equal = true;
    if( m_HostName != other.GetHostName() )
        equal = false;
    if( m_DatabaseName != other.GetDatabaseName() )
        equal = false;
    if( m_UserName != other.GetUserName() )
        equal = false;
    if( m_Password != other.GetPassword() )
        equal = false;
    if( m_SizeLimit != other.GetSizeLimit() )
        equal = false;
    if( m_UseSizeLimit != other.IsSizeLimitUsed() )
        equal = false;

    return equal;
}

///
/// \brief Copy constructor.
/// \param CopyFrom Copy from instance.
///
CSqlConnectorSetting::CSqlConnectorSetting( const CSqlConnectorSetting& copyFrom )
{
    CopyFrom( copyFrom );
}

///
/// \brief Operator = overload
/// \param Right operand
/// \return Return this instace.
///
CSqlConnectorSetting& CSqlConnectorSetting::operator= ( const CSqlConnectorSetting& right )
{
    CopyFrom( right );
    return *this;
}

///
/// \brief Sets host name for connection. For local connection is name "localhost".
/// \param hostName Host name for connection.
///
void CSqlConnectorSetting::SetHostName( QString hostName )
{
    m_HostName = hostName;
}

///
/// \brief Returns host name for connection.
/// \return Host name for connection.
///
QString CSqlConnectorSetting::GetHostName() const
{
    return m_HostName;
}

///
/// \brief Sets database name.
/// \param dbName Database name.
///
void CSqlConnectorSetting::SetDatabaseName( QString dbName )
{
    m_DatabaseName = dbName;
}

///
/// \brief Returns database name
/// \return Database name.
///
QString CSqlConnectorSetting::GetDatabaseName() const
{
    return m_DatabaseName;
}


///
/// \brief Sets user name for database connection.
/// \param user User name for database connection.
///
void CSqlConnectorSetting::SetUserName( QString user )
{
    m_UserName = user;
}

///
/// \brief Returns user name for database connection.
/// \return User name or database connection.
///
QString CSqlConnectorSetting::GetUserName() const
{
    return m_UserName;
}

///
/// \brief Sets password for database connection.
/// \param pswd Password for database connection.
///
void CSqlConnectorSetting::SetPassword( QString pswd )
{
    m_Password = pswd;
}

///
/// \brief Returns password for database connection.
/// \return Password for database connection.
///
QString CSqlConnectorSetting::GetPassword() const
{
    return m_Password;
}

///
/// \brief Sets size limit of database.
/// \param size Size limit.
///
void CSqlConnectorSetting::SetSizeLimit( unsigned int size )
{
    if( size < 10 * 1024 )
    {
        m_SizeLimit = 10*1024;
    }
    else
    {
        m_SizeLimit = size;
    }
}

///
/// \brief Sets using of size limit of database.
/// \param use True or false for using.
///
void CSqlConnectorSetting::UseSizeLimit( bool use )
{
    m_UseSizeLimit = use;
}

///
/// \brief Returns true if size limit is used.
/// \return True if size limit is used.
///
bool CSqlConnectorSetting::IsSizeLimitUsed() const
{
    return m_UseSizeLimit;
}

///
/// \brief Returns size limit of database.
/// \return Size limit of database.
///
unsigned int CSqlConnectorSetting::GetSizeLimit() const
{
    return m_SizeLimit;
}

///
/// \brief Constructor
/// \param setting Connection setting.
///
CSqlConnector::CSqlConnector( QString connectionName, CSqlConnectorSetting setting, QObject *parent ):
    QThread( parent ),
    m_ThreadRunning( true ),
    m_ConnectionName( connectionName ),
    m_ConnectionState( -1 ), // unknown state
    m_BusyState( -1 ),
    m_Setting( setting )
{
}

///
/// \brief Destructor
///
CSqlConnector::~CSqlConnector()
{
    disconnect();
    m_QueryLock.lock();
    while( !m_Queries.isEmpty() )
    {
        delete m_Queries.dequeue();
    }
    m_ThreadRunning = false;
    m_QueryCond.wakeAll();
    m_QueryLock.unlock();
    wait();
    QSqlDatabase::removeDatabase( m_ConnectionName );
}

///
/// \brief Initialize database connection.
///
void CSqlConnector::Init()
{
    start();
}

///
/// \brief Check connection to database. Returns existing connection or create new connection if not exist.
/// \param retDb Returned connection.
/// \return True when is openned.
///
bool CSqlConnector::CheckOpen( QSqlDatabase& retDb )
{
    bool openned = false;

    // Get connection.
    QSqlDatabase db;
    if( !QSqlDatabase::contains( m_ConnectionName ) )
    {
        db = QSqlDatabase::addDatabase( "QMYSQL", m_ConnectionName );
    }
    else
    {
        db = QSqlDatabase::database( m_ConnectionName );
    }

    if( db.isValid() )
    {
        QSqlQuery testQuery( db );
        retDb = db;
        if( testQuery.exec( "SELECT DATABASE();" ) )
        {
            if( testQuery.first() )
            {
                if( testQuery.value( 0 ).toString() == QString( m_Setting.GetDatabaseName() ) )
                {
                    openned = true;
                }
            }
        }

    }
    // Open new connection.
    if( !openned )
    {
        db.setHostName( m_Setting.GetHostName() );
        db.setDatabaseName( m_Setting.GetDatabaseName() );
        db.setUserName( m_Setting.GetUserName() );
        db.setPassword( m_Setting.GetPassword() );
        db.open();

        retDb = db;
        QSqlQuery testQuery( db );
        openned = testQuery.exec( "SELECT 1;" );

    }

    return openned;
}

///
/// \brief Thread run function - sends queries to DB.
///
void CSqlConnector::run()
{
    QSqlDatabase db;
    bool isOpen = false;
    bool emitBusy = false;

    while( m_ThreadRunning )
    {
        m_QueryLock.lock();
        CDatabaseQuery* query = nullptr;

        // Queue is empty - wait max 5 second.
        if( m_Queries.isEmpty() || ( !isOpen ) )
        {
            m_QueryCond.wait( &m_QueryLock, 5000 );
        }

        // Check connection do DB.
        isOpen = CheckOpen( db );

        // Check connection
        if( isOpen )
        {
            // Get query from queue.
            if( !m_Queries.isEmpty() )
            {
                query = m_Queries.dequeue();
            }
        }

        m_QueryLock.unlock();

        // Do query
        if( query != nullptr )
        {
            QSqlQuery sqlQuery( db );
            bool queryOk = query->DoWork( sqlQuery );
            query->SetError( sqlQuery.lastError() );
            QueryProcessed( queryOk, query );
            delete query;

            // Change busy state
            if( m_BusyState != 0 )
            {
                m_BusyState = 0;
                emitBusy = true;
            }
        }
        else if( !isOpen )
        {
            sleep( 1 );
        }

        // Emit database connection change
        if( m_ConnectionState != static_cast<int>( isOpen ) )
        {
            emit connectionStateChange( isOpen );
            m_ConnectionState = static_cast<int>( isOpen );
        }

        // Emit busy state change.
        if( emitBusy )
        {
            emit busyStateChange( false );
            emitBusy = false;
        }
    }
}


///
/// \brief Add query to queue.
/// \param query New query.
///
bool CSqlConnector::AddQuery( CDatabaseQuery* query )
{
    bool retVal = false;
    bool emitBusy = false;

    m_QueryLock.lock();
    if( query != nullptr )
    {
        if( m_Queries.size() < MaxQueryQueueSize )
        {
            m_Queries.enqueue( query );
            retVal = true;
        }
        else
        {
            qDebug() << "CSqlConnector::AddQuery - Queue is FULL! Query will be lost!";
            delete query;

            // Change busy state
            if( m_BusyState != 1 )
            {
                emitBusy = true;
                m_BusyState = 1;;
            }
        }

        m_QueryCond.wakeAll();
    }
    m_QueryLock.unlock();

    // Emit busy state change.
    if( emitBusy )
    {
        emit busyStateChange( true );
    }
    return retVal;
}


