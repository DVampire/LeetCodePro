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
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        // Values are within [1, 1e5]
        vector<char> del(100001, 0);
        for (int x : nums) del[x] = 1;

        ListNode dummy(0, head);
        ListNode* prev = &dummy;
        ListNode* cur = head;

        while (cur) {
            if (del[cur->val]) {
                prev->next = cur->next;
                ListNode* toDelete = cur;
                cur = cur->next;
                delete toDelete; // optional
            } else {
                prev = cur;
                cur = cur->next;
            }
        }
        return dummy.next;
    }
};