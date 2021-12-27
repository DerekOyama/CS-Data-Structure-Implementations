#pragma once
#include <iostream>
/*
  dlist.h
  Doubly-linked lists of ints
 */
class dlist
{
public:
    // You don't need to modify the constructor, node struct, or head/tail methods.

    dlist()
    {
    }

    struct node
    {
        node(int value, node *next, node *prev) : value(value), next(next), prev(prev)
        {
        }

        int value;  // The value of this node
        node *next; // Ptr. to the next node in the list
        node *prev; // Ptr. to the previous node in the list
    };

    node *head() const { return _head; }
    node *tail() const { return _tail; }

    // **** Implement ALL the following methods ****

    // Returns the node at a particular index (0 is the head). If n >= size()
    // return nullptr; if n < 0, return the head of the list.
    // Must run in O(n) time.
    node *at(int n) const
    {
        if (n >= size())
        {
            return nullptr;
        }
        node *i = head();
        while (n > 0)
        {
            if (i->next == nullptr)
            {
                return nullptr;
            }
            i = i->next;
            n--;
        }

        return i;
    }

    // Insert a new value, after an existing one. If previous == nullptr, then
    // the element is added *before* the head (or, if the list is empty,
    // becomes the new head).
    // Must run in O(1) time.
    void insert(node *previous, int value)
    {
        node *n = new node(value, nullptr, nullptr);
        if (previous == nullptr)
        {
            if (_head == nullptr) //nothing in list
            {
                _head = n;
                _tail = n;
            }
            else if (_head != nullptr) //insert before head
            {
                //node n;
                n->next = _head;
                _head->prev = n;
                _head = n;
            }
        }
        else if (previous == _tail) //insert after tail
        {
            previous->next = n;
            n->prev = _tail;
            _tail = n;
            _tail -> next = nullptr;
        }
        else // insert between 2 nodes
        {
            node *a = previous->next;
            previous->next = n;
            n->prev = previous;
            n->next = a;
            a->prev = n;
        }
    }

    // Delete the given node. Should do nothing if which == nullptr.
    // Must run in O(1) time.
    void remove(node *which)
    {
        if (which == nullptr) //none in list
        {
            return;
        }
        else
        {
            if (_head == _tail && _head == which) // 1 in list
            {
                _head = nullptr;
                _tail = nullptr;
            }
            else if (which == _head) // delete head
            {
                (which->next)->prev = nullptr;
                _head = which->next;
            }
            else if (which == _tail) // delete tail
            {
                (_tail->prev)->next = nullptr;
                _tail = which->prev;
            }
            else // delete any one in middle
            {
                (which->prev)->next = which->next;
                (which->next)->prev = which->prev;
            }
            delete which;
        }
    }

    // Add a new element to the *end* of the list.
    // Must run in O(1) time.
    void push_back(int value)
    {
        insert(tail(), value);
    }

    // Add a new element to the *beginning* of the list.
    // Must run in O(1) time.
    void push_front(int value)
    {
        insert(nullptr, value);
    }

    // Remove the first element.
    // Must run in O(1) time
    void pop_front()
    {
        remove(head());
    }

    // Remove the last element.
    // Must run in O(1) time
    void pop_back()
    {
        remove(tail());
    }

    // Get the size of the list.
    // Should run in O(n) time at the worst
    int size() const
    {
        int i = 0;
        node *n = head();
        if (n == nullptr)
        {
            return 0;
        }
        while (n != nullptr)
        {
            i++;
            n = n->next;
        }
        return i;
    }

    // Returns true if the list is empty.
    // Must run in O(1) time
    bool empty() const
    {
        if (_head == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

private:
    node *_head = nullptr;
    node *_tail = nullptr;
};

// **** Implement ALL the following functions ****

/* a == b
   Compares two lists for equality, returning true if they have the same
   elements in the same positions. (Hint: it is *not* enough to just compare
   pointers! You have to compare the values stored in the nodes.)

   Must run in O(m) time, where m is the length of the shorter of the two lists.
*/
bool operator==(const dlist &a, const dlist &b)
{
    if (a.size() == b.size())
    {
        for (int i = 0; i < a.size(); i++)
        {
            if (a.at(i) -> value != b.at(i) -> value)
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

/* a + b
   Returns a new list consisting of all the elements of a, followed by all the
   elements of b (i.e., the list concatenation).

   Must run in O(n) time in the length of the result.
*/
dlist operator+(const dlist &a, const dlist &b)
{
    dlist ans;
    for (int i = 0; i < a.size(); i++)
    {
        ans.push_back(a.at(i)->value);
    }
    for (int i = 0; i < b.size(); i++)
    {
        ans.push_back(b.at(i)->value);
    }
    return ans;
}

/* reverse(l)
   Returns a new list that is the *reversal* of l; that is, a new list
   containing the same elements as l but in the reverse order.

   Must run in O(n) time.
*/
dlist reverse(const dlist &l)
{
    dlist ans;
    for(int i = l.size() - 1; i >= 0; i--)
    {
        ans.push_back(l.at(i)->value);
    }
    return ans;
}