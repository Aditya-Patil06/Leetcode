class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int p = find(nums.begin(), nums.end(), 0) - nums.begin();
        if (p == n) return -1; // 0 not found, invalid for a permutation

        auto check = [&](int shift, bool reversed) -> bool {
            for (int i = 0; i < n; ++i) {
                int idx = (shift + i) % n;
                int val = reversed ? nums[n - 1 - idx] : nums[idx];
                if (val != i) return false;
            }
            return true;
        };

        int ans = INT_MAX;

        // Even number of reversals: 0 or 2.
        if (check(p, false)) {
            ans = min(ans, min(p, n - p + 2));
        }

        // Odd number of reversals: 1, 3, ...
        int q = n - 1 - p; // index of 0 after reversing nums
        if (check(q, true)) {
            ans = min(ans, 1 + min(q, n - q));
        }

        return ans == INT_MAX ? -1 : ans;
    }
};