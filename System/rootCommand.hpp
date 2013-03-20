/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#ifndef SHELL_HPP
#define SHELL_HPP

#include <QObject>
#include <expect.h>
#include <expect_comm.h>
#include <QProcess>
#include <QProcessEnvironment>

class Shell : public QObject
{
    Q_OBJECT
public:
    explicit Shell(QObject *parent = 0, QString rootpw = "");

    int     setRootPassword(QString);

signals:

public slots:

};

#endif // SHELL_HPP
