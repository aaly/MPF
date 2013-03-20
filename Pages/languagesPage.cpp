/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#include "languagesPage.hpp"
#include "ui_languagesPage.h"
#include <QTranslator>

languagesPage::languagesPage(QWidget *parent) :
    pageBase(parent){

    Ui_languagesPage::setupUi(this);
}


int languagesPage::initAll()
{
    pageBase::initAll();
    initLanguages();
    connect(okPushButton, SIGNAL(clicked()), this, SLOT(applyLanguage()));
    emit Done(true);
    return 0;
}

int languagesPage::initLanguages()
{
    emit Status(tr("Loading languages"), BUSY);

    QDir languagesDir;
    QString languagesDirDirPath = getApplicationFile("/Translations/");
    languagesDir.cd(languagesDirDirPath);

    if (!languagesDir.exists())
    {
        emit Status(tr("Ooops , Couldn't find the languages directory : ")+languagesDirDirPath, ERROR);
        emit Status(tr("Assuming english language"), INFORMATION);
        return 1;
    }

    for ( unsigned int lang =0; lang < languagesDir.count(); lang++)
    {
        QString translation = languagesDir.entryList().at(lang);

        if (translation == "." || translation == "..")
        {
            continue;
        }

        if (translation.contains(".qm"))
        {
            languagesListWidget->addItem(new QListWidgetItem(translation.mid(0, translation.indexOf(".qm"))));
        }


    }
    return 0;
}

int languagesPage::applyLanguage()
{
    if (! qtTranslator->load(getApplicationFile("/Translations/")+languagesListWidget->selectedItems().at(0)->text()) )
    {
        emit Status(tr("loaded ") + languagesListWidget->selectedItems().at(0)->text() + tr(" language"), ERROR);
    }
    //QApplication::installTranslator(qtTranslator);
    qApp->installTranslator(qtTranslator);

    emit Status(tr("loaded ") + languagesListWidget->selectedItems().at(0)->text() + tr(" language"), INFORMATION);

    language = languagesListWidget->selectedItems().at(0)->text();
    emit selectedLanguage(language);

    //retranslateUi(this);

    return 0;
}

languagesPage::~languagesPage()
{
}


QString languagesPage::SelectedLanguage()
{
    return language;
}

void languagesPage::changeEvent(QEvent* event)
{


    if (event->type() == QEvent::LanguageChange)
    {
        Ui_languagesPage::retranslateUi(this);
    }

    pageBase::changeEvent(event);

}
