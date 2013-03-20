/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#ifndef MPF_H
#define MPF_H

#include <QMainWindow>
#include "ui_MPF.h"
#include "Pages/pageBase.hpp"
#include "Pages/loadingpage.hpp"

enum widgetEffects
{
    FADING =0,
    RESIZING
};

class MPF : public QMainWindow, private Ui::MPF
{
    Q_OBJECT


public:
	explicit MPF(QWidget *parent = 0);

	~MPF();
	int     addPage(pageBase* page);

private:

    int     messageIconWidth;
    int     messageIconHeight;
    bool    pageReady;
    int     currentPage;
    QVector<pageBase*>* pages;



    int     step;


    loadingPage*    loadingpage;

    int         loadMessages(pageBase*);
    int         clearMessages();

    void        changeEvent(QEvent* event);
    int         generateList();
    bool        helpMaximized;
    bool        nextAlreadyEnabled;

public slots:
    int     addMessage(QString, int);
    int     showHelp();
    int     nextPage();
    int     prevPage();
    int     showFullHelp();



private slots:
    int animateWidget(QWidget*, bool, int);
    int     changePage();

    int     updateLayout(QString);


};

#endif // MPF_H
