#include<stdio.h>
#include<stdlib.h>

int coeff(int n,int k){
	if(k!=0 && n>1 && n!=k)	{
		return coeff(n-1,k-1)+coeff(n-1,k);
	}
	else return 1;
}

int main(){
	int n;
	int k;
	int ans;
	
	scanf("%d %d",&n,&k);	
	ans=coeff(n,k);
	
	printf("%d",ans);
	
	return 0;
}

