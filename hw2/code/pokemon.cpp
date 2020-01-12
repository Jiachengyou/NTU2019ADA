#include<bits/stdc++.h>

#include <array>
#include <iostream>
#include <random>
#include <stdint.h>
using namespace std;




typedef long long ll;

int findright(int num, int *battle_arr, int left, int right);

int main() {
	int n,k;
	cin >> n >> k;
	int *a = new int[n];
	int *b = new int[n];
	for (int i=0; i<n; i++) {
		cin >> a[i] >> b[i];
	}
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
	
//	for (int i=0; i<n; i++) {
//		cout << "A:" << a[i] << "B:" << b[i] << endl;
//	}
	vector<vector<ll>> dp(n+1);
	for (int i = 0; i < dp.size(); i++) dp[i].resize(k+1);
	vector<vector<ll>> dp_e(n+1);
	for (int i = 0; i < dp_e.size(); i++) dp_e[i].resize(k+1);
	for (int i=0; i<k+1; i++) {
		dp[0][i] = 0;
		dp_e[0][i] = 0;
	}
	for (int i=0; i<n+1; i++) {
		dp[i][0] = 0;
		dp_e[i][0] = 0;
	}
	
	for (int i=1; i<n+1; i++) {
		for (int j=1; j<k+1; j++) {
			//´´½¨dp
			//choose  
			ll max2 = dp[i-1][j-1] + a[i-1]*dp_e[i-1][j-1];
			int t = i;
			int t1 = j;
			for (int m=i; m>=1; m--) {
				for (int n=j; n>=1; n--) {
					if (dp[m-1][n-1] + a[i-1]*dp_e[m-1][n-1] > max2) {
						max2 = dp[m-1][n-1] + a[i-1]*dp_e[m-1][n-1];
						t = m;
						t1 = n;
	//					cout << dp[m-1][j-1] + a[m-1]*dp_e[m-1][j-1] << endl;
	//					cout << max2 << ":" << endl; 
					}
				}	
			}
			ll choose = max2;
			ll Nchoose = dp[i-1][j];
			if (choose > Nchoose) {
				dp[i][j] = choose;
				dp_e[i][j] = dp_e[t-1][t1-1] + b[i-1];
			} else if (choose < Nchoose) {
				dp[i][j] = Nchoose;
				dp_e[i][j] = dp_e[i-1][j];
			} else {
				dp[i][j] = choose;
				dp_e[i][j] = max(dp_e[i-1][j-1] + b[i-1], dp_e[i-1][j]);
			}
		}
	}
	//±ídp 
//	for (int i=0; i<n+1; i++) {
//		for (int j=0; j<k+1; j++) {
//			cout << " " << dp[i][j] << " ";
//		}
//		cout << endl;
//	}
//	for (int i=0; i<n+1; i++) {
//		for (int j=0; j<k+1; j++) {
//			cout << " " << dp_e[i][j] << " ";
//		}
//		cout << endl;
//	}
//	
	cout << dp[n][k] << endl;
	return 0;
   
}


