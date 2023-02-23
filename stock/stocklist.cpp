#include "stocklist.h"

///
/// \brief Constructor
/// \param dbService
/// \param parent Parent widget
///
CStockList::CStockList( CDbService* dbService, QWidget* parent ):
    QVBoxLayout{parent},
    m_DbService( dbService ),
    m_EditDialog( nullptr )
{
    m_EditDialog = new CStockItemEditDialog( parent );
    create();
}

///
/// \brief Creates gui components
///
void CStockList::create()
{
    QPushButton* addBtn = new QPushButton();
    addBtn->setText( tr("Add Item") );
    addWidget( addBtn );
    connect( addBtn, SIGNAL( pressed()), this, SLOT( showDialog_AddItem() ) );

    if( m_DbService != nullptr )
    {
        connect( m_DbService, SIGNAL( suppliersReady(QMap<int,QString>) ), m_EditDialog, SLOT( setSupplierList(QMap<int,QString>) ) );
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
        if( m_DbService != nullptr )
        {
            m_DbService->GetSupplier();
        }
        // Open dialog
        int retVal = m_EditDialog->exec();

        if( retVal > 0 )
        {
            m_DbService->AddSupplier( m_EditDialog->getSupplier(0) );
        }
    }
}


