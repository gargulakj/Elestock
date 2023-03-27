#ifndef CSUPPLIERDB_H
#define CSUPPLIERDB_H

#include "sql/dbservice.h"

///
/// \brief Implementation of adding supplier to database.
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
/// \brief Implementation of getting suppliers from database.
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
/// \brief Implementation of removing supplier from database.
///
class CRemSupplierQuery : public CDatabaseQuery
{
private:
    int m_SupplierId;
public:
    ///
    /// \brief Constructor
    ///
    CRemSupplierQuery( int id ) :
        CDatabaseQuery( static_cast<int>( EStockDbQuery::RemSupplier ) ),
        m_SupplierId( id )
    {}
    // DoWork implementation of removing supplier.
    bool DoWork( QSqlQuery& query ) override;

};

///
/// \brief Database servis of suppliers.
///
class CSupplierDb : public CDbService
{
    Q_OBJECT
private:
    //! Overrided function of result processing.
    void QueryProcessed( bool result, CDatabaseQuery* query ) override;

public:
    // Constructor
    CSupplierDb( CSqlConnectorSetting stt, QObject *parent = nullptr );
    // Adds query for supplier adding.
    void AddSupplier( QString supplierName );
    // Adds query for supplier getting.
    void GetSupplier();
    // Adds query for supplier removing.
    void RemSupplier( int supplierId );

signals:
    // Is emitted when list of suppliers was readed.
    void suppliersReady( QMap<int,QString> supplierList );
};

#endif // CSUPPLIERDB_H
