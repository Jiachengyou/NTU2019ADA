#include<bits/stdc++.h>

using namespace std;




typedef long long ll;


#define MAX(a, b) ((a) > (b) ? (a) : (b) )
# define INF 0x3f3f3f3f

//定义图的定点
typedef struct Vertex {
	int id;
	vector<pair<int, pair<int, int> > > connectors;    //存储节点的后续连接顶点编号
	
	Vertex() : id(-1) {}
	Vertex(int nid) : id(nid) {}
} Vertex;




//定义Graph的邻接表表示
typedef struct Graph {
	vector<Vertex> vertexs;   //存储定点信息
	int nVertexs;		      //计数：邻接数
	bool isDAG;               //标志：是有向图吗

	Graph(int n, bool isDAG) : nVertexs(n), isDAG(isDAG) { vertexs.resize(n); }

	//向图中添加边
	bool addEdge(int id1, int id2, int d, int l) {
		if (!(MAX(id1, id2) < vertexs.size())) return false;
		
		pair <int, int> info(d, l);
		pair <int, pair<int, int> > edge1(id1, info);
		pair <int, pair<int, int> > edge2(id2, info);
		if (isDAG) {
			vertexs[id1].connectors.push_back(edge2);
		}
		else {
			vertexs[id1].connectors.push_back(edge2);
			vertexs[id2].connectors.push_back(edge1);
		}
		return true;
	}
	
	pair<bool, int> likeDFS(int start, int end,vector<bool> bool_arr) {
		bool_arr[start] = true;
		if (start == end) {
			return make_pair(true,0);
		}
		for (int i=0; i < vertexs[start].connectors.size(); i++) {
			if (bool_arr[vertexs[start].connectors[i].first]) {
				continue;
			}
			if (vertexs[start].connectors[i].first == end) {
				return make_pair(true,vertexs[start].connectors[i].second.second);
			} else {
				pair<bool, int>  temp = likeDFS(vertexs[start].connectors[i].first, end,bool_arr);
				if (temp.first) {
					return make_pair(true, max(temp.second, vertexs[start].connectors[i].second.second));
				} else {
					return make_pair(false, 0);
				}
			}
		}
		return make_pair(false, 0);
	}
	
	void print() {
		for (int i=0; i<nVertexs; i++) {
			for (int j=0; j<vertexs[i].connectors.size(); j++) {
				cout << " start:" <<  i
					<< " end:" << vertexs[i].connectors[j].first 
					<< " d:" << vertexs[i].connectors[j].second.first
					<< " l:" << vertexs[i].connectors[j].second.second
					<< endl;
			}
		}
	}
	
	ll shortestPath(int src, int L, int end) 
	{ 
	    // Create a set to store vertices that are being 
	    // prerocessed 
	    set< pair<ll, int> > setds; 
	  
	    // Create a vector for distances and initialize all 
	    // distances as infinite (INF) 
	    vector<ll> dist(nVertexs, LLONG_MAX-1); 
	  
	    // Insert source itself in Set and initialize its 
	    // distance as 0. 
	    setds.insert(make_pair(0, src)); 
	    dist[src] = 0; 
	  
	    /* Looping till all shortest distance are finalized 
	       then setds will become empty */
	    while (!setds.empty()) 
	    { 
	        // The first vertex in Set is the minimum distance 
	        // vertex, extract it from set. 
	        pair<ll, int> tmp = *(setds.begin()); 
	        setds.erase(setds.begin()); 
	  
	        // vertex label is stored in second of pair (it 
	        // has to be done this way to keep the vertices 
	        // sorted distance (distance must be first item 
	        // in pair) 
	        int u = tmp.second; 
	        // 'i' is used to get all adjacent vertices of a vertex 
	        vector<pair<int, pair<int, int> > >::iterator i; 
	        for (i =vertexs[u].connectors.begin(); i != vertexs[u].connectors.end(); ++i) 
	        { 
	            // Get vertex label and weight of current adjacent 
	            // of u. 
	            int v = (*i).first; 
	            int d = (*i).second.first; 
	            int l = (*i).second.second;
	            //  If there is shorter path to v through u. 
	            if (dist[v] > dist[u] + d && l <=L) 
	            { 
	                /*  If distance of v is not INF then it must be in 
	                    our set, so removing it and inserting again 
	                    with updated less distance.   
	                    Note : We extract only those vertices from Set 
	                    for which distance is finalized. So for them,  
	                    we would never reach here.  */
	                if (dist[v] != LLONG_MAX-1) 
	                    setds.erase(setds.find(make_pair(dist[v], v))); 
	  				
	                // Updating distance of v 
	                dist[v] = dist[u] + d; 
	                setds.insert(make_pair(dist[v], v)); 
	            } 
	        } 
	    } 
	  	return dist[end];
	} 
	
} Graph; 


