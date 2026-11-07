#include "template/template.hpp"
void mo(vec<ll> &A,vec<ll> &B,auto addA,auto delA,auto addB,auto delB,auto ans){
  ll Q=(ll)A.size(),block=512,curA=0,curB=0;
  vec ord(Q);
  iota(all(ord),0);
  sort(all(ord),[&](ll x,ll y){
    auto key=[&](ll q){
      ll u=A[q]/block,v=B[q];
      if(u&1) v*=-1;
      return tup(u,v);
    };
    return key(x)<key(y);
  });
  for(ll q=0;q<Q;q++){
    ll qid=ord[q],qa=A[qid],qb=B[qid];
    while(curA<qa) addA(curA,curB),curA++;
    while(curA>qa) delA(curA,curB),curA--;
    while(curB<qb) addB(curA,curB),curB++;
    while(curB>qb) delB(curA,curB),curB--;
    ans(qid);
  }
};