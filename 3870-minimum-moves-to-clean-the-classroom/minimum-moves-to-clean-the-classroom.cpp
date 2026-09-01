class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr, sc;
        vector<vector<int>> id(m, vector<int>(n, -1));

        int k = 0;

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (classroom[r][c] == 'S') {
                    sr = r;
                    sc = c;
                }
                else if (classroom[r][c] == 'L') {
                    id[r][c] = k++;
                }
            }
        }

        int fullMask = (1 << k) - 1;

        if (k == 0)
            return 0;

        /*
         * best[state] = maximum remaining energy with which
         * we have already reached this (r,c,mask).
         *
         * Since BFS guarantees that states are processed in
         * increasing distance, a state with <= energy is dominated.
         */
        int totalStates = m * n * (1 << k);

        vector<int8_t> best(totalStates, -1);

        auto index = [&](int r, int c, int mask) {
            return ((r * n + c) << k) | mask;
        };

        struct Node {
            short pos;
            short energy;
            short mask;
        };

        queue<Node> q;

        int startIdx = index(sr, sc, 0);
        best[startIdx] = energy;

        // Store distance level-by-level instead of inside every node.
        q.push({(short)(sr * n + sc), (short)energy, 0});

        int dist = 0;

        const int dr[4] = {1, -1, 0, 0};
        const int dc[4] = {0, 0, 1, -1};

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                Node cur = q.front();
                q.pop();

                int pos = cur.pos;
                int r = pos / n;
                int c = pos % n;

                int e = cur.energy;
                int mask = cur.mask;

                if (mask == fullMask)
                    return dist;

                // No energy means we cannot make another move.
                if (e == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    if (classroom[nr][nc] == 'X')
                        continue;

                    int ne = e - 1;
                    int nmask = mask;

                    char cell = classroom[nr][nc];

                    // Collect litter.
                    if (cell == 'L') {
                        nmask |= (1 << id[nr][nc]);
                    }

                    // Reset energy after entering R.
                    if (cell == 'R') {
                        ne = energy;
                    }

                    int idx = index(nr, nc, nmask);

                    // Dominated if we've already reached this state
                    // with at least as much energy.
                    if (best[idx] >= ne)
                        continue;

                    best[idx] = ne;

                    q.push({
                        (short)(nr * n + nc),
                        (short)ne,
                        (short)nmask
                    });
                }
            }

            dist++;
        }

        return -1;
    }
};