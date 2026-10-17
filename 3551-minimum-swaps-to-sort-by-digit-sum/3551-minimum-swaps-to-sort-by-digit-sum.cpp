class Solution {
public:
    int digitSum(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }

    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> v;

        for (int i = 0; i < n; i++)
            v.push_back({digitSum(nums[i]), nums[i]});

        sort(v.begin(), v.end());

        unordered_map<int, int> pos;
        for (int i = 0; i < n; i++)
            pos[nums[i]] = i;

        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (nums[i] == v[i].second)
                continue;

            int j = pos[v[i].second];

            pos[nums[i]] = j;
            pos[nums[j]] = i;

            swap(nums[i], nums[j]);
            swaps++;
        }

        return swaps;
    }
};