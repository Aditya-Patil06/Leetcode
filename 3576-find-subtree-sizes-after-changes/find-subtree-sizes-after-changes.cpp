class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        // Original tree children
        vector<vector<int>> children(n);
        for (int i = 1; i < n; ++i) {
            children[parent[i]].push_back(i);
        }

        // newParent[i] = closest ancestor of i with the same character as s[i],
        // or original parent[i] if no such ancestor exists.
        vector<int> newParent(n, -1);
        int last[26];
        fill(begin(last), end(last), -1);

        vector<int> prevLast(n, -1);

        // Iterative DFS with enter/exit events to maintain last occurrence
        // of each character along the current root-to-node path.
        vector<pair<int, int>> st; // {node, state}, state 0 = enter, 1 = exit
        st.push_back({0, 0});

        while (!st.empty()) {
            auto [u, state] = st.back();
            st.pop_back();

            int c = s[u] - 'a';

            if (state == 0) {
                // Enter node u
                if (u == 0) {
                    newParent[u] = -1;
                } else {
                    newParent[u] = (last[c] == -1 ? parent[u] : last[c]);
                }

                prevLast[u] = last[c];
                last[c] = u;

                // Schedule exit after all children
                st.push_back({u, 1});
                for (int v : children[u]) {
                    st.push_back({v, 0});
                }
            } else {
                // Exit node u: restore previous last occurrence for its character
                last[c] = prevLast[u];
            }
        }

        // Build final tree
        vector<vector<int>> finalChildren(n);
        for (int i = 1; i < n; ++i) {
            finalChildren[newParent[i]].push_back(i);
        }

        // Get a traversal order of the final tree
        vector<int> order;
        order.reserve(n);

        vector<int> stack2;
        stack2.push_back(0);

        while (!stack2.empty()) {
            int u = stack2.back();
            stack2.pop_back();
            order.push_back(u);

            for (int v : finalChildren[u]) {
                stack2.push_back(v);
            }
        }

        // Compute subtree sizes bottom-up
        vector<int> sz(n, 1);
        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            if (newParent[u] != -1) {
                sz[newParent[u]] += sz[u];
            }
        }

        return sz;
    }
};