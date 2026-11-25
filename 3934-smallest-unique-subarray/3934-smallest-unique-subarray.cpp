class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        struct State {
            int len, link, cnt;
            unordered_map<int, int> next;
        };

        vector<State> st(2 * n + 5);
        int sz = 1, last = 0;

        st[0].len = 0;
        st[0].link = -1;
        st[0].cnt = 0;

        // Build suffix automaton
        for (int x : nums) {
            int cur = sz++;
            st[cur].len = st[last].len + 1;
            st[cur].cnt = 1;
            st[cur].link = 0;
            st[cur].next.clear();

            int p = last;

            while (p != -1 && !st[p].next.count(x)) {
                st[p].next[x] = cur;
                p = st[p].link;
            }

            if (p == -1) {
                st[cur].link = 0;
            } else {
                int q = st[p].next[x];

                if (st[p].len + 1 == st[q].len) {
                    st[cur].link = q;
                } else {
                    int clone = sz++;
                    st[clone].len = st[p].len + 1;
                    st[clone].link = st[q].link;
                    st[clone].cnt = 0;
                    st[clone].next = st[q].next;

                    while (p != -1 && st[p].next[x] == q) {
                        st[p].next[x] = clone;
                        p = st[p].link;
                    }

                    st[q].link = st[cur].link = clone;
                }
            }

            last = cur;
        }

        // Counting sort states by len (ascending)
        vector<int> bucket(n + 1, 0);
        for (int i = 0; i < sz; ++i) {
            ++bucket[st[i].len];
        }
        for (int i = 1; i <= n; ++i) {
            bucket[i] += bucket[i - 1];
        }

        vector<int> order(sz);
        for (int i = sz - 1; i >= 0; --i) {
            order[--bucket[st[i].len]] = i;
        }

        // Propagate occurrence counts through suffix links
        for (int i = sz - 1; i > 0; --i) {
            int v = order[i];
            if (st[v].link != -1) {
                st[st[v].link].cnt += st[v].cnt;
            }
        }

        // Find the shortest substring that occurs exactly once
        int ans = n;
        for (int i = 1; i < sz; ++i) {
            if (st[i].cnt == 1) {
                ans = min(ans, st[st[i].link].len + 1);
            }
        }

        return ans;
    }
};