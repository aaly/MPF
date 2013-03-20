/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#ifndef RICHTEXTDELEGATE_HPP
#define RICHTEXTDELEGATE_HPP


#include <QStyledItemDelegate>
#include <QTextDocument>


class richTextDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit richTextDelegate(QObject *parent = 0);

    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    
signals:
    
public slots:
    
};

#endif // RICHTEXTDELEGATE_HPP
