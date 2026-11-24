class Solution {
public:
    int maxLength(vector<int>& nums) {
        const int primes[4] = {2, 3, 5, 7};
        int n = nums.size();
        int ans = 0;

        for (int l = 0; l < n; ++l) {
            int sum[4] = {0, 0, 0, 0};
            int mn[4]  = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};
            int mx[4]  = {0, 0, 0, 0};

            for (int r = l; r < n; ++r) {
                int x = nums[r];
                int e[4] = {0, 0, 0, 0};

                for (int p = 0; p < 4; ++p) {
                    while (x % primes[p] == 0) {
                        x /= primes[p];
                        ++e[p];
                    }
                }

                bool ok = true;

                for (int p = 0; p < 4; ++p) {
                    sum[p] += e[p];
                    mn[p] = min(mn[p], e[p]);
                    mx[p] = max(mx[p], e[p]);

                    if (sum[p] != mn[p] + mx[p]) {
                        ok = false;
                    }
                }

                if (ok) {
                    ans = max(ans, r - l + 1);
                }
            }
        }

        return ans;
    }
};