#include <stdio.h>
#include <hal_interrupt.h>
#include <hal_status.h>
#include <nuttx/irq.h>
#include <nuttx/spinlock.h>
#include <nuttx/arch.h>

static hal_irq_handler_t g_irqhandler[NR_IRQS];

static int up_common_handler(int irq, void *context, void *arg)
{
	if (g_irqhandler[irq]) {
		return g_irqhandler[irq](arg);
	}
	return -1;
}

int32_t hal_request_irq(int32_t irq, hal_irq_handler_t handler, const char *name, void *data)
{
	g_irqhandler[irq] = handler;
	return irq_attach(irq, up_common_handler, data);
}

void hal_free_irq(int32_t irq)
{
	irq_detach(irq);
	g_irqhandler[irq] = NULL;
}

int hal_enable_irq(int32_t irq)
{
	up_enable_irq(irq);

	return HAL_OK;
}

void hal_disable_irq(int32_t irq)
{
	up_disable_irq(irq);
}

uint32_t hal_interrupt_get_nest(void)
{
	return up_interrupt_context();
}

unsigned long hal_interrupt_disable_irqsave(void)
{
    return (unsigned long)up_irq_save();
}

void hal_interrupt_enable_irqrestore(unsigned long flag)
{
	up_irq_restore((irqstate_t)flag);
}

unsigned long hal_interrupt_is_disable(void)
{
	unsigned long cpsr = irqstate();
	if (cpsr & 0x80)
		return 1;
	return 0;
}

void hal_interrupt_init(void)
{
}

#ifdef enter_critical_section
#undef enter_critical_section
#endif

#ifdef leave_critical_section
#undef leave_critical_section
#endif

irqstate_t enter_critical_section(void)
{
	return up_irq_save();
}

void leave_critical_section(irqstate_t flag)
{
	up_irq_restore(flag);
}
