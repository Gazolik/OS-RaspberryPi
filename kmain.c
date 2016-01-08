#include "sched.h"
#include "sched_irq.h"
#include "shell.h"
#include "fb.h"
#include "hw.h"
#include "kheap.h"

static void init()
{
	kheap_init();
	hw_init();
	FramebufferInitialize();
	sched_init();
	
    //create_process(&start_shell);
	irq_init();
}

#include "malloc.h"
void kmain()
{
	init();
	
	int* momo = gmalloc(sizeof(int) * 5);
	momo[0] = 45;
	momo[4] = 33;
	
	momo = grealloc(momo, sizeof(int) * 10);
	
	
	__asm("cps 0x10"); // CPU to USER mode

	while (1) ;
}
