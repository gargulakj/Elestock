#include "translation.h"

///
/// \brief Constructor
/// \param path Path to directory with translation files.
/// \param parent
///
CTranslation::CTranslation( QString path, QObject *parent ):
    QObject{parent},
    m_CurrLang( QLocale::Language::AnyLanguage ),
    m_LangPath( path )
{

}

///
/// \brief Loads translation and instals it to app.
/// \param translator Reference to translator.
/// \param filename Language name.
///
void CTranslation::switchTranslator( QTranslator& translator, const QString& filename )
{
    // remove the old translator
    qApp->removeTranslator( &translator );

    // load the new translator
    if( translator.load( m_LangPath + filename ) ) {
        qApp->installTranslator( &translator );
    }
}

///
/// \brief Loads and instal translation.
/// \param lang Requested languge.
///
void CTranslation::translate( QLocale::Language lang )
{
    if(m_CurrLang != lang)
    {
        m_CurrLang = lang;
        QLocale locale = QLocale( m_CurrLang );
        QLocale::setDefault( locale );
        QString name = locale.name();
        name.truncate( name.lastIndexOf('_') );

        switchTranslator( m_Translator, QString("ElestockTr_%1.qm").arg( name ) );
        switchTranslator( m_TranslatorQt, QString("qt_%1.qm").arg( name ) );
    }
}

///
/// \brief Returns system language.
/// \return System language.
///
QLocale::Language CTranslation::getSystemLanguage()
{
    return QLocale::system().language();
}

///
/// \brief Return list of possible translation.
///
QList<QLocale::Language> CTranslation::getLanguageList()
{
    QList<QLocale::Language> langList;

    QDir dir( m_LangPath );
    QStringList fileNames = dir.entryList( QStringList( "ElestockTr_*.qm" ) );
    langList.clear();

    for (int i = 0; i < fileNames.size(); ++i) {
        // get locale extracted by filename
        QString locale;
        locale = fileNames[i]; // "ElestockTr_de.qm"
        locale.truncate( locale.lastIndexOf('.') ); // "TranslationExample_de"
        locale.remove( 0, locale.lastIndexOf('_') + 1 ); // "de"

        langList.append( QLocale(locale).language() );
    }

    return langList;
}
