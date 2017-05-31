#include <stdio.h>
#include <stdbool.h>

int page_table[1000], tpn[1000], tpfn[1000], refstring[1000], used[1000], usedtlb[1000], refstringoffset[1000];
int szrs = 0,pnt_pagetable = 0, szpt = 0, pnt_tlb = 0, sztlb = 0, tlbhit = 0;

void clear(){
	int i;
	for(i = 0; i < 1000; i++){
		page_table[i] = -1;
		tpn[i] = -1;
		tpfn[i] = -1;
		used[i] = 0;
	}
}

void setup(){
	clear();
	FILE *input = fopen("input.txt", "r");
	fscanf(input, "%d", &szpt);
	int i;
	for(i = 0; i < szpt; i++){
		int x, y;
		fscanf(input, "%d %d", &x, &y);
		page_table[x] = y;
	}
	fscanf(input, "%d", &szrs);
	for(i=0; i<szrs; i++) fscanf(input, "%d %d", &refstring[i], &refstringoffset[i]);
	printf("Enter the size of TLB\n");
	scanf("%d", &sztlb);

}

void pop_front_and_push(int x, int y, int z){
	printf("Erasing page %d from TLB and replacing with page %d\n", tpn[0], x);
	used[tpn[0]] = 0;
	used[x] = 1;
	int i;
	for(i = 0; i < sztlb-1; i++){
		tpn[i] = tpn[i+1]; 
		tpfn[i] = tpfn[i+1];
	}
	tpn[sztlb - 1] = x;
	tpfn[sztlb - 1] = y;
	printf("Frame is %d. Offset is %d\n", y, z);

}

void find_and_replace(int x, int y){
	int idx;
	int i;
	for(i=0; i<sztlb; i++) 
		if(tpn[i] == x){
			idx = i;
			break;
		}
	for(i=idx; i<sztlb-1; i++){
		tpn[i] = tpn[i+1];
		tpfn[i] = tpfn[i+1];
	}
	tpn[sztlb-1] = x;
	tpfn[sztlb-1] = y;
}

void print(){
	int i;
	for(i=0; i<12; i++) printf("-");
	printf("\n");
	printf("  TLB state  \n");
	for(i=0; i<12; i++) printf("-");
	printf("\n");
	for(i=0; i<sztlb; i++){
		if(tpn[i] != -1) printf("|%d | %d|\n", tpn[i], tpfn[i]);
	}
	printf("\n\n");
}

bool check(){
	int i;
	for(i=0; i<sztlb; i++) if(tpn[i] == -1) return true;
	return false;
}

void swap(){
	int i;
	for(i=0; i<sztlb; i++){
		int j;
		for(j=0; j<sztlb-1; j++){
			if(tpn[j] == -1 && tpn[j+1] != -1){
				int tempp = tpn[j+1];
				tpn[j+1] = tpn[j];
				tpn[j] = tempp;
				int tempf = tpfn[j+1];
				tpfn[j+1] = tpfn[j];
				tpfn[j] = tempf;
			}
		}
	}
}

int main(){
	setup();
	int i, k;
	for(k = 0; k < szrs; k++){
		swap();
		print();
		if(!used[refstring[k]]){
			printf("TLB miss occurred. Looking in page table for page %d\n", refstring[k]);
			if(check()){
				int i;
				for(i=0; i < sztlb; i++){
					if(tpn[i] == -1){
						pnt_tlb = i;
						break;
					}
				}
				tpn[pnt_tlb] = refstring[k];
				tpfn[pnt_tlb] = page_table[refstring[k]];
				used[refstring[k]] = 1;
			}
			else{
				pop_front_and_push(refstring[k],page_table[refstring[k]], refstringoffset[k]);
			}
		}
		else{
			printf("Page %d is in TLB. TLB hit occurred\n", refstring[k]);
			find_and_replace(refstring[k],page_table[refstring[k]]);
			printf("Frame is %d. Offset is %d\n", page_table[refstring[k]], refstringoffset[k]);
			tlbhit++;
		}
		if(k == szrs - 1) print();
	}

	printf("Hit ratio is: %2.f%%\n", (float)tlbhit/(float)szrs * 100.0);


	return 0;
}