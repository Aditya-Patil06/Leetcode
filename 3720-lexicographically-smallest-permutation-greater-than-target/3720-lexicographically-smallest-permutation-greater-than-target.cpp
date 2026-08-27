class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        // Frequency of characters in s
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        // Try every position from right to left as the
        // first position where answer differs from target.
        for (int i = n - 1; i >= 0; --i) {

            // Characters needed for target[0 ... i-1]
            vector<int> used(26, 0);
            bool possible = true;

            for (int j = 0; j < i; ++j) {
                int c = target[j] - 'a';
                used[c]++;

                if (used[c] > freq[c]) {
                    possible = false;
                    break;
                }
            }

            if (!possible)
                continue;

            // Characters remaining after constructing target[0 ... i-1]
            vector<int> remaining(26);

            for (int c = 0; c < 26; ++c) {
                remaining[c] = freq[c] - used[c];
            }

            int cur = target[i] - 'a';

            // Choose the smallest character strictly greater
            // than target[i].
            for (int c = cur + 1; c < 26; ++c) {
                if (remaining[c] > 0) {

                    remaining[c]--;

                    string ans = target.substr(0, i);
                    ans += char('a' + c);

                    // Put the remaining characters in sorted order.
                    for (int x = 0; x < 26; ++x) {
                        ans += string(remaining[x], char('a' + x));
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};