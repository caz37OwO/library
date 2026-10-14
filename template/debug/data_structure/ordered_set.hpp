template<class T>
concept DebugOrderedSetLike = requires(T& x, ll i) {
  x.size();
  x.kth(i);
};

template<DebugOrderedSetLike T>
void debug_print(T& x) {
  cerr << "[";

  for (ll i = 0; i < x.size(); i++) {
    if (i) cerr << ", ";
    debug_print(x.kth(i));
  }

  cerr << "]";
}
