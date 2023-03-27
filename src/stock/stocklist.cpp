#include "stocklist.h"

///
/// \brief Constructor
/// \param dbItem Database servise of items.
/// \param dbSupplier Database service of suppliers.
/// \param parent Parent widget
///
CStockList::CStockList( CItemDb* dbItem, CSupplierDb* dbSupplier, QWidget* parent ):
    QVBoxLayout{parent},
    m_ItemModel( nullptr ),
    m_DbItems( dbItem ),
    m_DbSupplier( dbSupplier ),
    m_EditDialog( nullptr )
{
    m_EditDialog = new CStockItemEditDialog( parent );
    if( m_DbItems != nullptr )
    {
        m_ItemModel = new CItemModel( *m_DbItems );
    }
    create();
}

///
/// \brief Creates gui components
///
void CStockList::create()
{    
    QTableView* tableView = new QTableView();
    addWidget( tableView );

    QPushButton* addBtn = new QPushButton();
    addBtn->setText( tr("Add Item") );
    addWidget( addBtn );
    connect( addBtn, SIGNAL( clicked(bool) ), this, SLOT( showDialog_AddItem() ) );

    if( m_ItemModel != nullptr )
    {
        tableView->setModel( m_ItemModel );
    }

    if( m_DbSupplier != nullptr )
    {
        connect( m_DbSupplier, SIGNAL( suppliersReady(QMap<int,QString>) ), m_EditDialog, SLOT( setSupplierList(QMap<int,QString>) ) );
    }

    if( m_EditDialog != nullptr )
    {
        connect( m_EditDialog, SIGNAL( supplierAddClicked(QString) ), this, SLOT( addSupplier(QString) ) );
        connect( m_EditDialog, SIGNAL( supplierRemClicked(int) ), this, SLOT( removeSupplier(int) ) );
    }

}


///
/// \brief Show dialog for item adding.
///
void CStockList::showDialog_AddItem()
{

    if( m_EditDialog != nullptr )
    {
        // Get request
        if( m_DbSupplier != nullptr )
        {
            m_DbSupplier->GetSupplier();
        }
        // Open dialog
        CItem newItem;
        int retVal = m_EditDialog->exec( newItem );

        if( retVal > 0 )
        {
            if( m_ItemModel != nullptr )
            {
                m_ItemModel->add( newItem );
            }
        }
    }
}

///
/// \brief Gets data from dialog for supplier adding. And adds supplier to database.
/// \param supplierName Name of new supplier
///
void CStockList::addSupplier( QString supplierName )
{
    if( m_EditDialog != nullptr )
    {
        m_DbSupplier->AddSupplier( supplierName );
        m_DbSupplier->GetSupplier();
    }
}

///
/// \brief Remove supplier with id.
/// \param supplierId Supplier id.
///
void CStockList::removeSupplier( int supplierId )
{
    m_DbSupplier->RemSupplier( supplierId );
    m_DbSupplier->GetSupplier();
}


