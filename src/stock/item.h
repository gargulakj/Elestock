#ifndef CSTOCKITEM_H
#define CSTOCKITEM_H

#include <QObject>
#include <QString>

///
/// \brief The CStockItem class - intem in stock
///
class CItem : public QObject
{
    Q_OBJECT
private:
    // Data of one stock item
    unsigned int m_Id;
    QString m_SymbolSupplier;
    QString m_SymbolProducer;
    QString m_Description;
    unsigned int m_Price;
    unsigned int m_Quantity;
    int m_SupplierId;
    QString m_SupplierName;

public:
    // Constructor
    explicit CItem(QObject *parent = nullptr);
    // Copy constructor
    explicit CItem( const CItem& item );
    // CItem::operator = overloading.
    CItem& operator = ( const CItem& righOp );
    // Copy function
    void copyFrom( const CItem& sourceItem );
    // Sets item identifier.
    void setId( unsigned int id );
    // Returns item identifier.
    unsigned int getId() const;
    // Sets symbol at the supplier.
    void setSymbolSuplier( QString symbol );
    // Returns symbol at the supplier.
    QString getSymbolSupplier() const;
    // Sets symbol at the producer.
    void setSymbolProducer( QString symbol );
    // Returns symbol at the producer.
    QString getSymbolProducer() const;
    // Sets description of the item.
    void setDescription( QString description );
    // Returns description of the item.
    QString getDescription() const;
    // Sets item price
    void setPrice( unsigned int price );
    // Returns item price.
    unsigned int getPrice() const;
    // Sets quantity of items.
    void setQuantity( unsigned int quantity );
    // Returns quantity of items.
    unsigned int getQuantity() const;
    // Sets supplier id.
    void setSupplierId( int supplierId );
    // Returns supplier id.
    int getSupplierId() const;    
    // Sets supplier name.
    void setSupplierName( QString supplName );
    // Returns supplier name.
    QString getSupplierName() const;

signals:

};

#endif // CSTOCKITEM_H
