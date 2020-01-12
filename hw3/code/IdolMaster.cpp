//reference(DFS):https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/ 
#include<iostream> 
#include<list> 
#include<vector>
#include <stdlib.h>
#include <time.h> 
using namespace std; 
  
// Graph class represents a directed graph 
// using adjacency list representation 
class Graph 
{ 
    int V;    // No. of vertices 
  
    // Pointer to an array containing 
    // adjacency lists 
    list<int> *adj; 
    
    vector<int> num;
  
    // A recursive function used by DFS 
    int DFSUtil(int v, bool visited[]); 
public: 
    Graph(int V);   // Constructor 
  
    // function to add an edge to graph 
    void addEdge(int v, int w); 
  
    // DFS traversal of the vertices 
    // reachable from v 
    int DFS_getSmall(int v); 
    
    void setNum();
}; 

void Graph::setNum()
{
//	cout << "num: "; 
	srand((unsigned)time(NULL));
	for (int i=0; i<this->V; i++) {
		this->num[i] = rand();
//		cout << this->num[i] <<" ";
	}
}  

Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<int>[V]; 

    for (int i=0; i<V; i++) {
    	this->num.push_back(0);
    }
} 
  
void Graph::addEdge(int v, int w) 
{ 
    adj[v].push_back(w); // Add w to v¡¯s list. 
} 
  
int Graph::DFSUtil(int v, bool visited[]) 
{ 
    // Mark the current node as visited and 
    // print it 
    visited[v] = true; 
    cout << v << " "; 
	int minn = this->num[v];
    // Recur for all the vertices adjacent 
    // to this vertex 
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visited[*i]) 
            return min(DFSUtil(*i, visited), minn); 
} 
  
int Graph::DFS_getSmall(int v)
{ 
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
  
    return DFSUtil(v, visited); 
} 
  

int main() 
{ 
	int n, m, q;
	int count = 1000;
	int cnt;
	cin >> n >> m >> q;
	Graph g(n); 
	int t1,t2;
	for (int i=0; i<m; i++) {
		cin >> t1 >> t2;
		g.addEdge(t1, t2);	
	} 
  	for (int i=0; i<q; i++) {
  		cnt = 0;
  		cin >> t1 >> t2;
  		for (int k=0; k<count; k++) {
			g.setNum();	
			int minn1 = g.DFS_getSmall(t1); 
			int minn2 = g.DFS_getSmall(t2);
			if (minn1 == minn2) {
				cnt++;
			} 
  		}
  		cout << cnt / count << endl;	
  	}
  
    return 0; 
} 
