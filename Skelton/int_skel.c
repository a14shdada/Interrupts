#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>

unsigned int irq = 18, my_dev_id = 1;

static irqreturn_t my_irq( int irq, void *dev_id)
{
	pr_info("%s: In Interrupt handler\n",__func__);
} 

static int __init my_init(void)
{
	int ret;

	/* int request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags,const char *name, void *dev) */
	/* The request_irq() function requests that a specified function (the handler) be called when ever the kernel receives a given interrpt on a irq line. */
	/**
	 * @arg1 : This is the interrupt number being requested. 
	 * @arg2 : The pointer to the handling function being installed.
	 * @arg3 : A bit mask of options  related to interrupt management.
	 * @arg4 : The string passed to request_irq is used in /proc/interrupts to show the owner of the interrupt 
	 * @arg5 : This pointer is used for shared interrupt lines. It is a unique identifier that is used when the interrupt line is freed and that may also be used by the driver to point to its own private data area (to identify which device is interrupting). When no sharing is in force, dev_id can be set to NULL.
	 */ 
	ret = request_irq(irq, my_irq, IRQF_SHARED,"my_interrupt",&my_dev_id);
	if(ret) {
		pr_err("%s: Cannot request irq: %d\n",__func__,ret);	
		return ret;
	}
	pr_info("%s: Module Loaded\n",__func__);
	return 0;
}

static void __exit my_exit(void)
{
	/**
 	*	free_irq - free an interrupt allocated with request_irq
	*	@irq: Interrupt line to free
 	*	@dev_id: Device identity to free
 	*
 	*	Remove an interrupt handler. The handler is removed and if the
 	*	interrupt line is no longer in use by any driver it is disabled.
 	*	On a shared IRQ the caller must ensure the interrupt is disabled
 	*	on the card it drives before calling this function. The function
 	*	does not return until any executing interrupts for this IRQ
 	*	have completed.
 	*
 	*	This function must not be called from interrupt context.
 	*
	*	Returns the devname argument passed to request_irq.
 	*/
	free_irq(irq,&my_dev_id);	
	pr_info("%s: Module Unloaded\n",__func__);
}

module_init(my_init);
module_exit(my_exit);

MODULE_DESCRIPTION("Skelton Module for Interrupt");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("dada_ji@gmail.com");
MODULE_VERSION("0.1");


