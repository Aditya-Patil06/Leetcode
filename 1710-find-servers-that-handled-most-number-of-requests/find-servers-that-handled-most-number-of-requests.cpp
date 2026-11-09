class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        // Available servers, ordered by index.
        set<int> free;
        for (int i = 0; i < k; ++i) free.insert(i);

        // Busy servers: (finishTime, serverIndex)
        priority_queue<pair<long long,int>,
                       vector<pair<long long,int>>,
                       greater<pair<long long,int>>> busy;

        vector<int> count(k, 0);
        int n = arrival.size();

        for (int i = 0; i < n; ++i) {
            long long t = arrival[i];

            // Release all servers that finish at or before this arrival.
            while (!busy.empty() && busy.top().first <= t) {
                free.insert(busy.top().second);
                busy.pop();
            }

            if (free.empty()) continue; // request dropped

            int start = i % k;
            auto it = free.lower_bound(start);
            if (it == free.end()) it = free.begin();

            int server = *it;
            free.erase(it);

            ++count[server];
            busy.push({t + load[i], server});
        }

        int best = *max_element(count.begin(), count.end());

        vector<int> ans;
        for (int i = 0; i < k; ++i) {
            if (count[i] == best) ans.push_back(i);
        }
        return ans;
    }
};