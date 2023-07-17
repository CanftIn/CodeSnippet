#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h>

static int hello_init(void) {
  printk("Hello world\n");
  return 0;
}

static void hello_exit(void) {
  printk("bye\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wwc7033@gmail.com");