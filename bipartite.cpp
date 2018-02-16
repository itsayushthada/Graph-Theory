#include <iostream>
#include <vector>
#include<math.h>
#include<limits.h>
#include <queue>

using namespace std;

struct alist
{
    vector<int> adj;
    int color;
    alist() : color(0){}
};

bool distance(vector<alist> &graph)
{
    int s=0;
    graph[s].color = -1; //This means that it is coloured white
    queue<int> Queue;
    Queue.push(s);
    while(!Queue.empty())
    {
        int x = Queue.front();
        Queue.pop();

        for(int i=0; i<graph[x].adj.size(); i++)
        {
            if (graph[graph[x].adj[i]].color == 0)
            {
                graph[graph[x].adj[i]].color = graph[x].color * -1; //This will ssign the complemetry color of parent node
                Queue.push(graph[x].adj[i]);
            }
            else
            {
                if ( graph[graph[x].adj[i]].color == graph[x].color)
                    return 0;
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
    for(int i=0; i<graph.size(); i++)
        if (graph[i].color >= 2)
            return 0;
    return 1;
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
    cout << distance(graph);
}
