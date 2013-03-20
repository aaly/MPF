/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#include "progressbarDelegate.hpp"
#include <QFlag>

progressbarDelegate::progressbarDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}


void progressbarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
		  const QModelIndex &index) const
{
    //Get item data
    ////bool value = index.data(Qt::UserRole).toBool();
    ////QString text = index.data(Qt::DisplayRole).toString();

    // fill style options with item data
    const QStyle *style = QApplication::style();
    QStyleOptionProgressBarV2 opt;
    opt.state |= QStyle::State_Active;
    opt.state |= QStyle::State_Enabled;
    opt.maximum = 100;
    opt.minimum = 0;
    //opt.textAlignment = Qal
    opt.progress = index.data(Qt::UserRole).toInt();
    opt.text = index.data(Qt::UserRole).toString();
    opt.rect = option.rect;

    // draw item data as CheckBox
    style->drawControl(QStyle::CE_ProgressBar,&opt,painter);
}

QWidget* progressbarDelegate::createEditor(QWidget *parent,
	     const QStyleOptionViewItem & option ,
	     const QModelIndex & index ) const
{
    // create check box as our editor
    QProgressBar *editor = new QProgressBar(parent);
    return editor;
}

void progressbarDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //set editor data
    QProgressBar *myEditor = static_cast<QProgressBar*>(editor);
    myEditor->setValue(index.data(Qt::DisplayRole).toInt());
    //myEditor->setChecked(index.data(Qt::UserRole).toBool());
}

void progressbarDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
					const QModelIndex &index) const
{
    //get the value from the editor (CheckBox)
    QProgressBar *myEditor = static_cast<QProgressBar*>(editor);
    ////bool value = myEditor->isChecked();

    //set model data
    QMap<int,QVariant> data;
    data.insert(Qt::DisplayRole,QString(myEditor-> value()));
    ////data.insert(Qt::UserRole,value);
    model->setItemData(index,data);

    emit itemStatusChanged(editor);
}


void progressbarDelegate::updateEditorGeometry(QWidget *editor,
const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    editor->setGeometry(option.rect);
}
