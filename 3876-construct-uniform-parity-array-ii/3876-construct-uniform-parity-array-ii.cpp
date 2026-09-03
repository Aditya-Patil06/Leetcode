class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int minOdd = INT_MAX;
        int minEven = INT_MAX;

        for (int x : nums1) {
            if (x % 2 == 1)
                minOdd = min(minOdd, x);
            else
                minEven = min(minEven, x);
        }

        // All numbers are already even.
        if (minOdd == INT_MAX)
            return true;

        // To make everything odd, every even number
        // needs a smaller odd number to subtract.
        return minOdd < minEven;
    }
};