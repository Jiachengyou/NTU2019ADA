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
int leadership[kN], team_value[kN];



int main() {
   int n = ada::Init(); // Get N
   for (int i = 0; i < n; i++) leadership[i] = ada::GetLeadership();
   for (int i = 0; i < n; i++) team_value[i] = ada::GetTeamValue();
//   for (int i = 0; i < n; i++) cout << team_value[i] << endl;
//   cout << "****" << endl;
//   for (int i = 0; i < n; i++) cout << leadership[i] << endl;
   
   // 问题解决分两部分，第一部分为dp找到最近的舰长，第二部分为根据舰长dp
   int *next_flagship = new int[n];
   next_flagship[0] = 0;
   int left_cur = 0;
   ll left_num = leadership[0];
   int cur = 0;
   while (cur < n) {
   		//dp
   		if (cur == left_cur) {
   			next_flagship[cur] =  left_cur;
   			left_cur = cur;
   			left_num = leadership[cur];
   			cur++;
   			continue;
   		}
   		if (team_value[cur] <= left_num) {
   		   left_num -= team_value[cur];
   		   next_flagship[cur] =  left_cur;
   		   cur++;
   		} else {
   		   left_cur++;
   		   left_num += leadership[left_cur] - leadership[left_cur-1] + team_value[left_cur];
   		}	
   }
   
   // 计算dp
   ll *dp = new ll[n];  
   dp[0] = 1;
   int left_flag_ship = 0;
   for (int i=1; i<n; i++) {
       left_flag_ship = next_flagship[i];
       ll left_sum = 0;
       for (int j=left_flag_ship+1; j<=i; j++) {
       		left_sum += team_value[j];	 
	   }
       ll sum = 0;
       for (int j=left_flag_ship; j<i; j++) {
       		if (leadership[j] >= left_sum && j>0) {
       			sum += dp[j-1];
       			left_sum -=  team_value[j+1];
       		} else if (leadership[j] >= left_sum && j == 0) {
       			sum += dp[j];
       			left_sum -=  team_value[j+1];
       		} else {
       			left_sum -=  team_value[j+1];
       		}
       } 
       dp[i] = sum + dp[i-1];
       
   }
   cout << dp[n-1] << endl; 
}

