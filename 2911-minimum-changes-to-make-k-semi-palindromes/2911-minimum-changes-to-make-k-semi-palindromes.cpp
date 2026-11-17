class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        vector<vector<int>> cost(n, vector<int>(n, INF));

        for (int len = 2; len <= n; ++len) {
            for (int l = 0; l + len <= n; ++l) {
                int r = l + len - 1;
                int best = INF;

                for (int d = 1; d < len; ++d) {
                    if (len % d != 0) continue;

                    int cur = 0;
                    int m = len / d; // length of each group

                    for (int off = 0; off < d; ++off) {
                        for (int a = 0, b = m - 1; a < b; ++a, --b) {
                            char ca = s[l + off + a * d];
                            char cb = s[l + off + b * d];
                            if (ca != cb) ++cur;
                        }
                    }

                    if (cur < best) best = cur;
                }

                cost[l][r] = best;
            }
        }

        vector<int> dp(n + 1, INF), ndp(n + 1, INF);
        dp[0] = 0;

        for (int t = 1; t <= k; ++t) {
            fill(ndp.begin(), ndp.end(), INF);

            for (int i = 2 * t; i <= n; ++i) {
                int best = INF;

                for (int j = 2 * (t - 1); j <= i - 2; ++j) {
                    if (dp[j] == INF) continue;
                    if (cost[j][i - 1] == INF) continue;

                    int val = dp[j] + cost[j][i - 1];
                    if (val < best) best = val;
                }

                ndp[i] = best;
            }

            dp.swap(ndp);
        }

        return dp[n];
    }
};