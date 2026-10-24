class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice,
                          string arriveBob, string leaveBob) {
        vector<int> days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // Prefix sum: prefix[m - 1] = number of days before month m
        vector<int> prefix(13, 0);
        for (int i = 1; i <= 12; ++i) {
            prefix[i] = prefix[i - 1] + days[i - 1];
        }

        auto toDay = [&](const string& date) -> int {
            int month = stoi(date.substr(0, 2));
            int day = stoi(date.substr(3, 2));
            return prefix[month - 1] + day;
        };

        int aliceStart = toDay(arriveAlice);
        int aliceEnd = toDay(leaveAlice);
        int bobStart = toDay(arriveBob);
        int bobEnd = toDay(leaveBob);

        int overlapStart = max(aliceStart, bobStart);
        int overlapEnd = min(aliceEnd, bobEnd);

        return max(0, overlapEnd - overlapStart + 1);
    }
};