#include <iostream>
#include <vector>
#include<math.h>
#include<limits.h>
#include <queue>

using namespace std;

struct alist
{
    vector<int> adj;
    int level;
    alist() : level(INT_MAX){}
};

int distance(vector<alist> &graph, int s, int t)
{
    graph[s].level = 0;
    queue<int> Queue;
    Queue.push(s);
    while(!Queue.empty())
    {
        int x = Queue.front();
        Queue.pop();

        for(int i=0; i<graph[x].adj.size(); i++)
        {
            if (graph[graph[x].adj[i]].level == INT_MAX)
            {
                graph[graph[x].adj[i]].level = graph[x].level + 1;
                Queue.push(graph[x].adj[i]);
            }
        }
    }/*
    for(int j=0; j<graph.size(); j++)
    {
        cout<<j+1<<" :  ";
        for(int i=0; i<graph[j].adj.size(); i++)
            cout<<graph[j].adj[i] + 1 <<"  ";
        cout<<"LEVEl ->> "<<graph[j].level<<endl;
    }
*/
    if (graph[s].level != INT_MAX && graph[t].level != INT_MAX)
        return abs(graph[s].level - graph[t].level);
    return -1;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<alist> graph(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x - 1].adj.push_back(y - 1);
        graph[y - 1].adj.push_back(x - 1);
    }
    int s, t;
    cin >> s >> t;
    s--, t--;
    cout << distance(graph, s, t);
}
