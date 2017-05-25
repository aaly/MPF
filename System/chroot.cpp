/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#include "chroot.hpp"
#include <QProcess>

CHRoot::CHRoot(QObject *parent) :
    QObject(parent)
{
    prepared=false;
}

/*chroot(QObject *parent = 0, QString& root)
{
    setRoot(root);
    prepare();
}*/

int CHRoot::setRoot(QString& croot)
{
    if (croot.size() == 0)
    {
        return 1;
    }


    root=croot;
    return 0;
}

int wait = 10000;

int CHRoot::prepare()
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

int CHRoot::unprepare()
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

int CHRoot::exec(QString comm, unsigned int waitDuration)
{
    mountRoot.execute("chroot " + root + " " + comm);
    int ret = mountRoot.waitForFinished(waitDuration);
    emit Done(ret);
    return ret;
}

CHRoot::~CHRoot()
{
    unprepare();
}
