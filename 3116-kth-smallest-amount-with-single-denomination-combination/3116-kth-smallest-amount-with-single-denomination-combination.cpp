#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using ll = long long;

    ll gcdll(ll a, ll b) {
        return std::gcd(a, b);
    }

    ll lcm(ll a, ll b) {
        return a / gcdll(a, b) * b;
    }

    ll count(ll x, const vector<ll>& coins) {
        int n = coins.size();
        ll total = 0;

        // Inclusion-exclusion over all subsets
        for (int mask = 1; mask < (1 << n); mask++) {
            ll common = 1;
            int bits = 0;
            bool valid = true;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    bits++;

                    common = lcm(common, coins[i]);

                    if (common > x) {
                        valid = false;
                        break;
                    }
                }
            }

            if (!valid)
                continue;

            if (bits % 2 == 1)
                total += x / common;
            else
                total -= x / common;
        }

        return total;
    }

    long long findKthSmallest(vector<int>& coins, long long k) {
        // Remove redundant coins.
        // If a coin is a multiple of a smaller coin,
        // it doesn't generate any new amounts.
        sort(coins.begin(), coins.end());

        vector<ll> useful;

        for (ll c : coins) {
            bool redundant = false;

            for (ll x : useful) {
                if (c % x == 0) {
                    redundant = true;
                    break;
                }
            }

            if (!redundant)
                useful.push_back(c);
        }

        // Binary search for the answer.
        ll lo = 1;
        ll hi = useful[0] * k;

        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;

            if (count(mid, useful) >= k)
                hi = mid;
            else
                lo = mid + 1;
        }

        return lo;
    }
};