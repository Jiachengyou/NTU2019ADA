#include<bits/stdc++.h>

#include <array>
#include <iostream>
#include <random>
#include <stdint.h>
using namespace std;




typedef long long ll;

int findright(int num, int *battle_arr, int left, int right);

//贾成铕nb 

int main() {
	int n,k;
	cin >> n >> k;
	int *a = new int[n];
	int *b = new int[n];
	for (int i=0; i<n; i++) {
		cin >> a[i] >> b[i];
	}
	int exper = 0;
	for (int i=0; i<n; i++) {
		exper += b[i];
	}
	vector< vector<int> > dp(k+1, vector<int>(exper+1));
	vector< vector<int> > dp_next(k+1, vector<int>(exper+1));
	//sort 
	for (int i=0; i<n; i++) {
		for (int j=0; j<n-i-1; j++) {
			if (float(b[j]) / float(a[j]) < float(b[j+1]) / float(a[j+1])) {
				//swap
				int t1 = b[j];
				b[j] = b[j+1];
				b[j+1] = t1;
				int t2 = a[j];
				a[j] = a[j+1];
				a[j+1] = t2;
			}
			if (a[j] ==0 && b[j] ==0) {
				int t1 = b[j];
				b[j] = b[j+1];
				b[j+1] = t1;
				int t2 = a[j];
				a[j] = a[j+1];
				a[j+1] = t2;
			}
		}
	}
	for (int i=0; i<k+1; i++) {
		for (int j=0; j<exper+1; j++) {
			dp[i][j] = -1;
		}
	}
	dp[0][0] = 0;
	
	for (int i=1; i<n+1; i++) {
		for (int j=0; j<k+1; j++) {
			for (int e=0; e<exper+1; e++) {
				if (e- b[i-1] < 0) {
					dp_next[j][e] = dp[j][e];
				} else {
					if (j == 0) {
						dp_next[j][e] = -1;
						continue;
					}
					// 前方遍历
					if (dp[j][e] == -1 && dp[j-1][e-b[i-1]] == -1) {
						dp_next[j][e] = -1;
					} else if (dp[j][e] == -1) {
						dp_next[j][e] = dp[j-1][e-b[i-1]] + a[i-1]*(e-b[i-1]);
					} else if (dp[j-1][e-b[i-1]] == -1) {
						dp_next[j][e] = dp[j][e];
					} else {
						dp_next[j][e] = max(dp[j][e], dp[j-1][e-b[i-1]] + a[i-1]*(e-b[i-1]));
					}
				}
			}
		}

		//swap
		
		for (int j=0; j<k+1; j++) {
			for (int e=0; e<exper+1; e++) {
				dp[j][e] = dp_next[j][e];
			}
		}
	}
	
	int res = 0;
	for (int e=0; e<exper+1; e++) {
		if (dp[k][e] > res) {
			res = dp[k][e];
		}
	}
	cout << res << endl;
	
	for (int i=0; i<n; i++) {
		cout << "A:" << a[i] << "B:" << b[i] << endl;
	}
	
	
	return 0;
   
}


