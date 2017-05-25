/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#ifndef LANGUAGESPAGE_HPP
#define LANGUAGESPAGE_HPP

#include <QtWidgets/QWidget>
#include "pageBase.hpp"
#include "../ui_languagesPage.h"
#include <QDir>


class languagesPage : public pageBase, private Ui::languagesPage
{
    Q_OBJECT

public:
    int initAll();
    int initLanguages();

    explicit languagesPage(QWidget *parent = 0);
    ~languagesPage();

    QString SelectedLanguage();

public slots:
    int applyLanguage();

private:
    void changeEvent(QEvent* event);
    QString language;

signals:
    void selectedLanguage(QString);

};


#endif // LANGUAGESPAGE_HPP

