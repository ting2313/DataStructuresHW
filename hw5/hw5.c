#include <stdio.h>
#include <stdlib.h>

int scale=0;
int deep=1;
typedef struct node *treeptr;
typedef struct node{
	int key;
	treeptr left,right;
}node;

typedef struct queue *queptr;
typedef struct queue{
	unsigned long int address;
	queptr link;
}queue;
queptr front = NULL;
queptr rear = NULL;

void addq(unsigned long int num){
	queptr temp = malloc(sizeof(queue));
	temp->address = num;
	temp->link = NULL;
	if(rear){
		rear->link = temp;
		rear = temp ;
	}
	else{
		front = rear = temp;
	}
}

unsigned long int deleteq(){
	if(rear==front) {
		rear=NULL;
	}
	unsigned long int num = front->address;
	queptr temp = front;
	front = front->link;
	free(temp);
	return num;
}

void cleanq(){
	while(rear){
		deleteq();
	}
}

void insert(treeptr *head,int num){
	scale++;
	treeptr temp = malloc(sizeof(node));
	temp->key = num;
	temp->left = NULL;
	temp->right = NULL;
    treeptr now = (*head);
	int count = 1;
	while(1){
		if(now->key > num){
			count++;
			if(count > deep) deep = count;
			if(now->left) now = now->left;
			else {
				now->left = temp;
				return;
			}
		}
		else{
			count++;
			if(count > deep) deep = count;
			if(now->right) now = now->right;
			else{
				now->right = temp;
				return;
			}
		}
	}
}


void delete(treeptr *head,int num){
    treeptr now = (*head);
	treeptr last = NULL;
	treeptr add = NULL;
	int flag_left = 1;
	int temp;
	while(now->key!=num){
		if(now->key > num){
			last = now;
			now = now->left;
			flag_left = 1;
		}
		else if(now->key < num){
			last = now;
			now = now->right;
			flag_left = 0;
		}
	}
	
	if(!(now->left)&&!(now->right)){
		free(now);
		now = NULL;
		if(flag_left==1) last->left = NULL;
		else last->right = NULL;
		return;
	}
			
	else if(!(now->right)){
		printf("\nno right\n");
		if(flag_left==1) last->left = now->left;
		else last->right = now->left;
		free(now);
		now = NULL;
		return;
	}
	else if(!(now->left)){
		if(flag_left==1) last->left = now->right;
		else last->right = now->right;
		free(now);
		now = NULL;
		return;
	}	
	
	else {
		add = now;
		last = now;
		now = now->left;
		printf("%d",now->key);
		while(now->right) {
			last = now;
			now = now->right;
			printf("\n%d\n",now->key);
		}
		add->key = now->key;
		delete(&last,now->key);
	}			
}
			

int search(treeptr *head,int num){
	treeptr now = (*head);
	int flag_left = 1;
	int temp;
	while(1){
		if(now->key > num){
			if(now->left) now = now->left;
			else return 0;
		}
		else if(now->key < num){
			if(now->right) now = now->right;
			else return 0;
		}
		else if((now->key)==num){
			return 1;
		}
	}
}

int full_node(){
	int i = deep;
	int ans = 1;
	for(;i>0;i--){
		ans = ans*2;
	}
	return (ans-1);
}

void print(treeptr *head){
	cleanq();
	treeptr now = (*head);
	int count = full_node();
	int row_print = 0;
	int row_long = 2; //the edge of the row
	printf("%2d \n",now->key);
	addq((unsigned long int)now);
	count--;
	while(count > 0){
		now = deleteq();
		if(now==NULL){
			printf(" *  * ");
			count-=2;
			row_print+=2;
			addq((unsigned long int)NULL);
			addq((unsigned long int)NULL);
		}
		else if(now->left) {
			printf("%2d ",now->left->key);
			count--;
			row_print++;
			addq((unsigned long int)now->left);
		}		
		else{
			printf(" * ");
			count--;
			row_print++;
			addq((unsigned long int)NULL);
		}
		if(now==NULL){}
		else if(now->right){
			printf("%2d ",now->right->key);
			count--;
			row_print++;
			addq((unsigned long int)now->right);
		}
		else{
			printf(" * ");
			count--;
			row_print++;
			addq((unsigned long int)NULL);
		}
		if(row_long==row_print){
			printf("\n");
			row_long *= 2 ;
			row_print = 0;
		}
	}
}

int main(){
  treeptr head = malloc(sizeof(node));
  head->left = NULL;
  head->right= NULL;
  int temp;
  char mode;
  int exist;
  
  scanf("%d",&(head->key));
  scale++;
  while(1){
	  getchar();
	  scanf("%d",&temp); 
	  if(temp==(-1)) break;
	  insert(&head,temp);
  }
  getchar();
  
  printf("Create Binary search tree\n");
  print(&head);
   
  printf("Delete element?(Y/N)");

  scanf("%c",&mode);
  getchar();
  
  while(mode=='Y'){
	scale--;
	printf("Choice element:");
	scanf("%d",&temp);
	getchar();
	
	exist = search(&head,temp);
	if(exist == 0) printf("%d is not in the tree",temp);
	else {
		delete(&head,temp);
		printf("\nBinary search tree\n");
		print(&head);
	}
	printf("\nDelete element?(Y/N)");
	scanf("%c",&mode);
	getchar();
  }
  
  return 0;
}
