#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <time.h>

	

double total = 0.0;
sem_t fCounter, tCounter, topCounter, flav1, flav2, flav3, flav4, top1, top2, top3;

void *IceCreamFactory(void *num);

int main(){
srand(time(0));	

int n = 10;
int flavors[4] = { (rand()%(20 - 15 + 1)) + 15 , (rand()%(20 - 15 + 1)) + 15 , (rand()%(20 - 15 + 1)) + 15 , (rand()%(20 - 15 + 1)) + 15};
int toppings[3] = {(rand()%(20 - 15 + 1)) + 15 , (rand()%(20 - 15 + 1)) + 15 , (rand()%(20 - 15 + 1)) + 15};

	int c;
	printf("Enter Number of customers: ");
	scanf("%d" , &c);
	int cus[c];
	
	sem_init(&tCounter , 0 , 1);
	sem_init(&fCounter , 0 , 1);
	sem_init(&topCounter , 0 , 1);	
	sem_init(&flav1 , 0 , flavors[0]);	
	sem_init(&flav2 , 0 , flavors[1]);
	sem_init(&flav3 , 0 , flavors[2]);
	sem_init(&flav4 , 0 , flavors[3]);
	sem_init(&top1 , 0 , toppings[0]);
	sem_init(&top2 , 0 , toppings[1]);		
	sem_init(&top3 , 0 , toppings[2]);		
	
	pthread_t customers[c];
	
	for(int i = 1; i <= c; i++){
		cus[i] = i;
	}
	
	for(int i = 0; i < c; i++){
		pthread_create(&customers[i], NULL, IceCreamFactory, &cus[i+1]);
	}
	
	for(int i = 0; i < c; i++){
		pthread_join(customers[i], NULL);
	}
	
}

void *IceCreamFactory(void *num){
	
	int no = *(int *)num;6
	printf("Customer %d arrives at the ticket counter! \n", no);
	sem_wait(&tCounter);
	printf("Customer %d arrives at the flavor counter! \n", no);
	sem_post(&tCounter);
	sem_wait(&fCounter);
	int fChoice = rand() % 3;
	if(fChoice == 0){
		sem_wait(&flav1);
		printf("Customer %d got flavor %d \n", no, fChoice + 1 );	

	}
	else if(fChoice == 1){
		sem_wait(&flav2);
		printf("Customer %d got flavor %d \n", no, fChoice + 1 );

	}
	else if(fChoice == 2){
		sem_wait(&flav3);
		printf("Customer %d got flavor %d \n", no, fChoice + 1 );

	}
	else{
		sem_wait(&flav4);
		printf("Customer %d got flavor %d \n", no, fChoice + 1 );
			
	}
	sem_post(&fCounter);
	printf("Customer %d has arrived at the toppings counter! \n" , no);
	
	int tChoice = rand() % 2;
	
	if(tChoice == 0){
		sem_wait(&top1);
		printf("Customer %d got topping %d \n", no, tChoice + 1 );	
	}
	else if(fChoice == 1){
		sem_wait(&top2);
		printf("Customer %d got topping %d \n", no, tChoice + 1 );	
	}
	else{
		sem_wait(&top3);
		printf("Customer %d got topping %d \n", no, tChoice + 1 );	
	}
	sem_post(&topCounter);
	
	printf("Customer %d is leaving the shop! \n" , no);
}

























