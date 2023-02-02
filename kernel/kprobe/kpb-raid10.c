#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/slab.h>

#define KPB_NUM		1

static struct kprobe **kpbs;

static int raid10_make_request_pre(struct kprobe *p, struct pt_regs *regs)
{
	dump_stack();
	return 0;
}

static void raid10_make_request_post(struct kprobe *p, struct pt_regs *regs,
				    unsigned long flags)
{
}

static int raid10_make_request_fault(struct kprobe *p, struct pt_regs *regs,
				      int trapnr)
{
	return 0;
}

static int handler_init(void)
{
	int i;
	struct kprobe *kpb;

	kpbs = (struct kprobe **)kzalloc(KPB_NUM*sizeof(struct kprobe *), GFP_KERNEL);
	if (!kpbs) {
		printk(KERN_ERR "%s: kzalloc failed for kpbs\n", __func__);
		goto abort;
	}

	for (i = 0; i < KPB_NUM; ++i) {
		kpb = (struct kprobe *)kzalloc(sizeof(struct kprobe), GFP_KERNEL);
		if (!kpb) {
			printk(KERN_ERR "%s: kzalloc failed for kpb at index %d\n",
			       __func__, i);
			goto abort;
		}

		kpbs[i] = kpb;
	}

	kpbs[0]->symbol_name = "raid10_make_request";
	kpbs[0]->pre_handler = raid10_make_request_pre;
	kpbs[0]->post_handler = raid10_make_request_post;
	kpbs[0]->fault_handler = raid10_make_request_fault;

	return 0;

abort:
	for (i = 0; i < KPB_NUM; ++i) {
		kpb = kpbs[i];
		kpbs[i] = NULL;
		if (kpb)
			kfree(kpb);
	}
	if (kpbs)
		kfree(kpbs);

	return -ENOMEM;
}

static int __init kprobe_init(void)
{
	int ret;

	handler_init();

	ret = register_kprobes(kpbs, KPB_NUM);
	if (ret < 0) {
		printk(KERN_ERR "%s: register_kprobes failed, returned %d\n",
		       __func__, ret);
		return ret;
	}

	printk(KERN_INFO "%s: planted kprobes at %p\n",
	       __func__, kpbs[0]->addr);
	return 0;
}

static void __exit kprobe_exit(void)
{
	int i;
	struct kprobe *kpb;

	unregister_kprobes(kpbs, KPB_NUM);
	for (i = 0; i < KPB_NUM; ++i) {
		kpb = kpbs[i];
		kpbs[i] = NULL;
		if (kpb)
			kfree(kpb);
	}

	kfree(kpbs);
	kpbs = NULL;

	printk(KERN_INFO "%s: kprobes unregistered\n", __func__);
}

module_init(kprobe_init)
module_exit(kprobe_exit)
MODULE_LICENSE("GPL");
