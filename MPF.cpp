/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#include "MPF.h"
#include "ui_MPF.h"
#include "Pages/pageBase.hpp"
#include <Pages/languagesPage.hpp>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include <QMessageBox>

#include <unistd.h> // getuid;

#include <QIcon>
#include <QPixmap>

#include <QProcess>

//#include <iostream>
//using namespace std;


// use setpriority(2) - Linux man page

#include <QScrollArea>

MPF::MPF(QWidget *parent) :
		QMainWindow(parent,0)
{

    if (getuid() != 0)
    {
        //QMessageBox::critical(this, tr("Need Root privilages"), tr("The installer must be ran by the root user"));
        //exit(1);
    }

    setupUi(this);

    showFullScreen();

    pages = new QVector<pageBase*>();
    step = 0;
    helpMaximized = false;
    nextAlreadyEnabled = false;

    messageIconWidth = 16;
    messageIconHeight = 16;
    currentPage = 0;
    pageReady = false;

    helpTextEdit->hide();
    fullHelpPushButton->hide();

    helpPushButton->setIcon(QIcon(getApplicationFile("/Icons/help.png")).pixmap(messageIconWidth, messageIconHeight));
    nextPushButton->setIcon(QIcon(getApplicationFile("/Icons/next.png")).pixmap(messageIconWidth, messageIconHeight));
    previousPushButton->setIcon(QIcon(getApplicationFile("/Icons/prev.png")).pixmap(messageIconWidth, messageIconHeight));
    exitPushButton->setIcon(QIcon(getApplicationFile("/Icons/exit.png")).pixmap(messageIconWidth, messageIconHeight));
    fullHelpPushButton->setIcon(QIcon(getApplicationFile("/Icons/maximize.png")).pixmap(messageIconWidth, messageIconHeight));


	//loadingpage = new loadingPage(this);
	//addPage(loadingpage);

	//loadingpage->setIcon("Icons/critical.png");
	//loadingpage->setIconEffect(FADEIN);
	//loadingpage->setMessageEffect(FADEIN);

	languagesPage* langspage = new languagesPage(this);
	langspage->pageName = tr("Language");
	langspage->pageHelpMessage = tr("Please choose your desired language");
	langspage->pageGroup = "Startup";
	langspage->pageIcon = getApplicationFile("/Icons/Languages.png");
	addPage(langspage);

    connect(helpPushButton, SIGNAL(clicked()), this, SLOT(showHelp()));
    connect(nextPushButton, SIGNAL(clicked()), this, SLOT(nextPage()));
    connect(previousPushButton, SIGNAL(clicked()), this, SLOT(prevPage()));
    connect(exitPushButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(fullHelpPushButton, SIGNAL(clicked()), this, SLOT(showFullHelp()));
    //connect(loadingpage, SIGNAL(finished()), this, SLOT(changePage()));
	//connect(langspage, SIGNAL(selectedLanguage(QString)), this, SLOT(updateLayout(QString)));

	prevPage();
	changePage();

    /*setStyleSheet("  QPushButton { \
                  border: 2px solid #8f8f91; \
                  border-radius: 6px; \
                  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \
                                                    stop: 0 #f6f7fa, stop: 1 #dadbde); \
                  min-width: 80px; \
              } \
 ");*/

    meskLogoLabel->setText("<img align=absmiddle width=180 src="+getApplicationFile("/Icons/mesklogo.png") + " >");
    meskLogoLabel->setAlignment(Qt::AlignHCenter);
    //meskLogoLabel->setText("<img src="+getApplicationFile("/Icons/mesklogo.png") + " >");


}

MPF::~MPF()
{
    delete pages;
}

int MPF::addMessage(QString message, int type)
{
    /*if(type == BUSY)
    {
        if(stackedWidget->currentWidget() != loadingpage)
        {
            stackedWidget->setCurrentWidget(loadingpage);
        }

        loadingpage->setMessage(message);
        loadingpage->setIcon(getApplicationFile("/Icons/busy.png"));
        stackedWidget->setCurrentWidget(loadingpage);
       // return 0;
    }*/

    QLabel* label = new QLabel(this);
    label->setTextFormat(Qt::RichText);
    //label->show();

    QString icon = "<img height=HEIGHT width=WIDTH src=\"PATH\">";
    icon.replace("WIDTH",QString::number(messageIconWidth));
    icon.replace("HEIGHT",QString::number(messageIconHeight));

    if (type == ERROR)
    {
       icon= icon.replace("PATH", getApplicationFile("/Icons/error.png"));
    }
    else if (type == INFORMATION)
    {
       icon= icon.replace("PATH", getApplicationFile("/Icons/information.png"));
    }
    else if (type == CRITICAL)
    {
       icon= icon.replace("PATH", getApplicationFile("/Icons/critical.png"));
    }
    else if (type == BUSY)
    {
        icon= icon.replace("PATH", getApplicationFile("/Icons/busy.png"));
    }
    else if (type == STATUS)
    {
      icon= icon.replace("PATH", getApplicationFile("/Icons/status.png"));
    }
    label->setText(icon+" "+message);

    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(this);
    opacityEffect->setOpacity(0);
    label->setGraphicsEffect(opacityEffect);
    QPropertyAnimation* anim = new QPropertyAnimation(this);
    anim->setTargetObject(opacityEffect);
    anim->setPropertyName("opacity");
    anim->setDuration(9000);
    anim->setStartValue(opacityEffect->opacity());
    anim->setEndValue(1);
    anim->setEasingCurve(QEasingCurve::OutQuad);

    messagesVerticalLayout->addWidget(label);

    anim->start(QAbstractAnimation::DeleteWhenStopped);

    return 0;

}

int MPF::showFullHelp()
{
    scrollArea->takeWidget();

    if(!helpMaximized)
    {
        fullHelpPushButton->setText(tr("Minimize Screen"));
        fullHelpPushButton->setIcon(QIcon(getApplicationFile("/Icons/minimize.png")).pixmap(messageIconWidth, messageIconHeight));
        helpMaximized = true;
        nextAlreadyEnabled = nextPushButton->isEnabled();
        nextPushButton->setEnabled(false);

        //helpTextEdit->setMaximumSize(helpTextEdit->maximumSize());

        ///line_3->hide();
        ///scrollArea->hide();
        ///helpTextEdit->updateGeometry();

        pages->at(step)->hide();

        scrollArea->setWidget(helpTextEdit);
        helpTextEdit->setMinimumHeight(scrollArea->height());



        //helpTextEdit->hide();
        //scrollArea->takeWidget();
        //scrollArea->setWidget(helpTextEdit);
    }
    else
    {
        fullHelpPushButton->setText(tr("Maximize Screen"));
        fullHelpPushButton->setIcon(QIcon(getApplicationFile("/Icons/maximize.png")).pixmap(messageIconWidth, messageIconHeight));
        helpMaximized = false;
        nextPushButton->setEnabled(nextAlreadyEnabled);

        //helpTextEdit->setMinimumSize(helpTextEdit->minimumSize());
        ///line_3->show();
        ///scrollArea->show();
        ///helpTextEdit->updateGeometry();

        //helpTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        pages->at(step)->show();
        scrollArea->setWidget(pages->at(step));
        helpVerticalLayout->addWidget(helpTextEdit);
        //helpTextEdit->show();
        //scrollArea->takeWidget();
        //scrollArea->setWidget(pages->at(step));
    }

    //update();
    //updateGeometry();
    helpVerticalLayout->update();

    return helpMaximized;
}

int MPF::showHelp()
{
    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(this);

    helpTextEdit->setGraphicsEffect(opacityEffect);
    //helpTextEdit->setText("");
    QPropertyAnimation* anim = new QPropertyAnimation(this);

    if(helpTextEdit->isHidden())
    {
        opacityEffect->setOpacity(1);
        anim->setEndValue(0);
        helpPushButton->setText(trUtf8("&Hide Help"));
        helpTextEdit->show();
        fullHelpPushButton->show();
    }
    else
    {
        opacityEffect->setOpacity(0);
        anim->setEndValue(1);
        helpPushButton->setText(trUtf8("&Show Help"));
        helpTextEdit->hide();
        fullHelpPushButton->hide();
    }

    anim->setTargetObject(opacityEffect);
    anim->setPropertyName("opacity");
    anim->setDuration(3000);
    anim->setStartValue(opacityEffect->opacity());
    anim->setEasingCurve(QEasingCurve::InBounce);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    return 0;
}


int MPF::animateWidget(QWidget* widget, bool hide, int effect)
{
    if(!widget)
    {
        return 1;
    }

    if(effect == FADING)
    {
        QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(this);
        opacityEffect->setOpacity(0);
        widget->setGraphicsEffect(opacityEffect);
        QPropertyAnimation* anim = new QPropertyAnimation(this);
        anim->setTargetObject(opacityEffect);
        anim->setPropertyName("opacity");
        anim->setDuration(3000);
        anim->setStartValue(opacityEffect->opacity());
        anim->setEndValue(1);
        anim->setEasingCurve(QEasingCurve::OutQuad);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }


    return 0;
}


int MPF::addPage(pageBase* page)
{
    if (page == NULL)
    {
        return 1;
    }

    //page->resize(stackedWidget->size());


    ////page->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ////stackedWidget->addWidget(page);
    ////stackedWidget->layout()->activate();
    ////stackedWidget->updateGeometry();
    ////stackedWidget->setFixedHeight(stackedWidget->minimumSizeHint().height());
    //scrollArea->setWidget(page);

//    stackedWidget->setFixedSize(stackedWidget->minimumSizeHint());

    pages->push_back(page);
    //stepsLabel->setText("test");

	/*stepsLabel->setText(stepsLabel->text() +
                        QString ("<img align=absmiddle height=30 width=30 src=\"PATH\">").replace("PATH", page->pageIcon)
                        +" "
						+QString(page->pageName) + "<br> <br>");*/

	listGridLayout->addWidget(new QLabel(QString ("<img align=absmiddle height=30 width=30 src=\"PATH\">").replace("PATH", page->pageIcon)), pages->count()-1, 0);
	listGridLayout->addWidget(new QLabel(QString(page->pageName)), pages->count()-1, 1);

	connect(page, SIGNAL(Status(QString,int)), this, SLOT(addMessage(QString,int)), Qt::QueuedConnection);
	//connect(page, SIGNAL(Status(QString,int)), this, SLOT(addMessage(QString,int)));
	connect(page, SIGNAL(Done(bool)), nextPushButton, SLOT(setEnabled(bool)));
	//connect(pages->at(pages->count()-1), SIGNAL(Ready()), loadingpage, SLOT(finish()));

    return 0;
}

int MPF::prevPage()
{
	//?stepsLabel->setText(stepsLabel->text().replace(getApplicationFile("/Icons/current.png"), pages->at(step)->pageIcon));
	QLabel* item0 = (QLabel*)listGridLayout->itemAtPosition(step, 0)->widget();
	item0->setText(item0->text().replace(QString(getApplicationFile("/Icons/current.png")), pages->at(step)->pageIcon));

    nextPushButton->setEnabled(true);

    if (step == 0)
    {
        previousPushButton->setEnabled(false);
        return 1;
    }
    if (step == 1)
    {
        previousPushButton->setEnabled(false);
    }

    pages->at(step)->hide();
    scrollArea->takeWidget();
    step--;

    changePage();

    return step;
}

int MPF::nextPage()
{

    pages->at(step)->finishUp();

	QLabel* item0 = (QLabel*)listGridLayout->itemAtPosition(step, 0)->widget();
	item0->setText(item0->text().replace(QString(getApplicationFile("/Icons/current.png")), pages->at(step)->pageIcon));

	//?stepsLabel->setText(stepsLabel->text().replace(getApplicationFile("/Icons/current.png"), pages->at(step)->pageIcon));


    if(!pages->at(step)->init)
    {
        nextPushButton->setDisabled(true);
    }

    previousPushButton->setEnabled(true);

    if (step == pages->size()-1)
    {
        return 1;
    }
    else if (step == pages->size()-2)
    {
        nextPushButton->setEnabled(false);
    }

    pages->at(step)->hide();
    scrollArea->takeWidget();
    step++;

    changePage();

    return step;
}

int MPF::changePage()
{
    clearMessages();
    loadMessages(pages->at(step));


    scrollArea->setWidget(pages->at(step));
    pages->at(step)->show();

    helpTextEdit->setText(pages->at(step)->pageHelpMessage);


    if (!pages->at(step)->init)
    {
        pages->at(step)->initAll();
    }

	QLabel* item0 = (QLabel*)listGridLayout->itemAtPosition(step, 0)->widget();
	item0->setText(item0->text().replace(pages->at(step)->pageIcon, QString(getApplicationFile("/Icons/current.png"))));

    return 0;
}

//TODO: change it to clear layout as we used this is diskpage ?
int MPF::clearMessages()
{
    QLayoutItem *child;
    while ((child = messagesVerticalLayout->takeAt(0)) != 0)
    {
      delete child->widget();
      delete child;
    }
    messagesVerticalLayout->update();
    return 0;
}

int MPF::loadMessages(pageBase* page)
{
    for ( int i =0; i < page->statuses.count(); i++)
    {
        if (page->statuses.at(i).second != BUSY)
        {
            addMessage(page->statuses.at(i).first, page->statuses.at(i).second);
        }
    }
    return 0;
}


void MPF::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        // retranslate designer form (single inheritance approach)
        retranslateUi(this);
        // retranslate other widgets which weren't added in designer
        generateList();
    }
    // remember to call base class implementation
	QMainWindow::changeEvent(event);
}

