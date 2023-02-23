#ifndef CSTOCKDB_H
#define CSTOCKDB_H

#include <QObject>
#include <QMap>
#include "sql/sqlconnector.h"

///
/// \brief Query on stock database.
///
enum class EStockDbQuery : char
{
    CreateTables,
    AddSupplier,
    GetSuppliers
};

///
/// \brief Creation tables implementation.
///
class CCreateTablesQuery : public CDatabaseQuery
{
private:
public:
    ///
    /// \brief Constructor
    ///
    CCreateTablesQuery() :
        CDatabaseQuery( static_cast<int>( EStockDbQuery::CreateTables ) )
    {}
    // DoWork implementation of table creation.
    bool DoWork( QSqlQuery& query ) override;

};

///
/// \brief Adding supplier implementation.
///
class CAddSupplierQuery : public CDatabaseQuery
{
private:
    QString m_SupplierName;
public:
    ///
    /// \brief Constructor
    ///
    CAddSupplierQuery( QString name ) :
        CDatabaseQuery( static_cast<int>( EStockDbQuery::AddSupplier ) ),
        m_SupplierName( name )
    {}
    // DoWork implementation of adding supplier.
    bool DoWork( QSqlQuery& query ) override;

};

///
/// \brief Getting suppliers implementation.
///
class CGetSuppliersQuery : public CDatabaseQuery
{
private:
    // Maps of supplier names
    QMap<int,QString> m_Result;
public:
    ///
    /// \brief Constructor
    ///
    CGetSuppliersQuery() :
        CDatabaseQuery( static_cast<int>( EStockDbQuery::GetSuppliers ) )
    {}
    // DoWork implementation of getting supplier.
    bool DoWork( QSqlQuery& query ) override;
    // Returns result of query - data readed from database
    QMap<int,QString> GetResult();

};

///
/// \brief Stock database servis.
///
class CDbService : public CSqlConnector
{
    Q_OBJECT
private:
    //! Overrided function of result processing.
    void QueryProcessed( bool result, CDatabaseQuery* query ) override;
public:
    // Construtor of stock database service
    explicit CDbService( CSqlConnectorSetting stt, QObject *parent = nullptr );
    // Destructor
    ~CDbService();
    // Adds query for supplier adding.
    void AddSupplier( QString supplierName );
    // Adds query for supplier getting.
    void GetSupplier();


signals:
    // Is emitted when list of suppliers was readed.
    void suppliersReady( QMap<int,QString> supplierList );


};

#endif // CSTOCKDB_H
