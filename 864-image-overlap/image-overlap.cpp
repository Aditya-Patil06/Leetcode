class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size(), ans = 0;

        for (int dx = -n + 1; dx < n; dx++) {
            for (int dy = -n + 1; dy < n; dy++) {
                int count = 0;

                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        int x = i + dx, y = j + dy;

                        if (x >= 0 && x < n && y >= 0 && y < n &&
                            img1[i][j] == 1 && img2[x][y] == 1)
                            count++;
                    }
                }

                ans = max(ans, count);
            }
        }

        return ans;
    }
};