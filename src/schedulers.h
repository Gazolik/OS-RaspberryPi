#ifndef SCHEDULERS_H
#define SCHEDULERS_H

enum SCHEDULERS
{
	ROUND_ROBIN_SCHED,
	RANDOM_SCHED,
	FIXED_PRIORITY_SCHED,
	DYNAMIC_PRIORITY_SCHED
};

void electRoundRobin();
void electRandom();
void electFixPriority();
void electDynamicPriority();

#endif // SCHEDULERS_H
