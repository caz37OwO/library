#include "template/template.hpp"
vec<ll> factor;
void init_factor(ll N){//最小約数
  factor.resize(N+1);
	for(ll i=2;i<=N;i++){
		if(factor[i]) continue;
		factor[i]=i;
		for(ll j=i;i*j<=N;j++) if(!factor[i*j]) factor[i*j]=i;
	}
}
vec<ll> get_prime(ll N){//素数列挙
  vec res;
  for(ll i=2;i<=N;i++) if(factor[i]==i) res.pb(i);
  return res;
}
vec<tup2<ll>> pfactor(ll N){//素因数分解
  vec<tup2<ll>> res;
  ll e=N;
  while(e!=1){
    ll f=factor[e],c=0;
    while(e%f==0) e/=f,c++;
    res.pb(tup(f,c));
  }
  return res;
}
vec<ll> get_div(ll N){//約数列挙
  vec<ll> res(1,1);
  vec<tup2<ll>> pfact=pfactor(N);
  for(auto [f,c]:pfact){
    ll sz=(ll)res.size();
    for(ll i=0;i<sz*c;i++) res.pb(res[i]*f);
  }
  sort(all(res));
  return res;
}