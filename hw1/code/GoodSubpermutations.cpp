#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	
	int n;
	cin >> n;
	int *arr = new int[n];
	for (int i=0; i<n; i++) {
		cin >> arr[i]; 
	}
	vector<vector<int> > maxArr(n,vector<int>(n));
	vector<vector<int> > minArr(n,vector<int>(n));
	int cnt = 0;
//	for (int i=0; i<n; i++) {0
//		vector<int> temArr;
//		maxArr.push_back(temArr);
//		minArr.push_back(temArr);
//		for (int j=0; j<n; j++) {
//			maxArr[i].push_back(0);
//			minArr[i].push_back(0);
//		}
//	}
	//³õÊ¼»¯ 
	for (int i=0; i<n; i++) {
		maxArr[i][i] = arr[i];
		minArr[i][i] = arr[i];
	}
	for (int i=0; i<n; i++) {
		for (int j=i+1; j<n; j++) {
			if (arr[j] > maxArr[i][j-1]) {
				maxArr[i][j] = arr[j];
			} else {
				maxArr[i][j] = maxArr[i][j-1];
			}
				
			if (arr[j] < minArr[i][j-1]) {
				minArr[i][j] = arr[j];
			} else {
				minArr[i][j] = minArr[i][j-1];
			}
			if (maxArr[i][j]-minArr[i][j] == j-i) {
				cnt++;
			}
		}
	} 
	cout << cnt+n << endl;
	
	 
	return 0;
}

