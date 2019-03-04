#include <iostream>
using namespace std;
struct queue{
	int value;
	queue *pre;
	queue *next;
};
queue *start,*aktualny;
void enqueue(){
	int w;
	queue *niu;
	
	niu = new queue;
	cin>>w;
	niu->value = w;
	if(start == NULL){
		niu->pre = NULL;
		niu->next = NULL;
		start = niu;
		aktualny = niu;
		return;
	}
	niu->pre = aktualny;
	niu->next = aktualny->next;
	aktualny->next = niu;
	aktualny = niu;
	return;
}
void dequeue(){
	if(start == NULL && aktualny == NULL){
		return;
	}
	
	if(aktualny->pre == NULL){
		if(aktualny->next == NULL){
			cout<<aktualny->value<<" ";
			start = aktualny = NULL;
		} else {
			aktualny->next->pre = NULL;
			if(aktualny == start){
				start = aktualny->next;
			}
			aktualny = aktualny->next;
		}
	} else {
		aktualny->pre->next = aktualny->next;
		aktualny->next->pre = aktualny->pre;
		aktualny = aktualny->pre;
	}
	return;
}
queue *search(int n){
	int i=1;
	aktualny = start;
	while((aktualny->next != NULL)&& i++<n){
		aktualny = aktualny->next;
	}
	return aktualny;	
}

int main() {
	start = aktualny = NULL;
	char znak;
	int n;
	queue *wypis;
	
	while(cin>>znak){
		if(znak == 'x'){
			break;
		}
		if(znak == 'i'){
			enqueue();
		}
		if(znak == 'd'){
			dequeue();
		}
		if(znak == 's'){
			cin>>n;
			aktualny = search(n);
		}
	}
	wypis = start;
	while(wypis != NULL){
		cout<<wypis->value<<" ";
		wypis = wypis->next;
	}
	cout<<"\nPoczatek: ";
	if(start != NULL){
			cout<<start->value;
	}
	cout<<", Biezacy: ";
	if(aktualny != NULL){
		cout<<aktualny->value;
	}
	
	return 0;
}