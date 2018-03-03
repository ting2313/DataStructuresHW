#include<stdio.h>

int hanoi(int n){
	if(n==1) return 1;
	else return (2*hanoi(n-1)+1);
}

int main(){
	int n;
	scanf("%d",&n);
	printf("Disk:%d\n",n);
	n=hanoi(n);
	printf("Total step:%d\n",n);
	return 0;
}

