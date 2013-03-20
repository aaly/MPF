/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#include "chroot.hpp"
#include <QProcess>

chroot::chroot(QObject *parent) :
    QObject(parent)
{
    prepared=false;
}

/*chroot(QObject *parent = 0, QString& root)
{
    setRoot(root);
    prepare();
}*/

int chroot::setRoot(QString& croot)
{
    if (croot.size() == 0)
    {
        return 1;
    }


    root=croot;
    return 0;
}

int wait = 10000;

int chroot::prepare()
{
    //mountRoot.start("test -d " + root + " || mkdir -p " + root);
    mountRoot.execute("mkdir -p " + root);
    mountRoot.waitForFinished(wait);

    mountRoot.execute("mount --bind /dev " + root + "/dev");
    mountRoot.waitForFinished(wait);
    mountRoot.execute("mount --bind /dev/pts " + root + "/dev/pts");
    mountRoot.waitForFinished(wait);
    mountRoot.execute("mount --bind /dev/shm " + root + "/dev/shm");
    mountRoot.waitForFinished(wait);
    mountRoot.execute("mount -t proc none " + root + "/proc");
    mountRoot.waitForFinished(wait);
    mountRoot.execute("mount -t sysfs none " + root + "/sys");
    prepared=true;
    return 0;
}

int chroot::unprepare()
{
    if (!prepared)
    {
        return 1;
    }

    mountRoot.execute("umount " + root + "/dev/shm");
    mountRoot.waitForFinished(wait);
    mountRoot.execute("umount " + root + "/dev/pts");
    mountRoot.waitForFinished(wait);
    mountRoot.execute("umount " + root + "/dev");
    mountRoot.waitForFinished(wait);
    mountRoot.execute("umount " + root + "/proc");
    mountRoot.waitForFinished(wait);
    mountRoot.execute("umount " + root + "/sys");
    mountRoot.waitForFinished(wait);
    return 0;
}

int chroot::exec(QString comm)
{
    mountRoot.execute("chroot " + root + " " + comm);
    int ret = mountRoot.waitForFinished(120000);
    emit Done(ret);
    return ret;
}

chroot::~chroot()
{
    //unprepare();
}
