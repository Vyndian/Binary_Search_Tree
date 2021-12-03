/*
* This file defines the AppDriver class, which is used to manage the flow of the program.
* The purpose is to run automatic tests on the Binary Search Tree (BST) using randomly
* generated values, and show those tests to the user.
*/

#pragma region Preprocessor Directives
// This file will only be included once.
#pragma once
// Allows use of console (cout, cin).
#include <iostream>
// Allows for certain math functions.
#include <algorithm>
// Allow for use of strings.
#include <string>
// Allows the use of time.
#include <time.h>
// Allows the use of random number generation.
#include <stdlib.h>
// Allows the use of arrays.
#include <array>
// The BST class.
#include "BinarySearchTree.h"
#pragma endregion Preprocessor Directives

// Define the AppDriver class.
class AppDriver
{
public:
	// Constructor for the AppDriver class. Initializes the BST object.
	AppDriver() : tree()
	{
		// Initialize rand with a random seed.
		srand(time(NULL));
	}

	/// <summary>
	/// Runs the intro scenario to welcome the user.
	/// </summary>
	void Intro()
	{
		// Welcome the user with an application title and description.
		Print("Binary Search Tree Showcase", 5, false);
		Print("by Joshua Thornton", 5);
		std::string temp = "Welcome! This application is designed to run automatic tests";
		temp += " on the Binary Search Tree class that I wrote. The numbers used will be";
		temp += " randomly generated and unsorted. The values will range from 1 to 100";
		Print(temp);
		Pause();
	}

