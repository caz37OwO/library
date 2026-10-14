template<class T>
concept DebugUnionFind = requires(T& x, ll i) {
  x.par;
  x.root(i);
};

template<DebugUnionFind T>
void debug_print(T& uf) {
  vector<vector<ll>> groups(uf.par.size());

  for (ll i = 0; i < (ll)uf.par.size(); i++) {
    groups[uf.root(i)].push_back(i);
  }

  cerr << "[";

  bool first_group = true;

  for (const auto& group : groups) {
    if (group.empty()) continue;

    if (!first_group) cerr << ", ";
    first_group = false;

    debug_print(group);
  }

  cerr << "]";
}
