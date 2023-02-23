#include "dbservice.h"

///
/// \brief DoWork implementation of table creation..
/// \param query Reference to sqlQuery instance. After execution it contains result.
///
bool CCreateTablesQuery::DoWork( QSqlQuery& query )
{
    bool retVal = true;

    QSqlQuery tabListQuery( query );
    tabListQuery.prepare( "SHOW TABLES;" );

    if( tabListQuery.exec() )
    {
        // Get list of existing tables.
        QStringList tableList;
        while( tabListQuery.next() )
        {
            tableList.append( tabListQuery.value( 0 ).toString() );
        }

        bool tableExist = false;

        // Create Suplier table
        if( !tableList.contains( "TabSupplier" ) )
        {
            QSqlQuery newTabQuery( query );
            newTabQuery.prepare( "CREATE TABLE TabSupplier ( "
                                 "ID int AUTO_INCREMENT, "
                                 "Name varchar(255) NOT NULL, "
                                 "PRIMARY KEY (ID)"
                                 ");" );

            if( !newTabQuery.exec() )
            {
                qDebug() << newTabQuery.lastError();
                tableExist = false;
            }
            else
            {
                tableExist = true;
            }
        }
        else
        {
            tableExist = true;
        }

        if( tableExist )
        {
            // Create Stock table
            if( !tableList.contains( "TabStock" ) )
            {
                QSqlQuery newTabQuery( query );
                newTabQuery.prepare( "CREATE TABLE TabStock ( "
                                     "ID int AUTO_INCREMENT, "
                                     "SymbolSupplier varchar(64), "
                                     "SymbolProducer varchar(64), "
                                     "Description varchar(64), "
                                     "Price int unsigned, "
                                     "Quantity int unsigned, "
                                     "Supplier int, "
                                     "PRIMARY KEY (ID), "
                                     "FOREIGN KEY (Supplier) REFERENCES TabSupplier(ID)"
                                     " );" );

                if( !newTabQuery.exec() )
                {
                    qDebug() << newTabQuery.lastError();
                    tableExist = false;
                }
            }
            else
            {
                tableExist = true;
            }
        }
    }
    else
    {
        retVal = false;
    }



    return retVal;
}

///
/// \brief DoWork implementation of adding supplier.
/// \param query Reference to sqlQuery instance. After execution it contains result.
/// \return
///
bool CAddSupplierQuery::DoWork( QSqlQuery& query )
{
    bool retVal = true;

    query.prepare(  "INSERT INTO TabSupplier (Name) "
                    "VALUES (?); " );
    query.bindValue( 0, m_SupplierName );

    retVal = query.exec();

    return retVal;
}

///
/// \brief DoWork implementation of getting supplier.
/// \param query Reference to sqlQuery instance. After execution it contains result.
/// \return
///
bool CGetSuppliersQuery::DoWork( QSqlQuery& query )
{
    bool retVal = true;
    m_Result.clear();
    query.prepare( "SELECT ID, Name FROM TabSupplier; " );

    retVal = query.exec();

    if( retVal )
    {
        while (query.next())
        {
            bool convertOk = false;
            int id = query.value(0).toInt( &convertOk );
            if( convertOk )
            {
                m_Result[id] = query.value(1).toString();
            }
        }
    }

    return retVal;
}

///
/// \brief Returns result of query - data readed from database
/// \return Result of query - data readed from database
///
QMap<int,QString> CGetSuppliersQuery::GetResult()
{
    return m_Result;
}

///
/// \brief Constructor of stock database service.
/// \param stt Setting for access to database.
/// \param parent
///
CDbService::CDbService( CSqlConnectorSetting stt, QObject *parent ):
    CSqlConnector( "DBStock", stt, parent )
{

    AddQuery( new CCreateTablesQuery() );

}

///
/// \brief Destructor
///
CDbService::~CDbService()
{
}

///
/// \brief Overrided function of result processing.
/// \param result Result of processing.
/// \param query Requested query
///
void CDbService::QueryProcessed( bool result, CDatabaseQuery* query )
{
    if( query != nullptr )
    {
        if( result )
        {
            switch( static_cast<EStockDbQuery>( query->GetType() ) )
            {
            // Gets list of suppliers.
            case EStockDbQuery::GetSuppliers:
            {
                CGetSuppliersQuery* sQuery = dynamic_cast<CGetSuppliersQuery*>(query);
                if( sQuery != nullptr )
                {
                    emit suppliersReady( sQuery->GetResult() );
                }
            }
            break;
            default:
            break;
            }
        }
        else
        {
            qDebug() << query->GetError().text();
        }
    }
}

///
/// \brief Adds query for supplier adding.
/// \param supplierName Supplier name.
///
void CDbService::AddSupplier( QString supplierName )
{
    AddQuery( new CAddSupplierQuery( supplierName ) );
}

///
/// \brief Adds query for supplier getting.
///
void CDbService::GetSupplier()
{
    AddQuery( new CGetSuppliersQuery() );
}

