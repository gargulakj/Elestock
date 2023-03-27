#include "item.h"

///
/// \brief Constructor
/// \param parent
///
CItem::CItem( QObject *parent ) :
    QObject{parent},
    m_Id( 0 ),
    m_SymbolSupplier( "" ),
    m_SymbolProducer( "" ),
    m_Description( "" ),
    m_Price( 0 ),
    m_Quantity( 0 ),
    m_SupplierId( 0 ),
    m_SupplierName( "" )
{

}

///
/// \brief Copy constructor
/// \param item Source item
///
CItem::CItem( const CItem& item )
{
    copyFrom( item );
}

///
/// \brief CItem::operator = overloading.
/// \param righOp Right operand.
/// \return Returns left operand (this)
///
CItem& CItem::operator = ( const CItem& righOp )
{
    copyFrom( righOp );
    return *this;
}

///
/// \brief Copy function
/// \param sourceItem Source item.
///
void CItem::copyFrom( const CItem& sourceItem )
{
    m_Id = sourceItem.m_Id;
    m_SymbolSupplier = sourceItem.m_SymbolSupplier;
    m_SymbolProducer = sourceItem.m_SymbolProducer;
    m_Description = sourceItem.m_Description;
    m_Price = sourceItem.m_Price;
    m_Quantity = sourceItem.m_Quantity;
    m_SupplierId = sourceItem.m_SupplierId;
    m_SupplierName = sourceItem.m_SupplierName;

}

///
/// \brief Sets item identifier.
/// \param id
///
void CItem::setId( unsigned int id )
{
    m_Id = id;
}

///
/// \brief Returns item identifier.
/// \return Item identifier.
///
unsigned int CItem::getId() const
{
    return m_Id;
}

///
/// \brief Sets symbol at the supplier.
/// \param symbol Symbol at the supplier.
///
void CItem::setSymbolSuplier( QString symbol )
{
    m_SymbolSupplier = symbol;
}

///
/// \brief Returns symbol at the supplier.
/// \return Symbol at the supplier.
///
QString CItem::getSymbolSupplier() const
{
    return m_SymbolSupplier;
}

///
/// \brief Sets symbol at the producer.
/// \param symbol Symbol at the producer.
///
void CItem::setSymbolProducer( QString symbol )
{
    m_SymbolProducer = symbol;
}

///
/// \brief Returns symbol at the producer.
/// \return Symbol at the producer.
///
QString CItem::getSymbolProducer() const
{
    return m_SymbolProducer;
}

///
/// \brief Sets description of the item.
/// \param description Description of the item.
///
void CItem::setDescription( QString description )
{
    m_Description = description;
}

///
/// \brief Returns description of the item.
/// \return Description of the item.
///
QString CItem::getDescription() const
{
    return m_Description;
}

///
/// \brief Sets item price
/// \param price Item price
///
void CItem::setPrice( unsigned int price )
{
    m_Price = price;
}

///
/// \brief Returns item price.
/// \return Item price
///
unsigned int CItem::getPrice() const
{
    return m_Price;
}

///
/// \brief Sets quantity of items.
/// \param quantity Quantity of items.
///
void CItem::setQuantity( unsigned int quantity )
{
    m_Quantity = quantity;
}

///
/// \brief Returns quantity of items.
/// \return Quantity of items.
///
unsigned int CItem::getQuantity() const
{
    return m_Quantity;
}

///
/// \brief Sets supplier id.
/// \param supplierId Supplier id.
///
void CItem::setSupplierId( int supplierId )
{
    m_SupplierId = supplierId;
}

///
/// \brief Returns supplier id.
/// \return Supplier id.
///
int CItem::getSupplierId() const
{
    return m_SupplierId;
}

///
/// \brief Sets supplier name.
/// \param supplName Supplier name.
///
void CItem::setSupplierName( QString supplName )
{
    m_SupplierName = supplName;
}

///
/// \brief Returns supplier name.
/// \return Supplier name.
///
QString CItem::getSupplierName() const
{
    return m_SupplierName;
}
