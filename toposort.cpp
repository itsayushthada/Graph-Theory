#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct node
{
    vector<int> adj;
    int visited;
    int pre;
    int post;

    node(): visited(0), pre(0), post(0){}
};

void explore(vector<node> &graph, int Node, int &clock, vector<int> &order)
{
    if(graph[Node].visited == 0)
    {
        graph[Node].visited = 1;
        graph[Node].pre = ++clock;

        for(int i=0; i<graph[Node].adj.size(); i++)
        {
            if(graph[graph[Node].adj[i]].visited == 0)
                explore(graph, graph[Node].adj[i], clock, order);
        }

        graph[Node].post = ++clock;
        order.push_back(Node);
    }
}

void dfs(vector<node> &graph, vector<int> &order)
{
    int clock=0;
    for(int i=0; i<graph.size(); i++)
        if(graph[i].visited == 0)
            explore(graph, i, clock, order);
}

vector<int> toposort(vector<node> graph)
{
    vector<int> ord;
    dfs(graph, ord);
    return ord;
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

    vector<int> final = toposort(graph);

    for(int i=final.size()-1; i>=0; i--)
            cout<<final[i]+1<<" ";

    cout<<endl;
    return 0;
}
