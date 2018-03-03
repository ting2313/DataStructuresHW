#include<stdio.h>
#define MAX_STACK 1002001

/*preparing for a stack*/
typedef struct{
	int x;
	int y;
}element;

element stack[MAX_STACK];
int top=-1;

void push(element item){
	stack[++top]=item;
}

element pop(){
	return stack[top--];
}

int flag_no_route=0;

void find(int n,int m,char map[n][m]){
	int temp[4]={0};
	element mem_loc;
	map[stack[top].y][stack[top].x]='1';
	if(stack[top].x+1<m){
		temp[0]=1;
		if(map[stack[top].y][stack[top].x+1]!='1'){
			mem_loc.x=stack[top].x+1;
			mem_loc.y=stack[top].y;
			push(mem_loc);
			return;
		}
	}
	if(stack[top].y+1<n){
		temp[1]=1;
		if(map[stack[top].y+1][stack[top].x]!='1'){
			mem_loc.x=stack[top].x;
			mem_loc.y=stack[top].y+1;
			push(mem_loc);
			return;
		}
	}
	if(stack[top].x-1>=0){
		temp[2]=1;
		if(map[stack[top].y][stack[top].x-1]!='1'){
			mem_loc.x=stack[top].x-1;
			mem_loc.y=stack[top].y;
			push(mem_loc);
			return;
		}
	}
	if(stack[top].y-1>=0) {
		temp[3]=1;
		if(map[stack[top].y-1][stack[top].x]!='1'){
			mem_loc.x=stack[top].x;
			mem_loc.y=stack[top].y-1;
			push(mem_loc);
			return;
		}
	}
	if(temp[0]==1&&temp[1]==1){
		if(map[stack[top].y+1][stack[top].x+1]!='1'){
			mem_loc.x=stack[top].x+1;
			mem_loc.y=stack[top].y+1;
			push(mem_loc);
			return;
		}
	}
	if(temp[1]==1&&temp[2]==1){
		if(map[stack[top].y+1][stack[top].x-1]!='1'){
			mem_loc.x=stack[top].x-1;
			mem_loc.y=stack[top].y+1;
			push(mem_loc);
			return;
		}
	}
	if(temp[2]==1&&temp[3]==1){
		if(map[stack[top].y-1][stack[top].x-1]!='1'){
			mem_loc.x=stack[top].x-1;
			mem_loc.y=stack[top].y-1;
			push(mem_loc);
			return;
		}
	}
	if(temp[3]==1&&temp[0]==1){
		if(map[stack[top].y-1][stack[top].x+1]!='1'){
			mem_loc.x=stack[top].x+1;
			mem_loc.y=stack[top].y-1;
			push(mem_loc);
			return;
		}
	}
	if(top!=0) mem_loc=pop();
	else flag_no_route=1;
}

int main(){

	int n,m,i,j;
	scanf("%d%d",&n,&m);
	char map[n][m];
	element loc;
	int flag=0;
	
	/*inicializing*/	
	for(i=0;i<n;++i){
		getchar();
		for(j=0;j<m;++j){
			scanf("%c",&map[i][j]);
			if(map[i][j]=='s'){
				loc.x=j;
				loc.y=i;
				push(loc);
			}				
		}
	}

	char origin_map[n][m];
	for(i=0;i<n;++i){
		for(j=0;j<m;++j){
			origin_map[i][j]=map[i][j];
		}
	}	

	/*find out the road and safe in the map*/
	for(;;){
		find(n,m,map);
		if(map[stack[top].y][stack[top].x]=='d') break;
		if(flag_no_route==1){
			printf("No route.\n");
			return 0;
		}
	}

	int origin_top;
	origin_top=top;

	/*replace the road with **/
	top--;
	while(top!=0){
		origin_map[stack[top].y][stack[top].x]='*';
		top--;
	}
	
	/*print*/
	printf("\n");
			
	for(i=0;i<n;++i){
		for(j=0;j<m;++j){
			printf("%c",origin_map[i][j]);
		}
		printf("\n");
	}
	
	printf("%d steps",origin_top+1);

	return 0;
}

