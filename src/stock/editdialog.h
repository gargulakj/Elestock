#ifndef CSTOCKITEMDIALOG_H
#define CSTOCKITEMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>
#include "item.h"

///
/// \brief Dialog for stock item editation.
///
class CStockItemEditDialog : public QDialog
{
Q_OBJECT
private:
    // Line editboxes for data editing.
    QLineEdit* m_EditId;
    QLineEdit* m_EditSuplSymbol;
    QLineEdit* m_EditProducerSymbol;
    QLineEdit* m_EditDescription;
    QLineEdit* m_EditPrice;
    QLineEdit* m_EditQuantity;
    QLineEdit* m_EditNewSupplier;
    // Combo for supplier editing.
    QComboBox* m_ComboSupplier;
    // Buttons
    QPushButton* m_BtnAdd;
    QPushButton* m_BtnEdit;
    QPushButton* m_BtnSuplAdd;
    QPushButton* m_BtnSuplRem;

    // Creates dialog.
    void create();

    // Creates horizontal layout with label and edit box.
    QHBoxLayout* createLineEdit( QString lbText, QLineEdit** lineEditPtr );
    // Create horinzontal layout with label and combo box
    QHBoxLayout* createCombo( QString lbText, QComboBox** combo, bool editable );
    // Fill dialog with data from item.
    void itemToDialog( const CItem& item );
    // Gets data from dialog to item object.
    void itemFromDialog( CItem& item );

public:
    // Constructor
    CStockItemEditDialog( QWidget *parent );
    // Destructor
    ~CStockItemEditDialog();
    // Synchonous function for editing item on dialog.
    int exec( CItem& item );

private slots:
    // Emits supplierAddClicked signal with supplier name.
    void supplierAdd();
    // Emits supplierRemClicked signal with supplier id.
    void supplierRem();
public slots:
    // Fill combobox of supplier.
    void setSupplierList( QMap<int,QString> supplierList );

signals:
    // Is emitted when user want add new supplier.
    void supplierAddClicked( QString supplierName );
    // Is emitted when user want to delete supplier.
    void supplierRemClicked( int supplierId );
};

#endif // CSTOCKITEMDIALOG_H
