class Solution {
public:
    const long long MOD = 1e9 + 7;

    long long power(long long a, long long b) {
        long long r = 1;
        while (b) {
            if (b & 1) r = r * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return r;
    }

    int numberOfSets(int n, int k) {
        int N = n + k - 1;
        vector<long long> fact(N + 1, 1);

        for (int i = 1; i <= N; i++)
            fact[i] = fact[i - 1] * i % MOD;

        long long ans = fact[N];
        ans = ans * power(fact[2 * k], MOD - 2) % MOD;
        ans = ans * power(fact[N - 2 * k], MOD - 2) % MOD;

        return ans;
    }
};