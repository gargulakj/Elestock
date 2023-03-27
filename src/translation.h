#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QObject>
#include <QApplication>
#include <QTranslator>
#include <QDir>

///
/// \brief App translation.
///
class CTranslation : public QObject
{
    Q_OBJECT

private:
    // Contains the translations for this application
    QTranslator m_Translator;
    // Contains the translations for qt
    QTranslator m_TranslatorQt;
    // Contains the currently loaded language
    QLocale::Language m_CurrLang;
    // Path to directory with translation files.
    QString m_LangPath;

    // Loads translation and instals it to app.
    void switchTranslator( QTranslator& translator, const QString& filename );
public:
    // Constructor
    explicit CTranslation( QString path, QObject *parent = nullptr );
    // Loads and instal translation.
    void translate( QLocale::Language lang );
    // Returns system language.
    QLocale::Language getSystemLanguage();
    // Return list of possible translation.
    QList<QLocale::Language> getLanguageList();

signals:

};

#endif // TRANSLATION_H
