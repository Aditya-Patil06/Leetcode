#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        int i = 0;
        set<string> resultSet = parseExpr(expression, i);
        return vector<string>(resultSet.begin(), resultSet.end());
    }

private:
    // Expr -> Term (',' Term)*
    set<string> parseExpr(const string& s, int& i) {
        set<string> res;
        while (i < s.length() && s[i] != '}') {
            set<string> term = parseTerm(s, i);
            res.insert(term.begin(), term.end()); // Union
            if (i < s.length() && s[i] == ',') {
                i++; // consume ','
            }
        }
        return res;
    }

    // Term -> Factor (Factor)*
    set<string> parseTerm(const string& s, int& i) {
        set<string> res = {""}; // Identity element for Cartesian product
        
        while (i < s.length() && s[i] != '}' && s[i] != ',') {
            set<string> factor = parseFactor(s, i);
            set<string> nextRes;
            for (const string& a : res) {
                for (const string& b : factor) {
                    nextRes.insert(a + b); // Cartesian product / Concatenation
                }
            }
            res = std::move(nextRes);
        }
        return res;
    }

    // Factor -> letter+ | '{' Expr '}'
    set<string> parseFactor(const string& s, int& i) {
        if (s[i] == '{') {
            i++; // consume '{'
            set<string> res = parseExpr(s, i);
            i++; // consume '}'
            return res;
        } else {
            string word = "";
            while (i < s.length() && isalpha(s[i])) {
                word += s[i++];
            }
            return {word};
        }
    }
};