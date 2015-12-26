#include "sem.h"
#include "syscall.h"
#include "pwm.h"
#include "hw.h"

int process()
{
	int32_t cpt = 10;
	
	int pid = sys_fork();
	if (pid == -1)
	{
		// failed
	}
	else if (pid == 0)
	{
		// Child
		cpt--;
		while (1) ;
	}
	else
	{
		// parent
		cpt++;
		while (1) ;
	}
	
	
	return 0;
}

void kmain()
{
	audio_init();
	sched_init();
	
	create_process(&process);
	
	irq_init();
	
	__asm("cps 0x10"); // CPU to USER mode
	
	while (1) ;
}
