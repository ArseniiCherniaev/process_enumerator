#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched/task.h>

int process_task(struct task_struct *task, int indent)
{	
	struct list_head *list;
	struct task_struct *child;
	int number_of_tasks = 1;

	printk(KERN_DEBUG "%*sProcess: {name: %s, pid: %d}\n", indent, "", task -> comm, task -> pid);
	
	list_for_each(list, &task->children)
	{
		child = list_entry(list, struct task_struct, sibling);
		number_of_tasks += process_task(child, indent + 2);	
	}

	return number_of_tasks;
}

static int init_enumerator(void)
{
	int total_number_of_processes = 0;

	printk(KERN_INFO "Process enumerator module being loaded.\n");
	printk(KERN_DEBUG "All processes:\n");
	total_number_of_processes = process_task(&init_task, 0);
	printk(KERN_INFO "Total number of processes: %d.\n", total_number_of_processes);

	return 0;
}

static void bye(void)
{
	printk(KERN_INFO "Process enumerator module being unloaded.\n");
}

module_init(init_enumerator);
module_exit(bye);

MODULE_AUTHOR("Arseny Chernyaev, https://github.com/ArsenyChernyaev");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Enumerate all processes.");
