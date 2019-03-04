#include <iostream>
using namespace std;
struct queue{
	int value;
	queue *next;
};
queue *start,*koniec;
void enqueue(){
	int w;
	queue *niu;
	niu = new queue;
	cin>>w;
	niu->value = w;
	if(start == NULL){
		start = niu;
		koniec = niu;
		return;
	}
	koniec->next = niu;
	koniec = niu;
	return;
}
void dequeue(){
	if(start == NULL && koniec == NULL){
		cout<<"! ";
		return;
	}
	if(start == koniec){
		cout<<start->value<<" ";
		start = koniec = NULL;
		return;
	}
	cout<<start->value<<" ";
	start = start->next;
	return;
}

int main() {
	start = koniec = NULL;
	char znak;
	while(cin>>znak){
		if(znak == 'x'){
			break;
		}
		if(znak == 'e'){
			enqueue();
		}
		if(znak == 'd'){
			dequeue();
		}
		
	}
	return 0;
}