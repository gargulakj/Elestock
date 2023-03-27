#ifndef CITEMDB_H
#define CITEMDB_H

#include "sql/dbservice.h"


///
/// \brief Implementation of adding item to database.
///
class CAddItemQuery : public CDatabaseQuery
{
private:
    CItem m_Item;
public:
    ///
    /// \brief Constructor
    ///
    CAddItemQuery( const CItem& item ) :
        CDatabaseQuery( static_cast<int>( EStockDbQuery::AddItem ) ),
        m_Item( item )
    {}
    // DoWork implementation of adding item.
    bool DoWork( QSqlQuery& query ) override;

};

class CItemDb;
///
/// \brief Implementation of getting items from database.
///
class CGetItemQuery : public CDatabaseQuery
{
private:
    // Pointer to list where will be stored result of query.
    QList<CItem*>* m_Result;
public:
    ///
    /// \brief Constructor
    ///
    CGetItemQuery( QList<CItem*>* resultList ) :
        CDatabaseQuery( static_cast<int>( EStockDbQuery::GetItems ) ),
        m_Result( resultList )
    {}
    // Implementation of getting items from database.
    bool DoWork( QSqlQuery& query ) override;

};

///
/// \brief Database service of stock item.
///
class CItemDb : public CDbService {
    Q_OBJECT
private:
    // Overrided function of result processing.
    void QueryProcessed( bool result, CDatabaseQuery* query ) override;
public:
    // Constructor of database servise of stock items.
    explicit CItemDb( CSqlConnectorSetting stt, QObject *parent = nullptr );
    // Destructor
    ~CItemDb();
    // Adds query for item adding.
    void queryAdd( const CItem& item );
    // Add query for item getting.
    void queryGet( QList<CItem*>* resultList );

signals:
    // Is emitted when items reading from database was finished.
    void queryGetFinished();
    // Is emitted when some errors occurs during query processing.
    void queryGetFailed();

};

#endif // CITEMDB_H
