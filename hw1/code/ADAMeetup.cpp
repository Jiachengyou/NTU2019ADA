#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n;
	cin >> n;
	int cnt = 0;
	ll diff;
	ll *prefer = new ll[n];
	ll *friendline = new ll[n];
	for (int i=0; i<n; i++){
		cin >> prefer[i];
	} 
	for (int i=0; i<n; i++){
		cin >> friendline[i];
	} 
	for (int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			diff = abs(prefer[i]-prefer[j]);
			if (friendline[j] >= diff) {
				cnt++;
			} else {
				continue;
			}
		}
	}
	cout << cnt << endl;
	
	return 0;
}

