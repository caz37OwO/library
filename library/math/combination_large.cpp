#include "template/template.hpp"
vec<mint> fact,invfact,fact_large;
vec<ll> vp;
ll n0,d0,p0;
void init_fact(ll N,ll D){
  n0=N,d0=D,p0=mint::mod();
  fact.resize(D+1),invfact.resize(D+1),fact_large.resize(2*D+1),vp.resize(2*D+1);
  fact[0]=1;
  for(ll i=1;i<=D;i++) fact[i]=fact[i-1]*i;
  invfact[D]=1/fact[D];
  for(ll i=D;i>=1;i--) invfact[i-1]=invfact[i]*i;
  fact_large[D]=1,vp[D]=0;
  for(ll i=D+1;i<=2*D;i++){
    ll x=i+N-D;
    while(x%p0==0) vp[i]++,x/=p0;
    vp[i]+=vp[i-1];
    fact_large[i]=fact_large[i-1]*x;
  }
  for(ll i=D-1;i>=0;i--){
    ll x=i+1+N-D;
    if(x<=0) break;
    while(x%p0==0) vp[i]--,x/=p0;
    vp[i]+=vp[i+1];
    fact_large[i]=fact_large[i+1]/x;
  }
}
mint comb(ll n,ll k){
  if(k<0||n<k) return 0;
  if(n<=d0) return fact[n]*invfact[k]*invfact[n-k];
  ll i=n-n0+d0,j=n-k-n0+d0;
  if(vp[i]-vp[j]) return 0;
  return fact_large[i]/fact_large[j]*invfact[k];
}
mint perm(ll n,ll k){
  if(k<0||n<k) return 0;
  if(n<=d0) return fact[n]*invfact[n-k];
  ll i=n-n0+d0,j=n-k-n0+d0;
  if(vp[i]-vp[j]) return 0;
  return fact_large[i]/fact_large[j];
}