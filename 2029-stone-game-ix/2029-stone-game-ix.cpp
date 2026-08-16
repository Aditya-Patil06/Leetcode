class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        int zero = cnt[0];
        int one  = cnt[1];
        int two  = cnt[2];

        // No stone changes the sum modulo 3.
        if (one == 0 && two == 0)
            return false;

        // Even number of 0-mod-3 stones:
        // Alice can win iff both 1 and 2 exist.
        if (zero % 2 == 0)
            return one > 0 && two > 0;

        // Odd number of 0-mod-3 stones:
        // Alice wins iff one remainder class exceeds the other by > 2.
        return abs(one - two) > 2;
    }
};