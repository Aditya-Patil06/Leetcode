#include <string>
#include <vector>
#include <unordered_map>

class Solution {
public:
    std::string evaluate(std::string s, std::vector<std::vector<std::string>>& knowledge) {
        std::unordered_map<std::string, std::string> dict;
        for (const auto& pair : knowledge) {
            dict[pair[0]] = pair[1];
        }

        std::string result = "";
        std::string key = "";
        bool inside = false;

        for (char c : s) {
            if (c == '(') {
                inside = true;
                key.clear();
            } else if (c == ')') {
                inside = false;
                auto it = dict.find(key);
                if (it != dict.end()) {
                    result += it->second;
                } else {
                    result += '?';
                }
            } else {
                if (inside) {
                    key += c;
                } else {
                    result += c;
                }
            }
        }

        return result;
    }
};