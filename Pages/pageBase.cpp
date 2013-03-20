/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#include "pageBase.hpp"

pageBase::pageBase(QWidget *parent) :
    QWidget(parent)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    if ( lang == "C" || lang == "POSIX")
    {
        lang="en";
    }
	init = false;
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
        emit Status(msg, type);
        statuses.push_back(QPair<QString, int>(msg, type));
        return 0;
 }

 int     pageBase::finishUp()
 {
     return 0;
 }
