#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include "translation.h"
#include "sql/dbservice.h"
#include "stock/stocklist.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow* ui;

    // App translation
    CTranslation m_Translation;
    // Database service
    CDbService* m_DbService;
    // Component for stock view.
    CStockList* m_StockList;


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
public:
    // Constructor
    MainWindow(QWidget *parent = nullptr);
    // Destructor
    ~MainWindow();

};
#endif // MAINWINDOW_H
