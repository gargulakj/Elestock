#ifndef CSTOCKITEMDIALOG_H
#define CSTOCKITEMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>

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
    QLineEdit* m_EditProductionSymbol;
    QLineEdit* m_EditDescription;
    QLineEdit* m_EditPrice;
    QLineEdit* m_EditQuantity;
    // Combo for supplier editing.
    QComboBox* m_ComboSupplier;
    // Buttons
    QPushButton* m_BtnAdd;
    QPushButton* m_BtnEdit;

    // Creates dialog.
    void create();

    // Creates horizontal layout with label and edit box.
    QHBoxLayout* createLineEdit( QString lbText, QLineEdit** lineEditPtr );
    // Create horinzontal layout with label and combo box
    QHBoxLayout* createCombo( QString lbText, QComboBox** combo, bool editable );

public:
    // Constructor
    CStockItemEditDialog( QWidget *parent );
    // Destructor
    ~CStockItemEditDialog();

    QString getSupplier( unsigned int selection );

public slots:
    // Fill combobox of supplier.
    void setSupplierList( QMap<int,QString> supplierList );
};

#endif // CSTOCKITEMDIALOG_H
