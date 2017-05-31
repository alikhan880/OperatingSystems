#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <windows.h>
int refstring[1000], n, head, used[1000], copy[1000], copy2[1000];

void clear(){
	int i;
	for(i=0; i<n; i++){
		used[i] = 0;
	}
}

void FCFS(){
	int ans = 0;
	int x = head;
	int i;
	for(i=0; i<n; i++){
		ans += abs(x - refstring[i]);
		x = refstring[i];
	}
	printf("Total head movement for FCFS is %d\n", ans);
}

void sort(int x){
	int i, j;
	for(i = 0; i < n; i++){
		for(j=0; j < n-1; j++){
			if(abs(x - copy[j]) > abs(x - copy[j + 1])){
				int temp = copy[j];
				copy[j] = copy[j+1];
				copy[j+1] = temp;
			}
		}
	}
}

bool check(){
	int i;
	for(i = 0; i < n; i++){
		if(!used[copy[i]]) return true;
	}
	return false;
}

void SSTF(){
	clear();
	int ans = 0;
	int i;
	int x = head;
	for(i = 0; i < n; i++) copy[i] = refstring[i];
	while(check()){
		sort(x);
		int t = 0;
		while(used[copy[t]]) t++;
		ans += abs(x - copy[t]);
		x = copy[t];
		used[copy[t]] = 1; 
	}
	printf("Total head movement for SSTF is %d\n", ans);
}


void SCAN(){
	srand(time(NULL));
	int iterations;
	int ans = 0, mass[1000], sz = 0;
	// int used[1000]; 
	int k;
	for(k=0; k<1000; k++){
		mass[k] = -1;
		used[k] = 0;
	}
	printf("How many iterations?\n");
	scanf("%d", &iterations);
	int way = -1;
	while(iterations--){
		if(head <= 0) way = 1;
		else if(head >= 99) way = -1;
		head += way;
		int rdot = rand() % 99;
		used[rdot] = 0;
		printf("Generated dot: %d\n", rdot);
		mass[sz++] = rdot;
		if(way == -1){
			int i, j;
			for(i=0; i<sz; i++){
				for(j=0; j<sz-1; j++){
					if(mass[j] < mass[j+1]){
						int temp = mass[j+1];
						mass[j+1] = mass[j];
						mass[j] = temp;
					}
				}
			}
			int idx = 0;
			bool check = false;
			while(idx < sz){
				if(!used[mass[idx]] && mass[idx] != -1 && mass[idx] < head){
					check = true;
					break;
				}
				idx++;
			}
			if(check){
				printf("Head moves from %d to %d\n", head, mass[idx]);
				ans += abs(head - mass[idx]);
				head = mass[idx];
				used[mass[idx]] = 1;
			}
			else{
				ans += 1;
			}
		}
		else if(way == 1){
			int i, j;
			for(i=0; i<sz; i++){
				for(j=0; j<sz-1; j++){
					if(mass[j] > mass[j+1]){
						int temp = mass[j+1];
						mass[j+1] = mass[j];
						mass[j] = temp;
					}
				}
			}
			int idx = 0;
			bool check = false;
			while(idx < sz){
				if(mass[idx] != -1 && !used[mass[idx]] && mass[idx] >= head){
					check = true;
					break;
				}
				idx++;
			}
			if(check){
				printf("Head moves from %d to %d\n", head, mass[idx]);
				ans += abs(head - mass[idx]);
				head = mass[idx];
				used[mass[idx]] = 1;
			}
			else{
				ans += 1;
			}
		}
	}
	printf("Total head movement is %d\n", ans);
}
	
void C_SCAN(){
	int iterations, mass[1000], sz = 0, ans = 0;
	int k;
	for(k=0; k<1000; k++){
		used[k] = 0;
		mass[k] = -1;
	}
	srand(time(NULL));
	printf("How many iterations?\n");
	scanf("%d", &iterations);
	while(iterations--){
		if(head >= 100) head = 0;
		head++;
		int rdot = rand() % 80;
		used[rdot] = 0;
		printf("Generated %d\n", rdot);
		mass[sz++] = rdot;
		int i, j;
		for(i=0; i<sz; i++){
			for(j=0; j<sz-1; j++){
				if(mass[j] > mass[j+1]){
					int temp = mass[j+1];
					mass[j+1] = mass[j];
					mass[j] = temp;
				}
			}
		}
		int idx = 0;
		bool check = false;
		while(idx < sz){
			if(mass[idx] != -1 && !used[mass[idx]] && head <= mass[idx]){
				check = true;
				break;
			}
			idx++;
		}
		if(check){
			printf("Head moves from %d to %d\n", head, mass[idx]);
			ans += abs(head - mass[idx]);
			used[mass[idx]] = 1;
			head = mass[idx];
		}
		else{
			ans++;
		}
	}
	printf("Total head movement is %d\n", ans);
}

int main(){

	FILE *input = fopen("input2.txt", "r");
	while(fscanf(input, "%d", &refstring[n++]) != EOF);n--;
	printf("Enter the value of the head\n");
	scanf("%d", &head);

	// FCFS();
	// SSTF();
	// SCAN();
	C_SCAN();


}