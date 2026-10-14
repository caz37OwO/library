#include "template/template.hpp"
vec<mint> fact,invfact,inv;
void init_fact(ll N){
  fact.resize(N+1),invfact.resize(N+1),inv.resize(N+1);
  fact[0]=1;
  for(ll i=1;i<=N;i++) fact[i]=fact[i-1]*i;
  invfact[N]=1/fact[N];
  for(ll i=N;i>=1;i--) invfact[i-1]=invfact[i]*i;
  for(ll i=1;i<=N;i++) inv[i]=fact[i-1]*invfact[i];
}
mint comb(ll n,ll k){
  if(k<0&&k<=n) return comb(n,n-k);
  if(n<0&&0<=k) return (k%2?-comb(-n+k-1,k):comb(-n+k-1,k));
  if(k<0||n<k) return 0;
  return fact[n]*invfact[k]*invfact[n-k];
}
mint perm(ll n,ll k){
  if(n<0&&0<=k) return (k%2?-perm(-n+k-1,k):perm(-n+k-1,k));
  if(k<0||n<k) return 0;
  return fact[n]*invfact[n-k];
}