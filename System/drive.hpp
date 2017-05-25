/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#ifndef DRIVE_H
#define DRIVE_H

#include <QVector>
#include <QPair>
#include <QString>
#include <parted/parted.h>
#include <sysfs/libsysfs.h>
#include <iostream>
#include <blkid/blkid.h>
#include <QDir>


// later add info like serial , model , SMART status


#include <sys/mount.h>
#include <mntent.h>


class Drive;
class Partition;


//QVector< QPair<QString, QString> > availableFileSystems;


////static inline int populateSysFSDrives(QList<Drive>&);
static inline int populatePartedDrives(QList<Drive>&);
////static inline QString getSysFSMount();

static QString partedTransports[] = {"unknown", "scsi", "ide", "dac960", "cpqarray",
				    "file", "ataraid", "i2o", "ubd", "dasd", "viodasd",
				    "sx8", "dm", "xvd", "sdmmc", "virtblk", "aoe", "md"};

//static QString mountPoints[] = {"/boot", "/home", "/opt", "/root"};


class Drive
{
private:
    QString name;
    QString status;
    QString devPath;
    QString SysFSPath;
    QVector<Partition> partitions;
    PedDevice*  partedDevice;
    PedDisk*    partedDisk;
    QVector<QString> fileSystems;
    bool                removable;
public:
    Drive(PedDevice*);
    Drive();
    Drive(QString);
  //  static int      populateDrives(QList<Drive>&);
    int		    setName(const QString&);
    int             setdevPath(const QString&);
    int             setSysFSPath(const QString&);
    QString         getName();
    QString         getdevPath();
    QString         getSysFSPath();
    QString         getModel();
    QString	    getSize();
    QString	    getTransport();
    long	    getPhysicalSectorSize();
    long	    getLogicalSectorSize();
    PedDevice*      getPartedDevice();
    PedPartition*   getPartedPartition();
    QVector<Partition> getPartitions() const;
    QVector<Partition> getExtendedPartitions();
    QVector<Partition> getFullPartitions();
    int             pushPartition(const Partition&);
    int		    setPartedDevice(PedDevice*);
    int		    setPartedDisk(PedDisk*);
    int		    populatePartitions();
    int		    setStatus(QString);
    QString	    getStatus();
    PedDisk*	    getPartedDisk();

    int		    Remove();
    int		    Resize(long long newsize);

    int         setRemovable(bool);
    bool        isRemovable() const;
};

class Partition
{
private:
    int			name;
    QString		devPath;
    QString		fstype;
    QString		size;
    PedDevice*		partedDevice;
    PedDisk*		partedDisk;
    PedPartition*	partedPartition;
    int			partitionNumber;
    int			diskNumber;
    QString		label;
    QVector<PedPartitionFlag> partitionFlags;
    QString partitionType;
    QVector<Partition> Partitions; // if extended or whatever :D
	QString    UUID;
public:
    Partition(PedDevice*, PedPartition*);
    Partition();
    int			Init();
    int			initPartitionFlags();
    int			getNumber();
    QString		getLabel() const;
    QString		getdevPath() const;
    int			setNumber(const int&);
    int			setdevPath(const QString&);
    int			setSysFSPath(const QString&);
    int			setSize(const QString&);
    int			setLabel(const QString&);
    int			setFSType(QString);
    QString		getSize();
    PedDisk*		getPartedDisk();
    PedPartition*	getPartedPartition();
    int			setPartedDisk(PedDisk*);
    int			setPartedDevice(PedDevice*);
    int			setPartedPartition(PedPartition*);
    int			populatePartitions();
    QString getFSType() const;
    PedDevice*		getPartedDevice();
    int			setFlags(const QList<PedPartitionFlag>& flags);
    QVector<PedPartitionFlag> getFlags();
    int			setPartitionType();
    QString		getPartitionType();

    int			setFS(const QString&);
    int                 addPartition(Partition);
    QVector<Partition>	getPartitions() const;

    int                 Format(QString);
	QString             getUUID() const;

};

/*static inline int populatePartedDrives(QList<Drive>& drivesList)
{
    PedDevice* dev = NULL;
    ped_device_probe_all();
    while ( (dev = ped_device_get_next(dev)) )
    {
        if(dev->length == 0)
        {
            continue;
        }

        Drive d(dev);
        PedDisk* di = ped_disk_new(d.getPartedDevice());
        d.setPartedDisk(di);
        drivesList.push_back(d);
    }
    return 0;
}*/


static inline QString getSysfsAtrribute(sysfs_class_device *clsdev, QString attribute)
{
	sysfs_attribute* attr = sysfs_get_classdev_attr(clsdev, attribute.toStdString().c_str());
	if(attr != NULL)
	{
		return QString(attr->value);
	}
	return QString("");

    dlist* dList = sysfs_get_classdev_attributes(clsdev);
    int counter = 0;

    if (dList)
    {
        counter = dList->count;
    }
    else
    {
        return "";
    }

    dList->marker = &dList->headnode;

    while (counter != 0)
    {
        counter--;
        DL_node* node = 0;
        node = dList->marker;
        dlist_next(dList);
        if(node->data == 0 ||
           node->data == NULL)
        {
            dlist_next(dList);
            continue;
        }
        sysfs_attribute* attr = (sysfs_attribute*)node->data;

        if (!strcmp(attr->name,attribute.toLatin1()))
        {
            return QString(attr->value);
        }
        delete attr;
    }

    return "";
}

