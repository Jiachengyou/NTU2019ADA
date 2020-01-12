#include<bits/stdc++.h>

#include <array>
#include <iostream>
#include <random>
#include <stdint.h>
using namespace std;




typedef long long ll;

int findright(int num, int *battle_arr, int left, int right);

int main() {
	int n;
	cin >> n;
	int s_len = 3; 
	int *s_arr = new int[s_len];
	for (int i=0; i<s_len; i++) {
		cin >> s_arr[i];
	}
	sort(s_arr, s_arr+3);
	int *battle_arr = new int[n];
	bool *bool_arr = new bool[n];
	for (int i=0; i<n; i++) {
		bool_arr[i] = 1;
	}
	for (int i=0; i<n; i++) {
		cin >> battle_arr[i];
	}
	sort(battle_arr, battle_arr+n, greater<int>());
	
	//process s_arr
	int s_max = s_arr[2];
	int s_mid = s_arr[1];
	int s_min = s_arr[0];
	//pattern1
	int cur = 0;
	int len = n;
	int cnt = 0;
	if (s_mid + s_min > s_max) {
		// seven cases
		while (cur < len) {
//			had
			if (!bool_arr[cur]) {
				cur++;
				cnt++;
				continue;
			}
			//case1
			if (battle_arr[cur] <= s_min) {
				cur++;
				while (cur < len && !bool_arr[cur]) {
					cur++;
				}
				if (cur < len) {
					cur++;
					while (cur < len && !bool_arr[cur]) {
						cur++;
					}
				}
			} else if (battle_arr[cur] <= s_mid) {
				//case2
				cur++;
				while (cur < len && !bool_arr[cur]) {
					cur++;
				}
				if (cur < len) {
					//big one
					cur++;
					while (cur < len && !bool_arr[cur]) {
						cur++;
					}
					//min one
					if (cur >= len) {
						cnt++;
						continue;
					}
					int right = findright(s_min,battle_arr, cur, n-1);
					while (!bool_arr[right]) {
						right++;
					}
					if (right <len) {
						bool_arr[right] = 0;
						cur++;
					}
				}
			} else if (battle_arr[cur] <= s_max) {
				//case3
				cur++;
				while (cur < len && !bool_arr[cur]) {
					cur++;
				}
				//mid one 
				if (cur >= len) {
					cnt++;
					continue;
				}
				int right = findright(s_mid,battle_arr, cur, n-1);
				while (!bool_arr[right]) {
					right++;
				}
				if (right <len) {
					bool_arr[right] = 0;
					cur++;
				}
				//min one
				if (cur >= len) {
					cnt++;
					continue;
				}
				right = findright(s_min,battle_arr, cur, n-1);
				while (!bool_arr[right]) {
					right++;
				}
				if (right <len) {
					bool_arr[right] = 0;
					cur++;
				}
			} else if (battle_arr[cur] <= s_min+s_mid) {
				//case4
				cur++;
				while (cur < len && !bool_arr[cur]) {
					cur++;
				}
				//max one 
				if (cur >= len) {
					cnt++;
					continue;
				}
				int right = findright(s_max,battle_arr, cur, n-1);
				while (!bool_arr[right]) {
					right++;
				}
				if (right <len) {
					bool_arr[right] = 0;
					cur++;
				}
			} else if (battle_arr[cur] <= s_min+s_max) {
				//case5
				cur++;
				while (cur < len && !bool_arr[cur]) {
					cur++;
				}
				//mid one 
				if (cur >= len) {
					cnt++;
					continue;
				}
				int right = findright(s_mid,battle_arr, cur, n-1);
				while (!bool_arr[right]) {
					right++;
				}
				if (right <len) {
					bool_arr[right] = 0;
					cur++;
				}
			} else if (battle_arr[cur] <= s_mid+s_max) {
				//case6
				cur++;
				while (cur < len && !bool_arr[cur]) {
					cur++;
				}
				//min one 
				if (cur >= len) {
					cnt++;
					continue;
				}
				int right = findright(s_min,battle_arr, cur, n-1);
				while (!bool_arr[right]) {
					right++;
				}
				if (right <len) {
					bool_arr[right] = 0;
					cur++;
				}
			} else if (battle_arr[cur] <= s_mid+s_max+s_min) {
				//case6
				cur++;
				while (cur < len && !bool_arr[cur]) {
					cur++;
				}
				//min one 
				if (cur >= len) {
					cnt++;
					continue;
				}
			} else {
				cout << -1 << endl;
				return 0;
			}
			cnt++; 
		}
		
	} else {
		while (cur < len) {
//			had
			if (!bool_arr[cur]) {
				cur++;
				cnt++;
				continue;
			}
			//case1
			if (battle_arr[cur] <= s_min) {
				cur++;
				while (cur < len && !bool_arr[cur]) {
					cur++;
				}
				if (cur < len) {
					cur++;
					while (cur < len && !bool_arr[cur]) {
						cur++;
					}
				}
			} else if (battle_arr[cur] <= s_mid) {
				//case2
				cur++;
				while (cur < len && !bool_arr[cur]) {
					cur++;
				}
				if (cur < len) {
					//big one
					cur++;
					while (cur < len && !bool_arr[cur]) {
						cur++;
					}
					//min one
					if (cur >= len) {
						cnt++;
						continue;
					}
					int right = findright(s_min,battle_arr, cur, n-1);
					while (!bool_arr[right]) {
						right++;
					}
					if (right <len) {
						bool_arr[right] = 0;
						cur++;
					}
				}
			} else if (battle_arr[cur] <= s_max) {
				int t = cur;
				cur++;
				while (cur < len && !bool_arr[cur]) {
					cur++;
				}
				if (cur >= len) {
					cnt++;
					continue;
				}
				
				//test 
				int right1 = findright(s_min,battle_arr, cur, n-1);
				while (!bool_arr[right1]) {
					right1++;
				}
				int right2 = findright(s_mid,battle_arr, cur, n-1);
				while (!bool_arr[right2]) {
					right2++;
				}
				//has two 
				if (right1 <len && right2<len) {
					bool_arr[right1] = 0;
					bool_arr[right2] = 0;
					cur++;
					continue;
				} else {
					// has not two; reback
					cur = t;
					if (battle_arr[cur] <= s_min+s_mid) {
						//like mid
						cur++;
						while (cur < len && !bool_arr[cur]) {
							cur++;
						}
						if (cur < len) {
							//big one
							cur++;
							while (cur < len && !bool_arr[cur]) {
								cur++;
							}
						}
							
					} else {
						//min one
						cur++;
						if (cur >= len) {
							cnt++;
							continue;
						}
						int right = findright(s_mid+s_min,battle_arr, cur, n-1);
						while (!bool_arr[right]) {
							right++;
						}
						if (right <len) {
							bool_arr[right] = 0;
							cur++;
						}
						
					}					
					 
					
				} 
			
			} else if (battle_arr[cur] <= s_min+s_max) {
				//case5
				cur++;
				while (cur < len && !bool_arr[cur]) {
					cur++;
				}
				//mid one 
				if (cur >= len) {
					cnt++;
					continue;
				}
				int right = findright(s_mid,battle_arr, cur, n-1);
				while (!bool_arr[right]) {
					right++;
				}
				if (right <len) {
					bool_arr[right] = 0;
					cur++;
				}
			} else if (battle_arr[cur] <= s_mid+s_max) {
				//case6
				cur++;
				while (cur < len && !bool_arr[cur]) {
					cur++;
				}
				//min one 
				if (cur >= len) {
					cnt++;
					continue;
				}
				int right = findright(s_min,battle_arr, cur, n-1);
				while (!bool_arr[right]) {
					right++;
				}
				if (right <len) {
					bool_arr[right] = 0;
					cur++;
				}
			} else if (battle_arr[cur] <= s_mid+s_max+s_min) {
				//case6
				cur++;
				while (cur < len && !bool_arr[cur]) {
					cur++;
				}
				//min one 
				if (cur >= len) {
					cnt++;
					continue;
				}
			} else {
				cout << -1 << endl;
				return 0;
			}
			cnt++; 
		}
		
		
	}
	
	cout << cnt << endl;
	return 0;
		
	
   
}

int findright(int num, int *battle_arr, int left, int right) {
	if (left >= right) {
		if (battle_arr[left] <= num) {
			return left;
		} else {
			return left-1;
		}
	}
	int mid = (left + right) / 2;
	if (battle_arr[mid] <= num) {
		return findright(num,battle_arr,left,mid-1);
	} else {
		return findright(num,battle_arr,mid+1,right);
	}
}

