#include <stdio.h>
#include <stdbool.h>

int mem[200], inUse[200], n, sz, pntr = 0, refstring[200];

void clear(){
	int i;
	for(i=0; i<200; i++){
		mem[i] = -1;
		inUse[i] = 0;
	}
}

void pop_front_and_push(int x){
	int i;
	inUse[mem[0]] = 0;
	for(i=0; i<sz-1; i++){
		mem[i] = mem[i+1];
	}
	mem[sz-1] = x;
}

void find_and_replace(int x){
	int idx;
	int i;
	for(i=0; i<sz; i++) 
		if(mem[i] == x){
			idx = i;
			break;
		}
	for(i=idx; i<sz-1; i++){
		mem[i] = mem[i+1];
	}
	mem[sz-1] = x;
}

int main(){

	FILE *input = fopen("input.txt", "r");
	while(fscanf(input, "%d", &refstring[n++]) != EOF); n--;

	printf("Enter the size of the memory\n");
	scanf("%d", &sz);
	clear();
	int i;
	int pf = 0;
	for(i=0; i<n; i++){
		bool check = false;
		if(!inUse[refstring[i]]){
			check = true;
			pf++;
			inUse[refstring[i]] = 1;
			if(mem[pntr] == -1){
				mem[pntr] = refstring[i];
				pntr = (pntr + 1) % sz;
			}
			else{
				pop_front_and_push(refstring[i]);
			}
		}
		else{
			find_and_replace(refstring[i]);
		}
		int j;
		for(j=0; j<sz; j++) if(mem[j] != -1) printf("%d ", mem[j]);
		if(check) printf("  Page fault\n");
		else printf("\n");
	}
	printf("Number of page faults %d\n", pf);
	return 0;
}