#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <linux/hugetlb.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/mmzone.h>
#include <linux/quicklist.h>
#include <linux/syscalls.h>
#include <linux/swap.h>
#include <linux/swapfile.h>
#include <linux/vmstat.h>
#include <linux/atomic.h>



struct sysinfo info;

static int readMemorie(struct seq_file *m, void *v){
	#define Convert(x) ((x) << (PAGE_SHIFT - 10))
	si_meminfo(&info); 
	seq_printf(m, "Carnet: 201213587\n");
	seq_printf(m, "Nombre: Marvin Emmanuel Pivaral Orellana\n");
	seq_printf(m, "Sistema Operativo: Debian GNU/Linux 9.3 (stretch)\n");	
	seq_printf(m, "Memoria Total: %8lu kB\n",Convert(info.totalram));
	seq_printf(m, "Memoria Libre: %8lu kB\n",Convert(info.freeram));
	seq_printf(m, "Memoria Usada: %ld %%\n", (((Convert(info.totalram)-Convert(info.freeram))*100) / (Convert(info.totalram))*100)/100);
	#undef K
	return 0;
}

static int Meminfo_open(struct inode *inode, struct file *file){
	return single_open(file, readMemorie, NULL);
}

static const struct file_operations Meminfo_fops = {
	.owner = THIS_MODULE,
	.open = Meminfo_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Titus");
MODULE_DESCRIPTION("Modulo de memoria - Sistemas Operativos 1");

static int __init memo_201213587_init(void)
{
	printk(KERN_INFO "201213587\n");
	proc_create("memo_201213587", 0, NULL, &Meminfo_fops);
	return 0;
}

static void __exit memo_201213587_cleanup(void)
{
	remove_proc_entry("memo_201213587", NULL);
	printk(KERN_INFO "Sistemas Operativos 1\n");
}

module_init(memo_201213587_init);
module_exit(memo_201213587_cleanup);
