/********************************************************************************
** Form generated from reading UI file 'loadingPage.ui'
**
** Created: Wed Dec 19 07:53:06 2012
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADINGPAGE_H
#define UI_LOADINGPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loadingPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *iconLabel;
    QLabel *messageLabel;

    void setupUi(QWidget *loadingPage)
    {
        if (loadingPage->objectName().isEmpty())
            loadingPage->setObjectName(QString::fromUtf8("loadingPage"));
        loadingPage->resize(625, 404);
        verticalLayout = new QVBoxLayout(loadingPage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        iconLabel = new QLabel(loadingPage);
        iconLabel->setObjectName(QString::fromUtf8("iconLabel"));

        verticalLayout->addWidget(iconLabel);

        messageLabel = new QLabel(loadingPage);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));

        verticalLayout->addWidget(messageLabel);


        retranslateUi(loadingPage);

        QMetaObject::connectSlotsByName(loadingPage);
    } // setupUi

    void retranslateUi(QWidget *loadingPage)
    {
        loadingPage->setWindowTitle(QApplication::translate("loadingPage", "Form", 0, QApplication::UnicodeUTF8));
        iconLabel->setText(QString());
        messageLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class loadingPage: public Ui_loadingPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADINGPAGE_H
