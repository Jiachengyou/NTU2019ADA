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
			if (a[j] ==0 && b[j] ==0) {
				int t1 = b[j];
				b[j] = b[j+1];
				b[j+1] = t1;
				int t2 = a[j];
				a[j] = a[j+1];
				a[j+1] = t2;
				continue;
			}
			if (float(b[j]) / float(a[j]) < float(b[j+1]) / float(a[j+1])) {
				//swap
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
	//¶þ·Ö±©Á¦ 
	ll max = 0;
	for (int i=0; i<(1<<n); i++) {
		ll sum = 0;
		int exper = 0;
		int num = 0;
		for (int j=0; j<n; j++) {
			if (i&(1<<j)) {
				sum = sum + a[j]*exper;
				exper = exper + b[j];
				num++;				
			}	
		}
//		if (sum == 604) {
//			for (int j=0; j<n; j++) {
//			if (i&(1<<j)) {
//				cout << j << " ";			
//			}	
//		}
		}
		if (sum > max && num<=k) {
			max = sum;
		}
	}
	
	cout << max << endl;
	return 0;
   
}


