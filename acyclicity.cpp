#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct node
{
    vector<int> adj;
    int visited;
    int pre;
    int post;
    node(): pre(0), post(0), visited(0) {}
};

void reset(vector<node> &graph)
{
    for(int i=0; i<graph.size(); i++)
        graph[i].visited=0;
}

void explore(vector<node> &graph, int Node , int &clock)
{
    if (graph[Node].visited == 0)
    {
        graph[Node].visited = 1;
        graph[Node].pre = ++clock;      //Previsit time

        for(int i=0; i<graph[Node].adj.size(); i++)
            if(graph[graph[Node].adj[i]].visited==0)
                explore(graph, graph[Node].adj[i], clock);

        graph[Node].post = ++clock;     //post visit time
    }
}

bool checkAcyclicity(vector<node> graph, int i)
{
    graph[i].visited = 1;
    for(int j=0; j<graph[i].adj.size(); j++)
    {
        if(graph[graph[i].adj[j]].visited == 0)
        {
            if(graph[i].pre > graph[graph[i].adj[j]].pre && graph[i].post < graph[graph[i].adj[j]].post)
                return 1;
            int a = checkAcyclicity(graph, graph[i].adj[j]);
        }
    }
    return 0;
}

bool acyclic(vector<node> graph)
{
    for(int i=0; i<graph.size(); i++)
        if(graph[i].visited==0)
            if(checkAcyclicity(graph, i) == 1)
                return 1;
    return 0;
}

int main()
{
    size_t n, m;
    cin >> n >> m;
    vector<node> graph(n);
    for (size_t i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x - 1].adj.push_back(y - 1);
    }
    for(int i=0; i<n; i++)
        sort(graph[i].adj.begin(), graph[i].adj.end());
    int clock=0;

    for(int i=0; i<n; i++)
        if(graph[i].visited == 0)
            explore(graph, i, clock); // 0 to set clock to zero

    reset(graph);
/*
    for(int i=0; i<n; i++)
    {
        cout<<i+1<<": "<<"("<<graph[i].pre<<"/"<<graph[i].post<<") :  ";
        for(int j=0; j<graph[i].adj.size()>0; j++)
            cout<< graph[i].adj[j]+1<<" ";
        cout<<endl;
    }*/
    cout<<acyclic(graph);
    return 0;
}
