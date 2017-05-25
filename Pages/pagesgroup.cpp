#include "pagesgroup.hpp"
#include <QtWidgets/QLabel>
#include <QLocale>
#include <QtWidgets/qapplication.h>

pagesGroup::pagesGroup(QWidget *parent) :QWidget(parent)
{
	currentPage = 0;
	hidden = false;
	listGridLayout = new QGridLayout();
	//setHidden(true);
}

pagesGroup::~pagesGroup()
{
	//delete listGridLayout;
}


int pagesGroup::hideList()
{
	for (int i = 0; i < listGridLayout->rowCount(); i++)
	{
		for (int k = 0; k < listGridLayout->columnCount(); k++)
		{
			listGridLayout->itemAtPosition(i, k)->widget()->setHidden(true);
		}
	}
	hidden = true;
	return 0;
}

int pagesGroup::showList()
{
	for (int i = 0; i < listGridLayout->rowCount(); i++)
	{
		for (int k = 0; k < listGridLayout->columnCount(); k++)
		{
			listGridLayout->itemAtPosition(i, k)->widget()->setHidden(false);
		}
	}
	hidden = false;
	return 0;
}

int pagesGroup::addPage(pageBase* page)
{
	if (page == NULL)
	{
		return 1;
	}
	pages.push_back(page);

	if (page->pageType == "GROUPSELECTOR")
	{
		listGridLayout->addWidget(new QLabel(QString ("<p style=\"img { image-rendering: auto; }\"> <img align=absmiddle height=64 width=64 src=\"PATH\"></p>").replace("PATH", page->pageIcon)), pages.count()-1, 0);
	}
	else
	{
		listGridLayout->addWidget(new QLabel(QString ("<p style=\"img { image-rendering: auto; }\"> <img align=absmiddle height=32 width=32 src=\"PATH\"></p>").replace("PATH", page->pageIcon)), pages.count()-1, 0);
	}
	listGridLayout->addWidget(new QLabel(QString(page->pageName)), pages.count()-1, 1);

	//connect(page, SIGNAL(Status(QString,int)), this, SLOT(addMessage(QString,int)), Qt::QueuedConnection);
	//connect(page, SIGNAL(Status(QString,int)), this, SLOT(processNewMessage(QString,int, (int)pages.size()-1)), Qt::QueuedConnection);
	connect(page, SIGNAL(Status(pageBase*, QString,int)), this, SLOT(processNewMessage(pageBase*, QString,int)), Qt::QueuedConnection);

	//connect(page, SIGNAL(Status(QString,int)), this, SLOT(addMessage(QString,int)));
	//connect(page, SIGNAL(Done(bool)), nextPushButton, SLOT(setEnabled(bool)));
	//connect(page, SIGNAL(Ready()), this, SLOT(processPageReady(pageBase*, bool)));
	connect(page, SIGNAL(Done(pageBase*, bool)), this, SLOT(processPageReady(pageBase*, bool)));
	connect(page, SIGNAL(clearMessages()), this, SLOT(clearMessages()));

	
	
	//connect(pages->at(pages->count()-1), SIGNAL(Ready()), loadingpage, SLOT(finish()));

	return 0;
}


int pagesGroup::clearMessages()
{
	emit clearPageMessages();
}

int pagesGroup::generateList()
{
	cout << "chengeeven2222t" << endl;
	for (int i =0; i < pages.count(); i++)
	{
		QLayoutItem* item0 = listGridLayout->itemAtPosition(i, 0);
		QLayoutItem* item1 = listGridLayout->itemAtPosition(i, 1);

		listGridLayout->removeItem(item0);
		listGridLayout->removeItem(item1);

		delete item0->widget();
		delete item1->widget();


		listGridLayout->addWidget(new QLabel(QString ("<img align=absmiddle height=30 width=30 src=\"PATH\">").replace("PATH", pages.at(i)->pageIcon)), i, 0);
		listGridLayout->addWidget(new QLabel(trUtf8(pages.at(i)->pageName.toStdString().data())), i, 1);

	}
	return 0;
}

int pagesGroup::processPageReady(pageBase*page ,bool cond)
{
	emit pageReady(cond, pages.indexOf(page), this);
	return 0;
}

int pagesGroup::processNewMessage(pageBase* page, QString message, int type)
{
	//find which page
	emit newMessage(message, type, pages.indexOf(page), this);
	return 0;
}

pageBase* pagesGroup::getCurrentPage()
{
	return pages.at(currentPage);
}


void pagesGroup::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{

		for (int i =0; i < pages.count(); i++)
		{
			QLabel* item1 = (QLabel*) listGridLayout->itemAtPosition(i, 1)->widget();
            item1->setText(QApplication::translate("Pages", pages.at(i)->pageName.toStdString().c_str(), 0));



			//listGridLayout->removeItem(item0);
			//listGridLayout->removeItem(item1);

			//delete item0->widget();
			//delete item1->widget();


			//QLabel* img = new QLabel(QString ("<img align=absmiddle height=30 width=30 src=\"PATH\">").replace("PATH", pages.at(i)->pageIcon));
			//img->setHidden(hidden);
			////QLabel* label = new QLabel(trUtf8(pages.at(i)->pageName.toStdString().data()),listGridLayout);
			//listGridLayout->addWidget(img, i, 0);
			////listGridLayout->addWidget(label, i, 1);
			//label->setHidden(hidden);
			//listGridLayout->itemAtPosition(i, 0)->widget()->setHidden(hidden);
			//listGridLayout->addWidget(new QLabel(trUtf8(pages.at(i)->pageName.toStdString().data())), i, 1);
			//listGridLayout->itemAtPosition(i, 1)->widget()->setHidden(hidden);
		}
	}
}


int pagesGroup::setTitle(QString name)
{
	title = name;
	return 0;
}

int pagesGroup::setIcon(QString iconpath)
{
	icon = QIcon(iconpath);
	return 0;
}

int pagesGroup::setHidden(bool cond)
{
	hidden = cond;
	return 0;
}

bool pagesGroup::isHidden()
{
	return hidden;
}


QString pagesGroup::getTitle()
{
	return title;
}

QIcon pagesGroup::getIcon()
{
	return icon;
}
