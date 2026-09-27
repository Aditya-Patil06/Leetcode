#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::string reverseParentheses(std::string s) {
        std::vector<int> openIndices;
        std::string res = "";

        for (char c : s) {
            if (c == '(') {
                openIndices.push_back(res.length());
            } else if (c == ')') {
                int start = openIndices.back();
                openIndices.pop_back();
                std::reverse(res.begin() + start, res.end());
            } else {
                res += c;
            }
        }

        return res;
    }
};