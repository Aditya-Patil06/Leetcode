class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        struct Fenwick {
            int n;
            vector<int> bit;
            Fenwick(int n) : n(n), bit(n + 1, 0) {}

            void add(int t, int delta) {
                for (int i = t + 1; i <= n; i += i & -i)
                    bit[i] += delta;
            }

            int prefix(int t) {
                if (t < 0) return 0;
                int s = 0;
                for (int i = t + 1; i > 0; i -= i & -i)
                    s += bit[i];
                return s;
            }
        };

        sort(logs.begin(), logs.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });

        int m = queries.size();
        vector<int> idx(m);
        iota(idx.begin(), idx.end(), 0);

        sort(idx.begin(), idx.end(), [&](int a, int b) {
            return queries[a] < queries[b];
        });

        int maxT = 0;
        for (auto& l : logs) maxT = max(maxT, l[1]);
        for (int q : queries) maxT = max(maxT, q);

        Fenwick bit(maxT + 2);

        // Initially all servers have latest = 0 (no request yet).
        bit.add(0, n);

        vector<int> latest(n + 1, 0);
        vector<int> ans(m);

        int p = 0;
        for (int qi : idx) {
            int q = queries[qi];

            while (p < (int)logs.size() && logs[p][1] <= q) {
                int id = logs[p][0];
                int t  = logs[p][1];

                if (latest[id] != t) {
                    bit.add(latest[id], -1);
                    bit.add(t, 1);
                    latest[id] = t;
                }
                ++p;
            }

            int L = q - x;
            ans[qi] = bit.prefix(L - 1);
        }

        return ans;
    }
};