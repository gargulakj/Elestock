QT       += core sql
TEMPLATE = app
CONFIG -= app_bundle
CONFIG += console

isEmpty(BOOST_INCLUDE_DIR): BOOST_INCLUDE_DIR=$$(BOOST_INCLUDE_DIR)
# set by Qt Creator wizard
isEmpty(BOOST_INCLUDE_DIR): BOOST_INCLUDE_DIR="D:/Projekty_PC_Qt/boost_1_81_0"
!isEmpty(BOOST_INCLUDE_DIR): INCLUDEPATH *= $${BOOST_INCLUDE_DIR}

isEmpty(BOOST_INCLUDE_DIR): {
    message("BOOST_INCLUDE_DIR is not set, assuming Boost can be found automatically in your system")
}

INCLUDEPATH += ../src/

HEADERS += \
    ../src/stock/item.h \
    ../src/stock/supplierdb.h \
    ../src/sql/sqlconnector.h \
    ../src/sql/dbservice.h \
    testClass.h

SOURCES += \
    main.cpp \
    ../src/stock/item.cpp \
    ../src/stock/supplierdb.cpp \
    ../src/sql/sqlconnector.cpp \
    ../src/sql/dbservice.cpp \
    testClass.cpp
