#include<bits/stdc++.h>

using namespace std; 

ll main() {

 // v1 = rand() % 100;         // v1 in the range 0 to 99
//v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
//v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014 
    ll T = 5;
    cout << T << endl;
    for (ll k=0; k<T; k++) {
	    ll n = rand() % 100 + 1;
	    ll m = rand() % 100 + 1;
	    ll a[100001];
	    cout << n << " " << m << endl;
	
	
	    for(ll i = 0; i < n; ++i) {
	        ll ai = rand() % 1000000 + 1;
	        a[i] = ai;
	        cout << ai << " ";
	    }
	    cout << endl;
	
	    for(ll i = 0; i < m; ++i) {
	        ll s1 = rand() % n + 1;
	        ll s2 = rand() % n + 1;
	        ll t1 = rand() % a[s1-1] + 1; 
	        ll t2 = rand() % a[s2-1] + 1; 
	        cout << s1 << " " << t1 << " " << s2 << " " << t2 << endl;
	    }
	}
    return 0;
}
