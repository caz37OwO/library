#include "template/template.hpp"
struct frac{
  __int128 p,q;
  __int128 gcd128(__int128 a,__int128 b){
    a=max(a,-a),b=max(b,-b);
    while(b) tie(a,b)=tup(b,a%b);
    return a;
  }
  frac():p(0),q(1){}
  frac(ll x):p(x),q(1){}
  frac(__int128 _p,__int128 _q){
    __int128 g=gcd128(_p,_q);
    p=_p/g,q=_q/g;
    if(q<0) p*=-1,q*=-1;
  }
  frac inv(){
    frac r=*this;
    swap(r.p,r.q);
    if(r.q<0) r.p*=-1,r.q*=-1;
    return r;
  }
  frac operator+(frac a){
    if(q==0&&a.q==0) return a;
    return frac(p*a.q+q*a.p,q*a.q);
  }
  frac operator*(frac a){
    return frac(p*a.p,q*a.q);
  }
  frac operator-(){return *this*(-1);}
  frac operator-(frac a){return *this+(-a);}
  frac operator/(frac a){return *this*a.inv();}
  frac& operator+=(frac a){
    *this=*this+a;
    return *this;
  };
  frac& operator-=(frac a){
    *this=*this-a;
    return *this;
  };
  frac& operator*=(frac a){
    *this=*this*a;
    return *this;
  };
  frac& operator/=(frac a){
    *this=*this/a;
    return *this;
  };
  friend bool operator==(frac a,frac b){return a.p==b.p&&a.q==b.q;}
  friend bool operator!=(frac a,frac b){return !(a==b);}
  friend bool operator<(frac a,frac b){
    __int128 x=a.p*b.q,y=a.q*b.p;
    return x==y?a.p<b.p:x<y;
  }
  friend bool operator>(frac a,frac b){return a<b;}
  friend bool operator<=(frac a,frac b){return !(a<b);}
  friend bool operator>=(frac a,frac b){return !(b<a);}
};