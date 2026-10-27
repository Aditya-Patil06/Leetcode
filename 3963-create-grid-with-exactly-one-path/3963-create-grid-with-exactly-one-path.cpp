class Solution {
public:
    vector<string> createGrid(int m, int n) {
        if (m == 1) {
            return {string(n, '.')};
        }
        if (n == 1) {
            return vector<string>(m, ".");
        }

        vector<string> grid(m, string(n, '#'));

        // Top row: go right until the second-to-last column.
        for (int j = 0; j < n - 1; ++j) {
            grid[0][j] = '.';
        }

        // Second-to-last column: go down to the last row.
        for (int i = 0; i < m; ++i) {
            grid[i][n - 2] = '.';
        }

        // Final step: move right to the bottom-right cell.
        grid[m - 1][n - 1] = '.';

        return grid;
    }
};