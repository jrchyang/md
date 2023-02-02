SUBDIRS=kernel user/mdadm-4.2

RECURSIVE_MAKE= @for subdir in $(SUBDIRS);				\
	do								\
		echo "making in $$subdir";				\
		( cd "$$subdir" && $(MAKE) ) || exit 1;			\
	done
RECURSIVE_CLEAN= @for subdir in $(SUBDIRS);				\
	do								\
		echo "cleaning in $$subdir";				\
		( cd $$subdir && $(MAKE) clean ) || exit 1;		\
	done

all:
	$(RECURSIVE_MAKE)
clean:
	$(RECURSIVE_CLEAN)
