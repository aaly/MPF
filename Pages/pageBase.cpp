/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#include "pageBase.hpp"

QString lang;

pageBase::pageBase(QWidget *parent) :
    QWidget(parent)
{
    lang  = QLocale::system().name().mid(0, QLocale::system().name().indexOf('_'));

    ////QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    if ( lang == "C" || lang == "POSIX")
    {
        lang="en";
    }
	init = false;
	done = false;
    //pages.push_back(this);
}

/*int pageBase::getCurrentStep()
{
    return step;
}*/

QString pageBase::getPageName()
{
    return pageName;
}

/*pageBase* pageBase::getCurrentPage()
{
    //return pages.at(step);
}*/

int pageBase::Depend(QString name, pageBase* dep)
{
    if (!dep)
    {
        return 1;
    }
    dependencies.push_back(QPair<QString, pageBase*>(name, dep));
    return 0;
}


 pageBase*  pageBase::getDependency(QString dep)
 {
     for (int i =0; i < dependencies.count(); i++)
     {
         if (dependencies.at(i).first == dep)
         {
             return dependencies.at(i).second;
         }
     }
 }

 int pageBase::setStatus(QString msg, int type)
 {
		emit Status(this, msg, type);
        statuses.push_back(QPair<QString, int>(msg, type));
        return 0;
 }

 int pageBase::finishUp()
 {
     return 0;
 }

 int pageBase::Clean()
 {
     return 0;
 }

 int pageBase::setDone(bool cond)
 {
	 done = cond;
	 emit Done(this, cond);
	 return cond;
 }




 QString getApplicationFile(QString file)
 {
     debug(QCoreApplication::tr("loading application file")+QCoreApplication::applicationDirPath()+file);
     return QCoreApplication::applicationDirPath()+file;
     //return ":"+file;
 }

  QString getApplicationLanguageFile(QString file)
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
