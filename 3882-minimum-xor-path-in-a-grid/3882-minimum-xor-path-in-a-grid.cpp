class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int total = m * n;

        vector<bitset<1024>> dp(total);

        auto id = [&](int i, int j) {
            return i * n + j;
        };

        // Start cell
        dp[0].set(grid[0][0]);

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue;

                int curId = id(i, j);
                int val = grid[i][j];
                auto& cur = dp[curId];

                if (i > 0) {
                    auto& up = dp[id(i - 1, j)];
                    for (int x = 0; x < 1024; ++x) {
                        if (up.test(x)) {
                            cur.set(x ^ val);
                        }
                    }
                }

                if (j > 0) {
                    auto& left = dp[id(i, j - 1)];
                    for (int x = 0; x < 1024; ++x) {
                        if (left.test(x)) {
                            cur.set(x ^ val);
                        }
                    }
                }
            }
        }

        auto& res = dp[id(m - 1, n - 1)];
        for (int x = 0; x < 1024; ++x) {
            if (res.test(x)) return x;
        }

        return -1;
    }
};