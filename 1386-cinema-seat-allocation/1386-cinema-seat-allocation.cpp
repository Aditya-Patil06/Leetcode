class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, unordered_set<int>> rows;

        for (auto& seat : reservedSeats) {
            rows[seat[0]].insert(seat[1]);
        }

        // Rows with no reservations can always fit 2 groups.
        int ans = (n - rows.size()) * 2;

        for (auto& [row, reserved] : rows) {
            bool left = true;    // seats 2-5
            bool middle = true;  // seats 4-7
            bool right = true;   // seats 6-9

            for (int seat = 2; seat <= 5; ++seat)
                if (reserved.count(seat))
                    left = false;

            for (int seat = 4; seat <= 7; ++seat)
                if (reserved.count(seat))
                    middle = false;

            for (int seat = 6; seat <= 9; ++seat)
                if (reserved.count(seat))
                    right = false;

            if (left && right)
                ans += 2;
            else if (left || middle || right)
                ans += 1;
        }

        return ans;
    }
};