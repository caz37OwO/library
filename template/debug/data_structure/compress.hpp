template<class T>
concept DebugCompress = requires(T& x, ll i) {
  x.X;
  x.get(x.X[i]);
  x[i];
};

template<DebugCompress T>
void debug_print(T& x) {
  cerr << "[";

  for (ll i = 0; i < (ll)x.X.size(); i++) {
    if (i) cerr << ", ";
    cerr << "(" << i << ", ";
    debug_print(x[i]);
    cerr << ")";
  }

  cerr << "]";
}
