// reference https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
// https://www.geeksforgeeks.org/find-longest-path-directed-acyclic-graph/
// https://www.geeksforgeeks.org/binary-search/
#include<bits/stdc++.h>
#define NINF LLONG_MIN 

// reference:https://www.geeksforgeeks.org/detect-cycle-in-an-undirected-graph-using-bfs/
//https://www.geeksforgeeks.org/find-longest-path-directed-acyclic-graph/
// discussion with lai ruitaos

using namespace std; 
typedef long long ll;


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

    bool isCyclicUtil(ll v, bool visited[], bool *rs);  // used by isCyclic() 

    
public:  
    Graph(ll V); // Constructor  
    ~Graph(); // Destructor 
  
    // function to add an edge to graph  
    void addEdge(ll u, ll v, ll weight);  
    
    // Finds longest distances from given source vertex  
    ll longestPath(ll s);  

    bool isCyclic();    // returns true if there is a cycle in this graph 

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
ll Graph::longestPath(ll s)  
{  
    stack<ll> Stack;  
    ll dist[V];  
    
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
        dist[i] = NINF;  
    dist[s] = 0;  
    
    // Process vertices in topological order  
    while (Stack.empty() == false) {  
        // Get the next vertex from topological order  
        ll u = Stack.top();  
        Stack.pop();  
    
        // Update distances of all adjacent vertices  
        list<AdjListNode>::iterator i;  
        if (dist[u] != NINF) {  
            for (i = adj[u].begin(); i != adj[u].end(); ++i)  
                if (dist[i->getV()] < dist[u] + i->getWeight())  
                    dist[i->getV()] = dist[u] + i->getWeight();  
        }  
    }  
    
    // Prll the calculated longest distances  
    ll ans = 0;
    for (ll i = 0; i < V; i++)  {
        if (dist[i] != NINF && dist[i] >= ans) {
            ans = dist[i];
        } 
    } 
    return ans;
      
    delete [] visited; 
} 

// This function is a variation of DFSUtil() in https://www.geeksforgeeks.org/archives/18212 
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
    //cout << "iscyclic" << endl;
    bool *visited = new bool[V]; 
    bool *recStack = new bool[V]; 
    for(ll i = 0; i < V; i++) 
    { 
        visited[i] = false; 
        recStack[i] = false; 
    } 
  
    // Call the recursive helper function to detect cycle in different 
    // DFS trees 
    for(ll i = 0; i < V; i++)  {
        //cout << "checkingutil" << endl;
        if (isCyclicUtil(i, visited, recStack)) {
            return true; 
        }
    }
  
    return false; 
} 

// Function to remove duplicate elements 
// This function returns new size of modified 
// array. 
ll removeDuplicates(ll arr[], ll n) 
{ 
    if (n==0 || n==1) 
        return n; 
  
    // To store index of next unique element 
    ll j = 0; 
  
    // Doing same as done in Method 1 
    // Just mallaining another updated index i.e. j 
    for (ll i=0; i < n-1; i++) 
        if (arr[i] != arr[i+1]) 
            arr[j++] = arr[i]; 
  
    arr[j++] = arr[n-1]; 
  
    return j; 
} 


// A iterative binary search function. It returns 
// location of x in given array arr[l..r] if present, 
// otherwise -1 
ll Search(ll arr[], ll l, ll r, ll x) 
{ 
    while (l <= r) { 
        ll m = (l + r )/ 2; 
  
        // Check if x is present at mid 
        if (arr[m] == x) 
            return m; 
  
        // If x greater, ignore left half 
        if (arr[m] < x) 
            l = m + 1; 
  
        // If x is smaller, ignore right half 
        else
            r = m - 1; 
    } 
  
    // if we reach here, then element was 
    // not present 
    return -1; 
} 
/*
ll songLen[100002];
ll split[100002];
ll edge[500001][4];
ll bound[100002]; */

