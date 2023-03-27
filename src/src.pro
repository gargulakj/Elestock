QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TRANSLATIONS = \
    languages/ElestockTr_cs.ts

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    stock/editdialog.cpp \
    sql/sqlconnector.cpp \
    sql/dbservice.cpp \
    stock/item.cpp \
    stock/itemdb.cpp \
    stock/itemmodel.cpp \
    stock/stocklist.cpp \
    stock/supplierdb.cpp \
    translation.cpp

HEADERS += \
    mainwindow.h \
    stock/editdialog.h \
    sql/sqlconnector.h \
    sql/dbservice.h \
    stock/item.h \
    stock/itemdb.h \
    stock/itemmodel.h \
    stock/stocklist.h \
    stock/supplierdb.h \
    translation.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/images.qrc

