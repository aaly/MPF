/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#ifndef MPF_H
#define MPF_H

//#include <QMainWindow>
#include <QtWidgets/QMainWindow>
#include "ui_MPF.h"
#include "Pages/pageBase.hpp"
#include "Pages/loadingpage.hpp"
#include "Pages/pagesgroup.hpp"

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
	int     addGroup(pagesGroup* grp);
	int     setGroup(pagesGroup* grp);
    int     cleanLastGroup();


private:

    int     messageIconWidth;
    int     messageIconHeight;
	//int     currentPage;
	//QVector<pageBase*>* pages;





	int currentGroup;


	//loadingPage*    loadingpage;

	QVector<pagesGroup*> groups;
	int selectedGroup;


    int         loadMessages(pageBase*);

    void        changeEvent(QEvent* event);
    bool        helpMaximized;
    bool        nextAlreadyEnabled;

public slots:
    int     addMessage(QString, int);
    int     showHelp();
    int     nextPage();
    int     prevPage();
    int     showFullHelp();
    int     clearMessages();



private slots:
	int animateWidget(QWidget*, bool, int);
	int     changePage(int direction);
    int     updateLayout(QString);


};

#endif // MPF_H
