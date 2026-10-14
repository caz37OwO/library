#include "template/template.hpp"
vec2<ll> matrix_prod(vec2<ll> &A,vec2<ll> &B,ll M){
  ll I=(ll)A.size(),J=(ll)B.size(),K=(ll)B[0].size();
  vec2<ll> res(I,vec<ll>(K));
  for(ll i=0;i<I;i++){
    for(ll j=0;j<J;j++){
      for(ll k=0;k<K;k++) res[i][k]=(res[i][k]+A[i][j]*B[j][k])%M;
    }
  }
  return res;
}
vec2<ll> matrix_prod(vec2<ll> &A,ll V,ll M){
  ll I=(ll)A.size(),J=(ll)A[0].size();
  vec2<ll> res(I,vec<ll>(J));
  for(ll i=0;i<I;i++){
    for(ll j=0;j<J;j++) res[i][j]=((A[i][j]*V)%M+M)%M;
  }
  return res;
}
vec2<ll> matrix_add(vec2<ll> &A,vec2<ll> &B,ll M){
  ll I=(ll)A.size(),J=(ll)A[0].size();
  vec2<ll> res(I,vec<ll>(J));
  for(ll i=0;i<I;i++){
    for(ll j=0;j<J;j++) res[i][j]=(A[i][j]+B[i][j])%M;
  }
  return res;
}