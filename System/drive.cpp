/******************************************************
* copyright 2011, 2012, 2013 AbdAllah Aly Saad , aaly90[@]gmail.com
* Part of Mesk Page Framework (MPF)
******************************************************/

#include "drive.hpp"

static inline QString getSysFSMount()
{
    QString sysfsPath;
    char sysfsMountPath[255];

    if(sysfs_get_mnt_path(sysfsMountPath, 255))
    {
        return "";
    }

    sysfsPath = sysfsMountPath;
    sysfsPath += "/";

    return sysfsPath;
}

static inline int changeLabel(QString partitionDevPath)
{
    return 0;
}

QVector< QPair<QString, QString> >  initFileSystems2()
//static inline int initFileSystems2()
{
    QVector< QPair<QString, QString> > availableFileSystems;

    availableFileSystems.push_back(QPair<QString, QString>("/sbin/mkfs.vfat -F 16", "fat16"));
    availableFileSystems.push_back(QPair<QString, QString>("/sbin/mkfs.vfat -F 32", "fat32"));
    availableFileSystems.push_back(QPair<QString, QString>("/sbin/mkfs.ntfs", "ntfs"));
    availableFileSystems.push_back(QPair<QString, QString>("/sbin/mkfs.ext2", "ext2"));
    availableFileSystems.push_back(QPair<QString, QString>("/sbin/mkfs.ext3", "ext3"));
    availableFileSystems.push_back(QPair<QString, QString>("/sbin/mkfs.ext4", "ext4"));
    availableFileSystems.push_back(QPair<QString, QString>("/sbin/mkfs.reiserfs", "reiserfs"));
    //availableFileSystems.push_back(QPair<QString, QString>("", "btrfs"));
    availableFileSystems.push_back(QPair<QString, QString>("/sbin/mkfs.xfs", "xfs"));
    availableFileSystems.push_back(QPair<QString, QString>("/sbin/mkfs.jfs", "jfs"));
    availableFileSystems.push_back(QPair<QString, QString>("/sbin/mkfs.bfs", "bfs"));
    availableFileSystems.push_back(QPair<QString, QString>("/sbin/mkfs.cramfs", "cramfs"));
    availableFileSystems.push_back(QPair<QString, QString>("/sbin/mkfs.minix", "minix"));
    availableFileSystems.push_back(QPair<QString, QString>("/sbin/mkfs.koko", "koko"));

    QVector< QPair<QString, QString> > availableFileSystemsOptions;

    availableFileSystemsOptions.push_back(QPair<QString, QString>("", "fat16"));
    availableFileSystemsOptions.push_back(QPair<QString, QString>("", "fat32"));
    availableFileSystemsOptions.push_back(QPair<QString, QString>("-f", "ntfs"));
    availableFileSystemsOptions.push_back(QPair<QString, QString>("", "ext2"));
    availableFileSystemsOptions.push_back(QPair<QString, QString>("", "ext3"));
    availableFileSystemsOptions.push_back(QPair<QString, QString>("", "ext4"));
    availableFileSystemsOptions.push_back(QPair<QString, QString>("", "reiserfs"));
    //availableFileSystemsOptions.push_back(QPair<QString, QString>("", "btrfs"));
    availableFileSystemsOptions.push_back(QPair<QString, QString>("", "xfs"));
    availableFileSystemsOptions.push_back(QPair<QString, QString>("", "jfs"));
    availableFileSystemsOptions.push_back(QPair<QString, QString>("", "bfs"));
    availableFileSystemsOptions.push_back(QPair<QString, QString>("", "cramfs"));
    availableFileSystemsOptions.push_back(QPair<QString, QString>("", "minix"));
    availableFileSystemsOptions.push_back(QPair<QString, QString>("", "koko"));

#include <iostream>
using namespace std;

    QProcess process;
    process.start(QString("bash -c \"ls -1 /sbin/mkfs.*\""));
    process.waitForFinished();
    QStringList fileSystemsList = QString(process.readAll()).split('\n');


    for (unsigned int i =0; i < availableFileSystems.size(); i++)
    {

        if (!fileSystemsList.contains(availableFileSystems.at(i).first.split(' ').at(0)) )
        {
            availableFileSystems.remove(i);
            i--;
        }
    }

   return availableFileSystems;
   // return 0;
}


////////////////////////////////////////////////////////////////

Drive::Drive()
{
    removable=false;
    //this->fileSystems = initFileSystems();
}

Drive::Drive(PedDevice* dev)
{
    removable=false;
    //this->fileSystems = initFileSystems();
    setPartedDevice(dev);
}


Drive::Drive(QString devPath)
{
    removable=false;
    //this->fileSystems = initFileSystems();
    PedDevice* dev = ped_device_get(devPath.toStdString().c_str());
    setdevPath(devPath);
    setPartedDevice(dev);
}

