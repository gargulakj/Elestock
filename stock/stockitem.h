#ifndef CSTOCKITEM_H
#define CSTOCKITEM_H

#include <QObject>

///
/// \brief The CStockItem class - intem in stock
///
class CStockItem : public QObject
{
    Q_OBJECT
private:
    unsigned int m_Id;
    QString m_SymbolSuplier;
    QString m_SymbolProducer;
    QString m_Description;
    unsigned int m_Price;
    unsigned int m_Quantity;

public:
    explicit CStockItem(QObject *parent = nullptr);

signals:

};

#endif // CSTOCKITEM_H
