//reference(DFS):https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/ 
#include<bits/stdc++.h>
using namespace std; 


#define CNT 400
#define MAX 200001
  
// Graph class represents a directed graph 
// using adjacency list representation 

int value[MAX][CNT];
vector<int> top_rank(MAX, -1);

class Graph 
{ 

public:
    int V;    // No. of vertices 
  
    // Pointer to an array containing 
    // adjacency lists 
    list<int> *adj; 
    list<int> *adj2;
    vector<int> indegree;
    
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
    void topologicalSort();
    void topologicalSortUtil(int v, bool visited[],  
                                stack<int> &Stack);
	 
}; 

void Graph::topologicalSortUtil(int v, bool visited[],  
                               stack<int> &Stack) 
{ 
    // Mark the current node as visited. 
    visited[v] = true; 
    Stack.push(v); 
    // Recur for all the vertices adjacent to this vertex 
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visited[*i]) 
            topologicalSortUtil(*i, visited, Stack); 
  
    // Push current vertex to stack which stores result 

} 
  
// The function to do Topological Sort. It uses recursive  
// topologicalSortUtil() 
void Graph::topologicalSort() 
{
    queue<int> q;
    int counter = 0;
    for (int i=0; i<this->V; i++) {
    	if (this->indegree[i] == 0) {
    		q.push(i);
    	}
    }
    
    while(!q.empty()) {
    	int v = q.front();
//    	cout << "v:" << v << endl;
    	q.pop();
    	top_rank[counter] = v;
    	counter++;
    	list<int>::iterator i; 
    	for (i = adj[v].begin(); i != adj[v].end(); ++i) {
    		this->indegree[*i]--;
    		if (this->indegree[*i] == 0) {
    			q.push(*i);
    		}
    	}
    }
    
} 

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
    adj2 = new list<int>[V];

//    for (int i=0; i<V; i++) {
//    	this->num.push_back(0);
//    }
    for (int i=0; i<V; i++) {
    	this->indegree.push_back(0);
    }
    
} 
  
void Graph::addEdge(int v, int w) 
{ 
    adj[v].push_back(w); // Add w to v¡¯s list.
    this->indegree[w]++;
	adj2[w].push_back(v);
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
	int count = CNT;
	int cnt;
	cin >> n >> m >> q;
	Graph g(n); 
	mt19937 gg(1111);
	for (int i=0; i<n; i++) {
		for (int j=0; j<count; j++) {
			value[i][j] = gg();
		}
	}
	int t1,t2;
	for (int i=0; i<m; i++) {
		cin >> t1 >> t2;
		g.addEdge(t1-1, t2-1);	
	} 
//	for (int i=0; i<n; i++) {
//		cout << top_rank[i] << endl;
//	}
	g.topologicalSort();
//	for (int i=0; i<n; i++) {
//		cout << top_rank[i] << endl;
//	}
	for (int i=n-1; i>=0; i--) {
		for (int j=0; j<count; j++) {
			list<int>::iterator k; 
			int temp = top_rank[i];
//			cout << 222 << endl;
    		for (k = g.adj2[temp].begin(); k != g.adj2[temp].end(); ++k) {
//    			cout << 333 << endl;
    			if (value[temp][j] < value[*k][j]) {
    				value[*k][j] = value[temp][j];
    			}    			
    		}
		}
	}
  	for (int i=0; i<q; i++) {
  		cnt = 0;
  		cin >> t1 >> t2;
  		for (int k=0; k<count; k++) {			
			int minn1 = value[t1-1][k];
			int minn2 = value[t2-1][k];
			if (minn1 == minn2) {
				cnt++;
			} 
  		}
//  		cout << "cnt:" << cnt << endl; 
  	  double result = (double)cnt / (double)count;
  	  printf("%f\n", result); 
  	}
  
    return 0; 
} 
