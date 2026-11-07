template<class T>
concept DebugCompress = requires(T& x, long long i) {
  x.X;
  x.get(x.X[i]);
  x[i];
};

template<DebugCompress T>
void debug_print(T& x) {
  cerr << "[";

  for (long long i = 0; i < (long long)x.X.size(); i++) {
    if (i) cerr << ", ";
    cerr << "(" << i << ", ";
    debug_print(x[i]);
    cerr << ")";
  }

  cerr << "]";
}
