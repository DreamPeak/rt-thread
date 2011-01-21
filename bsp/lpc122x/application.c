/*
 * File      : app.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */

/**
 * @addtogroup LPC122x
 */
/*@{*/
#include <rtthread.h>
#include "tc_comm.h"

/*
 * This is an example for delay thread
 */
static struct rt_thread thread;
static char thread_stack[THREAD_STACK_SIZE];
static void thread_entry(void* parameter)
{
	rt_tick_t tick;
	rt_kprintf("thread inited ok\n");

	tick = rt_tick_get();
	rt_kprintf("thread tick %d\n", tick);
	rt_kprintf("thread delay 10 tick\n");
	rt_thread_delay(10);
	
	if (rt_tick_get() - tick > 10)
	{
		tc_done(TC_STAT_FAILED);
		return;
	}

	tick = rt_tick_get();
	rt_kprintf("thread delay 15 tick\n");
	rt_thread_delay(15);
	if (rt_tick_get() - tick > 15)
	{
		tc_done(TC_STAT_FAILED);
		return;
	}

	rt_kprintf("thread exit\n");

	tc_done(TC_STAT_PASSED);
}

rt_err_t thread_delay_init()
{
	rt_err_t result;

	result = rt_thread_init(&thread,
		"test",
		thread_entry, RT_NULL,
		&thread_stack[0], sizeof(thread_stack),
		THREAD_PRIORITY, 10);

	if (result == RT_EOK)
		rt_thread_startup(&thread);
	else
		tc_stat(TC_STAT_END | TC_STAT_FAILED);

	return result;
}

int rt_application_init()
{
	thread_delay_init();

	return 0;
}

/*@}*/