#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
ll findSum(int i,int j,ll *prefer, ll *friendline);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n;
	cin >> n;
	ll cnt = 0;
	ll diff;
	ll *prefer = new ll[n];
	ll *friendline = new ll[n];
	for (int i=0; i<n; i++){
		cin >> prefer[i];
	} 
	for (int i=0; i<n; i++){
		cin >> friendline[i];
	} 
	cnt = findSum(0,n-1,prefer,friendline);
	cout << cnt << endl;
	
	return 0;
}

ll findSum(int i,int j,ll *prefer, ll *friendline) { 
	if (i==j) {
		return 0;
	}
	if ((j - i) == 1) {
		if (abs(prefer[j]-prefer[i]) <= friendline[j]) {
			return 1;
		} else {
			return 0;
		}
	}
	int mid = (i+j)/2;
	ll leftSum = findSum(i,mid,prefer,friendline);
	ll rightSum = findSum(mid+1,j,prefer,friendline);
	ll cnt = 0;
	// LEFT 
	//left
	ll left_n = mid-i+1;
	ll *left_arr =  new ll[left_n];
	for (int k=0; k<mid-i+1; k++) {
		left_arr[k] = prefer[i+k];		
	}
	sort(left_arr, left_arr+left_n);
	//right
	int right_n = j-mid;
	ll *right_arr_left =  new ll[right_n];
	ll *right_arr_right =  new ll[right_n];
	for (int k=0; k<j-mid; k++) {
		right_arr_left[k] = prefer[mid+1+k]-friendline[mid+1+k];		
	}
	for (int k=0; k<j-mid; k++) {
		right_arr_right[k] = prefer[mid+1+k]+friendline[mid+1+k];		
	}
	sort(right_arr_left, right_arr_left+right_n);
	int left_cur = 0;
	int right_cur = 0;
	while(left_cur < left_n && right_cur < right_n) {
		if (left_arr[left_cur] < right_arr_left[right_cur]) {
			left_cur++;
		} else {
			cnt += left_n - left_cur;
			right_cur++;
		}
	}
	// RIGHT
	//left
	sort(left_arr, left_arr+left_n,greater<int>());
	//right
	sort(right_arr_right, right_arr_right+right_n,greater<int>());
	left_cur = 0;
	right_cur = 0;
	while(left_cur < left_n && right_cur < right_n) {
		if (left_arr[left_cur] > right_arr_right[right_cur]) {
			left_cur++;
		} else {
			cnt += left_n - left_cur;
			right_cur++;
		}
	}
	delete [] right_arr_left;
	delete [] right_arr_right;
	delete [] left_arr;
	cnt -= left_n*right_n;
	return leftSum + rightSum + cnt;
}

