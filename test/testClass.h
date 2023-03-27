#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QObject>

class dbTestClass : public QObject {
    Q_OBJECT
public:
    dbTestClass();
    bool isConnected;
public slots:
    void dbStateChanged( bool state );
};

#endif // TESTCLASS_H
