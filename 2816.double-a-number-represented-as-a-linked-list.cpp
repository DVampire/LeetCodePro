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
private:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        while (head) {
            ListNode* nxt = head->next;
            head->next = prev;
            prev = head;
            head = nxt;
        }
        return prev;
    }

public:
    ListNode* doubleIt(ListNode* head) {
        head = reverseList(head);

        int carry = 0;
        ListNode* cur = head;
        ListNode* prev = nullptr;

        while (cur) {
            int v = cur->val * 2 + carry;
            cur->val = v % 10;
            carry = v / 10;
            prev = cur;
            cur = cur->next;
        }

        if (carry) {
            prev->next = new ListNode(carry);
        }

        head = reverseList(head);
        return head;
    }
};