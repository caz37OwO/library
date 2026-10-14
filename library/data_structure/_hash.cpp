#include "template/template.hpp"
struct Hash{
  inline static ll MOD1=999990373,MOD2=1000003777;
  inline static ll BASE1=3737,BASE2=373737;
  ll v1,v2;
  tup2<ll> norm(ll a,ll b){return tup((a%MOD1+MOD1)%MOD1,(b%MOD2+MOD2)%MOD2);}
  Hash():v1(0),v2(0){}
  Hash(ll v){tie(v1,v2)=norm(v,v);}
  Hash(ll a,ll b){tie(v1,v2)=norm(a,b);}
  Hash operator+(Hash a){
    Hash r;
    tie(r.v1,r.v2)=norm(v1+a.v1,v2+a.v2);
    return r;
  }
  Hash operator-(Hash a){
    Hash r;
    tie(r.v1,r.v2)=norm(v1-a.v1,v2-a.v2);
    return r;
  }
  Hash operator*(Hash a){
    Hash r;
    tie(r.v1,r.v2)=norm(v1*a.v1,v2*a.v2);
    return r;
  }
  bool operator==(Hash a){return v1==a.v1&&v2==a.v2;}
  bool operator!=(Hash a){return v1!=a.v1||v2!=a.v2;}
  bool operator<(Hash a){return v1!=a.v1?v1<a.v1:v2<a.v2;}
  bool operator>(Hash a){return v1!=a.v1?v1>a.v1:v2>a.v2;}
  bool operator<=(Hash a){return !(*this>a);}
  bool operator>=(Hash a){return !(*this<a);}
};