class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        vector<int> dp(n, INT_MAX);
        
        int left = 0, sum = 0, ans = INT_MAX;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            while (sum > target)
                sum -= arr[left++];

            if (sum == target) {
                int len = right - left + 1;

                if (left > 0 && dp[left - 1] != INT_MAX)
                    ans = min(ans, len + dp[left - 1]);

                dp[right] = len;
            }

            if (right > 0)
                dp[right] = min(dp[right], dp[right - 1]);
        }

        return ans == INT_MAX ? -1 : ans;
    }
};