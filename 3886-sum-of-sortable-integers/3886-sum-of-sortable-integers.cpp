class Solution {
public:
    // Build the KMP LPS array.
    vector<int> buildLPS(const vector<int>& pattern) {
        int m = pattern.size();
        vector<int> lps(m, 0);

        for (int i = 1, len = 0; i < m; ) {
            if (pattern[i] == pattern[len]) {
                lps[i++] = ++len;
            } else if (len > 0) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }

        return lps;
    }

    // Check whether pattern is a cyclic rotation of block.
    bool isRotation(const vector<int>& nums,
                    const vector<int>& sorted,
                    int start, int k) {
        vector<int> pattern(sorted.begin() + start,
                            sorted.begin() + start + k);

        vector<int> lps = buildLPS(pattern);

        int j = 0;

        // Search in the block repeated twice, without
        // repeating the first element at the end.
        for (int i = 0; i < 2 * k - 1; i++) {
            int x = nums[start + (i % k)];

            while (j > 0 && x != pattern[j]) {
                j = lps[j - 1];
            }

            if (x == pattern[j]) {
                j++;
            }

            if (j == k) {
                return true;
            }
        }

        return false;
    }

    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());

        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) {
                continue;
            }

            bool valid = true;

            for (int start = 0; start < n; start += k) {
                if (!isRotation(nums, sorted, start, k)) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                ans += k;
            }
        }

        return ans;
    }
};