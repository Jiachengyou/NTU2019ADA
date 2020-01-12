#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
	string word1, word2;
	cin >> word1;
	cin >> word2;
	int len1 = word1.length();
	int len2 = word2.length();
	int minn = min(len1,len2);
	vector<vector<int> > dp(len1+1, vector<int>(len2+1));
	dp[len1][len2] = 0;
	for (int i=len1-1; i>=0; i--) {
		dp[i][len2] = 0;
	}
	for (int i=len2-1; i>=0; i--) {
		dp[len1][i] = 0;
	}
	for (int i=len1-1; i>=0; i--) {
		for (int j=len2-1; j>=0; j--) {
			if (word1[i] != word2[j]) {
				dp[i][j] = dp[i+1][j+1];
			} else {
				dp[i][j] = 1+min(dp[i+1][j+1],min(dp[i][j+1],dp[i+1][j]));
			}
		}
	}
	cout << dp[0][0] << endl;
	return 0;
}

