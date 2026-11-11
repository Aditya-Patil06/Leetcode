class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        long long n1 = need1, n2 = need2;

        vector<long long> candidates = {
            0,
            min(n1, n2),
            n1,
            n2,
            max(n1, n2)
        };

        long long ans = LLONG_MAX;

        for (long long c : candidates) {
            long long a = max(0LL, n1 - c);
            long long b = max(0LL, n2 - c);

            long long total = c * costBoth + a * cost1 + b * cost2;
            ans = min(ans, total);
        }

        return ans;
    }
};