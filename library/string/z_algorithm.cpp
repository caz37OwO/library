#include "template/template.hpp"
template<class Iterator>
vec<ll> z_algorithm(Iterator l, Iterator r){
  ll N=distance(l,r);
  vec<ll> res(N);
  res[0]=N;
  ll i=1,j=0;
  while(i<N){
    while(i+j<N&&l[j]==l[i+j]) j++;
    res[i]=j;
    ll k=1;
    while(i+k<N&&k+res[k]<j) res[i+k]=res[k],k++;
    i+=k,j=max(0LL,j-k);
  }
  return res;
}