int Drive::setName(const QString& dname)
{
    if (dname.length() != 0)
    {
        name = dname;
        return 0;
    }
    return 1;
}

QString Drive::getName()
{
    return name;
}

int Drive::setdevPath(const QString& dpath)
{
    if (dpath.length() != 0)
    {
        devPath = dpath;
        return 0;
    }
    return 1;
}

QString Drive::getdevPath()
{
    return devPath;
}

int Drive::setSysFSPath(const QString& sysfspath)
{
    if (sysfspath.length() != 0)
    {
         SysFSPath = sysfspath;
        return 0;
    }
    return 1;
}

QString Drive::getSysFSPath()
{
    return SysFSPath;
}

int Drive::setPartedDevice(PedDevice* dev)
{
    partedDevice = dev;
    populatePartitions();
    return 0;
}


PedDevice* Drive::getPartedDevice()
{
    return partedDevice;
}

int Drive::setPartedDisk(PedDisk* disk)
{
    partedDisk = disk;
    return 0;
}


PedDisk* Drive::getPartedDisk()
{
    return partedDisk;
}

int Drive::pushPartition(const Partition& partition)
{
    partitions.push_back(partition);
    return 0;
}

QVector<Partition> Drive::getPartitions() const
{
    return partitions;
}

QVector<Partition> Drive::getExtendedPartitions()
{
    QVector<Partition> parts;
    for(int i =0; i < partitions.size(); i++)
    {
        for(int k =0; k < partitions.at(i).getPartitions().size(); k++)
        {
            parts.push_back( partitions.at(i).getPartitions().at(k));
        }

        if (partitions.at(i).getPartitions().size() == 0)
        {
            parts.push_back(partitions.at(i));
        }
    }
    return parts;
}

QVector<Partition> Drive::getFullPartitions()
{
    QVector<Partition> parts;

    for(int i =0; i < partitions.size(); i++)
    {
        parts.push_back(partitions.at(i));
        for(int k =0; k < partitions.at(i).getPartitions().size(); k++)
        {
            parts.push_back( partitions.at(i).getPartitions().at(k));
        }
    }
    return parts;
}

QString Drive::getModel()
{
    return (QString::fromAscii(partedDevice->model));
}

QString	Drive::getSize()
{
    char* size = ped_unit_format_byte(partedDevice,
				      partedDevice->length * partedDevice->sector_size);
    return (QString::fromAscii(size));
}

QString Drive::getTransport()
{
    return (partedTransports[partedDevice->type]);
}

int Drive::setRemovable(bool cond)
{
    removable= cond;
    return 0;
}

bool Drive::isRemovable() const
{
    return removable;
}


long Drive::getPhysicalSectorSize()
{
    return (partedDevice->phys_sector_size);
}

long Drive::getLogicalSectorSize()
{
    return (partedDevice->sector_size);
}

int Drive::populatePartitions()
{

    if (partedDevice == NULL)
    {
        return 1;
    }
    PedDisk* disk = ped_disk_new(partedDevice);

    if(disk == NULL)
    {
        return 1;
    }

    partedDisk = disk;

    PedPartition* part;
    for (part = ped_disk_next_partition (disk, NULL); part;
    part = ped_disk_next_partition (disk, part))
    {

	if (part->num < 0)
	{
	    continue;
	}

        Partition p(partedDevice, part);

        //p.setPartedDevice(partedDevice);
	p.setPartedDisk(partedDisk);
	partitions.push_back(p);
    }

    for ( int i =0; i< partitions.count(); i++)
    {
        if (partitions[i].getPartitionType() == "extended" &&
            i != partitions.count()-1)
        {
            for (int j =i+1; j < partitions.count(); j++)
            {
                partitions[i].addPartition(partitions[j]);
                // remove it from main partitions
            }
            partitions.remove(i+1, partitions.count()-i-1);
            break;
        }
    }

    return 0;
}


///////////////////////////////////////////////////////////////////////////
Partition::Partition()
{
}

Partition::Partition(PedDevice* dev, PedPartition* part)
{
   label = ped_partition_get_name(part);
   partedPartition = part;
   partedDevice = dev;
   Init();
}

