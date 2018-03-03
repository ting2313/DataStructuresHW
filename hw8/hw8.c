#include <stdio.h>
#include <stdlib.h>

int cost[9][9];
int distance[9][9];
int route[9][9][9];//start->end->route
int count[9][9];//start->end

void allCost(){
	int i,j,k,m,n;
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			distance[i][j] = cost[i][j];
	
	for(k=0;k<9;k++)
		for(i=0;i<9;i++)
			for(j=0;j<9;j++)
				if(distance[i][k]+distance[k][j]<distance[i][j]){
					distance[i][j] = distance[i][k]+distance[k][j];
					count[i][j] = 0;
					for(m=0;m<count[i][k];m++){
						route[i][j][m] = route[i][k][m];
						count[i][j]++;
					}
					route[i][j][m] = k;
					count[i][j]++;
					for(n=0;n<count[k][j];n++){
						route[i][j][n+m+1] = route[k][j][n];
						count[i][j]++;
					}
				}
}

int main(){

	int start,end;
	int i,j;
	for(i=0;i<9;i++){
		count[i][j] = 0;
		for(j=0;j<9;j++){
				cost[i][j] = 200;
			}
	}
	cost[0][1] = 5;
	cost[0][2] = 4;
	cost[0][3] = 2;
	cost[1][4] = 3;
	cost[2][1] = 1;
	cost[2][4] = 2;
	cost[2][5] = 8;
	cost[3][2] = 1;
	cost[3][5] = 7;
	cost[4][6] = 7;
	cost[4][8] = 15;
	cost[4][7] = 10;
	cost[5][7] = 3;
	cost[6][8] = 6;
	cost[7][8] = 5;

	scanf("%d",&start);
	getchar();
	scanf("%d",&end);
	
	allCost();

	if(distance[start][end]==200){
		printf("No solution.\n");
		return 0;
	}
	printf("Distance:%d\n",distance[start][end]);
	printf("The route for the shortest path:%d->",start);
	for(i=0;i<count[start][end];i++){
		printf("%d->",route[start][end][i]);
	}
	printf("%d\n",end);
	
	return 0;
}