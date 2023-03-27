#include "testClass.h"

dbTestClass::dbTestClass() :
    isConnected( false )
{

}
void dbTestClass::dbStateChanged( bool state )
{
    isConnected = state;
    printf("dbStateChanged\n");
}
