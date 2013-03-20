/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#include "loadingpage.hpp"
#include "ui_loadingPage.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <iostream>

using namespace std;

loadingPage::loadingPage(QWidget *parent) :
    pageBase(parent)
{
    Ui_loadingPage::setupUi(this);

    pageName = tr("Loading Page");
    pageHelpMessage = tr("");

    iconLabel->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    messageLabel->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    messageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    messageLabel->setTextFormat(Qt::AutoText);
    //messageLabel->setFont(label->font());
    //label->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    //label->setText(tr("الملك"));

    iconSize.setHeight(-1);
    iconSize.setWidth(-1);
    iconMovie = new QMovie(this);
}

#include <unistd.h>

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
    iconLabel->setPixmap(QPixmap(getApplicationFile(file)));
    iconLabel->setScaledContents(true);
    setIconSize(iconLabel->pixmap()->size());
    iconLabel->resize(iconSize);


    /*
    QString icon;

    if(iconSize.width() == -1 && iconSize.height() == -1)
    {
        icon = "<img src=\"" + file + "\" width="+ QString::number(iconSize.width()) +
                "height=" + QString::number(iconSize.height()) + ">";
    }
    else
    {
        icon = "<img src=\"" + file + "\">";
    }
    iconLabel->setText(icon);*/



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
    iconLabel->resize(iconSize);
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
    pAnimation = new QPropertyAnimation(this);

    if(effect == FADEIN)
    {
        QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(this); // make sure to create using new, since effect has to be alive as long as the target widget is using it.
        opacityEffect->setOpacity(0);
        pAnimation->setTargetObject(opacityEffect);
        pAnimation->setPropertyName("opacity");
        pAnimation->setStartValue(opacityEffect->opacity());
        pAnimation->setEndValue(1);
        widget->setGraphicsEffect(opacityEffect);
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

    pAnimation->setDuration(3000);
    //pAnimation->setEasingCurve(QEasingCurve::OutQuad);
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    return 0;
}

int loadingPage::initAll()
{
    pAnimation->setDuration(3000);
    //pAnimation->setEasingCurve(QEasingCurve::OutQuad);
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);

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

