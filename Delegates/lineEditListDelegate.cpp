/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#include "lineEditListDelegate.hpp"

lineEditListDelegate::lineEditListDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

/*
void lineEditListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                  const QModelIndex &index) const
{
    //Get item data
    QString text = index.data(Qt::DisplayRole).toString();

    // fill style options with item data
    const QStyle *style = QApplication::style();
    QStyleOptionButton opt;
    opt.state |= QStyle::State_Enabled;
    opt.text = text;
    opt.rect = option.rect;

    // draw item data as CheckBox
    //style->drawControl(QStyle::CT_LineEdit,&opt,painter);
    style->drawPrimitive(QStyle::PE_PanelLineEdit, opt, painter, this);
}*/

QWidget* lineEditListDelegate::createEditor(QWidget *parent,
             const QStyleOptionViewItem & option ,
             const QModelIndex & index ) const
{
    // create check box as our editor
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void lineEditListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //set editor data
    QLineEdit *myEditor = static_cast<QLineEdit*>(editor);
    myEditor->setText(index.data(Qt::DisplayRole).toString());
}

void lineEditListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                        const QModelIndex &index) const
{
    //get the value from the editor (CheckBox)
    QLineEdit *myEditor = static_cast<QLineEdit*>(editor);

    //set model data
    QMap<int,QVariant> data;
    data.insert(Qt::DisplayRole,myEditor->text());
    model->setItemData(index,data);

    emit itemStatusChanged(editor);
}


void lineEditListDelegate::updateEditorGeometry(QWidget *editor,
const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    editor->setGeometry(option.rect);
}
