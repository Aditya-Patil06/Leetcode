class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return {-1, -1};

        ListNode* prev = head;
        ListNode* curr = head->next;

        int index = 1;
        int firstCritical = -1;
        int prevCritical = -1;

        int minDist = INT_MAX;
        int maxDist = -1;

        while (curr->next != nullptr) {
            int prevVal = prev->val;
            int currVal = curr->val;
            int nextVal = curr->next->val;

            bool isCritical =
                (currVal > prevVal && currVal > nextVal) ||
                (currVal < prevVal && currVal < nextVal);

            if (isCritical) {
                if (firstCritical == -1) {
                    // First critical point
                    firstCritical = index;
                } else {
                    // Distance from previous critical point
                    minDist = min(minDist, index - prevCritical);

                    // Distance from first critical point
                    maxDist = index - firstCritical;
                }

                prevCritical = index;
            }

            prev = curr;
            curr = curr->next;
            index++;
        }

        if (prevCritical == firstCritical)
            return {-1, -1};

        return {minDist, maxDist};
    }
};