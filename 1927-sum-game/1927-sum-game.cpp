class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int half = n / 2;

        int diff = 0;
        int qLeft = 0, qRight = 0;

        for (int i = 0; i < half; i++) {
            if (num[i] == '?')
                qLeft++;
            else
                diff += num[i] - '0';
        }

        for (int i = half; i < n; i++) {
            if (num[i] == '?')
                qRight++;
            else
                diff -= num[i] - '0';
        }

        // Odd number of '?' means Alice always wins.
        if ((qLeft + qRight) % 2)
            return true;

        // Bob wins only when the difference can be exactly balanced.
        return diff != 9 * (qRight - qLeft) / 2;
    }
};