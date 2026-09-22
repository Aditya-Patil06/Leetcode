class Solution {
    struct Node {
        int prod;
        int cnt[5] = {};

        Node(int p = 1) : prod(p) {}
    };

    int k;
    vector<Node> tree;

    Node merge(Node a, Node b) {
        Node c((a.prod * b.prod) % k);

        for (int r = 0; r < k; r++) {
            c.cnt[r] += a.cnt[r];
            c.cnt[(a.prod * r) % k] += b.cnt[r];
        }

        return c;
    }

    Node makeNode(int x) {
        Node t(x % k);
        t.cnt[x % k] = 1;
        return t;
    }

    void build(int p, int l, int r, vector<int>& nums) {
        if (l == r) {
            tree[p] = makeNode(nums[l]);
            return;
        }

        int m = (l + r) / 2;
        build(p * 2, l, m, nums);
        build(p * 2 + 1, m + 1, r, nums);
        tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
    }

    void update(int p, int l, int r, int idx, int val) {
        if (l == r) {
            tree[p] = makeNode(val);
            return;
        }

        int m = (l + r) / 2;

        if (idx <= m)
            update(p * 2, l, m, idx, val);
        else
            update(p * 2 + 1, m + 1, r, idx, val);

        tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
    }

    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tree[p];

        int m = (l + r) / 2;

        if (qr <= m)
            return query(p * 2, l, m, ql, qr);

        if (ql > m)
            return query(p * 2 + 1, m + 1, r, ql, qr);

        return merge(
            query(p * 2, l, m, ql, qr),
            query(p * 2 + 1, m + 1, r, ql, qr)
        );
    }

public:
    vector<int> resultArray(vector<int>& nums, int K, vector<vector<int>>& queries) {
        k = K;
        int n = nums.size();

        tree.resize(4 * n);
        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto &q : queries) {
            int index = q[0], value = q[1];
            int start = q[2], x = q[3];

            update(1, 0, n - 1, index, value);

            Node res = query(1, 0, n - 1, start, n - 1);
            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};