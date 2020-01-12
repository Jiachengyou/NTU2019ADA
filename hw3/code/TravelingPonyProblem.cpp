#include<bits/stdc++.h>

using namespace std;




typedef ll ll;


#define MAX(a, b) ((a) > (b) ? (a) : (b) )
# define INF 0x3f3f3f3f

//定义图的定点
typedef struct Vertex {
	ll id;
	vector<pair<ll, pair<ll, ll> > > connectors;    //存储节点的后续连接顶点编号
	
	Vertex() : id(-1) {}
	Vertex(ll nid) : id(nid) {}
} Vertex;




//定义Graph的邻接表表示
typedef struct Graph {
	vector<Vertex> vertexs;   //存储定点信息
	ll nVertexs;		      //计数：邻接数
	bool isDAG;               //标志：是有向图吗

	Graph(ll n, bool isDAG) : nVertexs(n), isDAG(isDAG) { vertexs.resize(n); }

	//向图中添加边
	bool addEdge(ll id1, ll id2, ll d, ll l) {
		if (!(MAX(id1, id2) < vertexs.size())) return false;
		pair <ll, ll> info(d, l);
		pair <ll, pair<ll, ll> > edge1(id1, info);
		pair <ll, pair<ll, ll> > edge2(id2, info);
		if (isDAG) {
			vertexs[id1].connectors.push_back(edge2);
		}
		else {
			vertexs[id1].connectors.push_back(edge2);
			vertexs[id2].connectors.push_back(edge1);
		}
		return true;
	}
	
	pair<bool, ll> likeDFS(ll start, ll end,vector<bool> bool_arr) {
		bool_arr[start] = true;
		if (start == end) {
			return make_pair(true,0);
		}
		for (ll i=0; i < vertexs[start].connectors.size(); i++) {
			if (bool_arr[vertexs[start].connectors[i].first]) {
				continue;
			}
			if (vertexs[start].connectors[i].first == end) {
				return make_pair(true,vertexs[start].connectors[i].second.second);
			} else {
				pair<bool, ll>  temp = likeDFS(vertexs[start].connectors[i].first, end,bool_arr);
				if (temp.first) {
					return make_pair(true, max(temp.second, vertexs[start].connectors[i].second.second));
				}
			}
		}
		return make_pair(false, 0);
	}
	
	void prll() {
		for (ll i=0; i<nVertexs; i++) {
			for (ll j=0; j<vertexs[i].connectors.size(); j++) {
				cout << " start:" <<  i
					<< " end:" << vertexs[i].connectors[j].first 
					<< " d:" << vertexs[i].connectors[j].second.first
					<< " l:" << vertexs[i].connectors[j].second.second
					<< endl;
			}
		}
	}
	
	ll shortestPath(ll src, ll L, ll end) 
	{ 
	    // Create a set to store vertices that are being 
	    // prerocessed 
	    set< pair<ll, ll> > setds; 
	  
	    // Create a vector for distances and initialize all 
	    // distances as infinite (INF) 
	    vector<ll> dist(nVertexs, LLONG_MAX-ll_MAX-1); 
	  
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
	        pair<ll, ll> tmp = *(setds.begin()); 
	        setds.erase(setds.begin()); 
	  
	        // vertex label is stored in second of pair (it 
	        // has to be done this way to keep the vertices 
	        // sorted distance (distance must be first item 
	        // in pair) 
	        ll u = tmp.second; 
	        // 'i' is used to get all adjacent vertices of a vertex 
	        vector<pair<ll, pair<ll, ll> > >::iterator i; 
	        for (i =vertexs[u].connectors.begin(); i != vertexs[u].connectors.end(); ++i) 
	        { 
	            // Get vertex label and weight of current adjacent 
	            // of u. 
	            ll v = (*i).first; 
	            ll d = (*i).second.first; 
	            ll l = (*i).second.second;
	            //  If there is shorter path to v through u. 
	            if (dist[v] > dist[u] + d && l <=L) 
	            { 
	                /*  If distance of v is not INF then it must be in 
	                    our set, so removing it and inserting again 
	                    with updated less distance.   
	                    Note : We extract only those vertices from Set 
	                    for which distance is finalized. So for them,  
	                    we would never reach here.  */
	                if (dist[v] != LLONG_MAX-ll_MAX-1) 
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


typedef struct DisjollSets 
{ 
    ll *parent, *rnk; 
    ll n; 
  
    // Constructor. 
    DisjollSets(ll n) 
    { 
        // Allocate memory 
        this->n = n; 
        parent = new ll[n]; 
        rnk = new ll[n]; 
  
        // Initially, all vertices are in 
        // different sets and have rank 0. 
        for (ll i = 0; i < n; i++) 
        { 
            rnk[i] = 0; 
            //every element is parent of itself 
            parent[i] = i; 
        } 
    } 
  
    // Find the parent of a node 'u' 
    // Path Compression 
    ll find(ll u) 
    { 
        /* Make the parent of the nodes in the path 
           from u--> parent[u] poll to parent[u] */
        if (u != parent[u]) 
            parent[u] = find(parent[u]); 
        return parent[u]; 
    } 
  
    // Union by rank 
    void merge(ll x, ll y) 
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
}DisjollSets; 

bool cmp(pair<ll, pair<ll, ll> > a, pair<ll, pair<ll, ll> > b)
{
       return a.first < b.first;
}


ll kruskalMST(ll n, vector<pair<ll, pair<ll, ll> > > &edges, ll start, ll end) { 
    ll mst_wt = 0; // Initialize result 
    // Sort edges in increasing order on basis of cost 
    sort(edges.begin(), edges.end(), cmp); 
    // Create disjoll sets 
    DisjollSets ds(n); 
  
    // Iterate through all sorted edges 
    vector< pair<ll, pair<ll, ll> > >::iterator it; 
    vector<pair<ll, pair<ll, ll> > > res;
    ll ans = 0;
    for (it=edges.begin(); it!=edges.end(); it++) 
    { 	
        ll u = it->second.first; 
        ll v = it->second.second; 
        ll w = it->first;
        ll set_u = ds.find(u); 
        ll set_v = ds.find(v); 
        ll set_s = ds.find(start);
        ll set_e = ds.find(end);
        // Check if the selected edge is creating 
        // a cycle or not (Cycle is created if u 
        // and v belong to same set) 
        
        if (set_s == set_e) {
//        	if (w > ans) {
//        		ans = w;
//        	}
        	break;
        }
        if (set_u != set_v) 
        { 
//             Current edge will be in the MST 
//             so prll it 
//            cout << u << " - " << v << endl; 
  			pair<ll, ll> temp(u, v);
  			pair<ll, pair<ll, ll> > t(w, temp);
  			res.push_back(t);
            // Update MST weight 
            mst_wt += it->first; 
            if ( w > ans) {
            	ans = w;
            }
  			
            // Merge two sets 
            ds.merge(set_u, set_v); 
        } 
    } 
//    cout << "w:" << mst_wt << endl;
	delete ds.parent;
	delete ds.rnk;
    return ans; 
}




ll main() {
	
	ll n,m;
	cin >> n >> m;
	ll start, end;
	cin >> start >> end;
	Graph g(n, false);
	ll arg1,arg2,arg3,arg4;
	vector<pair<ll, pair<ll, ll> > > edges;
	for (ll i=0; i<m; i++) {
		cin >> arg1 >> arg2 >> arg3 >> arg4;
		g.addEdge(arg1,arg2,arg3,arg4);
		pair <ll, ll> e_info(arg1, arg2);
		pair <ll, pair<ll, ll> > edge(arg4, e_info);
		edges.push_back(edge);
	}	
	ll L = kruskalMST(n,edges,start,end);
//	Graph mst_g(mst.size()+1, false);
//	
//	for (ll i=0; i<mst.size(); i++) {
//		mst_g.addEdge(mst[i].second.first, mst[i].second.second, 0, mst[i].first);
//	}
////	mst_g.prll();
//	vector<bool> bool_arr(n);
//	for (ll i=0; i<n; i++) {
//		bool_arr[i] = false;
//	}
//	pair<bool, ll> result = mst_g.likeDFS(start, end, bool_arr);
//	ll L = result.second;
	ll D = g.shortestPath(start, L, end);	
	cout << D << " " << L << endl;
	
	
	return 0;
} 
