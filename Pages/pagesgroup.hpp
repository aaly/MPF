#ifndef PAGESGROUP_HPP
#define PAGESGROUP_HPP

#include <QObject>
#include "pageBase.hpp"
#include <QtWidgets/QLayoutItem>
#include <QtWidgets/QGridLayout>
#include <QIcon>

class pagesGroup : public QWidget
{
		Q_OBJECT
	public:
		explicit pagesGroup(QWidget *parent = 0);
		~pagesGroup();
		int setTitle(QString name);
		int setIcon(QString iconpath);
		int setHidden(bool cond);
		bool isHidden();
		int addPage(pageBase* page);
		//int removePage(pageBase*);
		QVector<pageBase*> pages;
		int     currentPage;
		int         generateList();

		QGridLayout* listGridLayout;

		pageBase* getCurrentPage();

		QString getTitle();
		QIcon getIcon();

		int hideList();
		int showList();
	signals:
		void pageReady(bool, int,pagesGroup*);
		void newMessage(QString,int, int, pagesGroup*);
		int clearPageMessages();
	public slots:
		int processPageReady(pageBase* page, bool cond);
		int processNewMessage(pageBase* page, QString message, int type);
		int clearMessages();
	private:
		void        changeEvent(QEvent* event);

		QIcon icon;
		QString title;
		bool hidden;
		
};

#endif // PAGESGROUP_HPP
