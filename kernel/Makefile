#
## Makefile for the kernel software RAID
#

EXTRA_CFLAGS		+= -g -Wall
EXTRA_CFLAGS		+= -DCONFIG_DEBUG -DCONFIG_TRACING
EXTRA_CFLAGS		+= -Wno-comment
KDIR			:= /lib/modules/$(shell uname -r)/build
PWD			:= $(shell pwd)


dm-mod-y		+= dm.o dm-table.o dm-target.o dm-linear.o dm-stripe.o \
			   dm-ioctl.o dm-io.o dm-kcopyd.o dm-sysfs.o dm-stats.o \
			   dm-rq.o
dm-multipath-y		+= dm-path-selector.o dm-mpath.o
dm-snapshot-y		+= dm-snap.o dm-exception-store.o dm-snap-transient.o \
			    dm-snap-persistent.o
dm-mirror-y		+= dm-raid1.o
dm-log-userspace-y	+= dm-log-userspace-base.o dm-log-userspace-transfer.o
dm-bio-prison-y		+= dm-bio-prison-v1.o dm-bio-prison-v2.o
dm-thin-pool-y		+= dm-thin.o dm-thin-metadata.o
dm-cache-y		+= dm-cache-target.o dm-cache-metadata.o dm-cache-policy.o \
			   dm-cache-background-tracker.o
dm-cache-smq-y		+= dm-cache-policy-smq.o
dm-era-y		+= dm-era-target.o
dm-verity-y		+= dm-verity-target.o

md-mod-y		:= md.o md-bitmap.o
raid456-y		:= raid5.o raid5-cache.o raid5-ppl.o

obj-m += dm-mod.o
obj-m += dm-builtin.o
obj-m += dm-bufio.o
obj-m += dm-bio-prison.o
obj-m += dm-crypt.o
obj-m += dm-delay.o
obj-m += dm-flakey.o
obj-m += dm-multipath.o dm-round-robin.o
obj-m += dm-queue-length.o
obj-m += dm-service-time.o
obj-m += dm-switch.o
obj-m += dm-snapshot.o
obj-m += dm-mirror.o dm-log.o dm-region-hash.o
obj-m += dm-log-userspace.o
obj-m += dm-zero.o
obj-m += dm-raid.o
obj-m += dm-thin-pool.o
obj-m += dm-verity.o
obj-m += dm-cache.o
obj-m += dm-cache-smq.o
obj-m += dm-era.o
obj-m += dm-log-writes.o
obj-m += persistent-data/

obj-m += md-mod.o
obj-m += raid456.o
obj-m += raid1.o
obj-m += raid10.o

obj-m += bcache/
obj-m += kprobe/


all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
