#include "template/template.hpp"
template<typename T>
struct Compress{
  vec<T> X;
  Compress(){}
  Compress(vec<T> &A){add(A);}
  void add(vec<T> &A){for(auto v:A) add(v);}
  void add(T v){X.pb(v);}
  ll build(){
    sort(all(X)),X.erase(unique(all(X)),X.end());
    return (ll)X.size();
  }
  ll get(T v){return low(all(X),v)-X.begin();}
  T operator[](ll k){return X[k];}
};