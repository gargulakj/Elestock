#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include "translation.h"
#include "stock/stocklist.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // Main windows
    Ui::MainWindow* ui;
    // DB status label
    QLabel* m_LbDbStatus;
    // DB status icon green
    QLabel* m_LbDbStatusIco_G;
    // DB status icon red
    QLabel* m_LbDbStatusIco_R;

    // App translation
    CTranslation m_Translation;
    // Items database service
    CItemDb* m_DbItems;
    // Supplier database service
    CSupplierDb* m_DbSupplier;
    // Component for stock view.
    CStockList* m_StockList;

    // Creates status bar
    void createStatusBar();
    // Creates the language menu dynamically from the content of language directory
    void createLanguageMenu(void);

protected:
    // Overriding changeEvent from widget parent.
    void changeEvent( QEvent* event ) override;

private slots:
    // Slot changes the language
    void changeLanguage( QAction* action );
    // Slot changes the label of database state.
    void changeDbState( bool state );
    // Slow shows message box.
    void showErrMessage( QString errText );
public:
    // Constructor
    MainWindow(QWidget *parent = nullptr);
    // Destructor
    ~MainWindow();

};
#endif // MAINWINDOW_H
