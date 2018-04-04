#include"node.h"
#include<iostream>

class list
{
	node * chain; 
public: 
	list();
void add(int item);
int getNodeData(int x); //return data of node x at list
node * getNode(int x);  //return pointer points to node number x
int sum();
int max();
};

list::list() :chain(NULL){}

void list::add(int item){
	node * temp = chain;
	if (chain == NULL) chain = new node(item);
	else
	{
		for (; temp->next!= NULL; temp = temp->next);
		temp->next = new node(item);
	}
}
int list::getNodeData(int x){
	if (x == 1) { if (chain == NULL) return 0; else return chain->data; }
	if (x > 1){
		node * temp = chain;
		for (int i = 1; i<x && temp != NULL; i++)
			temp = temp->next;
		if (temp == NULL) return 0;
		else
			return temp->data;
	}
	if (x<1) return 0;
} //return data of node x at list

int list::sum(){
	node * temp = chain;
	int s = 0;
	if (chain == NULL) return 0;
	if (chain->next == NULL) return chain->data;
	for (; temp->next != NULL; temp = temp->next)
		s += temp->data;
	return (s + temp->data);
}

node * list::getNode(int x){
	if (x == 1) { return chain; }
	if (x > 1){
		node * temp = chain;
		for (int i = 1; i<x && temp != NULL; i++)
			temp = temp->next;
		if (temp == NULL) return NULL;
		else
			return temp;
	}
	if (x<1) return NULL;

}
int list::max(){
	node * temp = chain;
	int max = temp->data;
	temp = temp->next;
	for (; temp != NULL; temp = temp->next)
	{
		if (max < temp->data)
			max = temp->data;
	}
	return max;
}