	/// <summary>
	/// Runs the test scenario to show the BST off to the user.
	/// </summary>
	void RunTests()
	{
		// Test deleting when BST is empty.
		std::string temp = "Before we even create out test array, let's try removing";
		temp += " a value from the BST while it is empty.";
		Print(temp);
		// Create a random number, 1-10.
		int random = rand() % 10 + 1;
		Print("Attempting to delete " + std::to_string(random) + ". It should return false.");
		Pause();
		// If deletion of the random number from the empty BST returns true (test failure),
		if (tree.Delete(random))
		{
			// then tell the user that the test failed.
			Print("Test FAILED because the deletion returned true.");
			Print("This means that the BST incorrectly thought that is deleted the value.");
		}
		// Else, deletion failed as expected (test success).
		else
		{
			Print("Test SUCCESS because the deletion returned false as expected.");
			Print("This means that the BST knows that the value was not stored.");
		}
		Pause();

		temp = "Now let's get started by filling in our test ";
		temp += "array with 20 random, unsorted integers.";
		Print(temp);
		Pause();

		// Fill the testArray.
		FillArray(testArray);
		// Print the array to the user.
		PrintTestArray(testArray);
		Pause();

		Print("Now let's add that entire array into the BST.");
		Pause();
		// Add the entire test array to the BST.
		AddArrayToBST(testArray);

		Print("And done. Array successfully added into the BST.");
		Print("Let's traverse the BST and print it out to see our handywork.");
		Pause();

		PrintBST();
		Pause();

		temp = "The BST handles insertion of the same value multiple times by ";
		temp += "storing the quantity of each value in its node. You may have seen ";
		temp += "this in action already if the test array duplicated any numbers.";
		Print(temp);
		temp = "Let's test that this works just in case it did not happen earlier.";
		temp += " Take note of the tree's current lowest vale, which should be at ";
		temp += "the top, and the quantity associated with it.";
		Print(temp);
		Pause();

		// Determine the BST's minimum value and store it here.
		int duplicateVal = tree.Minimum();
		temp = "The tree's lowest value is " + std::to_string(duplicateVal);
		temp += ". Let's try adding this value again. We should see the quantity on ";
		temp += "that value increase when we print the BST out again.";
		Print(temp);
		Pause();

		// Insert that value into the BST (as a duplicate of its minimum value).
		tree.Insert(duplicateVal);
		Print("Done. Now let's see what it looks like.");
		Pause();

		PrintBST();
		Pause();

		temp = "You should see that the tree is exactly the same as before, except that ";
		temp += "the quantity associated with the smallest value has increased by 1. ";
		temp += "If not, then this test failed.";
		Print(temp);
		Pause();

		temp = "Now, to test deletion of nodes with exactly one or two children, we ";
		temp += "should start with a clean slate and an empty tree. This presents us with ";
		temp += "a great opportunity to test deleting a node with no children, since ";
		temp += "clearing the entire tree is accomplished by recursively traversing through ";
		temp += "the tree until we reach a node with no children, then deleting that node. ";
		temp += "Let's go ahead and clear the BST.";
		Print(temp);
		Pause();

		// If we successfully clear the tree,
		if (tree.Clear())
		{
			Print("Clearing successful. Multiple nodes with no children deleted.");
			Print("Printing the tree should now show nothing...");
			Pause();

			temp = tree.Traverse();
			// If Traverse returned only the formatting (no values),
			if (temp == "\n   ")
			{
				// then the tree is empty.
				Print("The BST is empty... Nothing to print.", 1);
				Pause();
			}
			else
			{
				Print("BST was NOT empty. Printing it...");
				Print(temp);
				Pause();
			}
		}
		// Else, we failed to clear the tree somehow.
		else
		{
			Print("Clear unsuccessful. Test has FAILED.");
			Print("Printing the tree to show what went wrong...");
			Pause();

			PrintBST();
			Pause();
		}

		temp = "It order to test deletion of a node with exactly 1 child, let's insert some ";
		temp += "values into the BST that will give us that. First, we will insert a 1, ";
		temp += "then a 2. The 1 will become the root, and the 2 will be its right child.";
		Print(temp);
		Pause();

		tree.Insert(1);
		tree.Insert(2);

		temp = "Done. Now the root, 1, has exactly one child, being its right child of 2. ";
		temp += "Let's print the BST to show that is does in fact have these two values.";
		Print(temp);
		Pause();

		PrintBST();
		Pause();

		temp = "Deleting the 1 will change the root member of the tree to point to the 2, ";
		temp += "and the 1 will be deleted. Let's do that now.";
		Print(temp);
		Pause();

		// If deletion of 1 is successful,
		if (tree.Delete(1))
		{
			Print("Value of 1 successfully deleted. Printing the tree...");
		}
		// Else, the deletion failed for some reason.
		else
		{
			Print("Deletion of 1 unsuccessful. Test FAILED. Printing tree for reference...");
		}

		PrintBST();
		Pause();

		temp = "Next up is to test deletion of a node with exactly 2 children nodes. ";
		temp += "We still have our 2 value as the root, so let's give it 2 children. ";
		temp += "1 is lower, so it will be its left child. 3 is higher, so it will be ";
		temp += "its right child.";
		Print(temp);
		Pause();

		tree.Insert(1);
		tree.Insert(3);

		temp = "Those values have been inserted. Let's print the tree for reference, but ";
		temp += "remember that this shows all values from lowest to highest, not necessarily ";
		temp += "showing the root first. In fact, this time, the root of 2 will be shown second.";
		Print(temp);
		Pause();

		PrintBST();
		Pause();

		temp = "Now that we have a root with 2 children, let's test deleting that value of 2-- ";
		temp += "not because that is the number of childrn it has, but because that is the value ";
		temp += "of this node.";
		Print(temp);
		Pause();

		// If the deleting is successful,
		if (tree.Delete(2))
		{
			Print("Deletion of value 2 successful. Printing tree for reference...");
			Pause();
		}
		// Else, the deletion failed for some reason.
		else
		{
			Print("Deletion of 2 unsuccessful. Test FAILED. Printing the tree for reference...");
			Pause();
		}

		PrintBST();
		Pause();

		Print("And that's all of the tests! Thank you for your time. Have a great day.");
		Pause();
	}

private:
	// The Binary Search Tree that this program is testing.
	BinarySearchTree tree;
	// The integer array used for testing the BST. Length of 20.
	std::array<int, 20> testArray = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };

	/// <summary>
	/// Formats the message then prints it to the console on a new line
	/// with the appropriate indent.
	/// </summary>
	/// <param name="msg"> The string to be printed. Include no formating.</param>
	/// <param name="indent"> The number of extra indents for the message.
	/// An indent is 3 spaces.</param>
	/// <param name="endingNewLine"> Whether or not to include a newline at the end.</param>
	void Print(std::string msg, int indent = 0, bool endingNewLine = true)
	{
		// Create a string for formatting with a newline and the mandatory 3-space indent.
		std::string formatting = "\n   ";
		// Add another 3-spaces an indent number of times.
		for (int i = 0; i < indent; i++)
		{
			formatting += "   ";
		}

		// If the msg is too long,
		if (msg.size() >= 65)
		{
			// then determine how many segments it should be.
			int segments = std::ceil(msg.size() / 65) + 1;
			// Add the formatting string in appropriate spots segments-1 times.
			for (int i = 1; i < segments; i++)
			{
				int found = msg.find_first_of(" ", ((65 * i) + (formatting.size() * (i-1))));
				msg.insert((std::abs(found) + 1), formatting);
			}
		}

		// Print the formatting string then the msg.
		std::cout << formatting << msg;

		// If appropriate, include an extra newline at the end.
		if (endingNewLine)
		{
			std::cout << "\n";
		}
	}

	/// <summary>
	/// Pause the program for the user to read before continuing.
	/// </summary>
	void Pause()
	{
		// Add newlines before and after the pause.
		std::cout << "\n";
		system("pause");
		std::cout << "\n";
	}

	/// <summary>
	/// Fills the array with random integers between -100 and 100.
	/// </summary>
	void FillArray(std::array<int, 20> &arr)
	{
		// Iterate through the array.
		for (int i = 0, len = arr.size(); i < len; i++)
		{
			// Set each element in the testArray to a random int between 1 and 100.
			arr[i] = rand() % 100 + 1;
		}
	}

	/// <summary>
	/// Print each element of the array on a new line for each element.
	/// Include expository text to tell the user what is happening.
	/// </summary>
	void PrintTestArray(std::array<int, 20>& arr)
	{
		Print("Printing the array of random, unsorted integers...", 1);
		// Iterate through the array
		for (int i = 0, len = arr.size(); i < len; i++)
		{
			Print(std::to_string(testArray[i]), false);
		}
		// Print an extra newline after the last element in the array.
		std::cout << "\n";
		Print("End of array.", 1);
	}

	/// <summary>
	/// Traverses the BST and prints it to the console.
	/// </summary>
	void PrintBST()
	{
		Print("Printing traversal of the BST...", 1);
		std::cout << tree.Traverse();
		Print("End of BST reached.", 1);
	}

	/// <summary>
	/// Add each element of the testArray into the BST.
	/// </summary>
	void AddArrayToBST(std::array<int, 20>& arr)
	{
		// Iterate through the array
		for (int i = 0, len = arr.size(); i < len; i++)
		{
			// Insert this element into the tree.
			tree.Insert(arr[i]);
		}
	}
};
