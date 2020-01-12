// A C++ program to find single source longest distances 
// in a DAG 
#include<bits/stdc++.h>
using namespace std; 
#define NINF ll_MIN
typedef ll ll;
  
// Graph is represented using adjacency list. Every  
// node of adjacency list contains vertex number of  
// the vertex to which edge connects. It also  
// contains weight of the edge  
class AdjListNode {  
    ll v;  
    ll weight;  
    
public:  
    AdjListNode(ll _v, ll _w)  
    {  
        v = _v;  
        weight = _w;  
    }  
    ll getV() { return v; }  
    ll getWeight() { return weight; }  
};  
    
// Class to represent a graph using adjacency list  
// representation  
class Graph {  
    ll V; // No. of vertices'  
    
    // Poller to an array containing adjacency lists  
    list<AdjListNode>* adj;  
    
    // A function used by longestPath  
    void topologicalSortUtil(ll v, bool visited[],  
                             stack<ll>& Stack);  
    
public:  
    Graph(ll V); // Constructor  
    ~Graph(); // Destructor 
  
    // function to add an edge to graph  
    void addEdge(ll u, ll v, ll weight);  
    
    void prll();
    bool isCyclicUtil(ll v, bool visited[], bool *rs);
    bool isCyclic();
    
    // Finds longest distances from given source vertex  
    ll longestPath();  
};  
    
Graph::Graph(ll V) // Constructor  
{  
    this->V = V;  
    adj = new list<AdjListNode>[V];  
}  
  
Graph::~Graph() // Destructor  
{  
	
    delete [] adj;  
}  

bool Graph::isCyclicUtil(ll v, bool visited[], bool *recStack) 
{ 
    if(visited[v] == false) 
    { 
        // Mark the current node as visited and part of recursion stack 
        visited[v] = true; 
        recStack[v] = true; 
  
        // Recur for all the vertices adjacent to this vertex 
        list<AdjListNode>::iterator i; 
        for(i = adj[v].begin(); i != adj[v].end(); ++i) 
        { 
            if ( !visited[i->getV()] && isCyclicUtil(i->getV(), visited, recStack) ) 
                return true; 
            else if (recStack[i->getV()]) 
                return true; 
        } 
  
    } 
    recStack[v] = false;  // remove the vertex from recursion stack 
    return false; 
} 
  
// Returns true if the graph contains a cycle, else false. 
// This function is a variation of DFS() in https://www.geeksforgeeks.org/archives/18212 
bool Graph::isCyclic() 
{ 
    // Mark all the vertices as not visited and not part of recursion 
    // stack 
    bool *visited = new bool[V]; 
    bool *recStack = new bool[V]; 
    for(ll i = 0; i < V; i++) 
    { 
        visited[i] = false; 
        recStack[i] = false; 
    } 
  
    // Call the recursive helper function to detect cycle in different 
    // DFS trees 
    for(ll i = 0; i < V; i++) 
        if (isCyclicUtil(i, visited, recStack)) 
            return true; 
  
    return false; 
} 
  
  
void Graph::addEdge(ll u, ll v, ll weight)  
{  
    AdjListNode node(v, weight);  
    adj[u].push_back(node); // Add v to u's list  
}  
    
// A recursive function used by longestPath. See below  
// link for details  
// https:// www.geeksforgeeks.org/topological-sorting/  
void Graph::topologicalSortUtil(ll v, bool visited[],  
                                stack<ll>& Stack)  
{  
    // Mark the current node as visited  
    visited[v] = true;  
    
    // Recur for all the vertices adjacent to this vertex  
    list<AdjListNode>::iterator i;  
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {  
        AdjListNode node = *i;  
        if (!visited[node.getV()])  
            topologicalSortUtil(node.getV(), visited, Stack);  
    }  
    
    // Push current vertex to stack which stores topological  
    // sort  
    Stack.push(v);  
}  
    
// The function to find longest distances from a given vertex.  
// It uses recursive topologicalSortUtil() to get topological  
// sorting.  
ll Graph::longestPath()  
{  
    stack<ll> Stack;  
    ll dist[V];  
    ll father[V];
    
    // Mark all the vertices as not visited  
    bool* visited = new bool[V];  
    for (ll i = 0; i < V; i++)  
        visited[i] = false;  
    
    // Call the recursive helper function to store Topological  
    // Sort starting from all vertices one by one  
    for (ll i = 0; i < V; i++)  
        if (visited[i] == false)  
            topologicalSortUtil(i, visited, Stack);  
    
    // Initialize distances to all vertices as infinite and  
    // distance to source as 0  
    for (ll i = 0; i < V; i++)  
        dist[i] = 0;    
    dist[Stack.top()] = 0;
    for (ll i = 0; i < V; i++)  
        father[i] = i;   
    
    // Process vertices in topological order  
    while (Stack.empty() == false) {  
        // Get the next vertex from topological order  
        ll u = Stack.top();  
        Stack.pop();  
    
        // Update distances of all adjacent vertices  
        list<AdjListNode>::iterator i;   
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        	// other song
    		if (dist[i->getV()] < dist[u] + i->getWeight()) {
    			if (i->getWeight() == 0 && (father[u] != u - 1)) {
    				dist[i->getV()] = dist[u] + 1;
    			} else {
    				dist[i->getV()] = dist[u] + i->getWeight();
    			}
    		}
           		  
        }
        
    }  
    
    ll ans = 0;
    for (ll i = 0; i < V; i++)  {
        if (dist[i] != NINF && dist[i] >= ans) {
            ans = dist[i];
        } 
    }    
    delete [] visited; 
    return ans;
}  

