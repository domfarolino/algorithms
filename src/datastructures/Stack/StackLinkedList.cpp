#include<iostream>
#include<cstdlib>
using namespace std;
class node{
private:
	int data;
	node *next;
    node *top=NULL;
public:
	void push();
	void pop();
	void display();
};

void node::push(){
	 node *temp = new node;
        int val;
        cout<<"enter the value you want to insert";
        cin>>temp->data;
        node *t = top;
        temp->next = NULL;
        if(top==NULL){
        top = temp;
    }
        else{
            node *t = top;
            temp->next = t;
            top = temp;
        }
	}
	void node::pop(){
		node *t = top;
		if(t==NULL){
			cout<<"\nList is empty";
		}
		else{
			top=t->next;
			cout<<"element popped is "<<t->data;
			delete t;
		}
	}
	void node::display(){
		node* t=top;
		if(t==NULL){
			cout<<"\nList is empty";
		}	
		while(t!=NULL){
				cout<<t->data<<" ";
				t= t->next;
			}
			cout<<endl;
	}
int main(){
	int choice,size,val;
	node n;
	cout<<"1 for push"<<endl<<"2 for pop"<<endl<<"3 for display"<<endl<<"4 for exit";
	while(1){
	cout<<endl<<"enter the choice";
	cin>>choice;
	switch(choice){
		case 1:{
			n.push();
			break;
		}
		case 2:{
			n.pop();
			break;
		}
		case 3:{
			n.display();
			break;
		}
		case 4:{
			exit(0);
			break;
		}
	}
}
}
