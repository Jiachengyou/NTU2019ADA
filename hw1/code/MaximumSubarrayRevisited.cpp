#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int maxSubarray(int *arr,int i,int j);
ll maxSubarray2(int *arr,int x,int j);
int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	
	int n,p;
	cin >> n;
	cin >> p;
	int *arr = new int[n];
	for (int i=0; i<n; i++) {
		cin >> arr[i];
	}
	cout << max(maxSubarray2(arr,0,n-1),ll(0)) << endl;
	int pi,vi; 
	for(int i=0; i<p; i++) {
		cin >> pi;
		cin >> vi;
		arr[pi-1] = vi;
		cout << max(maxSubarray2(arr,0,n-1),ll(0)) << endl;		
	}
	
	return 0;
}

ll maxSubarray2(int *arr,int x,int j){
	ll maxx=0;
	ll sum = 0;
	for (int i=0; i<j-x+1; i++){
		if (sum>=0) {
			sum = sum+arr[i];
			if (sum > maxx) {
				maxx = sum;
			}
		} else {
			sum = arr[i]; 
			if (sum > maxx) {
				maxx = sum;
			}
		} 
	} 
	return maxx;
}


int maxSubarray(int *arr,int i,int j) {
	if (i==j) {
		return arr[i];
	}
	int mid=(i+j)/2;
	int left = maxSubarray(arr,i,mid);
	int right = maxSubarray(arr,mid+1,j);
	int middle = arr[mid];
	int lefti = mid-1, righti=mid+1;
	int leftSum=0,rightSum=0;
	int leftMax=0,rightMax=0;
	while(lefti >= i) {
		leftSum += arr[lefti];
		lefti--;
		if (leftSum > leftMax) {
			leftMax = leftSum;
		}
	}
	while(righti <= j) {
		rightSum += arr[righti];
		righti++;
		if (rightSum > rightMax) {
			rightMax = rightSum;
		}
	}
	middle = middle+leftMax+rightMax;
	return max(max(middle,left),right);
}

