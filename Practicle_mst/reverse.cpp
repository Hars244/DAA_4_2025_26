class Solution
{
public:
    ListNode *reverse(ListNode *start, ListNode *end)
    {
        ListNode *pre = nullptr;
        while (start != end)
        {
            ListNode *next = start->next;
            start->next = pre;
            pre = start;
            start = next;
        }
        return pre;
    }
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        if (!head)
            return nullptr;
        ListNode *node = head;
        for (int i = 0; i < k; i++)
        {
            if (!node)
                return head;
            node = node->next;
        }
        ListNode *newHead = reverse(head, node);
        head->next = reverseKGroup(node, k);
        return newHead;
    }
};