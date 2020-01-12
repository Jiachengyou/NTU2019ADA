#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
ll findNum(int i, int j, int *arr);
int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	
	int n;
	cin >> n;
	int *arr = new int[n];
	for (int i=0; i<n; i++) {
		cin >> arr[i]; 
	}
	
	ll cnt = findNum(0,n-1,arr);
	cout << cnt+n << endl;
	
	 
	return 0;
}


ll findNum(int i, int j, int *arr) {
	if (i == j) {
		return 0;
	}
	if (j - i == 1) {
		if (abs(arr[j]-arr[i]) == 1) {
			return 1;
		} else {
			return 0;
		}
	} 
	int mid = (i+j)/2; 
	ll leftSum = findNum(i, mid, arr);
	ll rightSum = findNum(mid, j, arr);
	ll middleSum = 0;
	//left遍历 max在左边  
	//right 计算
	int right_cur = mid+1;
	int left_cur = mid-1;
	int left_max = arr[mid], left_min = arr[mid];
	int right_max = arr[mid];
	int right_min = arr[mid];
	int right_max_cur = mid;
	int right_min_cur = j;
	int *right_min_arr = new int[j-mid+1];
	int *right_max_arr = new int[j-mid+1];
	int find_num = left_cur+left_max;
	right_min_arr[0] = arr[mid];
	right_max_arr[0] = arr[mid];
	//计算最小值数组
	for (int k=1; k<j-mid+1; k++) {
		if (arr[mid+k] < right_min_arr[k-1]) {
			right_min_arr[k] = arr[mid+k];
		} else {
			right_min_arr[k] = right_min_arr[k-1];
		}
			  
	}
	//计算最大值数组
	for (int k=1; k<j-mid+1; k++) {
		if (arr[mid+k] > right_max_arr[k-1]) {
			right_max_arr[k] = arr[mid+k];
		} else {
			right_max_arr[k] = right_max_arr[k-1];
		}
			
	}
	map<int,int > mp;
	map<int,int >::iterator p;
	//先更新一次 
		//max_cur 用中心位置先做
	while (right_min_cur > mid+1 && right_min_arr[right_min_cur-mid] <= left_min) {
		right_min_cur--;
	}
	while (right_max_cur <= j-1 && arr[right_max_cur+1] < left_max) {
		right_max_cur++;
	}
	//记录一次
	for (int k=right_min_cur; k<=right_max_cur; k++) {
		if (k == mid) {
			continue;
		}
		p = mp.find(k+right_min_arr[k-mid]);
		if (p != mp.end()) {
			mp[k+right_min_arr[k-mid]] += 1;
		} else {
			mp[k+right_min_arr[k-mid]] = 1;
		}
	}
	while (left_cur >= i) {
		if (arr[left_cur] > left_max) {
			//最大值更新 
			left_max = arr[left_cur];
			while (right_max_cur <= j-1 && arr[right_max_cur+1] < left_max) {
				right_max_cur++;
				if (right_max_cur >= right_min_cur) {
					find_num = right_max_cur + right_min_arr[right_max_cur-mid];
					p = mp.find(find_num);
					if (p != mp.end()) {
						mp[find_num] += 1;
					} else {
						mp[find_num] = 1;
					}
				}
			}
										
		} else if (arr[left_cur] < left_min){
			//最小值更新 
			left_min = arr[left_cur];
			//循环更新 
				while (right_min_cur <= j && right_min_arr[right_min_cur-mid] > left_min) {
					if (right_max_cur >= right_min_cur) {
						find_num = right_min_cur + right_min_arr[right_min_cur-mid];
						p = mp.find(find_num);
						if (p != mp.end()) {
							mp[find_num] -= 1;
						} else {
							mp[find_num] = 0;
						}
					}
					right_min_cur++;
				}
		} 
		//计算 
		find_num = left_max + left_cur; 
		p = mp.find(find_num);
		if (p != mp.end()) {
			middleSum += mp[find_num];
		}
		left_cur--;
	}
	
	//left遍历 max在左边 min在左边 
	//right 计算
	int pos;
	left_cur = mid-1;
	left_max = arr[mid], left_min = arr[mid];
	while(left_cur >= i)  {
		if (arr[left_cur] > left_max) {
			left_max = arr[left_cur];
		} else if (arr[left_cur] < left_min) {
			left_min = arr[left_cur];
		}
		pos = left_max - left_min + left_cur;
		if (pos > mid && pos <=j && right_min_arr[pos-mid] > left_min && right_max_arr[pos-mid] < left_max) {
			middleSum++;
		}
		left_cur--;
	}
	

	//right遍历 max在右边 min在左边  
	//right 计算
	right_cur = mid+1;
	left_cur = mid-1;
	left_max = arr[mid], left_min = arr[mid];
	right_max = arr[mid];
	right_min = arr[mid];
	int left_max_cur = mid;
	int left_min_cur = i;
	int *left_min_arr = new int[mid-i+1];
	int *left_max_arr = new int[mid-i+1];
	find_num = left_min_cur - left_min;
	left_min_arr[mid-i] = arr[mid];
	left_max_arr[mid-i] = arr[mid];
	//计算最小值数组
	for (int k=mid-i-1; k>=0; k--) {
		if (arr[k+i] < left_min_arr[k+1]) {
			left_min_arr[k] = arr[k+i];
		} else {
			left_min_arr[k] = left_min_arr[k+1];
		}
			
	}
	//计算最大值数组
	for (int k=mid-i-1; k>=0; k--) {
		if (arr[k+i] > left_max_arr[k+1]) {
			left_max_arr[k] = arr[i+k];
		} else {
			left_max_arr[k] = left_max_arr[k+1];
		}
			
	}
	map<int,int > mp2;
	
	//先更新一次 
		//max_cur 用中心位置先做
	while (left_min_cur < mid-1 && left_min_arr[left_min_cur-i] <= right_min) {
		left_min_cur++;
	}
	while (left_max_cur >= i+1 && arr[left_max_cur-1] < right_max) {
		left_max_cur--;
	}
	//记录一次
	for (int k=left_max_cur; k<=left_min_cur; k++) {
		if (k == mid) {
			continue;
		}
		p = mp2.find(left_min_arr[k-i]-k);
		if (p != mp2.end()) {
			mp2[left_min_arr[k-i]-k] += 1;
		} else {
			mp2[left_min_arr[k-i]-k] = 1;
		}
	}

	while (right_cur <= j) {
		if (arr[right_cur] > right_max) {
			//最大值更新 
			right_max = arr[right_cur];
			while (left_max_cur >= i+1 && arr[left_max_cur-1] < right_max) {
				left_max_cur--;
				if (left_min_cur >= left_max_cur) {
					find_num = -left_max_cur + left_min_arr[left_max_cur-i];
					p = mp2.find(find_num);
					if (p != mp.end()) {
						mp2[find_num] += 1;
					} else {
						mp2[find_num] = 1;
					}
				}
			}
										
		} else if (arr[right_cur] < right_min){
			//最小值更新 
			right_min = arr[right_cur];
			//循环更新  
				while (left_min_cur >= i && left_min_arr[left_min_cur-i] > right_min) {
					if (left_max_cur <=  left_min_cur) {
						find_num = - left_min_cur + left_min_arr[left_min_cur-i];
						p = mp2.find(find_num);
						if (p != mp2.end()) {
							mp2[find_num] -= 1;
						} else {
							mp2[find_num] = 0;
						}
					}
					left_min_cur--;
				}
		} 
		//计算 
		find_num = right_max - right_cur; 
		p = mp2.find(find_num);
		if (p != mp2.end()) {
			middleSum += mp2[find_num];
		}
		right_cur++;
	}
	
	//right遍历 max在右边 min在右边 
	//left 计算
	right_cur = mid+1;
	right_max = arr[mid], right_min = arr[mid];
	while(right_cur <= j)  {
		if (arr[right_cur] > right_max) {
			right_max = arr[right_cur];
		} else if (arr[right_cur] < right_min) {
			right_min = arr[right_cur];
		}
		pos = -right_max + right_min + right_cur;
		if (pos >= i && pos < mid && left_min_arr[pos-i] > right_min && left_max_arr[pos-i] < right_max) {
			middleSum++;
		}
		right_cur++;
	}
	return leftSum + middleSum + rightSum;
	 
	
}

