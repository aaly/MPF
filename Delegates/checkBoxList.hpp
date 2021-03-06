/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#ifndef CHECKBOXLIST_H
#define CHECKBOXLIST_H

#include "checkBoxListDelegate.hpp"
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QAbstractItemView>
#include <QEvent>
#include <QtWidgets/QStylePainter>

class CheckBoxList: public QComboBox
{
        Q_OBJECT;

public:
        CheckBoxList(QWidget *widget = 0);
        virtual ~CheckBoxList();
        bool                        eventFilter(QObject *object, QEvent *event);
        virtual void                paintEvent(QPaintEvent *);
        void                        SetDisplayText(QString text);
        QString                     GetDisplayText() const;
        void                        addItem ( const QString &, const QVariant & );
        QVector<QString>           getSelectedItems();
        QVector<QString>            getunSelectedItems();
        int                         setAutoUpdateDisplayText(bool);
        bool                        getAutoUpdateDisplayText();

private:
        CheckBoxListDelegate*       checkBoxListDelegate;
        QVector<QString>            originalSelectedItems;
        QVector<QString>            selectedItems;
        QVector<QString>            unSelectedItems;
        QString                     m_DisplayText;
        bool                        autoUpdateDisplayText;
        int                         matchComboListItem(const QVector<QString>&, const QString&);
        bool                	    itemsUpdated;
private slots:
	int			    updateCurrentSelection(QWidget*);
	int			    updateCurrentSelection();
	int			    updateDisplayText();
signals:
	void			    sendCurrentSelection(QStringList);
	void			    currentItemsUpdated();
public slots:
    int			    resetSelection();
    bool            selectAll(bool);
};
#endif // CHECKBOXLIST_H
