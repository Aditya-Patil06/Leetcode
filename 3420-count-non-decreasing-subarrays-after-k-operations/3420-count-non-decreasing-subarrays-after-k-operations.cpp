class Solution {
    int n;
    vector<int> a;
    long long k;
    vector<long long> rMax, prefRMax, prefA_R, stkVal;
    vector<int> stkCnt;

    long long solve(int L, int R) {
        if (L >= R) return (L == R) ? 1 : 0;
        int mid = (L + R) / 2;
        long long ans = solve(L, mid) + solve(mid + 1, R);

        int nR = R - mid;
        rMax[0] = 0; prefRMax[0] = 0; prefA_R[0] = 0;
        long long curMax = 0;
        for (int i = mid + 1; i <= R; i++) {
            if ((long long)a[i] > curMax) curMax = a[i];
            int idx = i - (mid + 1);
            rMax[idx] = curMax;
            prefRMax[idx + 1] = prefRMax[idx] + curMax;
            prefA_R[idx + 1] = prefA_R[idx] + a[i];
        }

        int top = -1;
        long long totalMaxSum = 0;
        long long leftMax = 0;
        int p = 0;
        int rPtr = nR - 1;
        long long sumA_left = 0;

        for (int l = mid; l >= L; --l) {
            long long v = a[l];
            if (v > leftMax) leftMax = v;
            sumA_left += v;

            int cnt = 1;
            long long poppedSum = 0;
            while (top >= 0 && stkVal[top] <= v) {
                cnt += stkCnt[top];
                poppedSum += stkVal[top] * stkCnt[top];
                --top;
            }
            totalMaxSum = totalMaxSum - poppedSum + v * cnt;
            ++top;
            stkVal[top] = v;
            stkCnt[top] = cnt;

            long long costL = totalMaxSum - sumA_left;

            while (p < nR && rMax[p] <= leftMax) ++p;

            while (rPtr >= 0) {
                long long S;
                if (rPtr < p) {
                    long long count = rPtr + 1;
                    S = leftMax * count - prefA_R[count];
                } else {
                    S = leftMax * p + (prefRMax[rPtr + 1] - prefRMax[p]) - prefA_R[rPtr + 1];
                }
                if (costL + S <= k) break;
                --rPtr;
            }
            if (rPtr < 0) break;
            ans += (rPtr + 1);
        }
        return ans;
    }

public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        n = nums.size();
        a = nums;
        this->k = k;
        rMax.assign(n + 1, 0);
        prefRMax.assign(n + 1, 0);
        prefA_R.assign(n + 1, 0);
        stkVal.assign(n + 1, 0);
        stkCnt.assign(n + 1, 0);
        return solve(0, n - 1);
    }
};