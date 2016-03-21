#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/fs.h>

static struct task_struct *t ;
static int walk(void);
/*
 * invoked from kthread_create, this function will walk the vfs list at interval & 
 * for 5 times and print the information in the log.
 */

static int walk_list ( void * data )  
{
	int i = 0;
	printk (KERN_INFO "walking the vfs list now " );
	for ( i = 0 ; i < 5 ; i++ ){
		walk(); 
		msleep(100);
	}
	return 0 ;
}
static int walk( void )
{
	char buf[1024]   ;
	int len = 0 ;
	len = get_filesystem_list(buf);
	printk ( KERN_INFO "%s", buf );
	return 0 ;
}
static __exit void tata ( void )
{
	if ( NULL != t ) {
		printk ( KERN_INFO "stopping the kernel thread for vfs_list_walker" );
		kthread_stop(t);
	}
	printk( KERN_INFO "Exiting  the .. " );
}
static __init int vfs_list_walker( void )
{
	t = NULL ;
	printk(KERN_INFO "Starting the vfs list walker ..." );
	t = kthread_run ( &walk_list, NULL, "vfs list walker" );
	if ( NULL == t ){
		printk (KERN_ERR "thread creation failed for vfs list walker " );
	} else {
		printk (KERN_ERR "thread creation successful and thread started " );
	}
	return 0;
}

module_init(vfs_list_walker);
module_exit(tata);

MODULE_AUTHOR("Yogesh Kulkarni" );
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("walk through vfs list for 5 times.");
