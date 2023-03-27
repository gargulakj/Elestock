#include "dbservice.h"

///
/// \brief DoWork implementation of table creation..
/// \param query Reference to sqlQuery instance. After execution it contains result.
///
bool CCreateTablesQuery::DoWork( QSqlQuery& query )
{
    bool retVal = true;

    QSqlQuery tabListQuery( query );
    tabListQuery.prepare( "SHOW TABLES;" );

    if( tabListQuery.exec() )
    {
        // Get list of existing tables.
        QStringList tableList;
        while( tabListQuery.next() )
        {
            tableList.append( tabListQuery.value( 0 ).toString() );
        }

        bool tableExist = false;

        // Create Suplier table
        if( !tableList.contains( "TabSupplier" ) )
        {
            QSqlQuery newTabQuery( query );
            newTabQuery.prepare( "CREATE TABLE TabSupplier ( "
                                 "ID int AUTO_INCREMENT, "
                                 "Name varchar(255) NOT NULL, "
                                 "PRIMARY KEY (ID), "
                                 "UNIQUE (Name) "
                                 ");" );

            if( !newTabQuery.exec() )
            {
                qDebug() << newTabQuery.lastError();
                tableExist = false;
            }
            else
            {
                tableExist = true;
            }
        }
        else
        {
            tableExist = true;
        }

        if( tableExist )
        {
            // Create Stock table
            if( !tableList.contains( "TabStock" ) )
            {
                QSqlQuery newTabQuery( query );
                newTabQuery.prepare( "CREATE TABLE TabStock ( "
                                     "ID int AUTO_INCREMENT, "
                                     "SymbolSupplier varchar(64), "
                                     "SymbolProducer varchar(64), "
                                     "Description varchar(64), "
                                     "Price int unsigned, "
                                     "Quantity int unsigned, "
                                     "Supplier int, "
                                     "PRIMARY KEY (ID), "
                                     "FOREIGN KEY (Supplier) REFERENCES TabSupplier(ID), "
                                     "CONSTRAINT UniqueItem UNIQUE (SymbolSupplier,Supplier) "
                                     " );" );

                if( !newTabQuery.exec() )
                {
                    qDebug() << newTabQuery.lastError();
                    tableExist = false;
                }
            }
            else
            {
                tableExist = true;
            }
        }
    }
    else
    {
        retVal = false;
    }



    return retVal;
}

///
/// \brief Constructor of stock database service.
/// \param connectionName Connection name
/// \param stt Setting for access to database.
/// \param parent
///
CDbService::CDbService( QString connectionName, CSqlConnectorSetting stt, QObject *parent ):
    CSqlConnector( connectionName, stt, parent )
{

    AddQuery( new CCreateTablesQuery() );

}

///
/// \brief Destructor
///
CDbService::~CDbService()
{
}
