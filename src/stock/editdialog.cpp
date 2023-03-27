#include "editdialog.h"

///
/// \brief Constructor
/// \param parent Parent widget
///
CStockItemEditDialog::CStockItemEditDialog( QWidget *parent ) :
    QDialog( parent ),
    m_EditId( nullptr ),
    m_EditSuplSymbol( nullptr ),
    m_EditProducerSymbol( nullptr ),
    m_EditDescription( nullptr ),
    m_EditPrice( nullptr ),
    m_EditQuantity( nullptr ),
    m_EditNewSupplier( nullptr ),
    m_ComboSupplier( nullptr ),
    m_BtnAdd( nullptr ),
    m_BtnEdit( nullptr ),
    m_BtnSuplAdd( nullptr ),
    m_BtnSuplRem( nullptr )
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
/// \brief Fill dialog with data from item.
/// \param item Item to edit.
///
void CStockItemEditDialog::itemToDialog( const CItem& item )
{
    if( m_EditId != nullptr )
    {
        m_EditId->setText( QString::number( item.getId() ) );
    }
    if( m_EditSuplSymbol != nullptr )
    {
        m_EditSuplSymbol->setText( item.getSymbolSupplier() );
    }
    if( m_EditProducerSymbol != nullptr )
    {
        m_EditProducerSymbol->setText( item.getSymbolProducer() );
    }
    if( m_EditDescription != nullptr )
    {
        m_EditDescription->setText( item.getDescription() );
    }
    if( m_EditPrice != nullptr )
    {
        m_EditPrice->setText( QString::number( item.getPrice() ) );
    }
    if( m_EditQuantity != nullptr )
    {
        m_EditQuantity->setText( QString::number( item.getQuantity() ) );
    }
    if( m_ComboSupplier != nullptr )
    {
        m_ComboSupplier->setCurrentIndex( item.getSupplierId() );
    }
}

///
/// \brief Gets data from dialog to item object.
/// \param item Item
///
void CStockItemEditDialog::itemFromDialog( CItem& item )
{
    if( m_EditSuplSymbol != nullptr )
    {
        item.setSymbolSuplier( m_EditSuplSymbol->text() );
    }
    if( m_EditProducerSymbol != nullptr )
    {
        item.setSymbolProducer( m_EditProducerSymbol->text() );
    }
    if( m_EditDescription != nullptr )
    {
        item.setDescription( m_EditDescription->text() );
    }
    if( m_EditPrice != nullptr )
    {
        bool convertOk = false;
        unsigned int price = m_EditPrice->text().toUInt( &convertOk );
        if( convertOk )
        {
            item.setPrice( price );
        }
    }
    if( m_EditQuantity != nullptr )
    {
        bool convertOk = false;
        unsigned int quantity = m_EditQuantity->text().toUInt( &convertOk );
        if( convertOk )
        {
            item.setQuantity( quantity );
        }
    }
    if( m_ComboSupplier != nullptr )
    {
        int supplier = m_ComboSupplier->currentData().toInt();
        item.setSupplierId( supplier );

    }
}
///
/// \brief Synchonous function for editing item on dialog.
/// \param item Stock item for editing.
/// \return Return QDialog::DialogCode (Accepted 1 / Rejected 0)
///
int CStockItemEditDialog::exec( CItem& item )
{

    itemToDialog( item );
    int retVal = QDialog::exec();
    itemFromDialog( item );

    return retVal;

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
        lb->setMinimumWidth( 110 );
        (*lineEditPtr) = new QLineEdit;
        (*lineEditPtr)->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed ) );
        (*lineEditPtr)->setMinimumHeight( 22 );
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
        lb->setMinimumWidth( 110 );
        (*combo) = new QComboBox;
        (*combo)->setEditable( editable );
        (*combo)->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed ) );
        (*combo)->setMinimumHeight( 22 );
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

    lineLayout = createLineEdit( tr("Manufacturer's label"), &m_EditProducerSymbol );
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

    // Create combo box of suppliers.
    lineLayout = createCombo( tr("Supplier"), &m_ComboSupplier, false );
    if( lineLayout != nullptr )
    {
        // Button for supplier remove.
        m_BtnSuplRem = new QPushButton;
        m_BtnSuplRem->setText("-");
        lineLayout->addWidget( m_BtnSuplRem );
        m_BtnSuplRem->setMaximumWidth( 25 );

        mainLayout->addLayout( lineLayout );

    }

    // Line with edit and button for add supplier
    lineLayout = createLineEdit( "", &m_EditNewSupplier );
    if( lineLayout != nullptr )
    {
        // Button for supplier add
        m_BtnSuplAdd = new QPushButton;
        m_BtnSuplAdd->setText("+");
        m_BtnSuplAdd->setMaximumWidth( 25 );
        lineLayout->addWidget( m_BtnSuplAdd );

        mainLayout->addLayout( lineLayout );
    }

    // Confirmation of dialog
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

    setMinimumSize( 200, 250 );
    setLayout( mainLayout );

    // Signal connection
    connect( m_BtnAdd, SIGNAL( clicked(bool) ), this, SLOT( accept() ) );
    connect( m_BtnEdit, SIGNAL( clicked(bool) ), this, SLOT( accept() ) );
    connect( m_BtnSuplAdd, SIGNAL( clicked(bool) ), this, SLOT( supplierAdd() ) );
    connect( m_BtnSuplRem, SIGNAL( clicked(bool) ), this, SLOT( supplierRem() ) );


}

///
/// \brief Emits supplierAddClicked signal with supplier name.
///
void CStockItemEditDialog::supplierAdd()
{
    if( m_EditNewSupplier != nullptr )
    {
        emit supplierAddClicked( m_EditNewSupplier->text() );
    }
}

///
/// \brief Emits supplierRemClicked signal with supplier id.
///
void CStockItemEditDialog::supplierRem()
{
    if( m_ComboSupplier != nullptr )
    {
        bool convertOk = false;
        int supplierId =  m_ComboSupplier->currentData().toInt( &convertOk );
        if( convertOk )
        {
            emit supplierRemClicked( supplierId );
        }
    }
}

///
/// \brief Fill combobox of supplier.
/// \param supplierList Data from database
///
void CStockItemEditDialog::setSupplierList( QMap<int,QString> supplierList )
{
    if( m_ComboSupplier != nullptr )
    {
        // Get count before clear.
        int curCount = m_ComboSupplier->count();
        m_ComboSupplier->clear();

        // Fill item from database.
        QList<int> keys = supplierList.keys();
        for( int i = 0; i < keys.size(); i++ )
        {
            int key = keys.at(i);
            m_ComboSupplier->addItem( supplierList[key], key );
        }

        // New supplier was added?
        if( (curCount > 0) && (curCount != supplierList.size() ) )
        {
            if( m_ComboSupplier->count() > 0 )
            {
                m_ComboSupplier->setCurrentIndex( m_ComboSupplier->count() - 1);
            }
        }
    }
}
/*
///
/// \brief Returns information about new supplier.
/// \return Information about new supplier.
///
QString CStockItemEditDialog::getNewSupplierInfo()
{
    QString supplierName = "";
    if( m_EditNewSupplier != nullptr )
    {
        supplierName = m_EditNewSupplier->text();
    }
    return supplierName;
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
}*/
