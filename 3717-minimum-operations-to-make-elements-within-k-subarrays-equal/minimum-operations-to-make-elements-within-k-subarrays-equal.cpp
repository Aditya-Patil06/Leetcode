class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        // ---------- Coordinate compression ----------
        vector<long long> sorted(nums.begin(), nums.end());
        sort(sorted.begin(), sorted.end());
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
        int m = sorted.size();

        auto getPos = [&](long long v) {
            return (int)(lower_bound(sorted.begin(), sorted.end(), v) - sorted.begin()) + 1;
        };

        // ---------- Fenwick trees: counts and sums ----------
        vector<long long> cnt(m + 1, 0), sm(m + 1, 0);
        int needed = (x + 1) / 2;
        long long totalSum = 0;

        auto add = [&](long long v) {
            totalSum += v;
            for (int j = getPos(v); j <= m; j += j & -j) {
                cnt[j] += 1;
                sm[j]  += v;
            }
        };

        auto remove = [&](long long v) {
            totalSum -= v;
            for (int j = getPos(v); j <= m; j += j & -j) {
                cnt[j] -= 1;
                sm[j]  -= v;
            }
        };

        vector<long long> cost(n - x + 1, 0);

        for (int i = 0; i < n; ++i) {
            add(nums[i]);
            if (i >= x) remove(nums[i - x]);

            if (i >= x - 1) {
                // find smallest position with prefix count >= needed
                int pos = 0;
                long long acc = 0;
                for (int step = 1 << 20; step > 0; step >>= 1) {
                    int next = pos + step;
                    if (next <= m && acc + cnt[next] < needed) {
                        pos = next;
                        acc += cnt[next];
                    }
                }
                int medPos = pos + 1;
                long long med = sorted[medPos - 1];

                long long countLE = 0, sumLE = 0;
                for (int j = medPos; j > 0; j -= j & -j) {
                    countLE += cnt[j];
                    sumLE   += sm[j];
                }

                cost[i - x + 1] = med * countLE - sumLE
                                + (totalSum - sumLE) - med * (x - countLE);
            }
        }

        // ---------- DP: choose exactly k non-overlapping windows ----------
        const long long INF = 4e18;
        vector<long long> prev(n + 1, 0), cur(n + 1, INF);

        for (int j = 1; j <= k; ++j) {
            fill(cur.begin(), cur.end(), INF);
            cur[0] = INF;

            for (int i = 1; i <= n; ++i) {
                cur[i] = cur[i - 1];
                if (i >= x) {
                    long long cand = prev[i - x] + cost[i - x];
                    if (cand < cur[i]) cur[i] = cand;
                }
            }

            swap(prev, cur);
        }

        return prev[n];
    }
};