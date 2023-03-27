#include "itemdb.h"

///
/// \brief Implementation of adding item to database.
/// \param query Reference to sqlQuery instance. After execution it contains result.
/// \return
///
bool CAddItemQuery::DoWork( QSqlQuery& query )
{
    bool retVal = true;

    query.prepare(  "INSERT INTO TabStock "
                    "( SymbolSupplier, SymbolProducer, Description, Price, Quantity, Supplier ) "
                    "VALUES (?, ?, ?, ?, ?, ?); " );

    query.bindValue( 0, m_Item.getSymbolSupplier() );
    query.bindValue( 1, m_Item.getSymbolProducer() );
    query.bindValue( 2, m_Item.getDescription() );
    query.bindValue( 3, m_Item.getPrice() );
    query.bindValue( 4, m_Item.getQuantity() );
    query.bindValue( 5, m_Item.getSupplierId() );

    retVal = query.exec();

    return retVal;
}

///
/// \brief Implementation of getting items from database.
/// \param query Reference to sqlQuery instance. After execution it contains result.
/// \return True if query was succeed.
///
bool CGetItemQuery::DoWork( QSqlQuery& query )
{
    bool retVal = false;

    query.prepare( "SELECT TabSupplier.ID, SymbolSupplier, SymbolProducer, Description, Price, Quantity, TabStock.Supplier, TabSupplier.Name "
                   "FROM TabStock "
                   "LEFT JOIN TabSupplier ON TabStock.Supplier = TabSupplier.ID" );

    if( query.exec() )
    {
        retVal = true;
        if( m_Result != nullptr )
        {
            m_Result->clear();

            while ( query.next() )
            {
                bool convertOk = false;
                int id = query.value(0).toInt( &convertOk );
                if( convertOk )
                {
                    CItem* item = new CItem();
                    if( item != nullptr )
                    {
                        item->setId( id );
                        item->setSymbolSuplier( query.value(1).toString() );
                        item->setSymbolProducer( query.value(2).toString() );
                        item->setDescription( query.value(3).toString() );
                        item->setPrice( query.value(4).toUInt() );
                        item->setQuantity( query.value(5).toUInt() );
                        item->setSupplierId( query.value(6).toInt() );
                        item->setSupplierName( query.value(7).toString() );
                    }
                    m_Result->append( item );
                }
            }
        }
    }


    return retVal;
}

///
/// \brief Constructor of database servise of stock items.
/// \param stt SQL connection setting.
/// \param parent
///
CItemDb::CItemDb( CSqlConnectorSetting stt, QObject *parent ) :
    CDbService( "ItemDB", stt, parent )
{

}

///
/// \brief Destructor
///
CItemDb::~CItemDb()
{
}

///
/// \brief Overrided function of result processing.
/// \param result Result of processing.
/// \param query Requested query
///
void CItemDb::QueryProcessed( bool result, CDatabaseQuery* query )
{
    if( query != nullptr )
    {
        EStockDbQuery queryType = static_cast<EStockDbQuery>( query->GetType() );
        switch( queryType )
        {
        case EStockDbQuery::GetItems:
            if( result )
            {
                emit queryGetFinished();
            }
            else
            {
                emit queryGetFailed();
            }
        break;
        default:
        break;
        }
    }
}

///
/// \brief Adds query for item adding.
/// \param item Item for add.
///
void CItemDb::queryAdd( const CItem& item )
{
    AddQuery( new CAddItemQuery( item ) );
}

///
/// \brief Add query for item getting.
/// \param resultList Pointer to list where result of query will be stored.
///
void CItemDb::queryGet( QList<CItem*>* resultList )
{
    AddQuery( new CGetItemQuery( resultList ) );
}

