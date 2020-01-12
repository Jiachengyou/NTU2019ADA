#include<bits/stdc++.h>

#include <array>
#include <iostream>
#include <random>
#include <stdint.h>
using namespace std;


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

typedef long long ll;
int main() {
//	input1
   int n = ada::Init(); // Get N
   for (int i = 0; i < n; i++) leadership[i] = ada::GetLeadership();
   for (int i = 0; i < n; i++) team_value[i] = ada::GetTeamValue();
//  for (int i = 0; i < n; i++) cout << team_value[i] << endl;
//  cout << "****" << endl;
//  for (int i = 0; i < n; i++) cout << leadership[i] << endl;
  
//  input2
//	int n;
//	cin >> n;
//	int *leadership = new int[n];
//	int *team_value = new int[n];
//	for (int i = 0; i < n; i++) cin >> leadership[i];
//  	for (int i = 0; i < n; i++) cin >> team_value[i];
  	
  	
  	//¶þ·Ö±©Á¦ 
	ll num = 0;
	for (int i=0; i<(1<<(n-1)); i++) {
		int v_leader = leadership[0];
		ll team_sum = 0;
		int flag = 1;
		for (int j=0; j<(n-1); j++) {
			if (!(i&(1<<j))) {
				team_sum += team_value[j+1];
				if (team_sum <= v_leader) {
					continue;
				} else {
					flag = 0;
					break;
				}				
			} else {
				team_sum = 0;
				v_leader = leadership[j+1];
				continue;
			}	
				
		}
//		if (sum == 604) {
//			for (int j=0; j<n; j++) {
//			if (i&(1<<j)) {
//				cout << j << " ";			
//			}	
//		}
		if (flag) {
			num = num % ll(1e9+7) + 1;
		}
	}
	
	cout << num % ll(1e9+7) << endl;
	return 0;
	
	
   
   
}
