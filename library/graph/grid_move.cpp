#include "template/template.hpp"
tup2<ll> grid_move(ll h,ll w,ll k){
  if(k==0) return tup2(h+1,w);
  if(k==1) return tup2(h,w+1);
  if(k==2) return tup2(h-1,w);
  if(k==3) return tup2(h,w-1);
}
ll out(ll h,ll w,ll H,ll W){return h<0||H<=h||w<0||W<=w;}