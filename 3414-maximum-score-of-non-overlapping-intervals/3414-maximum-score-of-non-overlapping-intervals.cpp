class Solution {
public:
    struct Node {
        long long score = 0;
        vector<int> id;
    };

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<long long, 3>> a(n);

        for (int i = 0; i < n; i++)
            a[i] = {intervals[i][0], intervals[i][1], i};

        sort(a.begin(), a.end());

        // next[i] = first interval whose start > a[i].right
        vector<int> next(n);

        for (int i = 0; i < n; i++) {
            next[i] = lower_bound(
                a.begin(), a.end(), a[i][1] + 1,
                [](const auto &x, long long val) {
                    return x[0] < val;
                }
            ) - a.begin();
        }

        vector<vector<Node>> dp(5, vector<Node>(n + 1));

        for (int i = n - 1; i >= 0; i--) {
            for (int k = 1; k <= 4; k++) {

                // Don't take this interval
                dp[k][i] = dp[k][i + 1];

                // Take this interval
                Node take = dp[k - 1][next[i]];

                take.score += intervals[a[i][2]][2];
                take.id.push_back(a[i][2]);

                sort(take.id.begin(), take.id.end());

                // Maximum score first, lexicographically smallest on tie
                if (take.score > dp[k][i].score ||
                    (take.score == dp[k][i].score &&
                     take.id < dp[k][i].id)) {

                    dp[k][i] = take;
                }
            }
        }

        return dp[4][0].id;
    }
};