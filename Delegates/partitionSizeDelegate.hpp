/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#ifndef PARITIONSIZEDELEGATE_H
#define PARITIONSIZEDELEGATE_H

#include <QtWidgets/QStyledItemDelegate>
#include <QSize>
#include <QPainter>
#include <QObject>
#include <QtWidgets/QStyleOptionViewItem>
#include <QModelIndex>

class partitionSizeDelegate : public QStyledItemDelegate
{
    Q_OBJECT // maybe needed later

    public:
	partitionSizeDelegate( QObject *parent = 0 );
	//const void paint(   QPainter *painter, const QStyleOptionViewItem &option,
	//		    const QModelIndex &index );
	void    paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	//const QSize sizeHint(	const QStyleOptionViewItem &option,
	//			const QModelIndex &index ) const;

	QSize sizeHint(const QStyleOptionViewItem &option,
				   const QModelIndex &index) const;
};

#endif // PARITIONSIZEDELEGATE_H
