/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#include "loadingpage.hpp"
#include "ui_loadingPage.h"
#include <QPropertyAnimation>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <iostream>

using namespace std;

loadingPage::loadingPage(QWidget *parent) :
    pageBase(parent)
{
    setupUi(this);

    pageName = tr("Loading Page");
    pageHelpMessage = tr("");

    iconLabel->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    messageLabel->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    messageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    messageLabel->setTextFormat(Qt::AutoText);
    //messageLabel->setFont(label->font());
    //label->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

    iconSize.setHeight(-1);
    iconSize.setWidth(-1);
    iconMovie = new QMovie(this);

    messageLabel->setScaledContents(true);
}

int loadingPage::finish()
{
    setWidgetEffect(messageLabel, SLIDELEFT);
    emit finished();
    return 0;
}

loadingPage::~loadingPage()
{
}

int loadingPage::setIcon(QString file)
{
    //iconLabel->setPixmap(QPixmap(getApplicationFile(file)));
    //iconLabel->setScaledContents(true);
    //setIconSize(iconLabel->pixmap()->size());
    //iconLabel->resize(iconSize);
    QString icon;

    /*
    if(iconSize.width() != -1 && iconSize.height() != -1)
    {
        icon = "<img src=\"" + file + "\" width="+ QString::number(iconSize.width()) +
                "height=" + QString::number(iconSize.height()) + " \>";
    }
    else
    {
        icon = "<img src=\"" + file + "\">";
    }*/
    iconFile = file;
    iconLabel->setText(QString ("<img align=absmiddle height="+QString::number(iconSize.height()) + " width="+QString::number(iconSize.width())+" src=\"PATH\">").replace("PATH", file));
    return 0;
}

int loadingPage::updateIcon()
{
    iconLabel->setText(QString ("<img align=absmiddle height="+QString::number(iconSize.height()) + " width="+QString::number(iconSize.width())+" src=\"PATH\">").replace("PATH", iconFile));
    return 0;
}

int loadingPage::setMessage(QString message)
{
    if (message== "")
    {
        return 1;
    }

    messageLabel->setText(message);
    messageLabel->adjustSize();
    return 0;
}

int loadingPage::setMessageSize(unsigned int size)
{
    messageLabel->setStyleSheet("font: "+QString::number(size)+"px;");
    //QFont f( "Arial", size, QFont::Bold);
    //messageLabel->setFont( f);
    return 0;
}

QString loadingPage::getMessage()
{
    return messageLabel->text();
}

int loadingPage::setMessageEffect(int effect)
{
    setWidgetEffect(messageLabel, effect);
    return 0;
}

int loadingPage::getMessageEffect()
{
    return messageEffect;
}


int loadingPage::setIconSize(QSize size)
{
    iconSize = size;
    updateIcon();
    resetLayout();
    return 0;
}

QSize loadingPage::getIconSize()
{
    return iconSize;
}

int loadingPage::setIconEffect(int effect)
{
    iconEffect = effect;
    setWidgetEffect(iconLabel, effect);
    return 0;
}

int loadingPage::getIconEffect()
{
    return iconEffect;
}

int loadingPage::setIconAlignment(int alignment)
{
    iconAlignment = alignment;
    return 0;
}

int loadingPage::getIconAlignment()
{
    return iconAlignment;
}


int loadingPage::setWidgetEffect(QWidget* widget, int effect)
{
    //pAnimation = new QPropertyAnimation(this);

    QPropertyAnimation* pAnimation = new QPropertyAnimation(this);
    animations.push_back(pAnimation);
    if(effect == FADEIN)
    {
        QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(widget); // make sure to create using new, since effect has to be alive as long as the target widget is using it.
        opacityEffect->setOpacity(0);
        pAnimation->setTargetObject(opacityEffect);
        pAnimation->setPropertyName("opacity");
        pAnimation->setStartValue(opacityEffect->opacity());
        pAnimation->setEndValue(1);
        widget->setGraphicsEffect(opacityEffect);
        //widget->graphicsEffect()->
    }
    else
    {
        resetLayout();
        pAnimation->setTargetObject(messageLabel);
        pAnimation->setPropertyName("pos");
        QPoint point = messageLabel->pos();
        point.setX(point.x()-iconSize.width());
        pAnimation->setEndValue(point);

        if (effect == SLIDERIGHT)
        {
            point.setX(-1*messageLabel->width());
        }
        else if (effect == SLIDELEFT)
        {
            //geo.setX(this->geometry().x()+this->geometry().width()+geo.width());

        }
        pAnimation->setStartValue(point);
    }
    return 0;
}

int loadingPage::initAll()
{
    for (unsigned int i =0; i < animations.size(); i++)
    {
        animations.at(i)->setDuration(5000);
        animations.at(i)->start();
        //pAnimation->setEasingCurve(QEasingCurve::OutQuad);
        //pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    }

    pageBase::initAll();
    return 0;
}

int loadingPage::resetLayout()
{
    iconLabel->move((width()+iconSize.width()/2), (height()));
    messageLabel->move(width()-messageLabel->width()/2, (height()+iconLabel->height()));

    return 0;
}

void loadingPage::changeEvent(QEvent* event)
{


    if (event->type() == QEvent::LanguageChange)
    {
        Ui_loadingPage::retranslateUi(this);
    }

    pageBase::changeEvent(event);

}

