/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#include "richTextDelegate.hpp"

richTextDelegate::richTextDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

#include <QPainter>
#include <QAbstractTextDocumentLayout>

/*
void richTextDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    painter->save();
    QTextDocument qtd;
    QVariant data = index.data(Qt::DisplayRole);
    qtd.setHtml(data.toString());
    qtd.drawContents(painter);
    painter->restore();

    QRect rect = option.rect;
    //browser.document()->setPageSize( rect.size());
    QTextDocument qtd;

    QVariant data = index.data(Qt::DisplayRole);
    qtd.setHtml(data.toString());
    qtd.setPageSize(rect.size());

    //painter->translate(option.rect.topLeft());
    painter->translate(option.rect.center());
    qtd.drawContents(painter, rect);
    //qtd.documentLayout()->draw(painter, context);
    painter->translate(-option.rect.center());

}
*/

QSize richTextDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QStyleOptionViewItemV4 newOption(option);
    initStyleOption(&newOption, index);

    QTextDocument doc;
    doc.setHtml(newOption.text);

    return QSize(doc.size().width(), doc.size().height());
}

// http://qt-project.org/forums/viewthread/12709
void richTextDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV4 newOption(option);
    initStyleOption(&newOption, index);

    painter->save();

    QTextDocument doc;
    doc.setHtml(newOption.text);

    newOption.text = "";
    newOption.state &= ~QStyle::State_Selected;
    newOption.state &= ~QStyle::State_HasFocus;
    newOption.state &= ~QStyle::State_MouseOver;

    newOption.widget->style()->drawControl(QStyle::CE_ItemViewItem, &newOption, painter);

    //painter->translate(newOption.rect.left() + 20, newOption.rect.top());
    painter->translate(newOption.rect.left(), newOption.rect.top());
    QRect clip(0, 0, newOption.rect.width(), newOption.rect.height());
    doc.drawContents(painter, clip);

    painter->restore();

   // QStyledItemDelegate::paint(painter, newOption, index);
}


