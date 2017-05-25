#ifndef GROUPSELECTOR_HPP
#define GROUPSELECTOR_HPP

#include <QtWidgets/QWidget>
#include "../ui_groupSelector.h"
#include "../MPF.h"
#include "pagesgroup.hpp"
#include "pageBase.hpp"
#include <QIcon>


class groupSelector : public pageBase, private Ui::groupSelector
{
		Q_OBJECT
		
	public:
		explicit groupSelector(QWidget *parent = 0);
		~groupSelector();
		int setTitle(QString);
		int setIcon(QString iconpath);
		int setIconSize(unsigned int, unsigned int);
		int addGroup(pagesGroup* group);
		int removeGroup(pagesGroup* group);
		int setMPF(MPF* frame);
		int Focus();
	private:
		QString title;
		QIcon icon;
		QSize   iconSize;
		QVector<pagesGroup*> groups;
		MPF* mpf;

        void        changeEvent(QEvent* event);

	public slots:
		int setGroup();
};

#endif // GROUPSELECTOR_HPP
