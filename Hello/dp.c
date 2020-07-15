#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define n 5
#define think 0
#define hungry 1
#define eat 2
#define left (i-1+n)%n
#define right (i+1)%n
int state[n];
sem_t s[n],mutex;
void thinking()
{
sleep(3);
}
void eating()
{
sleep(3);
}
void test(int i)
{
	if(state[i]==hungry && state[left]!=eat && state[right]!=eat)
	{	
		printf("philo %d has taken forks %d and %d",i,i,(i-1+n)%n);
		state[i]=eat;
	}
	sem_post(&s[i]);
}
void put_fork(int i)
{
	sem_wait(&mutex);
	printf("\nphilo %d has put forks %d and %d",i,i,(i-1+n)%n);
	state[i]=think;
	test(left);
	test(right);
	sem_post(&mutex);
	printf("\nphilo %d is thinking",i);
}
void take_fork(int i)
{
sem_wait(&mutex);
state[i]=hungry;
test(i);
sem_post(&mutex);
sem_wait(&s[i]);
}

void *philo(void *no)
{
int i;
i=(int)no;
printf("\nphilo %d is thinking..",i);
thinking();
printf("\nphilo %d is hungry..",i);
take_fork(i);
printf("\nphilo %d is eating..",i);
eating();
put_fork(i);
}
int main()
{
int i;
pthread_t p[5];
for(i=0;i<n;i++)
	sem_init(&s[i],0,0);
sem_init(&mutex,0,1);

for(i=0;i<n;i++)
pthread_create(&p[i],NULL,philo,(void*)i);
for(i=0;i<n;i++)
pthread_join(p[i],NULL);
}
 
