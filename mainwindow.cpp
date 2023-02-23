#include <QDir>
#include <QActionGroup>
#include "mainwindow.h"
#include "ui_mainwindow.h"

///
/// \brief Constructor
/// \param parent
///
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_Translation( QApplication::applicationDirPath() + "/languages/" ),
      m_DbService( nullptr ),
      m_StockList( nullptr )
{
    ui->setupUi(this);
    createLanguageMenu();


    CSqlConnectorSetting stt;
    stt.SetHostName("192.168.1.5");
    stt.SetDatabaseName("testDB");
    stt.SetUserName("test");
    stt.SetPassword("test");

    m_DbService = new CDbService( stt );
    connect( m_DbService, SIGNAL(connectionStateChange(bool)), this, SLOT(changeDbState(bool)));
    m_DbService->Init();

    m_StockList = new CStockList( m_DbService, ui->tabStockList );

}

///
/// \brief Destructor
///
MainWindow::~MainWindow()
{
    if( m_DbService != nullptr )
    {
        delete m_DbService;
    }
    delete ui;
}

///
/// \brief Creates the language menu dynamically from the content of language directory
///
void MainWindow::createLanguageMenu()
{
    QActionGroup* langGroup = new QActionGroup( ui->menuLanguage );
    langGroup->setExclusive( true );

    connect( langGroup, SIGNAL( triggered(QAction*) ), this, SLOT( changeLanguage(QAction*) ) );

    QList<QLocale::Language> langList = m_Translation.getLanguageList();
    QLocale::Language systemLang = m_Translation.getSystemLanguage();

    for( int i = 0; i < langList.size(); i++ )
    {
        QLocale locale = QLocale( langList[i] );
        QAction* action = new QAction( QLocale::languageToString(locale.language()), this );
        action->setCheckable( true );
        action->setData( static_cast<ushort>(langList[i]) );

        ui->menuLanguage->addAction( action );
        langGroup->addAction( action );

        // set default translators and language checked
        if ( langList[i] == systemLang ) {
            action->setChecked( true );
        }
    }
}


///
/// \brief Overriding changeEvent from widget parent.
/// \param event
///
void MainWindow::changeEvent( QEvent* event )
{
    if( event != nullptr ) {
        switch(event->type()) {
            // this event is send if a translator is loaded
        case QEvent::LanguageChange:
            ui->retranslateUi( this );
        break;

            // this event is send, if the system, language was changed
        case QEvent::LocaleChange:
        {
            m_Translation.translate( QLocale::system().language() );
        }
        break;
        }
    }
    QMainWindow::changeEvent( event );
}

///
/// \brief Slot changes the language
/// \param action Source action
///
void MainWindow::changeLanguage( QAction* action )
{
    if( action != nullptr )
    {
        m_Translation.translate( static_cast<QLocale::Language>( action->data().toUInt() ) );
    }
}

///
/// \brief Slot changes the label of database state.
/// \param state
///
void MainWindow::changeDbState( bool state )
{
    ui->statusbar->showMessage( tr("Database: %1").arg( state ? tr("Connected") : tr("Disconnected") ) );
}

