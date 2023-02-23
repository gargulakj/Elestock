#include "editdialog.h"

///
/// \brief Constructor
/// \param parent Parent widget
///
CStockItemEditDialog::CStockItemEditDialog( QWidget *parent ) :
    QDialog( parent ),
    m_EditId( nullptr ),
    m_EditSuplSymbol( nullptr ),
    m_EditProductionSymbol( nullptr ),
    m_EditDescription( nullptr ),
    m_EditPrice( nullptr ),
    m_EditQuantity( nullptr ),
    m_ComboSupplier( nullptr ),
    m_BtnAdd( nullptr ),
    m_BtnEdit( nullptr )
{
    create();
}

///
/// \brief Destructor
///
CStockItemEditDialog::~CStockItemEditDialog()
{
}

///
/// \brief Creates horizontal layout with label and edit box.
/// \param lbText Text to label.
/// \param lineEditPtr Pointer to poiter to edit box.
/// \return Horizontal layout with label and edit box.
///
QHBoxLayout* CStockItemEditDialog::createLineEdit( QString lbText, QLineEdit** lineEditPtr )
{
    QHBoxLayout* lineLayout = new QHBoxLayout;
    if( lineEditPtr != nullptr )
    {
        QLabel* lb = new QLabel;
        lb->setText( lbText );
        (*lineEditPtr) = new QLineEdit;
        lb->setBuddy( *lineEditPtr );
        lineLayout->addWidget( lb );
        lineLayout->addWidget( *lineEditPtr );
    }
    return lineLayout;
}

///
/// \brief Create horinzontal layout with label and combo box
/// \param lbText Text to label.
/// \param combo Pointer to pointer to combox.
/// \param editable True if text in combo can be editable.
/// \return Horizontal layout with label and combo box.
///
QHBoxLayout* CStockItemEditDialog::createCombo( QString lbText, QComboBox** combo, bool editable )
{
    QHBoxLayout* lineLayout = new QHBoxLayout;
    if( combo != nullptr )
    {
        QLabel* lb = new QLabel;
        lb->setText( lbText );
        (*combo) = new QComboBox;
        (*combo)->setEditable( editable );
        lb->setBuddy( *combo );
        lineLayout->addWidget( lb );
        lineLayout->addWidget( *combo );
    }
    return lineLayout;
}
///
/// \brief Creates dialog.
///
void CStockItemEditDialog::create()
{

    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* lineLayout = nullptr;

    lineLayout = createLineEdit( tr("ID"), &m_EditId );
    if( lineLayout != nullptr )
    {
        mainLayout->addLayout( lineLayout );
    }

    lineLayout = createLineEdit( tr("Supplier's label"), &m_EditSuplSymbol );
    if( lineLayout != nullptr )
    {
        mainLayout->addLayout( lineLayout );
    }

    lineLayout = createLineEdit( tr("Manufacturer's label"), &m_EditProductionSymbol );
    if( lineLayout != nullptr )
    {
        mainLayout->addLayout( lineLayout );
    }

    lineLayout = createLineEdit( tr("Description"), &m_EditDescription );
    if( lineLayout != nullptr )
    {
        mainLayout->addLayout( lineLayout );
    }

    lineLayout = createLineEdit( tr("Price"), &m_EditPrice );
    if( lineLayout != nullptr )
    {
        mainLayout->addLayout( lineLayout );
    }

    lineLayout = createLineEdit( tr("Quantity"), &m_EditQuantity );
    if( lineLayout != nullptr )
    {
        mainLayout->addLayout( lineLayout );
    }

    lineLayout = createCombo( tr("Supplier"), &m_ComboSupplier, false );
    if( lineLayout != nullptr )
    {
        mainLayout->addLayout( lineLayout );
    }

    lineLayout = new QHBoxLayout;

    // Add button
    m_BtnAdd = new QPushButton;
    m_BtnAdd->setText( "Add" );;
    lineLayout->addWidget( m_BtnAdd );
    // Edit button
    m_BtnEdit = new QPushButton;
    m_BtnEdit->setText( "OK" );
    lineLayout->addWidget( m_BtnEdit );

    mainLayout->addLayout( lineLayout );

    connect( m_BtnAdd, SIGNAL(pressed()), this, SLOT( accept() ) );
    connect( m_BtnEdit, SIGNAL(pressed()), this, SLOT( accept() ) );

    setMinimumSize( 200, 250 );
    setLayout( mainLayout );


}

///
/// \brief Fill combobox of supplier.
/// \param supplierList Data from database
///
void CStockItemEditDialog::setSupplierList( QMap<int,QString> supplierList )
{
    if( m_ComboSupplier != nullptr )
    {
        QList<int> keys = supplierList.keys();
        for( int i = 0; i < keys.size(); i++ )
        {
            int key = keys.at(i);
            m_ComboSupplier->addItem( supplierList[key], key );
        }
    }
}

QString CStockItemEditDialog::getSupplier( unsigned int selection )
{
    QString supplierName;
    if( m_ComboSupplier != nullptr )
    {
        supplierName = m_ComboSupplier->currentText();
    }
    qDebug() << m_ComboSupplier->currentData() << " " << m_ComboSupplier->currentIndex();
    return supplierName;
}
