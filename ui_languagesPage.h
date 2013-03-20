/********************************************************************************
** Form generated from reading UI file 'languagesPage.ui'
**
** Created: Wed Dec 19 07:53:06 2012
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LANGUAGESPAGE_H
#define UI_LANGUAGESPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_languagesPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *languagesListWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *okPushButton;

    void setupUi(QWidget *languagesPage)
    {
        if (languagesPage->objectName().isEmpty())
            languagesPage->setObjectName(QString::fromUtf8("languagesPage"));
        languagesPage->resize(400, 300);
        verticalLayout = new QVBoxLayout(languagesPage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(languagesPage);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        languagesListWidget = new QListWidget(languagesPage);
        languagesListWidget->setObjectName(QString::fromUtf8("languagesListWidget"));

        verticalLayout->addWidget(languagesListWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        okPushButton = new QPushButton(languagesPage);
        okPushButton->setObjectName(QString::fromUtf8("okPushButton"));

        horizontalLayout->addWidget(okPushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(languagesPage);

        QMetaObject::connectSlotsByName(languagesPage);
    } // setupUi

    void retranslateUi(QWidget *languagesPage)
    {
        languagesPage->setWindowTitle(QApplication::translate("languagesPage", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("languagesPage", "Available languages :", 0, QApplication::UnicodeUTF8));
        okPushButton->setText(QApplication::translate("languagesPage", "&0k", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class languagesPage: public Ui_languagesPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LANGUAGESPAGE_H
