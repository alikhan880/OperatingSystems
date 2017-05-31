#include <windows.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

int pointsInSquare, pointsInCircle = 0;
DWORD i;

DWORD WINAPI Randomize(CONST LPVOID lpParam){
	printf("How many dots to produce?\n");
	scanf("%d", &pointsInSquare);
	for(i=0; i<pointsInSquare; i++){
		double x = (double)rand() / RAND_MAX;
		double y = (double)rand() / RAND_MAX;
		double z = x * x + y * y;
		if(z <= 1){
			pointsInCircle++;
		}
	}
	ExitThread(0);
}

int main(){

	HANDLE pointsThread;
	pointsThread = CreateThread(NULL, 0, &Randomize, NULL, 0, NULL);
	WaitForSingleObject(pointsThread, INFINITE);

	double respi = 4 * (double)pointsInCircle/pointsInSquare;
	printf("%f\n",respi );

	return 0;
}