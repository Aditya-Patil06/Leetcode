class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1000000007;
        int m = grid.size(), n = grid[0].size();
        if (m == 1 && n == 1) return 1;

        // dp[x][y] = ways to be standing on the 0-cell (x,y) (start counts as a 0-cell)
        vector<vector<long long>> dp(m, vector<long long>(n, 0));
        dp[0][0] = 1;

        long long answer = 0;

        auto traverse = [&](int cx, int cy, int dir_in, long long ways) {
            while (cx < m && cy < n) {
                if (cx == m - 1 && cy == n - 1) {         // reached the goal
                    answer = (answer + ways) % MOD;
                    return;
                }
                if (grid[cx][cy] == 0) {                  // free cell -> land
                    dp[cx][cy] = (dp[cx][cy] + ways) % MOD;
                    return;
                }
                // mirror: flip and step
                int dir_out = 1 - dir_in;
                if (dir_out == 0) ++cy; else ++cx;
                dir_in = dir_out;
            }
            // fell off the grid -> this path dies
        };

        // Process cells in order of increasing x+y (every step increases x+y by 1).
        for (int s = 0; s <= m + n - 2; ++s) {
            for (int x = 0; x < m; ++x) {
                int y = s - x;
                if (y < 0 || y >= n) continue;

                long long ways = dp[x][y];
                if (ways == 0) continue;

                if (y + 1 < n) traverse(x, y + 1, 0, ways);  // start a right leg
                if (x + 1 < m) traverse(x + 1, y, 1, ways);  // start a down leg
            }
        }

        return (int)answer;
    }
};