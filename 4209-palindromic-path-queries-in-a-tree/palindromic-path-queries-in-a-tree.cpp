class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        // ---------- Build adjacency ----------
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // ---------- Heavy-Light Decomposition ----------
        vector<int> parent(n, -1), depth(n, 0), sz(n, 1), heavy(n, -1);
        vector<int> head(n), pos(n);

        vector<int> order;
        order.reserve(n);
        order.push_back(0);

        for (int i = 0; i < (int)order.size(); ++i) {
            int u = order[i];
            for (int v : adj[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                order.push_back(v);
            }
        }

        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            sz[u] = 1;
            int bestSize = 0;
            for (int v : adj[u]) {
                if (parent[v] != u) continue;
                sz[u] += sz[v];
                if (sz[v] > bestSize) {
                    bestSize = sz[v];
                    heavy[u] = v;
                }
            }
        }

        int timer = 0;
        vector<pair<int,int>> st;
        st.push_back({0, 0});

        while (!st.empty()) {
            auto [start, h] = st.back();
            st.pop_back();

            int u = start;
            while (u != -1) {
                head[u] = h;
                pos[u] = timer++;

                for (int v : adj[u]) {
                    if (parent[v] == u && v != heavy[u]) {
                        st.push_back({v, v});
                    }
                }

                u = heavy[u];
            }
        }

        // ---------- Fenwick tree for XOR ----------
        struct BIT {
            int n;
            vector<int> bit;
            BIT(int n) : n(n), bit(n + 1, 0) {}

            void add(int idx, int val) {
                for (++idx; idx <= n; idx += idx & -idx)
                    bit[idx] ^= val;
            }

            int prefixXor(int idx) {
                int res = 0;
                for (++idx; idx > 0; idx -= idx & -idx)
                    res ^= bit[idx];
                return res;
            }

            int rangeXor(int l, int r) {
                if (l > r) swap(l, r);
                int res = prefixXor(r);
                if (l > 0) res ^= prefixXor(l - 1);
                return res;
            }
        };

        BIT bit(n);
        vector<int> nodeMask(n);

        for (int i = 0; i < n; ++i) {
            nodeMask[i] = 1 << (s[i] - 'a');
            bit.add(pos[i], nodeMask[i]);
        }

        auto pathXor = [&](int u, int v) -> int {
            int res = 0;

            while (head[u] != head[v]) {
                if (depth[head[u]] < depth[head[v]]) swap(u, v);

                res ^= bit.rangeXor(pos[head[u]], pos[u]);
                u = parent[head[u]];
            }

            if (depth[u] > depth[v]) swap(u, v);
            res ^= bit.rangeXor(pos[u], pos[v]);

            return res;
        };

        vector<bool> answer;

        for (const string& query : queries) {
            if (query[0] == 'u') {
                int u = 0, i = 7;
                while (query[i] != ' ') {
                    u = u * 10 + (query[i] - '0');
                    ++i;
                }
                char c = query[i + 1];

                int newMask = 1 << (c - 'a');
                int delta = nodeMask[u] ^ newMask;

                nodeMask[u] = newMask;
                bit.add(pos[u], delta);
            } else {
                int u = 0, v = 0, i = 6;
                while (query[i] != ' ') {
                    u = u * 10 + (query[i] - '0');
                    ++i;
                }
                ++i;
                while (i < (int)query.size()) {
                    v = v * 10 + (query[i] - '0');
                    ++i;
                }

                int mask = pathXor(u, v);
                answer.push_back(__builtin_popcount(mask) <= 1);
            }
        }

        return answer;
    }
};