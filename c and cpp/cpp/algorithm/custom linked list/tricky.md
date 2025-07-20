why this error is correct even when the list is `[]`, the terminal->next->next will pointing to what?
```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* temp = new ListNode(0,head);
        ListNode* first = temp;
        ListNode* second;

        ListNode* terminal;
        terminal = first;

        while(terminal->next && terminal->next->next){
            first = terminal->next->next;
            second = terminal->next;
            
            second->next = first->next;
            first->next = second;
            terminal->next = first;
            
            terminal = second;
        }

        ListNode* ans = temp->next;
        delete temp;
        return ans;

    }
};

```
because:
**logical AND (`&&`) operator short-circuits**:
- If `terminal->next` is `nullptr`, it doesn't evaluate `terminal->next->next`
- This prevents any null pointer dereference