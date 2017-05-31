#include <stdio.h>
#include <stdlib.h>

int used[1000];

int main(){
	time_t t;
	srand((unsigned) time(&t));
	FILE *output = fopen("input.txt", "w");
	int rnd = rand()%100;
	fprintf(output, "%d\n", rnd);
	int i;
	for(i=0; i<rnd;){
		int x = rand()%rnd;
		int y = rand();
		if(!used[x]){
			i++;
			used[x] = 1;
			fprintf(output, "%d %d\n", x, y);
		}
	}
	fprintf(output, "\n");
	int refsz = rand()%100;
	fprintf(output, "%d\n", refsz);
	for(i=0; i<refsz;){
		int t = rand() % rnd;
		int offset = rand() % rnd; 
		if(used[t]){
			fprintf(output, "%d %d\n", t, offset);
			i++;
		}
	}
}