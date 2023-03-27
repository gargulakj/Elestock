#ifndef CSTOCKLISTMODEL_H
#define CSTOCKLISTMODEL_H

#include <QAbstractTableModel>

#include "itemdb.h"

class CItemModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    // Database service
    CItemDb& m_Db;
    // List shown in this model.
    QList<CItem*> m_ItemList;
    // Temporary list for data obtaining.
    QList<CItem*> m_ItemListTmp;

    // Clears list of items.
    void clearItemList( QList<CItem*> itemList );


private slots:
    //! Resets and refill all data to model.
    void updateModel();

public:
    // Constructor
    explicit CItemModel( CItemDb& db, QObject *parent = nullptr );
    // Destructor
    ~CItemModel();
    // Returns count of items.
    int rowCount(const QModelIndex &parent) const;
    // Returns count of columns.
    int columnCount(const QModelIndex &parent) const;
    // Data getter implementation.
    QVariant data(const QModelIndex &index, int role) const;
    // Returns the data for the given role and section in the header with the specified orientation
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void add( const CItem& item );
    const CItem* get( int itemPos ) const;
    void change( const CItem& item );
    void set( QList<CItem*> items );
};

#endif // CSTOCKLISTMODEL_H
