#include <QDir>
#include <QActionGroup>
#include <QMessageBox>
#include <QPixmap>

#include "mainwindow.h"
#include "ui_mainwindow.h"

///
/// \brief Constructor
/// \param parent
///
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_LbDbStatus( nullptr ),
      m_LbDbStatusIco_G( nullptr ),
      m_LbDbStatusIco_R( nullptr ),
      m_Translation( QApplication::applicationDirPath() + "/languages/" ),
      m_DbItems( nullptr ),
      m_DbSupplier( nullptr ),
      m_StockList( nullptr )
{
    ui->setupUi(this);
    createLanguageMenu();
    createStatusBar();


    CSqlConnectorSetting stt;
    stt.SetHostName("192.168.1.5");
    stt.SetDatabaseName("testDB");
    stt.SetUserName("test");
    stt.SetPassword("test");

    m_DbItems = new CItemDb( stt );
    m_DbSupplier = new CSupplierDb( stt );
    connect( m_DbItems, SIGNAL(connectionStateChange(bool)), this, SLOT(changeDbState(bool)));
    connect( m_DbItems, SIGNAL(queryFailed(QString)),this,SLOT(showErrMessage(QString)));
    connect( m_DbSupplier, SIGNAL(queryFailed(QString)),this,SLOT(showErrMessage(QString)));
    m_DbItems->Init();
    m_DbSupplier->Init();

    m_StockList = new CStockList( m_DbItems, m_DbSupplier, ui->tabStockList );


}

///
/// \brief Destructor
///
MainWindow::~MainWindow()
{
    if( m_DbItems != nullptr )
    {
        delete m_DbItems;
    }

    if( m_DbSupplier != nullptr )
    {
        delete m_DbSupplier;
    }
    delete ui;
}

void MainWindow::createStatusBar()
{
    // Horinzontal layout for label and image
    QWidget* dbStatusWidget = new QWidget;
    QHBoxLayout* dbStatusLayout = new QHBoxLayout( dbStatusWidget );
    dbStatusLayout->setContentsMargins(0,0,0,0);

    // Green icon for indication db state
    QPixmap icon;
    if( icon.load("://images/iconLedGreen") )
    {
        m_LbDbStatusIco_G = new QLabel;
        m_LbDbStatusIco_G->setPixmap( icon );
        m_LbDbStatusIco_G->setVisible( false );
        dbStatusLayout->addWidget( m_LbDbStatusIco_G );
    }

    // Red icon for indication db state
    if( icon.load("://images/iconLedRed") )
    {
        m_LbDbStatusIco_R = new QLabel;
        m_LbDbStatusIco_R->setPixmap( icon );
        m_LbDbStatusIco_R->setVisible( false );
        dbStatusLayout->addWidget( m_LbDbStatusIco_R );
    }

    // Label for indication db state
    m_LbDbStatus = new QLabel;
    dbStatusLayout->addWidget( m_LbDbStatus );
    ui->statusbar->addPermanentWidget( dbStatusWidget );

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
/// \param state Connected/Disconnected
///
void MainWindow::changeDbState( bool state )
{
    m_LbDbStatus->setText( tr("Database %1").arg( state ? tr("Connected") : tr("Disconnected") ) );
    m_LbDbStatusIco_G->setVisible( state );
    m_LbDbStatusIco_R->setVisible( !state );
}

///
/// \brief Slow shows message box.
/// \param errText Message.
///
void MainWindow::showErrMessage( QString errText )
{
    QMessageBox msgBox;
    msgBox.setWindowTitle( tr("Error") );
    msgBox.setText( errText );
    msgBox.setIcon( QMessageBox::Icon::Warning );
    msgBox.exec();
}
