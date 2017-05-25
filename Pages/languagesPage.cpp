/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#include "languagesPage.hpp"
#include "ui_languagesPage.h"
#include <QTranslator>

extern QString lang;


languagesPage::languagesPage(QWidget *parent) :
    pageBase(parent){

    Ui_languagesPage::setupUi(this);
    ////QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
}


int languagesPage::initAll()
{
    pageBase::initAll();
    initLanguages();
    connect(okPushButton, SIGNAL(clicked()), this, SLOT(applyLanguage()));
	setDone(true);
    return 0;
}

int languagesPage::initLanguages()
{
	setStatus(tr("Loading languages"), BUSY);

    QDir languagesDir;
    QString languagesDirDirPath = getApplicationFile("/Translations/");
    languagesDir.cd(languagesDirDirPath);

    if (!languagesDir.exists())
    {
		setStatus(tr("Ooops , Couldn't find the languages directory : ")+languagesDirDirPath, ERROR);
		setStatus(tr("Assuming english language"), INFORMATION);
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
        setStatus(tr("couldn't load ") + languagesListWidget->selectedItems().at(0)->text() + tr(" language"), ERROR);
    }
    //QApplication::installTranslator(qtTranslator);
    qApp->installTranslator(qtTranslator);


    if (! qtTranslator2->load("/usr/include/MPF/Translations/"+languagesListWidget->selectedItems().at(0)->text()) )
	{
        setStatus(tr("couldn't load ") + languagesListWidget->selectedItems().at(0)->text() + tr(" language"), ERROR);
	}
	//QApplication::installTranslator(qtTranslator);
    qApp->installTranslator(qtTranslator2);

	setStatus(tr("loaded ") + languagesListWidget->selectedItems().at(0)->text() + tr(" language"), INFORMATION);

    language = languagesListWidget->selectedItems().at(0)->text();
    lang = language;
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
