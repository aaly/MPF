/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#ifndef CHECKBOXLISTDELEGATE_HPP
#define CHECKBOXLISTDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QStyle>
#include <QApplication>
#include <QCheckBox>

class CheckBoxListDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    CheckBoxListDelegate(QObject *parent = 0);
    void    paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget*createEditor(QWidget *parent, const QStyleOptionViewItem & option , const QModelIndex & index ) const;
    void    setEditorData(QWidget *editor, const QModelIndex &index) const;
    void    setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void    updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
signals:
    void    itemStatusChanged(QWidget*) const;
 };

#endif // CHECKBOXLISTDELEGATE_HPP


