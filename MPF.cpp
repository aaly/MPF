/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#include "MPF.h"
#include "ui_MPF.h"
#include "Pages/pageBase.hpp"
#include <Pages/languagesPage.hpp>
#include <Pages/groupSelector.hpp>

#include <QtWidgets/QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include <QtWidgets/QMessageBox>

#include <unistd.h> // getuid;

#include <QIcon>
#include <QPixmap>

#include <QProcess>

//#include <iostream>
//using namespace std;

languagesPage* langspage;
pagesGroup* languagesGroup;

// use setpriority(2) - Linux man page

#include <QtWidgets/QScrollArea>

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

	currentGroup = -1;
	selectedGroup = 0;
    helpMaximized = false;
    nextAlreadyEnabled = false;

    messageIconWidth = 16;
    messageIconHeight = 16;

    helpTextEdit->hide();
    fullHelpPushButton->hide();

	
	previousPushButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon	);
	nextPushButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon	);
	exitPushButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon	);
	
	
	//previousPushButton->setAlignment(Qt::AlignLeft);
    helpPushButton->setIcon(QIcon(getApplicationFile("/Icons/help.png")).pixmap(messageIconWidth, messageIconHeight));
    nextButtonIcon->setIcon(QIcon(getApplicationFile("/Icons/next.png")).pixmap(messageIconWidth, messageIconHeight));
    prevButtonIcon->setIcon(QIcon(getApplicationFile("/Icons/prev.png")).pixmap(messageIconWidth, messageIconHeight));
    exitButtonIcon->setIcon(QIcon(getApplicationFile("/Icons/exit.png")).pixmap(messageIconWidth, messageIconHeight));
    fullHelpPushButton->setIcon(QIcon(getApplicationFile("/Icons/maximize.png")).pixmap(messageIconWidth, messageIconHeight));


	//loadingpage = new loadingPage(this);
	//addPage(loadingpage);

	//loadingpage->setIcon("Icons/critical.png");
	//loadingpage->setIconEffect(FADEIN);
	//loadingpage->setMessageEffect(FADEIN);

	langspage = new languagesPage(this);
	langspage->pageName = tr("Language");
	langspage->pageHelpMessage = tr("Please choose your desired language");
	langspage->pageGroup = "Startup";
	langspage->pageIcon = getApplicationFile("/Icons/Languages.png");
	//addPage(langspage);
	languagesGroup = new pagesGroup(this);
    languagesGroup->addPage(langspage);
	addGroup(languagesGroup);



	prevButtonIcon->setFocusPolicy(Qt::NoFocus);
	nextButtonIcon->setFocusPolicy(Qt::NoFocus);
	exitButtonIcon->setFocusPolicy(Qt::NoFocus);
	
	connect(prevButtonIcon, SIGNAL(clicked()), this, SLOT(prevPage()));
    connect(nextButtonIcon, SIGNAL(clicked()), this, SLOT(nextPage()));
    connect(exitButtonIcon, SIGNAL(clicked()), this, SLOT(close()));
    
	//connect(prevButtonIcon, SIGNAL(clicked()), previousPushButton, SLOT(click()));
    //connect(nextButtonIcon, SIGNAL(clicked()), nextPushButton, SLOT(click()));
    //connect(exitButtonIcon, SIGNAL(clicked()), exitPushButton, SLOT(click()));
    
    
    //connect(nextPushButton, SIGNAL(clicked()), nextButtonIcon, SLOT(animateClick()));
    //connect(previousPushButton, SIGNAL(clicked()), prevButtonIcon, SLOT(animateClick()));
    //connect(exitPushButton, SIGNAL(clicked()), exitButtonIcon, SLOT(animateClick()));
    
    connect(helpPushButton, SIGNAL(clicked()), this, SLOT(showHelp()));
    connect(nextPushButton, SIGNAL(clicked()), this, SLOT(nextPage()));
    connect(previousPushButton, SIGNAL(clicked()), this, SLOT(prevPage()));
    connect(exitPushButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(fullHelpPushButton, SIGNAL(clicked()), this, SLOT(showFullHelp()));
    //connect(loadingpage, SIGNAL(finished()), this, SLOT(changePage()));
	connect(langspage, SIGNAL(selectedLanguage(QString)), this, SLOT(updateLayout(QString)));

    /*setStyleSheet("  QPushButton { \
                  border: 2px solid #8f8f91; \
                  border-radius: 6px; \
                  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \
                                                    stop: 0 #f6f7fa, stop: 1 #dadbde); \
                  min-width: 80px; \
              } \
 ");*/

	//meskLogoLabel->setText("<img align=absmiddle width=180 src="+getApplicationFile("/Icons/mesklogo.png") + " >");
    meskLogoLabel->setAlignment(Qt::AlignHCenter);
	meskLogoLabel->setText(QString("<img hspace=\"5\" align=absmiddle width=186 src="+getApplicationFile("/Icons/mesklogo.png") + " >"));

    fullHelpPushButton->setEnabled(false);
	previousPushButton->setEnabled(false);
	prevButtonIcon->setEnabled(false);

	setGroup(languagesGroup);

	//QVBoxLayout* messagesVerticalLayout = new QVBoxLayout(this);
    //scrollArea_2->setWidget(messagesVerticalLayout);

}

