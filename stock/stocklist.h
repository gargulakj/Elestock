#ifndef CSTOCKLIST_H
#define CSTOCKLIST_H

#include <QVBoxLayout>
#include <QPushButton>
#include "stock/editdialog.h"
#include "sql/dbservice.h"

class CStockList : public QVBoxLayout
{
    Q_OBJECT
private:
    // DB service
    CDbService* m_DbService;
    // Dialog for item editing or adding.
    CStockItemEditDialog* m_EditDialog;
    // Creates gui components
    void create();
private slots:
    // Show dialog for item adding.
    void showDialog_AddItem();
public:
    // Constructor
    explicit CStockList( CDbService* dbService, QWidget *parent = nullptr);

signals:

};

#endif // CSTOCKLIST_H
