/*
* This class is for a Binary Search Tree (BST), a data structure for holding elements
* in a particular layout that conceptually resembles an upside-down tree. This tree
* will be built specifically to hold integers, as per the assignment instructions.
* 
* The tree will hold nodes, each of which hold an integer value and pointers to the
* nodes that are down to its left and down to its right (simply called leftNode and 
* rightNode for simplicity). No pointer is maintained to ancetors of nodes.
* The BST will not hold references to each node, but only to the first node, known as
* the "root", which can be used to reach any other node in the tree.
* 
* Taking the value X of any given node, the value of that node's leftNode must be < X
* and the value of the rightNode must be > X. Smaller numbers left, larger numbers right.
* 
* No duplicate values will be stored. Instead, each node will also hold a reference to the
* number of times that value has been added (minimum 1, else the node will be deleted).
* 
* This class will NOT be self-balancing, at least not yet.
* 
* This class is being stored only in a .h file because I intent to template the class
* in the future to hold any value type, not just integers.
* 
* This file also defines the Node struct, which again for now will only work
* for integers, but may be made generic in the future.
* 
* I did NOT copy/paste code from the textbook, but did use it as a reference when
* designing code for my methods. I wrote it all by hand and learned what it all meant.
*/

#pragma region Preprocessor Directives
// This file will only be included once.
#pragma once
// Allows for certain math functions.
#include <algorithm>
// Allow for use of strings.
#include <string>
#pragma endregion Preprocessor Directives

// Define the Node struct (for integers).
struct Node
{
	// The value of this Node.
	int value;
	// A pointer to the node that is to this node's bottom-left.
	Node* leftNode;
	// A pointer to the node that is to this node's bottom-right.
	Node* rightNode;
	// The number of times this value has been included.
	int quantity;

	/// <summary>
	/// Constructor for Node struct.
	/// </summary>
	/// <param name="val"> The value this Node will hold.</param>
	/// <param name="left"> Pointer to the Node to this Node's left.</param>
	/// <param name="right"> Pointer to the Node to this Node's right.</param>
	/// <param name="quant"> The number of times this value has been included.</param>
	Node(int val, Node* left = nullptr, Node* right = nullptr, int quant = 1)
	{
		value = val;
		leftNode = left;
		rightNode = right;
		// Ensure that quantity is at least one.
		quantity = std::max(1, quant);
	}

	// The destructor for the Node struct.
	~Node()
	{
		// Intentionally left blank.
	}
};

// Define the Binary Search Tree class (for integers).
class BinarySearchTree
{
	// Public members.
public:
	/// <summary>
	/// Constructor for the Binary Search Tree.
	/// </summary>
	BinarySearchTree()
	{
		// Intentionally left blank.
	}

	/// <summary>
	/// Insert the value provided into the BST quant times.
	/// </summary>
	/// <param name="val"> The value to be stored in the BST.</param>
	void Insert(int val)
	{
		// Calls the private, recursive Insert().
		Insert(val, root);
	}

	/// <summary>
	/// Delete the requested val from the BST.
	/// Returns true if deletion was successful, false is nothing was removed.
	/// </summary>
	/// <param name="val"> The value to be deleted from the BST.</param>
	bool Delete(int val)
	{
		// Calls the private, recursive Delete() starting at the root.
		return Delete(val, root);
	}

	/// <summary>
	/// Returns the maximum value stored in the BST.
	/// </summary>
	/// <returns></returns>
	int Maximum()
	{
		// Call the private FindMax on the root and return its value.
		return FindMax(root)->value;
	}

	/// <summary>
	/// Returns the minimum value stored in the BST.
	/// </summary>
	/// <returns></returns>
	int Minimum()
	{
		// Call the private FindMin on the root and return its value.
		return FindMin(root)->value;
	}

	/// <summary>
	/// Traverses the BST in an INORDER path and returns the resulting string.
	/// </summary>
	/// <returns></returns>
	std::string Traverse()
	{
		// Create the string to be manipulated and an int for depth.
		std::string str = "\n   ";
		int depth = 1;
		// Traverse the BST with the private Traverse(), starting at the root,
		// and return the result.
		return Traverse(str, root, depth);
	}

