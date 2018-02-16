#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct node
{
    vector<int> adj;
    int id;
    int visited;
    int pre;    // Use as preorder in exploring and label in deepExploration
    int post;
    node(): id(0), pre(-1), visited(0), post(-1){}
};

void print(vector<node> graph)
{
    for(int i=0; i<graph.size(); i++)
    {
        cout<< graph[i].id <<"\t"<<graph[i].post<<"\t"<<graph[i].visited<<"\t"<<graph[i].pre<<endl;
    }
    cout<<endl;
}

bool compare(node& a, node& b)
{
    return (a.post> b.post);
}

void explore(vector<node> &graph, int Node, int &clock)
{
    if(graph[Node].visited == 0)
    {
        graph[Node].visited = 1;
        graph[Node].pre = ++clock;

        for(int j=0; j<graph[Node].adj.size(); j++)
            if(graph[graph[Node].adj[j]].visited == 0)
                explore(graph, graph[Node].adj[j], clock);

        graph[Node].post = ++clock;
    }
}

void DFS(vector<node> &graph)
{
    int clock =0;
    for(int i=0; i<graph.size(); i++)
        if(graph[i].visited == 0)
            explore(graph, i, clock);
}

void deepExplore(vector<node> &graph, int Node, const vector<int> &dictionary, int label)
{
    if(graph[Node].visited == 0)
    {
        graph[Node].visited = 1;
        graph[Node].pre = label;

        for(int j=0; j<graph[Node].adj.size(); j++)
                deepExplore(graph, dictionary[graph[Node].adj[j]], dictionary, label);
    }
}

int number_of_strongly_connected_components(vector<node> &graph, vector<node> &rgraph)
{
    DFS(rgraph);
    int clock=0, count=0;
    for(int i=0; i<graph.size(); i++)
        graph[i].post = rgraph[i].post;

    rgraph.clear();
    sort(graph.begin(), graph.end(), compare);

    vector<int> dictionary(graph.size());

    for(int i=0; i<dictionary.size(); i++)
        dictionary[graph[i].id -1] = i;

    int comp_id=0;
    for(int i=0; i<graph.size(); i++)
        if(graph[i].visited == 0)
            deepExplore(graph, i, dictionary, ++comp_id);

    return comp_id;
}

int main()
{
    size_t n, m;
    cin >> n >> m;
    vector<node> graph(n), rgraph(n);
    for (size_t i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x - 1].adj.push_back(y - 1);
        rgraph[y - 1].adj.push_back(x - 1);
    }
    for(int i=0; i<n; i++)
        graph[i].id = rgraph[i].id = i+1;

    cout << number_of_strongly_connected_components(graph, rgraph);
}
