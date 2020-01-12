#include<bits/stdc++.h>

// reference https://aiden-dong.github.io/2018/04/12/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E4%B9%8B%E6%8B%93%E6%89%91%E6%8E%92%E5%BA%8F%E4%B8%8E%E5%85%B3%E9%94%AE%E8%B7%AF%E5%BE%84/
using namespace std;
stack <int> st; 
queue<int> qu; 

template <class T>
inline void scan_d(T &ret)
{
    char c;
    ret = 0;
    while ((c = getchar()) < '0' || c > '9');
    while (c >= '0' && c <= '9')
    {
        ret = ret * 10 + (c - '0'), c = getchar();
    }
}

//int indegree[262145]; 
//int father[262145];
int a[262145];
int father[262145];
int quick_del[262145];
int vs[262145];

vector<int> indegree(262145);

int n; // number of total vertices
int p;
int q;
int m; // number of vertices to be removed
int cur_vertex;

int find_counter(int vs[], int m) {
    int ans = 0;

    for(int i = 0; i < m; ++i) {
         int x = vs[i] - 1;
         ans += quick_del[x];
         qu.push(a[father[x]]);
    }

    while(!qu.empty()) {
        int curr_v = qu.front();
        st.push(curr_v);
        indegree[curr_v]--;
        
        qu.pop();
        if(indegree[curr_v] == 0) {
            qu.push(a[father[curr_v]]);
            ans += quick_del[curr_v];
        }
    }
   // for adding back indegrees
    while(!st.empty()) {
        int curr_v = st.top();
        st.pop();
        indegree[curr_v]++;
    }
    return ans;
   // int des = a[src];
/*
    indegree[des]--;
    if(indegree[des] == 0) {
        ans = quick_del[src] + quick_del[father[des]];


        
        int search = father[des];
        for(int i = 1; i <= n; ++i) {
            if(father[i] == search) {
                ++ans;
            }
        }
        cout << "adding -- " << ans << endl;
        return ans; 

        //ans += indegree[des] - indegree[father[des]];
        //return ans;
    } else {
        return 1;
    } */


}

int main() {
    scan_d(n);
    //cout << n << endl;
    //indegree[0] = 0;
    for(int i = 0; i < n; ++i) {
        indegree[i] = 0;
        father[i] = i;
        quick_del[i] = 1;
    }

    for(int i = 0; i < n; ++i) {
        // vertex 1 to n
        // i -> p
        scan_d(p);
        a[i] = p-1;
        //a[i] = p;
        // construct indegree array
        indegree[a[i]]++;
    }
    /*
    for(int i = 0; i <= n; ++i) {
        cout << indegree_cp[i] << endl;
    } */

    // indegree = indegree_cp;

    //cout << "-----end of indegree-------"<< endl;

    for(int i = 0; i < n; ++i) {
        /*
        if(father[i] != 0) {
            continue;
        } */
        if(indegree[i] != 1) {
                int curr_father = i;
                int next = a[i];
            while(indegree[next] == 1 && next != curr_father) {
                //curr_father = next;
                quick_del[i]++;
                /*
                if(next == 0) {
                    break;
                } */
                // st.push(next);
                curr_father = next;
                next = a[next];
            } 
                father[i] = curr_father;
                /*
            while(!st.empty()) {
                father[st.top()] = curr_father;
                st.pop();
            } */
        } 
    }

/*
    for(int i = 1; i <= n; ++i) {
        cout << father[i] << endl;
    } 
    cout << "-----end of father-------"<< endl;  */
/*
    for(int i = 1; i <=n; ++i) {
        int adding_v = father[i];
        quick_del[adding_v]++;
    } */
/*
    for(int i = 1; i <= n; ++i) {
        cout << quick_del[i] << endl;
    } 
    cout << "-----end of quick_del-------"<< endl;
    */

    scan_d(q);
   // cout << q << endl;
    int counter = 0;
    for(int i = 0; i < q; ++i) {
        scan_d(m);
        counter = 0;
        //indegree = indegree_cp;
        for(int i = 0; i < m; ++i) {
            scan_d(cur_vertex);
            vs[i] = cur_vertex;
        }
        //cout << "--------" << endl;
        counter = find_counter(vs, m);
        printf("%d\n", counter);
    }

    return 0;
}
