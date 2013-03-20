/********************************************************************************
** Form generated from reading UI file 'pageBase.ui'
**
** Created: Wed Dec 19 07:53:06 2012
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEBASE_H
#define UI_PAGEBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pageBase
{
public:
    QVBoxLayout *verticalLayout_2;

    void setupUi(QWidget *pageBase)
    {
        if (pageBase->objectName().isEmpty())
            pageBase->setObjectName(QString::fromUtf8("pageBase"));
        pageBase->resize(600, 365);
        verticalLayout_2 = new QVBoxLayout(pageBase);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        retranslateUi(pageBase);

        QMetaObject::connectSlotsByName(pageBase);
    } // setupUi

    void retranslateUi(QWidget *pageBase)
    {
        pageBase->setWindowTitle(QApplication::translate("pageBase", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class pageBase: public Ui_pageBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEBASE_H
