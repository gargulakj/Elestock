#define BOOST_TEST_MODULE StockList
#include <boost/test/included/unit_test.hpp>
#include "stock/item.h"
#include "stock/supplierdb.h"
#include "testClass.h"

#include <QEventLoop>

BOOST_AUTO_TEST_CASE( AddItem )
{
    CItem* item = new CItem();;
    item->setPrice( 123 );

    BOOST_TEST( item->getPrice() == 123 );
    delete item;
}


BOOST_AUTO_TEST_CASE( DatabaseTesting )
{
    dbTestClass testDb;
    CSqlConnectorSetting stt;
    stt.SetHostName("192.168.1.5");
    stt.SetDatabaseName("testDB");
    stt.SetUserName("test");
    stt.SetPassword("test");
    CSupplierDb* db = new CSupplierDb( stt );

    QObject::connect( db, SIGNAL(connectionStateChange(bool)), &testDb, SLOT(dbStateChanged( bool) ) );
    db->Init();
    QEventLoop loop;
    for( int i = 0 ;i < 100; i++ )
    {
        loop.processEvents();
        Sleep(100);
    }
    BOOST_TEST( testDb.isConnected == true );

}
