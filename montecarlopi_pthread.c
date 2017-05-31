#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdbool.h>


int pointsInSquare, pointsInCircle = 0;

void* Randomize(){
	printf("How many dots to produce?\n");
	// int n;
	scanf("%d", &pointsInSquare);
	for(int i=0; i<pointsInSquare; i++){
		double x = (double)rand() / RAND_MAX;
		double y = (double)rand() / RAND_MAX;
		double z = x * x + y * y;
		if(z <= 1){
			pointsInCircle++;
		}
	}
}

int main(){

	pthread_t pointsThread;
	pthread_create(&pointsThread, NULL, Randomize, NULL);
	pthread_join(pointsThread, NULL);
	printf("%d\n", pointsInCircle);

	double respi = 4 * (double)pointsInCircle/pointsInSquare;
	printf("%f\n",respi );

	return 0;
}