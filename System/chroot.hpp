/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#ifndef CHROOT_HPP
#define CHROOT_HPP

#include <QObject>
#include <QProcess>

class CHRoot : public QObject
{
    Q_OBJECT
public:
    explicit CHRoot(QObject *parent = 0);
    //chroot(QObject *parent = 0);
    ~CHRoot();

    int setRoot(QString&);
    int prepare();
    int exec(QString comm, unsigned int waitDuration=120000);
    int unprepare();

    
signals:
    void    Done(int);
public slots:

private:
    QString root;
    QProcess mountRoot;
    bool    prepared;

    
};

#endif // CHROOT_HPP
