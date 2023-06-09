
/*
This is a implementation of the general (0,1) knapsack problem

Problem statement:Given a set of items, each with a weight and a value, determine the number of each item 
to include in a collection so that the total weight is less than or equal to a given limit and the total value is as large as possible.

Code:-
To consider all subsets of items, there can be two cases for every item: (1) the item is included in the optimal subset, (2) not included in the optimal set.
Therefore, the maximum value that can be obtained from n items is max of following two values.
1) Maximum value obtained by n-1 items and W weight (excluding nth item).
2) Value of nth item plus maximum value obtained by n-1 items and W minus weight of the nth item (including nth item).

We exploit this property for knapsack problem and build a 2-D array for storing value corresponding to certain weight and no of items

Time Complexity: O(nW) where n is the number of items and W is the capacity of knapsack.



*/








#include<bits/stdc++.h>

using namespace std;

//returns maximum of two numbers
int maxm(int a, int b) {
    return (a > b)? a : b; 
}


//a DP implementation of the famous knapsack problem 
/*
Each element of the array k stores the optimal value for the corresponding weight size and number of items.
We see that the relation comes out to be (from the initial discussion):

k[i][j]=maxm(k[i-1][j-w[i-1]]+v[i-1],k[i-1][j]);

i.e >If you take the last weight find and optimal solution as if the weight didnt exist and If you dont the optimal
solution is just k[i-1][j].
*/
int knapsack(int v[],int w[],int n,int wmax){
    
    int k[n+1][wmax+1];
    

    for(int i=0;i<=n;i++)
        {
            for(int j=0;j<=wmax;j++)
                {
                if(i==0||j==0)
                    k[i][j]=0;
                    else if(w[i-1]<=j){
                           k[i][j]=maxm(k[i-1][j-w[i-1]]+v[i-1],k[i-1][j]);
                        }
                        else{
                        k[i][j]=k[i-1][j];
                        }

                }
        }

return k[n][wmax];

}

int main(){

    int n;
    //Enter size of the input array
    cout<<"Enter the size:";
    cin>>n;
    int v[n];
    int w[n];
    int wmax;
    //  Enter the values
    for(int i =0;i<n;i++)
        cin>>v[i];

    //Enter the weights for each of the value
    for(int i =0;i<n;i++)
        cin>>w[i];

    cin>>wmax;

        //Knapsack solution
    cout<<knapsack(v,w,n,wmax)<<endl;

    }
