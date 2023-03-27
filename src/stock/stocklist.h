#ifndef CSTOCKLIST_H
#define CSTOCKLIST_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QTableView>
#include "editdialog.h"
#include "itemmodel.h"
#include "supplierdb.h"

class CStockList : public QVBoxLayout
{
    Q_OBJECT
private:
    // Table model of items.
    CItemModel* m_ItemModel;
    // Database service of items.
    CItemDb* m_DbItems;
    // Database service of suppliers.
    CSupplierDb* m_DbSupplier;
    // Dialog for item editing or adding.
    CStockItemEditDialog* m_EditDialog;
    // Creates gui components
    void create();
private slots:
    // Show dialog for item adding.
    void showDialog_AddItem();
    // Add supplier
    void addSupplier( QString supplierName );
    // Remove supplier with id.
    void removeSupplier( int supplierId );
public:
    // Constructor
    explicit CStockList( CItemDb* dbItem, CSupplierDb* dbSupplier, QWidget *parent = nullptr);

signals:

};

#endif // CSTOCKLIST_H