typedef struct DisjointSets 
{ 
    int *parent, *rnk; 
    int n; 
  
    // Constructor. 
    DisjointSets(int n) 
    { 
        // Allocate memory 
        this->n = n; 
        parent = new int[n+1]; 
        rnk = new int[n+1]; 
  
        // Initially, all vertices are in 
        // different sets and have rank 0. 
        for (int i = 0; i <= n; i++) 
        { 
            rnk[i] = 0; 
            //every element is parent of itself 
            parent[i] = i; 
        } 
    } 
  
    // Find the parent of a node 'u' 
    // Path Compression 
    int find(int u) 
    { 
        /* Make the parent of the nodes in the path 
           from u--> parent[u] point to parent[u] */
        if (u != parent[u]) 
            parent[u] = find(parent[u]); 
        return parent[u]; 
    } 
  
    // Union by rank 
    void merge(int x, int y) 
    { 
        x = find(x), y = find(y); 
  
        /* Make tree with smaller height 
           a subtree of the other tree  */
        if (rnk[x] > rnk[y]) 
            parent[y] = x; 
        else // If rnk[x] <= rnk[y] 
            parent[x] = y; 
  
        if (rnk[x] == rnk[y]) 
            rnk[y]++; 
    } 
}DisjointSets; 

bool cmp(pair<int, pair<int, int> > a, pair<int, pair<int, int> > b)
{
       return a.first < b.first;
}


vector<pair<int, pair<int, int> > > kruskalMST(int n, vector<pair<int, pair<int, int> > > &edges) { 
    int mst_wt = 0; // Initialize result 
    // Sort edges in increasing order on basis of cost 
    sort(edges.begin(), edges.end(), cmp); 
    // Create disjoint sets 
    DisjointSets ds(n); 
  
    // Iterate through all sorted edges 
    vector< pair<int, pair<int, int> > >::iterator it; 
    vector<pair<int, pair<int, int> > > res;
    for (it=edges.begin(); it!=edges.end(); it++) 
    { 	
        int u = it->second.first; 
        int v = it->second.second; 
        int w = it->first;
        int set_u = ds.find(u); 
        int set_v = ds.find(v); 
        // Check if the selected edge is creating 
        // a cycle or not (Cycle is created if u 
        // and v belong to same set) 
        if (set_u != set_v) 
        { 
            // Current edge will be in the MST 
            // so print it 
//            cout << u << " - " << v << endl; 
  			pair<int, int> temp(u, v);
  			pair<int, pair<int, int> > t(w, temp);
  			res.push_back(t);
            // Update MST weight 
            mst_wt += it->first; 
  
            // Merge two sets 
            ds.merge(set_u, set_v); 
        } 
    } 
//    cout << "w:" << mst_wt << endl;
    return res; 
}




int main() {
	
	int n,m;
	cin >> n >> m;
	int start, end;
	cin >> start >> end;
	Graph g(n, false);
	int arg1,arg2,arg3,arg4;
	vector<pair<int, pair<int, int> > > edges;
	for (int i=0; i<m; i++) {
		cin >> arg1 >> arg2 >> arg3 >> arg4;
		g.addEdge(arg1,arg2,arg3,arg4);
		pair <int, int> e_info(arg1, arg2);
		pair <int, pair<int, int> > edge(arg4, e_info);
		edges.push_back(edge);
	}	
//	vector<pair<int, pair<int, int> > > mst = kruskalMST(n,edges);
//	Graph mst_g(mst.size()+1, false);
//	
//	for (int i=0; i<mst.size(); i++) {
//		mst_g.addEdge(mst[i].second.first, mst[i].second.second, 0, mst[i].first);
//	}
//	vector<bool> bool_arr(n);
//	for (int i=0; i<n; i++) {
//		bool_arr[i] = false;
//	}
//	pair<bool, int> result = mst_g.likeDFS(start, end, bool_arr);
	int L = arg4;
	ll D = g.shortestPath(start, L, end);	
	cout << D << " "<< L << endl;
	
	
	return 0;
} 
