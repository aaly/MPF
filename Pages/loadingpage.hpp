/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#ifndef LOADINGPAGE_HPP
#define LOADINGPAGE_HPP


#include "pageBase.hpp"
#include "../ui_loadingPage.h"
#include <QSize>
#include <QMovie>
#include <QPropertyAnimation>

enum AnimationEffect
{
    SLIDERIGHT =0,
    SLIDELEFT,
    SLIDEUP,
    SLIDEDOWN,
    FADEIN
};

enum iconPlace
{
    TOP =0,
    BOTTOM,
    RIGHT,
    LEFT
};

class loadingPage : public pageBase, private Ui::loadingPage
{
    Q_OBJECT

public:
    explicit loadingPage(QWidget *parent = 0);
    ~loadingPage();

    int     setIcon(QString);
    int     setMessage(QString);
    QString getMessage();
    int     setMessageEffect(int);
    int     getMessageEffect();
    int     setIconSize(QSize);
    QSize   getIconSize();
    int     setIconEffect(int);
    int     getIconEffect();
    int     setIconAlignment(int);
    int     getIconAlignment();
    int     resetLayout();
    int     initAll();
    int     setMessageSize(unsigned int size);


private:
    QSize   iconSize;
    int     iconAlignment;
    int     iconEffect;
    QMovie* iconMovie;

    int     messageEffect;
    int     setWidgetEffect(QWidget*, int);

    void changeEvent(QEvent* event);
    QString iconFile;

    int     updateIcon();

    QVector<QPropertyAnimation*> animations;


signals:
    void finished();
    void started();

public slots:
    int     finish();
};

#endif // LOADINGPAGE_HPP
