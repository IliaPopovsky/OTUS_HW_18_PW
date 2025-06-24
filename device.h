/* SPDX-License-Identifier: GPL-2.0 */

#include <linux/blk_types.h>
#include <linux/blkdev.h>
#include <linux/device.h>
#include <linux/blk-mq.h>
#include <linux/list.h>

/*
* The key structure of our module.
* It contains all the information about the device that the kernel module needs, in particular: the capacity of the block device, a set of tags for the request queues, a pointer to the disk.
*/
/*
 * Ключевая структура нашего модуля.
 * Она содержит всю необходимую модулю ядра информацию об устройстве, в частности: ёмкость блочного устройства, набор тегов для очередей запросов, указатель на диск.
*/
struct sblkdev_device {                                  
	struct list_head link;

	sector_t capacity;		/* Device size in sectors */        /* Размер устройства в секторах */
	u8 *data;			/* The data in virtual memory */    /* Данные в виртуальной памяти */
#ifdef CONFIG_SBLKDEV_REQUESTS_BASED
	struct blk_mq_tag_set tag_set;
#endif
	struct gendisk *disk;
};

struct sblkdev_device *sblkdev_add(int major, int minor, char *name,
				  sector_t capacity);
void sblkdev_remove(struct sblkdev_device *dev);
