// Module:		LinkedListClass.h
// Project:		CIS023_F2018_Lab18b
// Developer:	Tom Chaparas
// Date:		November 10, 2018
// Purpose:		Header file for LinkedListClass.cpp
//

#pragma once
class LinkedListClass
{
public:
	LinkedListClass();
	~LinkedListClass();

	void Append(string);						// append node to list
	void Insert(string);						// insert node at current location
	void Delete();								// delete a node
	void Next();								// set current node to next node
	void Previous(); // set current node to previous node
	void SwapWithPrevious();

	NodeClass* GetFirstNode();					// return 1st node
	NodeClass* GetLastNode();					// return last node
	NodeClass* GetCurrentNode();				// return current node
	void SetCurrentNode(NodeClass*);			// change current node

private:
	NodeClass* firstNode;						// pointer to first node
	NodeClass* lastNode;						// pointer to last node
	NodeClass* currentNode;						// pointer to current node

};

