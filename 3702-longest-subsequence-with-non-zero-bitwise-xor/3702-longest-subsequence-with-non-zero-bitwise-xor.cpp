class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int x = 0;
        bool hasNonZero = false;

        for (int num : nums) {
            x ^= num;
            if (num != 0)
                hasNonZero = true;
        }

        if (x != 0)
            return nums.size();

        return hasNonZero ? nums.size() - 1 : 0;
    }
};