#include "template/template.hpp"
tup3<ll> extgcd(ll A,ll B){
  ll x,y,g;
  auto dfs=[&](this auto dfs,ll a,ll b)->void{
    if(!b){
      x=1,y=0,g=a;
      return;
    }
    dfs(b,a%b);
    swap(x,y);
    y-=a/b*x;
  };
  dfs(A,B);
  if(g<0) x*=-1,y*=-1,g*=-1;
  return tup(x,y,g);
}

//Ax+By=|gcd(A,B)|