class Solution {
public:
    int n;
    vector<int> suffix;
    vector<vector<int>> dp;

    int solve(int i, int M) {
        // No piles left
        if (i >= n)
            return 0;

        // Already calculated
        if (dp[i][M] != -1)
            return dp[i][M];

        int best = 0;

        // Take X piles, where 1 <= X <= 2*M
        for (int X = 1; X <= 2 * M && i + X <= n; X++) {

            // Stones Alice gets if she takes these X piles
            int taken = suffix[i] - suffix[i + X];

            // Bob will play optimally and maximize his own stones.
            // Therefore Alice gets the remaining optimal amount
            // after Bob's turn.
            int next = solve(i + X, max(M, X));

            int totalRemaining = suffix[i];

            best = max(best, totalRemaining - next);
        }

        return dp[i][M] = best;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();

        // suffix[i] = total stones from i to n-1
        suffix.assign(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        // M can grow up to n.
        dp.assign(n, vector<int>(n + 1, -1));

        return solve(0, 1);
    }
};