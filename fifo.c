#include <stdio.h>
#include <stdbool.h>


int inUse[200], mem[200];
int n = 0, refstring[200];
int sz;

void clear(){
	int i;
	for(i=0; i<200; i++){
		mem[i] = -1;
		inUse[i] = 0;
	}
}

int main(){
	FILE *input = fopen("input.txt", "r");
	while(fscanf(input,"%d", &refstring[n++]) != EOF); n--;
	clear();
	printf("Enter the size of the memory array\n");
	scanf("%d", &sz);
	int pntr = 0;
	int i;
	int pf = 0;
	for(i=0; i<n; i++){
		bool check = false;
		if(inUse[refstring[i]] == 0){
			check = true;
			pf++;
			inUse[refstring[i]] = 1;
			int temp  = mem[pntr];
			if(temp != -1) inUse[temp] = 0;
			mem[pntr] = refstring[i];
			pntr = (pntr + 1) % sz;
		}
		int j;
		for(j=0; j<sz; j++){
			if(mem[j] != -1) printf(" %d", mem[j]);
			if(j == pntr && mem[j] != -1) printf("*");
		}
		if(check) printf("   Page fault\n");
		else printf("\n");
	}

	printf("Number of page faults %d\n", pf);

	return 0;
}