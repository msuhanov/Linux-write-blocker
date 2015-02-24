/*
 * (c) Maxim Suhanov, 2015
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

static struct jprobe jp;

static int generic_make_request_checks_fork(struct bio *bio)
{
	char b[BDEVNAME_SIZE];

	if (bio->bi_rw & REQ_WRITE_SAME)
	{
		printk(KERN_INFO "forensic-tracer: captured write_same request for %s (block #%Lu)\n",
			bdevname(bio->bi_bdev, b),
			(unsigned long long)bio->bi_iter.bi_sector);
	} else if (bio->bi_rw & (REQ_WRITE | REQ_DISCARD))
	{
		printk(KERN_INFO "forensic-tracer: captured %s request for %s (block #%Lu, size: %u)\n",
			(bio->bi_rw & REQ_DISCARD) ? "discard" : "write",
			bdevname(bio->bi_bdev, b),
			(unsigned long long)bio->bi_iter.bi_sector,
			bio->bi_iter.bi_size);
	}

	jprobe_return();
	return 0;
}

static int __init jprobe_init(void)
{
	int ret;

	jp.kp.symbol_name = "generic_make_request_checks";
	jp.entry = generic_make_request_checks_fork;

	ret = register_jprobe(&jp);
	if (ret < 0) {
		printk(KERN_INFO "forensic-tracer: register_jprobe() failed: %d\n", ret);
		return ret;
	}
	printk(KERN_INFO "forensic-tracer: installed jprobe at %p\n", jp.kp.addr);
	return 0;
}

static void __exit jprobe_exit(void)
{
	unregister_jprobe(&jp);
	printk(KERN_INFO "forensic-tracer: jprobe at %p unregistered\n", jp.kp.addr);
}

module_init(jprobe_init);
module_exit(jprobe_exit);
MODULE_AUTHOR("Maxim Suhanov");
MODULE_DESCRIPTION("trace write and discard requests going to a block device (better than built-in I/O debugging)");
MODULE_LICENSE("GPL");
