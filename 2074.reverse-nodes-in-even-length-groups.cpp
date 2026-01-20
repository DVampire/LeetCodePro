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
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        if (!head) return head;

        ListNode dummy(0);
        dummy.next = head;
        ListNode* prevGroupTail = &dummy;

        int groupSize = 1;
        while (prevGroupTail->next) {
            // Find actual group length and tail
            ListNode* groupHead = prevGroupTail->next;
            ListNode* groupTail = groupHead;
            int len = 1;

            while (len < groupSize && groupTail->next) {
                groupTail = groupTail->next;
                len++;
            }

            ListNode* nextGroupHead = groupTail->next;

            if (len % 2 == 0) {
                // Reverse [groupHead, groupTail]
                ListNode* prev = nextGroupHead;
                ListNode* cur = groupHead;
                while (cur != nextGroupHead) {
                    ListNode* nxt = cur->next;
                    cur->next = prev;
                    prev = cur;
                    cur = nxt;
                }
                // prev is new head of reversed group (original groupTail)
                prevGroupTail->next = groupTail;
                prevGroupTail = groupHead; // original head becomes tail
            } else {
                // No reversal
                prevGroupTail = groupTail;
            }

            groupSize++;
        }

        return dummy.next;
    }
};
