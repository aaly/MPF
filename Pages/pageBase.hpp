/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#ifndef PAGEBASE_HPP
#define PAGEBASE_HPP

#include <QLocale>

#include <QWidget>
#include <QTextCodec>
#include <QCoreApplication>
#include <QFile>
#include <QVector>
#include <QPair>


#include <iostream>
using namespace std;

#include <QTranslator>

static QTranslator* qtTranslator = new QTranslator();



static int debug(QString msg)
{
    cout << msg.toStdString() << endl;
    return 0;
}

static QString lang  = QLocale::system().name().mid(0, QLocale::system().name().indexOf('_'));

static QString getApplicationFile(QString file)
{
    debug(QCoreApplication::tr("loading application file")+QCoreApplication::applicationDirPath()+file);
    return QCoreApplication::applicationDirPath()+file;
    //return ":"+file;
}

static QString getApplicationLanguageFile(QString file)
{
    file = getApplicationFile(file);

    if (!QFile::exists(file+"."+lang))
    {
        //debug(QCoreApplication::tr("loading language file")+file+".en");
        return file+".en";
    }
    //debug(QCoreApplication::tr("loading language file")+file+"."+lang);
    return file+"."+lang;
}

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

public:
    int                         Depend(QString name, pageBase*dep);
    //static int                  index;
    QString                     pageName;
    QString                     pageHelpMessage;
    QString                     pageGroup;
    QString                     pageIcon;

    bool                        init;
    pageBase*                   getDependency(QString);
    int                         setStatus(QString, int);
    QVector< QPair<QString, int> > statuses;

    //static QVector<pageBase*>   pages;
signals:
    void    Status(const QString&, int);
    //void    Busy();
    void    Done(bool);
    void    Ready();
    void    Abort(QString);
    void    Debug(QString);
    void    NotReady();
public slots:
    virtual int     finishUp();
private:
    QVector< QPair<QString, pageBase*> > dependencies;
};

#endif // PAGEBASE_HPP
