#include <iostream>
#include <vector>
#include <queue>
#include<limits.h>

using namespace std;

struct node
{
    int key;
    vector<int> children;
    vector<int> cost;
    int dist;
    int prev;
    node():dist(INT_MAX),prev(-1){}
    bool operator<(node x){return(dist<x.dist);}
    bool operator>(node x){return(dist>x.dist);}
};

void path(vector<node>& graph, int s, int x)
{
    cout<<"Path is: ";
    vector<int> test;
    int q = x;
    while(graph[x].prev!=-1)
    {
        test.push_back(graph[x].key+1);
        x= graph[x].prev;
    }
    test.push_back(s+1);
    test[0]=q+1;

    for(int i=test.size()-1 ; i>=0 ; i--)
        cout<<test[i]<<"--> ";
    cout<<endl;
}

int distance(vector<node>& graph, int s, int t)
{
    graph[s].dist = 0;
    vector<int> Queue;      //Heap Implementation
    Queue.push_back(s);
    make_heap(Queue.begin(), Queue.end(), greater<int>());

    while(!Queue.empty())
    {
        int x = Queue.front();
        pop_heap(Queue.begin(),Queue.end(),greater<int>());
        Queue.pop_back();

        for(int i=0; i<graph[x].children.size(); i++)
        {
            if(graph[graph[x].children[i]].dist > graph[x].dist + graph[x].cost[i])
            {
                graph[graph[x].children[i]].dist = graph[x].dist + graph[x].cost[i];
                graph[graph[x].children[i]].prev = graph[x].key;

                Queue.push_back(graph[x].children[i]);
                push_heap(Queue.begin(), Queue.end(), greater<int>());

            }
        }
    }
    //path(graph, s, t);
    if(graph[t].dist != INT_MAX)
        return graph[t].dist;
    else
        return -1;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<node> graph(n);

    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        graph[x-1].key = x-1;
        graph[x-1].children.push_back(y-1);
        graph[x-1].cost.push_back(w);
    }
    int s, t;
    cin >> s >> t;
    s--, t--;
    cout << distance(graph, s, t);
}
