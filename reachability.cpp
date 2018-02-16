#include<iostream>
#include<vector>

using namespace std;

struct alist
{
    vector<int> adj;
    int comp;
    alist() : comp(0){}
};

void DepthVisit(int key, vector<alist> &obj, int noc)
{
    for(int i=0 ; i<obj[key].adj.size() ; i++)
        if(obj[obj[key].adj[i]].comp==0)
        {
            obj[obj[key].adj[i]].comp = noc;
            DepthVisit(obj[key].adj[i],obj,noc);
        }
}

int main()
{
    size_t n, m;
    cin >> n >> m;
    vector<alist> adj(n);
    for (size_t i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x - 1].adj.push_back(y - 1);
        adj[y - 1].adj.push_back(x - 1);
    }

    int x,y;
    cin>>x>>y;

    int noc=0;
    for(int i=0 ; i<n; i++)
        if (adj[i].comp==0)
        {
            noc++;
            adj[i].comp=noc;
            DepthVisit(i,adj,noc);
        }

    if(adj[x-1].comp==adj[y-1].comp)
        cout<<"1";
    else
        cout<<"0";
    return 0;
}