	/// <summary>
	/// Clears the BST by deleting all nodes.
	/// False is failed to clear, true is clear successful.
	/// </summary>
	bool Clear()
	{
		// Call the private, recursive Clear() starting at the root.
		// Root will be deleting last.
		return Clear(root);
	}

	// Private members.
private:
	// A pointer to the root node for this BST. nullptr when tree is empty.
	Node* root = nullptr;

	/// <summary>
	/// Insert the value provided into the BST quant times. (Private)
	/// </summary>
	/// <param name="val"> The value to be stored in the BST.</param>
	/// <param name="t"> The root node of the subtree we are inserting under.</param>
	void Insert(const int &val, Node* &t)
	{
		// If this node is nullptr,
		if (t == nullptr)
		{
			// then create a new node here with the value.
			t = new Node(val);
		}
		// Else, this node is not nullptr. If val is less than this node's value,
		else if (val < t->value)
		{
			// then recursively call the private Insert on this node's leftNode.
			Insert(val, t->leftNode);
		}
		// Else, val was not less than this node's value. If val is greater than,
		else if (val > t->value)
		{
			// then recursively call the private Insert on this node's rightNode.
			Insert(val, t->rightNode);
		}
		// Else, val must actually be equal to this node's value.
		else
		{
			// Increment the quantity in this node to account for it being inserted multiple times.
			t->quantity++;
		}
	}

	/// <summary>
	/// Delete the requested val from the BST, starting the search at subtree t.
	/// Returns true if deletion was successful, false is nothing was removed. (Private)
	/// </summary>
	/// <param name="val"> The value to be deleted from the BST.</param>
	/// <param name="t"> The root node of the subtree currently being used to find val.</param>
	bool Delete(const int& val, Node* &t)
	{
		// If this node is nullptr,
		if (t == nullptr)
		{
			// then we did not find the value. Do nothing.
			return false;
		}
		// Else, this node is not null. If val is less than this node's value,
		else if (val < t->value)
		{
			// then recursively call the private Delete on the leftNode.
			return Delete(val, t->leftNode);
		}
		// Else, val was not less than this node's value. If val is greater than,
		else if (val > t->value)
		{
			// then recursively call the private Delete on the rightNode.
			return Delete(val, t->rightNode);
		}
		// Else, val must actually be equal to this node's value.
		// If this value has a quantity of more than 1,
		else if (t->quantity > 1)
		{
			// then simply lower the quantity by 1.
			t->quantity--;
			return true;
		}
		// Else, this value must be stored with a quantity of only 1.
		else
		{
			// We can delete this node, but children make it tricky.
			// If this node has 2 children,
			if (t->leftNode != nullptr && t->rightNode != nullptr)
			{
				// then we must move the minimum node from the rightNode onto this node
				// (by moving values only).
				Node* tempNode = FindMin(t->rightNode);
				t->value = tempNode->value;
				t->quantity = tempNode->quantity;

				// Set that minimum node's quantity to 1 so it gets fully removed later.
				tempNode->quantity = 1;

				// Recursively call Delete for the moved value starting at this node's rightNode.
				return Delete(tempNode->value, t->rightNode);
			}
			// Else, this node has no more than 1 child.
			else
			{
				// Hold a reference to this node to be deleted.
				Node* oldNode = t;

				/* Because t is the parent's pointer to this node, changing t is essentially
				* changing which node the parent's pointer is pointing to. This node would
				* then still need to be deleted with the "delete" keyword since it was created
				* with the "new" keyword. */

				// Change t to equal the child of this node (will be nullptr is no children).
				// This line essentially says:
				// If this node's leftNode is valid, then set t equal to it.
				// Otherwise, set t to this node's rightNode (which might still be nullptr).
				t = (t->leftNode != nullptr) ? t->leftNode : t->rightNode;

				// Finally, delete the oldNode.
				delete oldNode;
				return true;
			}
		}
	}