void Graph::prll() {
	
	 
	for (ll i=0; i<V; i++) {
		list<AdjListNode>::iterator j;   
        for (j = adj[i].begin(); j != adj[i].end(); ++j) {
            cout << " start:" <<  i
				<< " end:" << j->getV()
				<< " weight" << j->getWeight()
				<< endl;
        }
	}
	
}
    
// Driver program to test above functions  
int main()  
{  

	std::ios::sync_with_stdio(false);
    std::cin.tie(0);
	ll T;
	cin >> T;
	for (ll t=0; t < T; t++) {
		ll N, M;
		cin >> N >> M;
		vector<ll> length_song(N);
		for (ll i=0; i<N; i++) {
			cin >> length_song[i];
		}
		vector <vector <ll> > node1(N);
		
		ll temp1;
		ll temp2;
		vector <ll> temp_arr;
		for (ll i=0; i< 2*M; i++) {
			cin >> temp1;
			temp_arr.push_back(temp1);
			cin >> temp2;
			temp_arr.push_back(temp2);
			node1[temp1 - 1].push_back(temp2);
		}
		for (ll i=0; i<N; i++) {
			sort(node1[i].begin(), node1[i].end());
			node1[i].erase(unique(node1[i].begin(), node1[i].end()), node1[i].end());
		}
		
		// prll node
//		cout << "node" << endl;
	//		
	//	for (ll i=0; i<N; i++) {
	//		cout << i <<":";
	//		for (ll j=0; j<node1[i].size(); j++) {
	//			cout << node1[i][j];
	//		}
	//		cout << endl;
	//	}
	//	
		// munber of node
		ll cnt = 0;
		vector< map<ll, ll> > encode_arr;
		for (ll i=0; i<N; i++) {
			// start
			map<ll, ll> map_temp;
			map_temp.insert(pair<ll, ll>(0, cnt));		
			cnt++;
			for (ll j=0; j<node1[i].size(); j++) {
				map_temp.insert(pair<ll, ll>(node1[i][j], cnt));		
				cnt++;	
			}
			// end
			if (node1[i].size() != 0 && node1[i][node1[i].size()-1] != length_song[i]) {
				map_temp.insert(pair<ll, ll>(length_song[i], cnt));
				cnt++;
			} else if (node1[i].size() == 0) {
				map_temp.insert(pair<ll, ll>(length_song[i], cnt));
				cnt++;
			}
			encode_arr.push_back(map_temp);
		}
		
		Graph g(cnt); 
//		cout << "cnt:" << cnt << endl;	
		
		ll cur_graph = 0;
		
		for (ll i=0; i<N; i++) {
			ll len = node1[i].size();
			if (len > 0) {
				g.addEdge(cur_graph, cur_graph+1, node1[i][0]);
				cur_graph++;
			}
//			cout << "i:" << i << endl;
//			cout << "cur_graph:" << cur_graph << endl; 
			for (ll j=0; j<len-1; j++) {
				g.addEdge(cur_graph, cur_graph+1, node1[i][j+1]-node1[i][j]);
				cur_graph++;
			}
			if ( len != 0 && node1[i][len-1] != length_song[i]) {
				g.addEdge(cur_graph, cur_graph+1, length_song[i]-node1[i][len-1]);
				cur_graph++;
			} else if (len == 0) {
				g.addEdge(cur_graph, cur_graph+1, length_song[i]);
				cur_graph++;
			}
			cur_graph++;
		}
//		cout << "cur_graph:" << cur_graph << endl;
	//	g.prll();
	//	cout << "temp_arr.size:" << temp_arr.size() << endl;
		for (ll i=0; i<temp_arr.size(); i++) {
			temp1 = temp_arr[i];
			temp2 = temp_arr[i+1];
			i += 2;
			ll vertex1;
			vertex1 = encode_arr[temp1-1].find(temp2)->second;
	//		cout << "vertex1:" << vertex1 << endl;
			temp1 = temp_arr[i];
			temp2 = temp_arr[i+1];
			ll vertex2;
			vertex2 = encode_arr[temp1-1].find(temp2)->second;
	//		cout << "vertex2:" << vertex2 << endl;
			i += 1; 
			g.addEdge(vertex1, vertex2, 0);
		}
//		g.prll();
		if (g.isCyclic()) {
			cout <<"LoveLive!" << "\n";
		} else {
			ll res = g.longestPath();  
	    	cout << res << "\n";
		}
	}
	
    return 0;  
} 
