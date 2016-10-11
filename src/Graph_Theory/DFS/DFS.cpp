#include<iostream>
using namespace std;

/*
	test values have been alongside in the comments.
*/


class node{
	int val,*adj,size;
	char col;
	public:
		int get_val()
		{
			return val;
		}
		void put_val(int x)
		{
			val=x;
		}
		char get_col()
		{
			return col;
		}
		int put_col(char x)				//returns value 0 or  1 depending on the fact that x=='w'
		{
			if(x=='w'||x=='g'||x=='b')
			{
				col=x;
				return 1;
			}
			return 0;
		}
		void put_adj(int n)					
		{
			int x;
			size=n;
			adj=new int(n);
			if(n!=0)
			cout<<"Enter the nodes one-by-one\n";
			/*
			{2,5,
			1,18,19,
			1,23,57,
			2,92,
			2,92,
			5,92,
			5,92,
			18,19,23,57}
			*/
			for(int i=0; i<n; ++i)
			{
				cin>>x;
				*(adj+i)=x;
			}
		}
		int* get_adj()
		{
			return adj;
		}
		int find_n()
		{
			return size;
		}
};

node visit_forward(node g[],node u,int n)
{
	int *temp=new int(n),i;
	temp=u.get_adj();
	for(i=0;i<n;++i)
	{
		if(g[*(temp+i)-1].get_col()=='w')
		{
			cout<<g[*(temp+i)-1].get_val();
			g[*(temp+i)-1].put_col('g');
			visit_forward(g,g[*(temp+i)-1],g[*(temp+i)-1].find_n());
			//cout<<"\nb";
		}
		
	}
	g[i].put_col('b');
	return u;
}

int main()
{
	int ctr_n,ctr_e,i,j,t,n;									//e=edges,n=nodes
	cout<<"Enter the number of nodes\n";
	cin>>ctr_n;													//for test give n=8
	cout<<"Enter the number of edges\n";						
	cin>>ctr_e;
	node g[ctr_n];
	for(i=0;i<ctr_n;++i)
	{
		int flag=0;
		while(!flag)				//this loop is just to check that no node is assigned a color apart from white, black or grey.
		{
			flag=g[i].put_col('w');
		}
		cout<<"Enter the value for node "<<i+1<<" :\n";
		cin>>t;															//	{1,2,5,18,1,23,57,92}
		g[i].put_val(t);
		cout<<"Enter the number of nodes to which the current node is connected\n";
		cin>>n;														   //   {2,3,3,2,2,2,2,4}
		g[i].put_adj(n);
	}
	for(i=0;i<ctr_n;++i)
	{
		if(g[i].get_col()=='w')
		{
			g[i].put_col('g');
			cout<<g[i].get_val();
		}
		g[i]=visit_forward(g,g[i],g[i].find_n());
		//g[i].put_col('b');
	}
	return 0;
}

