/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#include "Delegates/comboBoxListDelegate.hpp"


ComboBoxListDelegate::ComboBoxListDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}


void ComboBoxListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                  const QModelIndex &index) const
{
    //Get item data
    bool value = index.data(Qt::UserRole).toBool();
    QString text = index.data(Qt::DisplayRole).toString();

    // fill style options with item data
    const QStyle *style = QApplication::style();
    QStyleOptionButton opt;
    opt.state |= value ? QStyle::State_On : QStyle::State_Off;
    opt.state |= QStyle::State_Enabled;
    opt.text = text;
    opt.rect = option.rect;

    // draw item data as CheckBox
    style->drawControl(QStyle::CE_ComboBoxLabel,&opt,painter);
}

QWidget* ComboBoxListDelegate::createEditor(QWidget *parent,
             const QStyleOptionViewItem & option ,
             const QModelIndex & index ) const
{
    // create check box as our editor
    QComboBox *editor = new QComboBox(parent);
    return editor;
}

void ComboBoxListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //set editor data
    QComboBox *myEditor = static_cast<QComboBox*>(editor);
    ////myEditor->setText(index.data(Qt::DisplayRole).toString());
    ////myEditor->setChecked(index.data(Qt::UserRole).toBool());
}

void ComboBoxListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                        const QModelIndex &index) const
{
    //get the value from the editor (CheckBox)
    QComboBox *myEditor = static_cast<QComboBox*>(editor);
    ////bool value = myEditor->isChecked();

    //set model data
    QMap<int,QVariant> data;
    ////data.insert(Qt::DisplayRole,myEditor->text());
    ////data.insert(Qt::UserRole,value);
    model->setItemData(index,data);

    emit itemStatusChanged(editor);
}


void ComboBoxListDelegate::updateEditorGeometry(QWidget *editor,
const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    editor->setGeometry(option.rect);
}
