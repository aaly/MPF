#include "groupSelector.hpp"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QDesktopWidget>

groupSelector::groupSelector(QWidget *parent) :	pageBase(parent)
{
	setupUi(this);
	mpf = NULL;
	//setHidden(true);
}

groupSelector::~groupSelector()
{
	if(mpf == NULL)
	{
		delete mpf;
	}
	mpf = NULL;
}


int groupSelector::setTitle(QString)
{
	return 0;
}

int groupSelector::setIcon(QString iconpath)
{
	return 0;
}

int groupSelector::setIconSize(unsigned int, unsigned int)
{
	return 0;
}

int groupSelector::setMPF(MPF* frame)
{
	mpf = frame;
	return 0;
}



int groupSelector::setGroup()
{
	if(mpf == NULL)
	{
		return 1;
	}
	pagesGroup* group = groups.at(groupsLayout->indexOf((QWidget*)sender()));
    mpf->cleanLastGroup();
	mpf->addGroup(group);
	mpf->setGroup(group);
	return 0;
}

int groupSelector::addGroup(pagesGroup* group)
{
	groups.push_back(group);
	QPushButton* button = new QPushButton(this);
	button->setText(group->getTitle());
	button->setIcon(group->getIcon());
	button->resize(200, 100);
	button->setFixedHeight(QApplication::desktop()->size().height()/6);
	button->setIconSize(QSize(button->size().height()/4,button->size().height()/4));
    //button->setStyleSheet("text-align:center;");
	//connect(button, SIGNAL(clicked()), this, SLOT(setGroup(group)));
	connect(button, SIGNAL(clicked()), this, SLOT(setGroup()));
	groupsLayout->addWidget(button);
	return 0;
}

int groupSelector::removeGroup(pagesGroup* group)
{
	int i = groups.indexOf(group);
	groups.remove(i);
	//diconnect
	delete (QPushButton*)groupsLayout->takeAt(i)->widget();
	return 0;
}

int groupSelector::Focus()
{
	groupsLayout->itemAt(0)->widget()->setFocus();
	return 0;
}

void groupSelector::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        for (int i =0; i < groups.count(); i++)
        {
            ((QPushButton*)groupsLayout->itemAt(i)->widget())->setLayoutDirection(Qt::LeftToRight);
            ((QPushButton*)groupsLayout->itemAt(i)->widget())->setText(QApplication::translate("Groups", groups.at(i)->getTitle().toStdString().c_str(), 0));


        }
        retranslateUi(this);
    }
}
