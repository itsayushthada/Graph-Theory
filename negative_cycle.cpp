#include <iostream>
#include <vector>
#include<cstdlib>
#include<limits.h>

using namespace std;

struct node
{
    vector<int> children;
    vector<int> cost;
};

bool negative_cycle(const vector<node> graph)
{
    vector<int> dist(graph.size(), (int)(INT_MAX/10)*8);
    dist[0] = 0;

    for(int k=0; k<graph.size(); k++)
        for(int i=0; i<graph.size(); i++)
            for(int j=0; j<graph[i].children.size(); j++)
            {
                if(dist[graph[i].children[j]] > dist[i]+graph[i].cost[j] && dist[i]!= (int)(INT_MAX/10)*8)
                    dist[graph[i].children[j]] = dist[i]+graph[i].cost[j];

                if(dist[graph[i].children[j]]!= (int)(INT_MAX/10)*8 && dist[i]== (int)(INT_MAX/10)*8)
                    dist[i] = dist[graph[i].children[j]] - graph[i].cost[j];
            }

    for(int i=0; i<graph.size(); i++)
        for(int j=0; j<graph[i].children.size(); j++)
            if(dist[graph[i].children[j]] > dist[i]+graph[i].cost[j] && dist[i]!=(int)(INT_MAX/10)*8)
                return true;

    return false;
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
        graph[x-1].children.push_back(y-1);
        graph[x-1].cost.push_back(w);
    }
    cout << negative_cycle(graph);
}
