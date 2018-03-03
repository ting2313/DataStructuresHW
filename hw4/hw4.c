#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int data;
	unsigned long int link;
}node;

int main(){
  node* head = malloc(sizeof(node));
  node* now = NULL;
  node* next = NULL;
  node* pre = NULL;
  node* temp = NULL;
  node* tail = NULL;
  now = head;
  temp = now;
  now->data = 1; 
  int i;
  
  for(i=2;i<=20;i++){
	next = malloc(sizeof(node));
	next->data = i;
	now->link = (unsigned long int)pre^(unsigned long int)next;
	now = (unsigned long int)pre^now->link;
	pre = temp;
	temp = now;
  }
  tail = now;
  now->link = (unsigned long int)NULL ^ (unsigned long int)pre;
  
  printf("The data from left to right:\n");  
  now = head;
  pre = NULL;
  temp = now;
  
  for(i=1;i<=19;i++){
	printf("%d, ",now->data);
	now = (unsigned long int)pre^now->link;
	pre = temp;
	temp = now;
  }
  printf("%d",now->data);
  
  printf("\n\nThe data from right to left:\n");
  now = tail;
  pre = NULL;
  temp = now;
  for(i=1;i<=19;i++){
	printf("%d, ",now->data);
	now = (unsigned long int)pre^now->link;
	pre = temp;
	temp = now; 	
  }
  printf("%d\n",now->data);	
	
  return 0;
}