#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

struct point
{
    int x;
    int y;
    int label;
    point(): x(0),y(0), label(0){}
};

struct edge
{
    int a;  /*Point A */
    int b;  /*Point B */
    double dist;
    edge(): a(0), b(0), dist(0){}
};

double distance(const point &a,const point &b)
{
    double xpart = (a.x - b.x)*(a.x - b.x);
    double ypart = (a.y - b.y)*(a.y - b.y);

    return (sqrt(xpart+ypart));
}

bool edgeCompare(const edge &a, const edge &b)
{
    return(a.dist < b.dist);
}

void printP(const vector<point> &graph)
{
    for(int i=0; i<graph.size(); i++)
        cout<< i+1 <<": " << graph[i].x <<", "<<graph[i].y<<"  Label = "<<graph[i].label<<endl;
    cout<<endl;
}

void printE(const vector<edge> &Edge, const vector<point> &graph)
{
    for(int i=0; i<Edge.size(); i++)
    {
        cout<< Edge[i].a+1 <<" " << Edge[i].b+1 <<" : ";
        cout<< Edge[i].dist<<endl;
    }
    cout<<endl;
}

int Find(const vector<point> graph,const int a)
{
    return (graph[a].label);
}

void Union(vector<point> &graph, const int a, const int b)
{
    int A = Find(graph, a);
    int B = Find(graph, b);

    if (A > B)
    {
        for(int i =0; i<graph.size(); i++)
            if (graph[i].label == A)
                graph[i].label = B;
    }

    else if (A < B)
    {
        for(int i =0; i<graph.size(); i++)
            if (graph[i].label == B)
                graph[i].label = A;
    }
}

double minimum_distance(vector<point> &graph)
{
    for(int i=0; i<graph.size(); i++)   /** Make Sets **/
        graph[i].label = i+1;

    vector<edge> Edge;
    for(int i=0; i<graph.size(); i++)
        for(int j=0; j<graph.size(); j++)
            if(i!=j)
            {
                edge temp;
                temp.a = i;
                temp.b = j;
                temp.dist = distance(graph[i], graph[j]);
                Edge.push_back(temp);
            }
    sort(Edge.begin(), Edge.end(), edgeCompare);    /** Sorting Edges  **/

    double length=0;
    for(int i=0; i<Edge.size(); i++)
    {
        if(Find(graph, Edge[i].a) != Find(graph, Edge[i].b))     /** Checking the sets for being disjoint **/
        {
            Union(graph, Edge[i].a, Edge[i].b);    /** Merging two disjoint sets **/
            length += Edge[i].dist;
        }
    }
    return length;
}

int main()
{
    size_t n;
    cin >> n;
    vector<point> graph(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> graph[i].x >> graph[i].y;
    }
    cout << setprecision(10) << minimum_distance(graph) <<endl;
    return 0;
}
