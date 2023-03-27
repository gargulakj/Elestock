#include "supplierdb.h"

///
/// \brief DoWork implementation of adding supplier.
/// \param query Reference to sqlQuery instance. After execution it contains result.
/// \return
///
bool CAddSupplierQuery::DoWork( QSqlQuery& query )
{
    bool retVal = true;

    query.prepare(  "INSERT INTO TabSupplier (Name) "
                    "VALUES (:name); " );
    query.bindValue( ":name", m_SupplierName );

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
/// \brief DoWork implementation of removing supplier.
/// \param query Reference to sqlQuery instance. After execution it contains result.
/// \return
///
bool CRemSupplierQuery::DoWork( QSqlQuery& query )
{
    bool retVal = true;

    query.prepare(  "DELETE FROM TabSupplier "
                    "WHERE ID=(:id); " );
    query.bindValue( ":id", m_SupplierId );

    retVal = query.exec();

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
/// \brief Constructor
///
CSupplierDb::CSupplierDb( CSqlConnectorSetting stt, QObject *parent ) :
    CDbService( "SupplierDB", stt, parent )
{
}

///
/// \brief Overrided function of result processing.
/// \param result Result of processing.
/// \param query Requested query
///
void CSupplierDb::QueryProcessed( bool result, CDatabaseQuery* query )
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
            emit queryFailed( query->GetError().text() );
        }
    }
}

///
/// \brief Adds query for supplier adding.
/// \param supplierName Supplier name.
///
void CSupplierDb::AddSupplier( QString supplierName )
{
    AddQuery( new CAddSupplierQuery( supplierName ) );
}

///
/// \brief Adds query for supplier getting.
///
void CSupplierDb::GetSupplier()
{
    AddQuery( new CGetSuppliersQuery() );
}

///
/// \brief Adds query for supplier removing.
/// \param supplierId Supplier ID.
///
void CSupplierDb::RemSupplier( int supplierId )
{
    AddQuery( new CRemSupplierQuery( supplierId ) );
}
