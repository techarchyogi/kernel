#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static __init int test( void )
{
	printk(KERN_INFO "Hello world a new chapter");
	return 0;
}

static __exit void bye( void )
{
	printk( KERN_INFO "Exiting .. " );
}

module_init(test);
module_exit(bye);

MODULE_AUTHOR("Yogesh Kulkarni" );
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Doing a whole lot of nothing.");
