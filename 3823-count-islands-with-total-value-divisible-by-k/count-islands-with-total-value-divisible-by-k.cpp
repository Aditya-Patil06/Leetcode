class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        int ans = 0;

        const int dirs[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        queue<pair<int,int>> q;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) continue;

                long long sum = 0;

                // Start a new island
                sum += grid[i][j];
                grid[i][j] = 0; // mark visited
                q.push({i, j});

                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();

                    for (auto &d : dirs) {
                        int nx = x + d[0];
                        int ny = y + d[1];

                        if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                        if (grid[nx][ny] == 0) continue;

                        sum += grid[nx][ny];
                        grid[nx][ny] = 0; // mark visited
                        q.push({nx, ny});
                    }
                }

                if (sum % k == 0) ++ans;
            }
        }

        return ans;
    }
};