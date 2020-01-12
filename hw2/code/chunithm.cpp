#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
int effort(int x, int y, int k);
#define MAX INT_MAX

vector <int> dequeue(int n, int k, vector<int>arr);

int main() {
	
	int n,m,k;
	cin >> n >> m >> k;
	vector<int> arr(n);
	for (int i=0; i<n; i++) {
		cin >> arr[i]; 
	} 
	
	vector<vector<int>> dp(n+1, vector<int>(m));
	
	// init
	
	for (int i=0; i<m; i++) {
		dp[0][i] = 0;
	}
	for (int i=0; i<m; i++) {
		dp[1][i] = 0;
	}
	
	int diff_old = 0;
	for (int i=2; i<n+1; i++) {
		// diff_min
		int diff_new = MAX;
		//same_window
		//begin 
		//change length
		vector <int> new_arr;
		for (int c=0; c<k; c++) {
			new_arr.push_back(MAX);
		} 
		for (int c=0; c<m; c++) {
			new_arr.push_back(dp[i-1][c]);
		} 
		for (int c=0; c<k; c++) {
			new_arr.push_back(MAX);
		} 
		vector <int> min_arr = dequeue(m+2*k, 1+2*k,new_arr);
//		for (int c=0; c<m; c++) {
//			cout << min_arr[c] << ":";
//		} 	
		for (int j=0; j<m; j++) {
			// case1 diff
			int diff_min = diff_old + effort(arr[i-2],j,k);
			// case same
			int same_min = min_arr[j] + effort(arr[i-1], arr[i-2], k);
			dp[i][j] = min(diff_min, same_min);
			//save_diff 
			if (i < n) {
				int diff_effort = dp[i][j] + effort(arr[i],j,k);
				if (diff_effort < diff_new) {
					diff_new = diff_effort;
				}
			}			
//			cout << "i:" << i << "j:" << j << "value" << dp[i][j] << endl;
			
			
		}
		diff_old = diff_new;
	}
	int result = MAX;
	for (int i=0; i<m; i++) {
		if (dp[n][i] < result) {
			result = dp[n][i];
		}
	}
	cout << result << endl;
	
	
	return 0;
}

int effort(int x, int y, int k) {
	if (abs(x-y) <= k) {
		return 0;
	} else {
		return abs(x-y)-k;
	}
}

vector <int> dequeue(int n, int k, vector<int> arr) {
	

	vector<int> res;
	deque<int> window; 
//	first init
	for (int i=0; i<k-1; i++) {
		while (!window.empty() && arr[i] < arr[window.back()]) {
			window.pop_back();
		}
		window.push_back(i);
	}
	
	for (int i=k-1; i<n; i++) {
		if (!window.empty() && window.front() <= i - k) {
				window.pop_front();
		}
		while (!window.empty() && arr[i] < arr[window.back()]) {
			window.pop_back();
		}
		window.push_back(i);
		res.push_back(arr[window.front()]);
	}
	
	return res;
}

