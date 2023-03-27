#ifndef CSTOCKDB_H
#define CSTOCKDB_H

#include <QObject>
#include <QMap>
#include "sql/sqlconnector.h"
#include "stock/item.h"

///
/// \brief Query on stock database.
///
enum class EStockDbQuery : char
{
    CreateTables,
    AddSupplier,
    GetSuppliers,
    RemSupplier,
    AddItem,
    GetItems
};

///
/// \brief Implementation of creation tables .
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
/// \brief Stock database servis.
///
class CDbService : public CSqlConnector
{
    Q_OBJECT
public:
    // Construtor of stock database service
    explicit CDbService( QString connectionName, CSqlConnectorSetting stt, QObject *parent = nullptr );
    // Destructor
    ~CDbService();

signals:
    // Is emitted when supplier adding was failed.
    void queryFailed( QString errorText );


};

#endif // CSTOCKDB_H
