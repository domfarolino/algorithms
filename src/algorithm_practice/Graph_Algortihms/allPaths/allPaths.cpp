#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

//Source: http://www.geeksforgeeks.org/find-paths-given-source-destination/
/*
Given a directed graph, a source vertex ‘s’ and a destination vertex ‘d’, print all paths from given ‘s’ to ‘d’.

The idea is to do Depth First Traversal of given undirected/directed graph. 
Start the traversal from source. 
Keep storing the visited vertices in an array say ‘path[]’. 
If we reach the destination vertex, print contents of path[]. 
The important thing is to mark current vertices in path[] as visited also, so that the traversal doesn’t go in a cycle.

Lets' take an example..
The graph is given in the allPaths.png file.
Let the source be 2 and destination be 3. There are 4 different paths from 2 to 3.
The answer is:

2 0 1 3
2 0 3
2 1 3 
There are 3 routes from the 2 to 3. 

*/
int c=0;
struct Graph
{
	int size; //Total Number of Nodes in the Graph
	list<int> adj[1000];
};
void addEdge(struct Graph *g,int v,int w)
{
	g->adj[v].push_back(w); 
	//g->adj[w].push_back(v); Uncomment this Line if you want To make an undirected graph
}
void DFSut(struct Graph *g,int visited[],int v)
{
	visited[v]=1;
	cout<<v<<" "; 
	list<int>::iterator i;
	for(i=g->adj[v].begin();i!=g->adj[v].end();i++)
	{
		if(visited[*i]==0)
			DFSut(g,visited,*i);
	}
}
void DFS(struct Graph *g,int visited[],int v)
{
	DFSut(g,visited,v);
}


void printAll(struct Graph *g,int s,int d,int visited[],int path[],int &index)
{
	visited[s]=1;
	path[index]=s;
	index++;
	//int i;
	if(s == d)
	{
		c++;
		for(int i=0;i<index;i++)
		{
			cout<<path[i]<<" ";
		}
		cout<<endl;
	}
	else
	{

		list<int>::iterator i;
		for(i=g->adj[s].begin();i!=g->adj[s].end();i++)
		{
		if(visited[*i]==0)
			printAll(g,*i,d,visited,path,index);
		}
		
	}
	index--;
	visited[s]=0;
}
void printPath(struct Graph *g,int s,int d)
{
	int visited[10000]={0};
	int path[10000]={0};
	int i;
	int index=0;
	printAll(g,s,d,visited,path,index);
	printf("There are %d routes from the %d to %d.\n",c,s,d );
	c=0;
}


int main(int argc, char const *argv[])
{
		
		int i;
		struct Graph *g=new Graph();
		int end;
		int a,b,start;
		cout<<"Enter the start Vertex:";
		cin>>start;
		cout<<"Enter the end Vertex:";
		cin>>end;
		g->size=100; //Total Number of nodes 
		cout<<"Building the Graph:\n";
		while(1)
		{
		
			cout<<"Enter (0 0 to Exit)\n";
			cout<<"Enter Source and Destination of the edge:";
			cin>>a>>b;
			if(a == 0 && b==0)
				break;
			addEdge(g,a,b);
		}
	
	printPath(g,start,end);
	return 0;
}