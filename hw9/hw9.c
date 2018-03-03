#include <stdio.h>
#include <stdlib.h>

int MAX_A;
int MAX_E;

typedef struct activity{
	int name,start,end,dur;
}activity;

typedef struct event *e_ptr;
typedef struct event{
	int name,dur,co_event;
	e_ptr link;
}event;

typedef struct head_event{
	e_ptr from_here;
	e_ptr to_here;
}head_event;

int main(){
	
	/*inicialize*/
	int i,j;
	e_ptr e_temp;
	scanf("%d",&MAX_A);
	MAX_A++;
	MAX_E = 0;
	activity all_activity[MAX_A];
	for(i=1;i<MAX_A;i++){
		getchar();
		scanf("%d",&all_activity[i].name);
		getchar();
		scanf("%d",&all_activity[i].start);
		getchar();
		scanf("%d",&all_activity[i].end);
		if(MAX_E < all_activity[i].end)
			MAX_E = all_activity[i].end;
		getchar();
		scanf("%d",&all_activity[i].dur);
	}
	MAX_E++;
	head_event route[MAX_E];
	e_ptr head_ptr[MAX_E][2]; //[0]from [1]to

	for(i=0;i<MAX_E;i++){
		route[i].from_here = NULL;
		route[i].to_here = NULL;
		head_ptr[i][0] = NULL;
		head_ptr[i][1] = NULL;
	}
	
	/*link the event to "from_here"*/
	for(i=1;i<MAX_A;i++){
		e_temp = malloc(sizeof(event));
		e_temp->name = all_activity[i].name;
		e_temp->dur = all_activity[i].dur;
		e_temp->link = NULL;
		e_temp->co_event = all_activity[i].end;
		if(head_ptr[all_activity[i].start][0] == NULL){
			head_ptr[all_activity[i].start][0] = e_temp;
			route[all_activity[i].start].from_here = e_temp;
		}
		else{
			head_ptr[all_activity[i].start][0]->link = e_temp;
			head_ptr[all_activity[i].start][0]  = e_temp;
		}
	}
	
	/*link the event to "to_here"*/
	for(i=1;i<MAX_A;i++){
		e_temp = malloc(sizeof(event));
		e_temp->name = all_activity[i].name;
		e_temp->dur = all_activity[i].dur;
		e_temp->link = NULL;
		e_temp->co_event = all_activity[i].start;
		if(head_ptr[all_activity[i].end][1] == NULL){
			head_ptr[all_activity[i].end][1] = e_temp;
			route[all_activity[i].end].to_here = e_temp;
		}
		else{
			head_ptr[all_activity[i].end][1]->link = e_temp;
			head_ptr[all_activity[i].end][1]  = e_temp;
			printf("%d:%d\n",i,all_activity[i].end);
		}	
	}
	
	/*compute ee&le*/
	int ee[MAX_E];
	int le[MAX_E];
	e_ptr find_temp = NULL;
	for(i=0;i<MAX_E;i++){
		le[i] = 99;
		ee[i] = 0;
	}
	
	for(i=0;i<MAX_E;i++){
		find_temp = route[i].to_here;
		while(find_temp!=NULL){
			if( (find_temp->dur)+ee[find_temp->co_event] > ee[i]){
				ee[i] = (find_temp->dur) + ee[find_temp->co_event];
			}
			find_temp = find_temp->link;
		}
	}
	
	le[MAX_E-1] = ee[MAX_E-1];
	for(i=MAX_E-1;i>=0;i--){
		find_temp = route[i].from_here;
		while(find_temp!=NULL){
			if(le[find_temp->co_event] - (find_temp->dur) < le[i])
				le[i] = le[find_temp->co_event] - (find_temp->dur);
			find_temp = find_temp->link;
		}
	}
	
	/*compute e,l*/
	int e[MAX_A],l[MAX_A];
	for(i=1;i<MAX_A;i++){
		e[i] = ee[all_activity[i].start];
		l[i] = le[all_activity[i].end]-all_activity[i].dur;
	}
	
	/*print*/
	printf("a.\n");
	printf("    ee le\n");
	for(i=0;i<MAX_E;i++){
		printf("%2d  %2d %2d\n",i,ee[i],le[i]);
	}
	printf("b.\n");
	printf("    e  l  s  c \n");
	for(i=1;i<MAX_A;i++){
		printf("%2d %2d %2d %2d  ",i,e[i],l[i],l[i]-e[i]);
		if(l[i]-e[i]==0) printf("Y\n");
		else printf("N\n");
	}
	
	return 0;
}