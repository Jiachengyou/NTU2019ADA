//reference(DFS):https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/ 
#include<bits/stdc++.h>
using namespace std; 
  
// Graph class represents a directed graph 
// using adjacency list representation 
#define count 600
int *arr = new int[200001][600];
int *value = new int[2000][600];
class Graph 
{ 
    int V;    // No. of vertices 
  
    // Pointer to an array containing 
    // adjacency lists 
    list<int> *adj; 
    
    vector<int> num;
  
    // A recursive function used by DFS 
    int DFSUtil(int v, bool visited[], int k); 
public: 
    Graph(int V);   // Constructor 
  
    // function to add an edge to graph 
    void addEdge(int v, int w); 
  
    // DFS traversal of the vertices 
    // reachable from v 
    int DFS_getSmall(int v, int k); 
    
    void setNum();
}; 

void Graph::setNum()
{
//	cout << "num: "; 
	for (int i=0; i<this->V; i++) {
		this->num[i] = rand();
//		cout << this->num[i] <<" ";
	}
//	cout << endl;
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
  
int Graph::DFSUtil(int v, bool visited[], int k) 
{ 
    // Mark the current node as visited and 
    // print it 
    visited[v] = true; 
//    cout << v << " "; 
	int minn = value[v][k];
	if (adj[v].size() == 0) {
		return minn;
	}
    // Recur for all the vertices adjacent 
    // to this vertex 
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visited[*i]) 
            return min(DFSUtil(*i, visited, k), minn);  
} 
  
int Graph::DFS_getSmall(int v, int k)
{ 
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
  	int result =  DFSUtil(v, visited, k);
  	delete [] visited;
    return result; 
} 
  

int main() 
{ 
	int n, m, q;
	int cnt;
	cin >> n >> m >> q;
	Graph g(n); 
	mt19937 g(1);
	for (int i=0; i<n; i++) {
		for (int j=0; j<count; j++) {
			value[i][j] = g();
		}
	}
	int t1,t2;
	for (int i=0; i<m; i++) {
		cin >> t1 >> t2;
		g.addEdge(t1-1, t2-1);	
	} 
	for (int i=0; i<n; i++) {
		for (int j=0; j<count; j++) {
			arr[i][j] = -1;
		}
	}
  	for (int i=0; i<q; i++) {
  		cnt = 0;
  		cin >> t1 >> t2;
  		t1--;
  		t2--;
  		for (int k=0; k<count; k++) {
//			g.setNum();	
			int minn1;
			if (arr[t1][k] == -1) {
				minn1 = g.DFS_getSmall(t1, k);
				arr[t1][k] = minn1;
			} else {
				minn1 = arr[t1][k];
			}
			int minn2;
			if (arr[t2][k] == -1) {
				minn2 = g.DFS_getSmall(t2, k);
				arr[t2][k] = minn2;
			} else {
				minn2 = arr[t2][k];
			}
			if (minn1 == minn2) {
				cnt++;
			} 
  		}
//  		cout << "cnt:" << cnt << endl; 
  	  double result = (double)cnt / (double)count;
  	  cout << result << endl;
  	}
  
    return 0; 
} 