int MPF::generateList()
{
    for (int i =0; i < pages->count(); i++)
    {
		QLayoutItem* item0 = listGridLayout->itemAtPosition(i, 0);
		QLayoutItem* item1 = listGridLayout->itemAtPosition(i, 1);

		listGridLayout->removeItem(item0);
		listGridLayout->removeItem(item1);

		delete item0->widget();
		delete item1->widget();


		listGridLayout->addWidget(new QLabel(QString ("<img align=absmiddle height=30 width=30 src=\"PATH\">").replace("PATH", pages->at(i)->pageIcon)), i, 0);
		listGridLayout->addWidget(new QLabel(trUtf8(pages->at(i)->pageName.toStdString().data())), i, 1);

    }
	helpTextEdit->setText(pages->at(step)->pageHelpMessage);
    return 0;
}

int MPF::updateLayout(QString language)
{
    if (language == "ar" )
    {
        setLayoutDirection(Qt::RightToLeft);
        setLocale(QLocale(QLocale::Arabic));
    }
    else
    {
        setLayoutDirection(Qt::LeftToRight);
    }
    return 0;

}



/*
const QRect final_geometry = _final_geometry.isValid() || widget->isWindow() ? _final_geometry :
      QRect(QPoint(-500 - widget->width(), -500 - widget->height()), widget->size());

#ifndef QT_NO_ANIMATION
  AnimationMap::const_iterator it = m_animation_map.constFind(widget);
  if (it != m_animation_map.constEnd() && (*it)->endValue().toRect() == final_geometry)
      return;

  QPropertyAnimation *anim = new QPropertyAnimation(widget, "geometry", widget);
  anim->setDuration(animate ? 200 : 0);
  anim->setEasingCurve(QEasingCurve::InOutQuad);
  anim->setEndValue(final_geometry);
  m_animation_map[widget] = anim;
  connect(anim, SIGNAL(finished()), SLOT(animationFinished()));
  anim->start(QPropertyAnimation::DeleteWhenStopped);
*/
