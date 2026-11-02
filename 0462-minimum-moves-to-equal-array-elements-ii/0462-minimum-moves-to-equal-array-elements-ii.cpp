class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int median = nums[nums.size() / 2];

        long long moves = 0;
        for (int x : nums) {
            moves += abs((long long)x - median);
        }

        return (int)moves;
    }
};