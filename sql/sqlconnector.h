#ifndef CSQLCONNECTOR_H
#define CSQLCONNECTOR_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
#include <atomic>


///
/// \brief Base class of database query.
///
class CDatabaseQuery
{
private:
    //! Query type.
    int m_Type;
    //! Error of processing.
    QSqlError m_Error;
public:
    ///
    /// \brief Constructor
    /// \param Query type.
    ///
    CDatabaseQuery( int type ) :
        m_Type( type )
    {}
    ///
    /// \brief Virtual destructor
    ///
    virtual ~CDatabaseQuery() {}

    ///
    /// \brief Virtual do work. Is implemented by query.
    /// \param query Reference to query instance. Query will be prepared and executed in doWork function. After execution it contains result.
    /// \retval Return true when query was succesful.
    ///
    virtual bool DoWork( QSqlQuery& query ) = 0;

    ///
    /// \brief Returns type of query.
    /// \return Type of query.
    ///
    int GetType() const
    {
        return m_Type;
    }

    ///
    /// \brief Set error of processing.
    /// \param err Error.
    ///
    void SetError( QSqlError err )
    {
        m_Error = err;
    }

    ///
    /// \brief Returns error of processing.
    /// \return Error of processing.
    ///
    QSqlError GetError() const
    {
        return m_Error;
    }

};


///
/// \brief Setting of connection do database.
///
class CSqlConnectorSetting
{
private:
    //! Host name.
    QString m_HostName;
    //! Database name.
    QString m_DatabaseName;
    //! User for log in.
    QString m_UserName;
    //! User password.
    QString m_Password;
    //! Limit of database size.
    unsigned int m_SizeLimit;
    //! Flag of using size limit size of database.
    bool m_UseSizeLimit;
    //! Copy data from another instance.
    void CopyFrom( const CSqlConnectorSetting& copyFrom );
public:
    //! Constructor
    CSqlConnectorSetting();
    //! Copy constructor.
    CSqlConnectorSetting( const CSqlConnectorSetting& copyFrom );
    //! Operator = overload
    CSqlConnectorSetting& operator= ( const CSqlConnectorSetting& right );
    //! Sets host name for connection. For local connection is name "localhost".
    void SetHostName( QString hostName );
    //! Returns host name for connection.
    QString GetHostName() const;
    //! Sets database name.
    void SetDatabaseName( QString dbName );
    //! Returns database name
    QString GetDatabaseName() const;
    //! Sets user name for database connection.
    void SetUserName( QString user );
    //! Returns user name for database connection.
    QString GetUserName() const;
    //! Sets password for database connection.
    void SetPassword( QString pswd );
    //! Returns password for database connection.
    QString GetPassword() const;
    //! Sets size limit of database.
    void SetSizeLimit( unsigned int size );
    //! Sets using of size limit of database.
    void UseSizeLimit( bool use );
    //! Returns true if size limit is used.
    bool IsSizeLimitUsed() const;
    //! Returns size limit of database.
    unsigned int GetSizeLimit() const;
    //! Returns true if this and other setting are equal.
    bool IsEqual( const CSqlConnectorSetting& other );
};

///
/// \brief Base class for communication with database.
///
class CSqlConnector : public QThread
{
    Q_OBJECT
private:
    //! Static mutex for lock multiple access to mysql server.
    static QMutex m_ServerLock;
    //! Mutex for condition QueryCond.
    mutable QMutex m_QueryLock;
    //! Wait/condition of query control.
    QWaitCondition m_QueryCond;
    //! List of pending queries to DB.
    QQueue<CDatabaseQuery*> m_Queries;
    //! Thread running.
    std::atomic<bool>m_ThreadRunning;
    //! Name of sql connection.
    QString m_ConnectionName;
    //! Connection state.
    int m_ConnectionState;
    //! Busy state
    int m_BusyState;
    //! Check connection to database. Returns existing connection or create new connection if not exist.
    bool CheckOpen( QSqlDatabase& retDb );
    //! Thread run function - sends queries to DB.
    void run() override;
public:
    //! Constructor
    explicit CSqlConnector( QString connectionName, CSqlConnectorSetting setting, QObject *parent = 0 );
    //! Destructor
    ~CSqlConnector();

    //! Initialize database connection.
    void Init();

protected:
    //! Connectin setting.
    CSqlConnectorSetting m_Setting;

    //! Add query to queue.
    bool AddQuery( CDatabaseQuery* query );
    //! Virtual function of result processing. Override this for get result from query.
    virtual void QueryProcessed( bool result, CDatabaseQuery* query )
    {
        Q_UNUSED( result )
        Q_UNUSED( query )
    }
signals:
    //! Is emitted when connection to database was changed.
    void connectionStateChange( bool state );
    //! Is emitted when busy state was changed.
    void busyStateChange( bool state );

};

#endif // CSQLCONNECTOR
