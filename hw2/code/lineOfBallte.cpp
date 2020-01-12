#include<bits/stdc++.h>

#include <array>
#include <iostream>
#include <random>
#include <stdint.h>
using namespace std;




typedef long long ll;

namespace ada {

class Xoroshiro128 {
 public:
  using result_type = uint32_t;
  static constexpr result_type(min)() { return 0; }
  static constexpr result_type(max)() { return UINT32_MAX; }
  static inline result_type rotl(const result_type x, int k) {
    return (x << k) | (x >> (32 - k));
  }
  Xoroshiro128() : Xoroshiro128(1, 2, 3, 4) {}
  Xoroshiro128(result_type a, result_type b, result_type c, result_type d)
      : s{a, b, c, d} {}
  result_type operator()() {
    const result_type result = rotl(s[0] + s[3], 7) + s[0];
    const result_type t = s[1] << 9;
    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];
    s[2] ^= t;
    s[3] = rotl(s[3], 11);
    return result;
  }

 private:
  std::array<result_type, 4> s;
};

namespace {
	int c_lead, c_team;
	Xoroshiro128 rng;
}  // namespace

int Init() {
  int n;
  uint32_t s1, s2, s3, s4;
  std::cin >> n >> c_lead >> c_team >> s1 >> s2 >> s3 >> s4;
  rng = Xoroshiro128(s1, s2, s3, s4);
  return n;
}

int GetLeadership() { return uint64_t(rng()) * c_lead >> 32; }

int GetTeamValue() {
  int tmp = int(uint64_t(rng()) * c_team >> 32) + 1;
  return int(c_team / sqrt(tmp));
}

}  // namespace ada



const int kN = 2000000;
ll leadership[kN], team_value[kN];

int findright(int pos, int num, ll *front_value_sum, int left, int right);

int main() {
//	input1
   int n = ada::Init(); // Get N
   for (int i = 0; i < n; i++) leadership[i] = ada::GetLeadership();
   for (int i = 0; i < n; i++) team_value[i] = ada::GetTeamValue();
   // 这是我的code 终于找到bug了 
//  for (int i = 0; i <	n; i++) cout << team_value[i] << endl;
//  cout << "****" << endl;
//  for (int i = 0; i < n; i++) cout << leadership[i] << endl;
  
//  input2
//	int n;
//	cin >> n;
//	int *leadership = new int[n];
//	int *team_value = new int[n];
//	for (int i = 0; i < n; i++) cin >> leadership[i];
//  	for (int i = 0; i < n; i++) cin >> team_value[i];
	
	
   ll *front_value_sum = new ll[n];
   front_value_sum[0] = team_value[0];
   for (int i=1; i<n; i++) {
   		front_value_sum[i] = front_value_sum[i-1] + team_value[i];
   }
   ll *dp = new ll[n+1];
   dp[n] = 1;
   ll *dp_sum = new ll[n+1];
   dp_sum[n] = 1;
   
   for (int i=n-1; i>=0; i--) {
   		int right = findright(i, leadership[i], front_value_sum, i, n-1);
//   		cout << i << ":" << right << endl;
   		if (right == i) {
   			dp[i] = dp[i+1];
   			dp_sum[i] = (dp[i] + dp_sum[i+1]) % ll(1e9+7);
   		} else {
		   dp[i] = (dp_sum[i+1] - dp_sum[right+1] + dp[right+1] + ll(1e9+7)) % ll(1e9+7);
   		   dp_sum[i] = (dp[i] + dp_sum[i+1]) % ll(1e9+7);
   		}
//   		cout << "dp:" << dp[i] << "dp_sum:" << dp_sum[i] << endl;
   }
   cout << (dp[0] + ll(1e9+7)) % ll(1e9+7);
   
}

int findright(int pos, int num, ll *front_value_sum, int left, int right) {
	if (left >= right) {
		if ((front_value_sum[left]-front_value_sum[pos]) <= num) {
			return left;
		} else {
			return left-1;
		}
	}
	int mid = (left + right) / 2;
	if ((front_value_sum[mid]-front_value_sum[pos]) <= num) {
		return findright(pos,num,front_value_sum, mid+1, right);
	} else {
		return findright(pos,num,front_value_sum, left, mid);
	}
}

