class Solution {
public:
    int maximumLengthSubstring(string s) {
        vector<int> freq(26, 0);
        int left = 0;
        int ans = 0;

        for (int right = 0; right < s.length(); right++) {
            freq[s[right] - 'a']++;

            // Shrink window if any character occurs more than twice
            while (freq[s[right] - 'a'] > 2) {
                freq[s[left] - 'a']--;
                left++;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};