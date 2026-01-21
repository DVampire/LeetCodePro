#include <bits/stdc++.h>
using namespace std;

/*
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        if (!head || !head->next || !head->next->next) return {-1, -1};

        ListNode* prev = head;
        ListNode* curr = head->next;
        int idx = 2; // 1-based index of curr

        int firstCrit = -1;
        int prevCrit = -1;
        int lastCrit = -1;
        int minDist = INT_MAX;
        int critCount = 0;

        while (curr && curr->next) {
            ListNode* nxt = curr->next;
            bool isMax = (curr->val > prev->val && curr->val > nxt->val);
            bool isMin = (curr->val < prev->val && curr->val < nxt->val);
            if (isMax || isMin) {
                critCount++;
                if (firstCrit == -1) firstCrit = idx;
                if (prevCrit != -1) minDist = min(minDist, idx - prevCrit);
                prevCrit = idx;
                lastCrit = idx;
            }
            prev = curr;
            curr = nxt;
            idx++;
        }

        if (critCount < 2) return {-1, -1};
        return {minDist, lastCrit - firstCrit};
    }
};