	/// <summary>
	/// Finds the node with the minimum value at or below node t.
	/// </summary>
	/// <param name="t"> The node to start the search for the minimum value.</param>
	/// <returns></returns>
	Node* FindMin(Node* &t)
	{
		// If this node it nullptr,
		if (t == nullptr)
		{
			// then the BST (or subtree provided) is empty. Return NULL.
			return nullptr;
		}
		// Else, if this node's leftNode is valid,
		else if (t->leftNode != nullptr)
		{
			// then recursively call FindMin on that leftNode.
			return FindMin(t->leftNode);
		}
		// Else, this node is valid but has no leftNode.
		else
		{
			// This node's value is the minimum. Return this node.
			return t;
		}
	}

	/// <summary>
	/// Finds the node with the maximum value at or below node t.
	/// </summary>
	/// <param name="t"> The node to start the search for the maximum value.</param>
	/// <returns></returns>
	Node* FindMax(Node*& t)
	{
		// If this node it nullptr,
		if (t == nullptr)
		{
			// then the BST (or subtree provided) is empty. Return NULL.
			return NULL;
		}
		// Else, if this node's rightNode is valid,
		else if (t->rightNode != nullptr)
		{
			// then recursively call FindMax on that rightNode.
			return FindMax(t->rightNode);
		}
		// Else, this node is valid but has no rightNode.
		else
		{
			// This node's value is the maximum. Return this node.
			return t;
		}
	}

	/// <summary>
	/// Traverses the BST in an INORDER path and returns the resulting string. (Private)
	/// </summary>
	/// <param name="str"> The string being manipulated.</param>
	/// <param name="t">The node acting as root of the subtree being traversed.</param>
	/// <returns></returns>
	std::string Traverse(std::string &str, Node* &t, int &depth)
	{
		// If the node provided is not valid,
		if (t == nullptr)
		{
			// then the BST (or subtree provided) is empty. Return str without manipulation.
			return str;
		}
		// Else, this node is valid.

		/* This Traverse() method follows the INORDER path, meaning left, node, right.
		* The left-most node will be processed, then its parent node, then the process
		* starts over with the node to the right of that parent node. */
		
		// LEFT
		// If this node has a leftNode,
		if (t->leftNode != nullptr)
		{
			// then recursively call the private Traverse() on that leftNode.
			Traverse(str, t->leftNode, depth);
		}

		// NODE
		/* When code reaches here, either the current node is a leaf,
		* or all of its left-side decendents have been processed already. */

		// Add this node's value and quantity to the string.
		str += "Value: " + std::to_string(t->value) + " - Quantity: " + std::to_string(t->quantity);
		// Add a newline character and 3 spaces, and then
		// a number of additional spaces equal to depth.
		str += "\n   ";
		for (int i = 0; i < depth; i++)
		{
			str += " ";
		}
		// Increment depth.
		depth++;

		// RIGHT
		// If this node has a rightNode,
		if (t->rightNode != nullptr)
		{
			// then recursively call the private Traverse() on that rightNode.
			Traverse(str, t->rightNode, depth);
		}

		// Return the manipulated string.
		return str;
	}

	/// <summary>
	/// Clears the subtree that has t as the root by deleting it and all of its
	/// descendants. t is cleared last. Follows left-right-node traversal.
	/// False is failed to clear, true is clear successful.
	/// </summary>
	/// <param name="t"> The root of the subtree being cleared.</param>
	bool Clear(Node* &t)
	{
		// Double check we are not on an invalid node.
		if (t == nullptr)
		{
			// If so, return false.
			return false;
		}

		// LEFT
		// This node is valid. If it has a left child,
		if (t->leftNode != nullptr)
		{
			// then recursively call the private Clear on that leftNode.
			Clear(t->leftNode);
		}

		// RIGHT
		// This node has no left child, or it did and it was deleted.
		// If it has a right child,
		if (t->rightNode != nullptr)
		{
			// then recursively call the private Clear on that rightNode.
			Clear(t->rightNode);
		}

		// NODE
		// This node has no children, or it did and they have been deleted.
		// It is safe to delete this node.
		delete t;
		t = nullptr;
		return true;
	}
};