static inline int deviceRemoveable(sysfs_class_device *clsdev)
{
    dlist* dList = sysfs_get_classdev_attributes(clsdev);
    int counter = 0;

    if (dList)
    {
        counter = dList->count;
    }
    else
    {
        return 1;
    }

    dList->marker = &dList->headnode;

    while (counter != 0)
    {
        counter--;
        DL_node* node = 0;
        node = dList->marker;
        dlist_next(dList);
        if(node->data == 0 ||
           node->data == NULL)
        {
            dlist_next(dList);
            continue;
        }
        sysfs_attribute* attr = (sysfs_attribute*)node->data;

        if (!strcmp(attr->name,"removable"))
        {
            if (!strcmp(attr->value, "1\n"))
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        delete attr;
    }

    return 1;
}

static inline int populatePartedDrives(QList<Drive>& drivesList)
{
    // darn , fast but legacy :D ( beats the others ;) )
    sysfs_class* sysfsClass;
    sysfsClass = sysfs_open_class("block");

    dlist* dList = sysfs_get_class_devices(sysfsClass);

    int counter = 0;

    if (dList)
    {
        counter = dList->count;
    }
    else
    {
        return 1;
    }

    dList->marker = &dList->headnode;

    while (counter != 0)
    {
        counter--;
        DL_node* node = 0;
        node = dList->marker;
        dlist_next(dList);
        if(node->data == 0 ||
           node->data == NULL)
        {
            //dlist_next(dList);
            continue;
        }
        sysfsClass = (sysfs_class*)node->data;

        if(sysfsClass->name[1] == 'r' || //sr
           sysfsClass->name[0] == 'f' || // fd
           sysfsClass->name[0] == 'l' )  // loop*
        {
            //dlist_next(dList);
            continue;
        }

        QString tmpStr("/dev/");
        tmpStr += sysfsClass->name;

        if (ped_device_get(tmpStr.toStdString().c_str()) != NULL)
        {
            Drive drive(tmpStr);
            //if (deviceRemoveable((sysfs_class_device*)node->data) == 0)
            if ( getSysfsAtrribute((sysfs_class_device*)node->data, "removable") == "1\n" )
            {
                drive.setRemovable(true);
            }
            drivesList.push_back(drive);
        }


        /*drive.setName(sysfsClass->name);

        //drive.setdevPath(tmpStr);
        //drive.setSysFSPath(sysfsClass->path);

        dlist* drivePartitionsDList =
        sysfs_open_directory_list(drive.getSysFSPath().toStdString().c_str());

        if(!drivePartitionsDList || !drivePartitionsDList->count)
        {
            return 1;
        }

        QString partition("");
        DL_node* partitionNode = 0;
        dlist_start(drivePartitionsDList);

        for ( unsigned long c = 0; c < drivePartitionsDList->count; c++)
        {
            partitionNode = 0;
            partitionNode = drivePartitionsDList->marker;
            if (partitionNode->data)
            {
                partition = QString::fromAscii((char*)partitionNode->data);
                if (partition.contains(drive.getName()))
                {
                    Partition p;
                    //p.setName(partition);
                    //p.setdevPath("/dev/" + p.getName());
                    //p.getPartedDisk()->dev.path;
                    //p.getPartedPartition()
                    //
                    //drive.pushPartition(p);
                }
            }
            dlist_next(drivePartitionsDList);
        }
        drivesList.push_back(drive);*/
    }
    return 0;
}


/*
static inline QVector<QString>&  initFileSystems()
{
    QVector<QString> fSystems;

    for ( PedFileSystemType* fs = ped_file_system_type_get_next (NULL); fs;
        fs = ped_file_system_type_get_next(fs))
    {
        fSystems.append(fs->name);
        // most of them doesn't even exist in arch
        // i need to check before appending, parted sucks :(
    }

    return fSystems;
}*/

#include <QProcess>

QVector< QPair<QString, QString> >  initFileSystems2();
//static inline int initFileSystems2()


inline bool mounted(QString devpath)
{
    FILE * mtab = NULL;
    struct mntent * part = NULL;
    int is_mounted = 0;
    if ( ( mtab = setmntent ("/etc/mtab", "r") ) != NULL)
    {
        while ( ( part = getmntent ( mtab) ) != NULL)
        {
            if ( ( part->mnt_fsname != NULL ) && ( strcmp ( part->mnt_fsname, devpath.toStdString().c_str() ) ) == 0 )
            {
                is_mounted = 1;
            }
        }
        endmntent ( mtab);
    }
    return is_mounted;
}

inline int unmount(QString part)
{
	//if ( mounted(part) )
    {
		umount2(part.toStdString().c_str(), MNT_FORCE);
    }
    return 0;
}


#endif // DRIVE_H