int main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    ll t, n, m;
    ll src1, des1, src2, des2;
    cin >> t;
    // taking care of n and m
     for(ll i = 0; i < t; ++i) {
         // getting n and m
         cin >> n ;
         cin >> m;
         ll bi = 0;
         ll after_size = 0;
         ll (*edge)[4];
         edge = new ll[m][4];
         //cout << "mallocing" << endl;
         ll *songLen = new ll[n+2];
         //cout << "mallocing1" << endl;
         ll *split = new ll[n+2];
         //cout << "mallocing2" << endl;
         ll *bound = new ll[2*n+2*m+2];
         //cout << "mallocing3" << endl;
         //edge = new ll[m][4];
         // input length of the songs
         songLen[0] = 0;

         for(ll i = 1; i <= n; ++i) {
             ll curr_len;
             cin >> curr_len;
             songLen[i] = curr_len;
         }

         for(ll i = 2; i <= n; ++i) {
             songLen[i] += songLen[i-1];
            // cout << songLen[i]  << "--song"<< endl;
         }
         
         for(ll i = 0; i < n; ++i) {
             bound[bi] = songLen[i];
             ++bi;
             bound[bi] = songLen[i]+1;
             ++bi;
             split[i] = 0;
         }
         split[n] = 0;
         // for the last one
         bound[bi] = songLen[n];
         ++bi;
         /*
         for(ll i = 0; i < bi; ++i) {
             cout << bound[i] << " -bound" << endl;
         }  */

     
     // process src and des

     for(ll i = 0; i < m; ++i) {
         cin >> src1;
         cin >> des1;
         cin >> src2;
         cin >> des2;
         edge[i][0] = src1;
         edge[i][1] = des1;
         edge[i][2] = src2;
         edge[i][3] = des2;
         ll new_des1 = des1 + songLen[src1-1];
         ll new_des2 = des2 + songLen[src2-1];
         bound[bi] = new_des1;
         ++bi;
         bound[bi] = new_des2;
         ++bi;
        // cout << "des1 " << des1 << endl; 
         //cout << "new des " << new_des1 <<  " " << new_des2 << endl;
     }

     sort(bound, bound+bi);
     after_size = removeDuplicates(bound, bi);
     /*
    for(ll i = 0; i <bi;++i){
         cout << bound[i] << " after sort"<< endl;
     }  */
     //cout << after_size << "-- after_size" << endl;
     ll cur_song = 1;
     for(ll i = 1; i < after_size; ++i) {
         if(bound[i] <= songLen[cur_song]) {
             split[cur_song]++;
         } else {
             ++cur_song;
             split[cur_song]++;
         }
     }
     for(ll i = 1; i <= cur_song; ++i) {
         split[i] += split[i-1];
          //cout << split[i] << "-split-" << endl;
     }

     // creating graph
     Graph g(after_size);
    
     ll cur_weight;
     ll song_count = 1;

    for(ll i = 0; i < n; ++i) {
         // link 0 to each song
         ll song_start = split[i]+1;
         g.addEdge(0, song_start, 0);
        // cout << 0 << " - " << song_start   << " "<< 0 << endl;
     }

     for(ll i = 1; i < after_size; ++i) {
         if(i >= split[song_count]) {
             // next song
             ++song_count;
         } else {
             cur_weight = bound[i+1] - bound[i];
             if(split[song_count-1]+1 == i) {
                 cur_weight++;
                 //cout << "here" << endl;
             }
             g.addEdge(i, i+1, cur_weight);
             //cout<<i<<"?-"<<i+1<<"-?"<<cur_weight<< endl;
         }
     }


     // adding links between songs
     for(ll i = 0; i < m; ++i) {
         ll songu = edge[i][0]-1;
         ll songv = edge[i][2]-1;
         ll search_u = edge[i][1] + songLen[songu];
         ll search_v = edge[i][3] + songLen[songv];
         ll lower_u = split[songu];
         ll lower_v = split[songv];
         ll u = Search(bound, lower_u, split[songu+1], search_u);
         ll v = Search(bound, lower_v, split[songv+1], search_v);
         //cout << u << v << " u v " << endl;
         if(u!= -1 && v != -1) {
         g.addEdge(u, v, 1);
         //cout << u << " " <<  v << " u v " << endl;
         }
     } 

   //  cout << "checking " << endl;
          if(g.isCyclic()) {
         // if contains a loop then lovelive
         cout << "LoveLive!" << endl;
     } else {
         // if not find the lonest path in the graph
         
         ll res = g.longestPath(0);
         cout << res << "\n";
     }
     


     delete[] edge;
     delete[] songLen;
     delete[] bound;
     delete[] split;

     }

     return 0;
}
