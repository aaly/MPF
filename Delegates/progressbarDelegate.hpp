/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#ifndef PROGRESSBARDELEGATE_HPP
#define PROGRESSBARDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QStyle>
#include <QApplication>
#include <QProgressBar>



class progressbarDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    progressbarDelegate(QObject *parent = 0);
    void    paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget*createEditor(QWidget *parent, const QStyleOptionViewItem & option , const QModelIndex & index ) const;
    void    setEditorData(QWidget *editor, const QModelIndex &index) const;
    void    setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void    updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
signals:
    void    itemStatusChanged(QWidget*) const;
 };
#endif // PROGRESSBARDELEGATE_HPP
