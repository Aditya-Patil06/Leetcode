
class Solution {
public:
    int minRotations(string s) {
        int total = 0;
        int current = 0;

        for (char c : s) {
            int digit = c - '0';
            int diff = abs(digit - current);

            total += min(diff, 10 - diff);
            current = digit;
        }

        return total;
    }
};
