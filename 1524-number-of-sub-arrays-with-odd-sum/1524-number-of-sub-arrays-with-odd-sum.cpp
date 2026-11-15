class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1e9 + 7;

        long long even = 1, odd = 0;
        long long ans = 0;
        int parity = 0; // current prefix sum parity: 0 even, 1 odd

        for (int x : arr) {
            if (x & 1) parity ^= 1;

            if (parity == 1) {
                ans = (ans + even) % MOD;
                ++odd;
            } else {
                ans = (ans + odd) % MOD;
                ++even;
            }
        }

        return (int)ans;
    }
};