#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int parent[MAX];

void heightUnion(int i,int j){
	if(-parent[i] < -parent[j]){
		parent[i] = j;
	}
	else if(-parent[i] > -parent[j]){
		parent[j] = i;
	}
	else{
		parent[j] = i;
		parent[i] -= 1;
	}
}

int main(){
	int i;
	for(i=0;i<MAX;i++){
		parent[i] = -1;
	}
	int n;
	scanf("%d",&n);
	
	for(i=1;i<n;i++){
		heightUnion(0,i);
	}
	
	printf("Node   parent\n");
	for(i=0;i<n;i++){
		if(parent[i]>=0)
			printf("%d      %d\n",i,parent[i]);
		else
			printf("%d      root\n",i);
	}
	
	return 0;
}