int Partition::Init()
{
    setNumber(partedPartition->num);
    setPartitionType();
    setdevPath((ped_partition_get_path(partedPartition)));

    setFSType((partedPartition->fs_type) ? partedPartition->fs_type->name : "Un-Known");
    if (fstype == "Un-Known" && partitionType != "extended")
   // if(true)
    {

        const char* devname = devPath.toStdString().c_str();
        blkid_probe pr;
        const char *ptname;
        ptname = "";
        pr = blkid_new_probe_from_filename(devname);
        if (pr)
        {
            blkid_probe_enable_partitions(pr, 1);
            blkid_do_fullprobe(pr);
            blkid_probe_lookup_value(pr, "TYPE", &ptname, NULL);

            if (!strcmp(ptname, ""))
            //if(ptname != "")
            {
                setFSType(QString(ptname));
            }
            blkid_free_probe(pr);
        }
    }

    setLabel(blkid_get_tag_value(NULL, "LABEL", devPath.toStdString().c_str()));
	UUID = blkid_get_tag_value(NULL, "UUID", devPath.toStdString().c_str());

    unsigned long long Unit = partedPartition->geom.length * partedDevice->sector_size;

    if (Unit/(1024*3) > 1)
    {
	Unit = PED_UNIT_GIGABYTE;
    }
    else if(Unit/(1024*2) > 1)
    {
	Unit = PED_UNIT_MEGABYTE;
    }
    else if(Unit/(1024*1) > 1)
    {
	Unit = PED_UNIT_KILOBYTE;
    }
    else
    {
        Unit = PED_UNIT_BYTE;
    }

    setSize(ped_unit_format_custom_byte (partedDevice,
				      partedPartition->geom.length * partedDevice->sector_size,
				      (PedUnit)Unit));

    /*QList<PedPartitionFlag> flags;

    for ( PedPartitionFlag flag; flag ; ped_partition_flag_next(flag))
    {
	ped_partition_flag_get_name (flag);
	flags.append(flag);
    }

    p.setFlags(flags);*/


	/*
	QDir devUUID("/dev/disk/by-uuid/");
	if(devUUID.exists())
	{
		for (int i =0; i < devUUID.entryList(QDir::NoDotAndDotDot | QDir::Files).size(); i++)
		{
			QString file = QFile::symLinkTarget(devUUID.entryList(QDir::NoDotAndDotDot | QDir::Files).at(i));
			if(file.mid(file.lastIndexOf("/")) == devPath.mid(devPath.lastIndexOf("/")))
			{
				UUID = devUUID.entryList(QDir::NoDotAndDotDot | QDir::Files).at(i);
			}
		}
	}*/



    return 0;
}

int Partition::initPartitionFlags()
{
    for (int i =0; i <  00; i++)
    {
	if( ped_partition_is_flag_available(partedPartition,(PedPartitionFlag)i) )
	{


	}
    }

    return 0;
}


QString Partition::getUUID() const
{
	return UUID;
}

int Partition::setNumber(const int& num)
{
    if (num > 0)
    {
	partitionNumber = num;
        return 0;
    }
    return 1;
}

int Partition::getNumber()
{
    return partitionNumber;
}

int Partition::setSize(const QString& size)
{
    this->size = size;
    return 0;
}

QString Partition::getSize()
{
    return size;
}

int Partition::setFSType(QString type)
{
    this->fstype = type;
    return 0;
}


QString Partition::getFSType() const
{
    return fstype;
}

int Partition::setdevPath(const QString& dpath)
{
    if (dpath.length() != 0)
    {
        devPath = dpath;
        return 0;
    }
    return 1;
}


QString Partition::getdevPath() const
{
    return devPath;
}

int Partition::setPartedDevice(PedDevice* dev)
{
    partedDevice = dev;
    return 0;
}

PedDevice* Partition::getPartedDevice()
{
    return partedDevice;
}

int Partition::setPartedDisk(PedDisk* dsk)
{
    partedDisk = dsk;
    return 0;
}

int Partition::setPartedPartition(PedPartition* pp)
{
    partedPartition = pp;
    Init();
    return 0;
}


PedPartition* Partition::getPartedPartition()
{
    return partedPartition;
}

int Partition::setLabel(const QString& partitionLabel)
{
    if (partitionLabel.length() != 0)
    {
        label = partitionLabel;
        ped_partition_set_name(partedPartition, label.toStdString().c_str());
        return 0;
    }
    return 1;
}

QString Partition::getLabel() const
{
    return label;
}

int Partition::setPartitionType()
{

    if (partedPartition != NULL)
    {
        partitionType = ped_partition_type_get_name(partedPartition->type);
        return 0;

    }
    return 1;
}

QString Partition::getPartitionType()
{
  return partitionType;
}

int Partition::addPartition(Partition part)
{
    Partitions.push_back(part);
    return 0;
}

QVector<Partition> Partition::getPartitions() const
{
    return Partitions;
}

int Partition::Format(QString newFS = "")
{
    if (newFS == "")
    {
        newFS = fstype;
    }

    int result = ped_partition_set_system(partedPartition, ped_file_system_type_get(newFS.toStdString().c_str()));

    if(!result)
    {
        return 1;
    }

    return 0;
}

///////////////////////////////////////////////