MPF::~MPF()
{
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

		groups.at(currentGroup)->getCurrentPage()->hide();

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
		groups.at(currentGroup)->getCurrentPage()->show();
		scrollArea->setWidget(groups.at(currentGroup)->getCurrentPage());
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





void MPF::changeEvent(QEvent* event)
{

    if (event->type() == QEvent::LanguageChange)
	{
        // retranslate designer form (single inheritance approach)
        retranslateUi(this);
		for (int i =0; i < groups.size(); i++)
		{
			//groups.at(i)->generateList();
			//groups.at(i)->updateList();
			QApplication::sendEvent(groups.at(i), event);
		}
    }
	QMainWindow::changeEvent(event);
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
	listGridLayout->update();
    return 0;

}




int MPF::prevPage()
{
	//listGridLayout->update();
	nextPushButton->setEnabled(true);
	cout << currentGroup  << ":" << groups.at(currentGroup)->currentPage << endl;

	int direction = -1;

	if (groups.at(currentGroup)->currentPage == 0)
	{
		if(currentGroup > 0)
		{
			setGroup(groups.at(currentGroup-1));
			//groups.at(currentGroup)->currentPage = groups.at(currentGroup)->pages.size()-1;
			//direction = 0;
		}

		if(currentGroup <= 0)
		{
			previousPushButton->setEnabled(false);
			prevButtonIcon->setEnabled(false);
		}
		return 0;
	}

	changePage(direction);
    groups.at(currentGroup)->getCurrentPage()->Clean();
	return groups.at(currentGroup)->currentPage;
}

int MPF::nextPage()
{
	groups.at(currentGroup)->getCurrentPage()->finishUp();

	if(groups.at(currentGroup)->currentPage < groups.at(currentGroup)->pages.size()-1)
	{
		if(!groups.at(currentGroup)->pages.at(groups.at(currentGroup)->currentPage+1)->init)
		{
			nextPushButton->setDisabled(true);
			nextButtonIcon->setEnabled(true);
		}
	}

	previousPushButton->setEnabled(true);
	prevButtonIcon->setEnabled(true);

	if (groups.at(currentGroup)->currentPage == groups.at(currentGroup)->pages.size()-1)
	{
		if(currentGroup < groups.size()-1)
		{
			setGroup(groups.at(currentGroup+1));
		}

		if(currentGroup == groups.size()-1)
		{
			nextPushButton->setDisabled(true);
			nextButtonIcon->setDisabled(true);
		}
		return 1;
	}
	else if (groups.at(currentGroup)->currentPage == groups.at(currentGroup)->pages.size()-2)
	{
		nextPushButton->setEnabled(false);
		nextButtonIcon->setEnabled(false);
	}



	changePage(1);

	return groups.at(currentGroup)->currentPage;
}

int MPF::changePage(int direction)
{

	
	if (groups.at(currentGroup)->currentPage+direction < 0
		|| groups.at(currentGroup)->currentPage+direction > groups.at(currentGroup)->pages.size()-1)
	{
		return -1;
	}


	scrollArea->takeWidget();
	if(direction != 0)
	{
		groups.at(currentGroup)->getCurrentPage()->hide();
		//scrollArea->takeWidget();
	}

	QLabel* item = (QLabel*)groups.at(currentGroup)->listGridLayout->itemAtPosition(groups.at(currentGroup)->currentPage, 1)->widget();
	//Ditem->setText(item->text().replace(QString(getApplicationFile("/Icons/current.png")), groups.at(currentGroup)->getCurrentPage()->pageIcon));
	item->setStyleSheet("");
	//item->style()->unpolish(item);
	//item->style()->polish(item);
	//item->update();
	groups.at(currentGroup)->currentPage += direction;
	clearMessages();
	loadMessages(groups.at(currentGroup)->getCurrentPage());


	if(groups.at(currentGroup)->getCurrentPage())
	{
		//QWidget* widget = scrollArea->takeWidget();
		//widget->hide();
		//widget->setParent(this);

		scrollArea->setWidget(groups.at(currentGroup)->getCurrentPage());
	}
	groups.at(currentGroup)->getCurrentPage()->show();

	helpTextEdit->setText(groups.at(currentGroup)->getCurrentPage()->pageHelpMessage);


	if (!groups.at(currentGroup)->getCurrentPage()->init)
	{
		groups.at(currentGroup)->getCurrentPage()->initAll();
	}



	

	QLabel* item0 = (QLabel*)groups.at(currentGroup)->listGridLayout->itemAtPosition(groups.at(currentGroup)->currentPage, 1)->widget();
	//Ditem0->setText(item0->text().replace(groups.at(currentGroup)->getCurrentPage()->pageIcon, QString(getApplicationFile("/Icons/current.png"))));
	item0->setStyleSheet("color : #44aaff; font-weight: bold;");
	//item0->style()->unpolish(item0);
	//item0->style()->polish(item0);
	//item0->update();

	helpTextEdit->setText(groups.at(currentGroup)->getCurrentPage()->pageHelpMessage);
	
	if (nextPushButton->isEnabled())
	{
		nextPushButton->setFocus();
	}
	else
	{
		previousPushButton->setFocus();
	}
	
	if(groups.at(currentGroup)->getCurrentPage()->pageType == "GROUPSELECTOR")
	{
		groupSelector* gSelector = (groupSelector*)groups.at(currentGroup)->getCurrentPage();
		gSelector->Focus();
		//groups.at(currentGroup)->groupsLayout->itemAt(0)->widget()->setFocus();
		//groups.at(currentGroup)->getCurrentPage()->setFocus();
	}
	
	return 0;
}

int MPF::addGroup(pagesGroup* grp)
{
	if (grp == NULL)
	{
		return 1;
	}

	groups.push_back(grp);
	return 0;
}

int MPF::cleanLastGroup()
{
    if(currentGroup < groups.size()-1)
    {
        groups.remove(groups.size()-1);
        return 0;
    }
    return 1;

}

int MPF::setGroup(pagesGroup* grp)
{
	if(groups.indexOf(grp) != -1 )
	{
		//if current group is set disconenct it....
		if(currentGroup != -1)
		{
			QObject::disconnect(groups.at(currentGroup), 0, 0, 0);
		}

		if(listGridLayout->itemAt(0))
		{

			//listGridLayout->removeItem(groups.at(currentGroup)->listGridLayout);
			//QLayoutItem * item = listGridLayout->takeAt(0);
			//delete item;
		}
		if(currentGroup != -1)
		{
			groups.at(currentGroup)->hideList();
			////groups.at(currentGroup)->listGridLayout->setParent(groups.at(currentGroup));
			//QLayoutItem* item =  listGridLayout->takeAt(0);
			//item->layout()->widget()->setHidden(true);

			//listGridLayout->itemAt(0)->layout()->widget()->setHidden(true);
			////groups.at(currentGroup)->setHidden(true);
			//listGridLayout->removeItem(listGridLayout->itemAt(0));
			//groups.at(currentGroup)->listGridLayout->setParent(groups.at(currentGroup));
			//groups.at(currentGroup)->setHidden(true);
			////listGridLayout->update();
			//groups.at(currentGroup)->setHidden(true);
			//groups.at(currentGroup)->listGridLayout->setParent(NULL);
			//groups.at(currentGroup)->setHidden(true);
		}
		currentGroup = groups.indexOf(grp);
		grp->showList();
		// set list and messages widgets ...
		grp->listGridLayout->setParent(NULL);
		listGridLayout->addLayout(grp->listGridLayout);


		// connect to groups signals
		connect(grp, SIGNAL(newMessage(QString,int, int, pagesGroup*)), this, SLOT(addMessage(QString,int)), Qt::QueuedConnection);
		connect(grp, SIGNAL(clearPageMessages()), this, SLOT(clearMessages()), Qt::QueuedConnection);
		connect(grp, SIGNAL(pageReady(bool, int, pagesGroup*)), nextPushButton, SLOT(setEnabled(bool)));
		connect(grp, SIGNAL(pageReady(bool, int, pagesGroup*)), nextPushButton, SLOT(setFocus()));
		//prevPage();
		changePage(0);
	}
	else
	{
		return 1;
	}

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
	else if (type == WARNING)
	{
	  icon= icon.replace("PATH", getApplicationFile("/Icons/warning.png"));
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
