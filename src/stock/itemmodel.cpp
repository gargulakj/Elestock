#include "itemmodel.h"
#include <QDebug>
#include <QVariant>
///
/// \brief Constructor
/// \param Reference to item database.
/// \param parent
///
CItemModel::CItemModel( CItemDb& db, QObject *parent )
    : QAbstractTableModel{parent},
      m_Db( db )
{
    m_ItemList.clear();
    m_ItemListTmp.clear();
    connect( &m_Db, SIGNAL(queryGetFinished()), this, SLOT(updateModel()) );
    m_Db.queryGet( &m_ItemListTmp );

}

///
/// \brief Destructor
///
CItemModel::~CItemModel()
{
    clearItemList( m_ItemList );
}

///
/// \brief Clears list of items.
/// \param itemList List for clear.
///
void CItemModel::clearItemList( QList<CItem*> itemList )
{
    for( int i = 0; i < itemList.size(); i++ )
    {
        CItem* item = itemList[i];
        if( item != nullptr )
        {
            delete item;
        }
    }

    itemList.clear();
}

///
/// \brief Update model according to processed query.
///
void CItemModel::updateModel()
{
    beginResetModel();
    clearItemList( m_ItemList );
    m_ItemList = m_ItemListTmp;
    endResetModel();
}

///
/// \brief Returns count of items (rows).
/// \param parent Is unused.
/// \return Count of items (rows).
///
int CItemModel::rowCount( const QModelIndex &parent ) const
{
    Q_UNUSED( parent )
    return m_ItemList.size();
}

///
/// \brief Returns count of columns.
/// \param parent Is unused.
/// \return Count of columns
///
int CItemModel::columnCount( const QModelIndex &parent ) const
{
    Q_UNUSED( parent )
    return 7;
}

///
/// \brief Data getter implementation.
/// \param index Data identifier.
/// \param role Data role
/// \return Data to table.
///
QVariant CItemModel::data( const QModelIndex &index, int role ) const
{
    QVariant val;

    if( index.isValid() && (role == Qt::DisplayRole) )
    {
        if( index.row() < m_ItemList.size() )
        {
            CItem* item = m_ItemList[index.row()];
            if( item != nullptr )
            {
                switch( index.column() )
                {
                case 0:
                    val = item->getId();
                break;
                case 1:
                    val = item->getSymbolSupplier();
                break;
                case 2:
                    val = item->getSymbolProducer();
                break;
                case 3:
                    val = item->getDescription();
                break;
                case 4:
                    val = item->getPrice();
                break;
                case 5:
                    val = item->getQuantity();
                break;
                case 6:
                    val = item->getSupplierName();
                break;
                }
            }
        }
    }
    return val;
}

///
/// \brief Returns the data for the given role and section in the header with the specified orientation
/// \param section Columnd id.
/// \param orientation Orientation of titles
/// \param role Role
/// \return
///
QVariant CItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant headerValue;

    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch( section )
            {
            case 0:
                headerValue = tr("ID");
            break;
            case 1:
                headerValue = tr("Symbol Supplier");
            break;
            case 2:
                headerValue = tr("Symbol Producer");
            break;
            case 3:
                headerValue = tr("Description");
            break;
            case 4:
                headerValue = tr("Price");
            break;
            case 5:
                headerValue = tr("Quantity");
            break;
            case 6:
                headerValue = tr("Supplier");
            break;
            }
        }
    }

    return headerValue;
}

void CItemModel::add( const CItem& item )
{
    m_Db.queryAdd( item );
    m_Db.queryGet( &m_ItemListTmp );
}

const CItem* CItemModel::get( int itemPos ) const
{
    return nullptr;
}

void CItemModel::change( const CItem& item )
{

}
void CItemModel::set( QList<CItem*> items )
{

}
