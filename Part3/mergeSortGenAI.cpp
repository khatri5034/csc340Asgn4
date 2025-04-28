#include <iostream>

// Definition for singly-linked list
struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution
{
    public:
        // Helper to print the linked list
        void printList(ListNode* head)
        {
            for (ListNode* cur = head; cur; cur = cur->next)
                std::cout << cur->val << " -> ";
            
            std::cout << "nullptr\n";
        }

        // Merge two sorted lists
        ListNode* merge(ListNode* l1, ListNode* l2)
        {
            ListNode dummy(0), * tail = &dummy;

            while (l1 && l2)
            {
                if (l1->val < l2->val)
                {
                    tail->next = l1;
                    l1 = l1->next;
                }
                else
                {
                    tail->next = l2;
                    l2 = l2->next;
                }

                tail = tail->next;
            }

            tail->next = l1 ? l1 : l2;

            return dummy.next;
        }

        // Split list into two halves, returning start of second half
        ListNode* splitMiddle(ListNode* head)
        {
            if (!head || !head->next)
                return nullptr;

            ListNode* slow = head, * fast = head->next, * prev = nullptr;

            while (fast && fast->next)
            {
                prev = slow;
                slow = slow->next;
                fast = fast->next->next;
            }

            // slow is end of first half
            ListNode* second = slow->next;
            slow->next = nullptr;

            return second;
        }

        // Recursive Merge Sort
        ListNode* mergeSortRec(ListNode* head)
        {
            if (!head || !head->next)
                return head;  // 0 or 1 element

            // Split
            ListNode* mid = splitMiddle(head);

            // Sort halves
            ListNode* left = mergeSortRec(head);
            ListNode* right = mergeSortRec(mid);

            // Merge sorted halves
            return merge(left, right);
        }

        // Public entry point
        ListNode* mergeSort(ListNode* head) 
        {
            return mergeSortRec(head);
        }

        // Helper to create a list from initializer list
        ListNode* createList(std::initializer_list<int> vals)
        {
            ListNode* head = nullptr, * tail = nullptr;
            for (int v : vals)
            {
                ListNode* node = new ListNode(v);
                
                if (!head)
                    head = tail = node;
                else
                {
                    tail->next = node;
                    tail = node;
                }
            }

            return head;
        }
};

int main()
{
    Solution sol;

    // Example list
    ListNode* head = sol.createList({ 4, 2, 1, 3, 5, 6 });

    std::cout << "Original list: ";
    sol.printList(head);

    // Sort
    ListNode* sorted = sol.mergeSort(head);

    std::cout << "Sorted list:   ";
    sol.printList(sorted);

    return 0;
}
