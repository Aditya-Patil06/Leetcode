class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();

        if (grid[0][0] == ')' || grid[m-1][n-1] == '(')
            return false;

        vector<vector<set<int>>> dp(m, vector<set<int>>(n));

        dp[0][0].insert(1);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0) continue;

                int change = grid[i][j] == '(' ? 1 : -1;

                if (i > 0) {
                    for (int b : dp[i-1][j])
                        if (b + change >= 0)
                            dp[i][j].insert(b + change);
                }

                if (j > 0) {
                    for (int b : dp[i][j-1])
                        if (b + change >= 0)
                            dp[i][j].insert(b + change);
                }
            }
        }

        return dp[m-1][n-1].count(0);
    }
};