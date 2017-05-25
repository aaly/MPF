/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#ifndef PAGEBASE_HPP
#define PAGEBASE_HPP

#include <QLocale>

#include <QtWidgets/QWidget>
#include <QTextCodec>
#include <QCoreApplication>
#include <QFile>
#include <QVector>
#include <QPair>


#include <iostream>
using namespace std;

#include <QTranslator>

static QTranslator* qtTranslator = new QTranslator();
static QTranslator* qtTranslator2 = new QTranslator();



static int debug(QString msg)
{
	cout << "[Debug] " << msg.toStdString() << endl;
    return 0;
}

extern QString lang;

QString getApplicationFile(QString file);
QString getApplicationLanguageFile(QString file);

enum messageType
{
    INFORMATION=0,
    WARNING,
    CRITICAL,
    ERROR,
    STATUS,
    BUSY,
    QUIT
};


class pageBase : public QWidget
{
    Q_OBJECT
public:
    explicit pageBase(QWidget *parent = 0);
    //int         getCurrentStep();
    //pageBase*   getCurrentPage();
    QString       getPageName();
	virtual int           initAll() { return init = true;}

	int                         Depend(QString name, pageBase*dep);
    //static int                  index;
    QString                     pageName;
    QString                     pageHelpMessage;
    QString                     pageGroup;
    QString                     pageIcon;
    QString                     pageType;

    bool                        init;
	bool                        done;
    pageBase*                   getDependency(QString);
    int                         setStatus(QString, int);
    QVector< QPair<QString, int> > statuses;
    

    //static QVector<pageBase*>   pages;
signals:
	void    Status(pageBase*, const QString&, int);
    //void    Busy();
	void    Done(pageBase*, bool);
    void    Ready();
    void    Abort(QString);
    void    Debug(QString);
    void    NotReady();
    void    clearMessages();
public slots:
    virtual int     finishUp();
    virtual int     Clean();
private:
    QVector< QPair<QString, pageBase*> > dependencies;
protected:
	int                         setDone(bool cond);

};

#endif // PAGEBASE_HPP
