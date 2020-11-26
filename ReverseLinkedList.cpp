#include<iostream>
using namespace std;
struct ListNode {
     int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
 ListNode* reverseList(ListNode* head) {
        ListNode* result;
        while(head != nullptr){
            ListNode* replacer;
            replacer = head;
            head = head -> next;
            replacer -> next = result;
            result = replacer;
            replacer = nullptr;
            delete replacer;
        }
        return result;
    }

int main()
{
    ListNode* head = new ListNode();
    ListNode* back = new ListNode();
    back -> val = 1;
    head -> next = back;
    cout<<head -> val;
    head = reverseList(head);
    cout<<head -> val;
}
