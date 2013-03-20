/********************************************************************************
** Form generated from reading UI file 'MPF.ui'
**
** Created: Thu Feb 28 02:47:20 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MPF_H
#define UI_MPF_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MPF
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout;
    QLabel *meskLogoLabel;
    QLabel *stepsIconsLabel;
    QSpacerItem *verticalSpacer;
    QLabel *stepsTextLabel;
    QGridLayout *listGridLayout;
    QVBoxLayout *verticalLayout;
    QFrame *line_7;
    QSpacerItem *verticalSpacer_4;
    QPushButton *previousPushButton;
    QPushButton *nextPushButton;
    QPushButton *exitPushButton;
    QFrame *line;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *messagesVerticalLayout;
    QFrame *line_3;
    QTextEdit *helpTextEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *helpPushButton;
    QPushButton *fullHelpPushButton;
    QSpacerItem *horizontalSpacer;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MPF)
    {
        if (MPF->objectName().isEmpty())
            MPF->setObjectName(QString::fromUtf8("MPF"));
        MPF->resize(654, 512);
        centralWidget = new QWidget(MPF);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        meskLogoLabel = new QLabel(frame);
        meskLogoLabel->setObjectName(QString::fromUtf8("meskLogoLabel"));

        gridLayout->addWidget(meskLogoLabel, 0, 0, 1, 2);

        stepsIconsLabel = new QLabel(frame);
        stepsIconsLabel->setObjectName(QString::fromUtf8("stepsIconsLabel"));
        stepsIconsLabel->setFrameShape(QFrame::NoFrame);
        stepsIconsLabel->setFrameShadow(QFrame::Plain);

        gridLayout->addWidget(stepsIconsLabel, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 247, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);

        stepsTextLabel = new QLabel(frame);
        stepsTextLabel->setObjectName(QString::fromUtf8("stepsTextLabel"));
        stepsTextLabel->setFrameShape(QFrame::NoFrame);
        stepsTextLabel->setFrameShadow(QFrame::Plain);

        gridLayout->addWidget(stepsTextLabel, 1, 1, 1, 1);

        listGridLayout = new QGridLayout();
        listGridLayout->setSpacing(6);
        listGridLayout->setObjectName(QString::fromUtf8("listGridLayout"));

        gridLayout->addLayout(listGridLayout, 2, 0, 1, 2);

        gridLayout->setRowStretch(0, 2);

        verticalLayout_5->addLayout(gridLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        line_7 = new QFrame(frame);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_7);

        verticalSpacer_4 = new QSpacerItem(17, 38, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        previousPushButton = new QPushButton(frame);
        previousPushButton->setObjectName(QString::fromUtf8("previousPushButton"));

        verticalLayout->addWidget(previousPushButton);

        nextPushButton = new QPushButton(frame);
        nextPushButton->setObjectName(QString::fromUtf8("nextPushButton"));

        verticalLayout->addWidget(nextPushButton);

        exitPushButton = new QPushButton(frame);
        exitPushButton->setObjectName(QString::fromUtf8("exitPushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(6);
        sizePolicy2.setHeightForWidth(exitPushButton->sizePolicy().hasHeightForWidth());
        exitPushButton->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(exitPushButton);


        verticalLayout_5->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(verticalLayout_5);

        line = new QFrame(frame);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinAndMaxSize);
        scrollArea = new QScrollArea(frame);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 513, 292));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy3);
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        messagesVerticalLayout = new QVBoxLayout();
        messagesVerticalLayout->setSpacing(6);
        messagesVerticalLayout->setObjectName(QString::fromUtf8("messagesVerticalLayout"));

        verticalLayout_2->addLayout(messagesVerticalLayout);

        line_3 = new QFrame(frame);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_3);

        helpTextEdit = new QTextEdit(frame);
        helpTextEdit->setObjectName(QString::fromUtf8("helpTextEdit"));
        helpTextEdit->setEnabled(true);
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(170);
        sizePolicy4.setVerticalStretch(4);
        sizePolicy4.setHeightForWidth(helpTextEdit->sizePolicy().hasHeightForWidth());
        helpTextEdit->setSizePolicy(sizePolicy4);
        helpTextEdit->setMaximumSize(QSize(16777215, 100));
        helpTextEdit->setFrameShape(QFrame::NoFrame);
        helpTextEdit->setFrameShadow(QFrame::Plain);
        helpTextEdit->setReadOnly(true);

        verticalLayout_2->addWidget(helpTextEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        helpPushButton = new QPushButton(frame);
        helpPushButton->setObjectName(QString::fromUtf8("helpPushButton"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(helpPushButton->sizePolicy().hasHeightForWidth());
        helpPushButton->setSizePolicy(sizePolicy5);

        horizontalLayout->addWidget(helpPushButton);

        fullHelpPushButton = new QPushButton(frame);
        fullHelpPushButton->setObjectName(QString::fromUtf8("fullHelpPushButton"));
        sizePolicy5.setHeightForWidth(fullHelpPushButton->sizePolicy().hasHeightForWidth());
        fullHelpPushButton->setSizePolicy(sizePolicy5);

        horizontalLayout->addWidget(fullHelpPushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);


        horizontalLayout_3->addWidget(frame);

        MPF->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MPF);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MPF->setStatusBar(statusBar);

        retranslateUi(MPF);
        QObject::connect(exitPushButton, SIGNAL(clicked()), MPF, SLOT(close()));

        QMetaObject::connectSlotsByName(MPF);
    } // setupUi

    void retranslateUi(QMainWindow *MPF)
    {
        MPF->setWindowTitle(QApplication::translate("MPF", "MainWindow", 0, QApplication::UnicodeUTF8));
        meskLogoLabel->setText(QString());
        stepsIconsLabel->setText(QString());
        stepsTextLabel->setText(QString());
        previousPushButton->setText(QApplication::translate("MPF", "&Previous", 0, QApplication::UnicodeUTF8));
        nextPushButton->setText(QApplication::translate("MPF", "&Next", 0, QApplication::UnicodeUTF8));
        exitPushButton->setText(QApplication::translate("MPF", "&Exit", 0, QApplication::UnicodeUTF8));
        helpPushButton->setText(QApplication::translate("MPF", "&Show Help", 0, QApplication::UnicodeUTF8));
        fullHelpPushButton->setText(QApplication::translate("MPF", "&Full Screen", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MPF: public Ui_MPF {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MPF_H
