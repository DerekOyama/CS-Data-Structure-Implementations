#pragma once
#include <cassert>
#include <stdexcept>
#include <iostream>

class splay_tree
{
public:
	struct node
	{
		node(int key, node *left, node *right, node *parent) : key(key), left(left), right(right), parent(parent)
		{
		}

		int key;
		node *left;
		node *right;
		node *parent;
	};

	/* root()
	   Returns the rt of the tree.

	   Runs in O(1) time.
	*/
	node *root() const
	{
		return rt;
	}

	/* size()
	   Returns the size (total number of nodes) in the tree.

	   Runs in O(n) time.
	*/
	int size() const
	{
		node *n = rt;
		return sizeh(n);
	}

	int sizeh(node *n) const
	{
		if (n == nullptr)
		{
			return 0;
		}
		return sizeh(n->left) + sizeh(n->right) + 1;
	}

	/* empty()
	   Returns true if the tree is empty.

	   Runs in O(1) time.
	*/
	bool empty() const
	{
		if (rt == nullptr)
		{
			return true;
		}
		return false;
	}

	/* rotate(c,p)
	   Rotate child node c with parent node p. c must be a child of p
	   (either c == p->left or c == p->right) and neither c nor p can be
	   nullptr.


	   Runs in O(1) time.
	*/
	static void rotate(node *c, node *p)
	{

		assert(c != nullptr and p != nullptr);
		assert(c == p->left or c == p->right);
		assert(c->parent == p);

		if (p->left == c)
		{
			node *n = c->right;
			c->right = p;
			if (n != nullptr)
			{
				n->parent = p;
			}
			p->left = n;
		}
		else if (c == p->right)
		{
			node *n = c->left;
			c->left = p;
			if (n != nullptr)
			{
				n->parent = p;
			}
			p->right = n;
		}
		c->parent = p->parent;
		if (p->parent != nullptr && p->parent->left == p)
		{
			p->parent->left = c;
		}
		if (p->parent != nullptr && p->parent->right == p)
		{
			p->parent->right = c;
		}
		p->parent = c;
	}

	/* splay(n)
	   Splays n to the rt of the tree, returning the new rt. n must not
	   be nullptr.

	   As with `rotate`, splay is a static member function, so it is not allowed
	   to access any member variables (it can call `rotate`, however).
	   Runs in O(d) time where d is the depth of node n (amortized, this
	   will be O(log n)).
	*/

	static node *splay(node *n)
	{
		while (n->parent != nullptr)
		{
			if (n->parent->parent == nullptr)
			{
				rotate(n, n->parent);
			}
			else if ((n->parent->left == n && n->parent == n->parent->parent->left) || (n->parent->right == n && n->parent == n->parent->parent->right))
			{
				rotate(n->parent, n->parent->parent);
				rotate(n, n->parent);
			}
			else if ((n->parent->left == n && n->parent == n->parent->parent->right) || (n->parent->right == n && n->parent == n->parent->parent->left))
			{
				rotate(n, n->parent);
				rotate(n, n->parent);
			}
		}
		return n;
	}

	/* find(k)
	   Finds and returns the node containing key k, splaying it to the rt.
	   If no such node exists, then `find` splay's the parent of the location
	   where k* should* be to the rt, and then returns the new rt. If the
	   tree is empty, returns nullptr. To determine whether a key k exists in
	   the (nonempty) tree, you would check

			k == find(k)->key

	   Runs in O(log n) amortized time.
	*/
	node *find(int k)
	{
		if (rt == nullptr)
		{
			return nullptr;
		}
		rt = splay(finder(rt, k));
		return rt;
	}

	node *finder(node *n, int k)
	{
		if (n->key == k)
		{
			return n;
		}
		else if (n->key < k)
		{
			if (n->right == nullptr)
			{
				return n;
			}
			return finder(n->right, k);
		}
		else
		{
			if (n->left == nullptr)
			{
				return n;
			}
			return finder(n->left, k);
		}
	}

	/* insert(k)
	   Inserts k into the tree, splaying the new node to the rt. If k
	   already exists in the tree, it should be splayed to the rt. Returns
	   the new rt of the tree.

	   Runs in O(log n) amortized time.
	*/
	node *insert(int k)
	{
		rt = splay(inserter(rt, k));
		return rt;
	}

	node *inserter(node *n, int k)
	{
		if (n == nullptr)
		{
			node *a = new node(k, nullptr, nullptr, nullptr);
			return a;
		}
		if (n->key == k)
		{
			return n;
		}
		else if (k < n->key)
		{
			if (n->left != nullptr)
			{
				return inserter(n->left, k);
			}
			else
			{
				node *a = new node(k, nullptr, nullptr, n);
				n->left = a;
				return a;
			}
		}
		else
		{
			if (n->right != nullptr)
			{
				return inserter(n->right, k);
			}
			else
			{
				node *a = new node(k, nullptr, nullptr, n);
				n->right = a;
				return a;
			}
		}
	}

	/* remove(k)
	   EXTRA CREDIT: Removes the node containing k, and splays its parent to
	   the rt. If k does not exist in the tree, then nothing is removed,
	   but the parent (of where k* should* exist) is still splayed. Returns
	   the new rt of the tree.

	   Runs in O(log n) amortized time.
	*/
	node *remove(int k)
	{
		if (rt == nullptr)
		{
			return nullptr;
		}
		else
		{
			if (find(k)->key != k)
			{
				return rt;
			}
			else
			{
				find(k);
				splay_tree left;
				splay_tree right;
				left.set_root(rt->left);
				right.set_root(rt->right);
				if (left.root() == nullptr)
				{
					rt = right.root();
					if(right.root() != nullptr)
					{
						right.set_root(nullptr);
					}
					rt = nullptr;
					return right.root();
				}
				else
				{
					left.find(k)->right = right.root();
					left.root() -> right -> parent = left.root();
					rt = left.root();
					return left.root();
				}
			}
		}
	}

	/* set_root(n)
	   Replaces the rt node with n; this is only used for testing.
	*/
	void
	set_root(node *n)
	{
		rt = n;
	}

private:
	node *rt = nullptr;
};
