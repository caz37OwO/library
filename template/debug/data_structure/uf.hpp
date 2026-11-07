template<class T>
concept DebugUnionFind = requires(T& x, long long i) {
  x.par;
  x.root(i);
};

template<DebugUnionFind T>
void debug_print(T& uf) {
  vector<vector<long long>> groups(uf.par.size());

  for (long long i = 0; i < (long long)uf.par.size(); i++) {
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
