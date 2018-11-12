// Module:		LinkedListClass.cpp
// Project:		CIS023_F2018_HW18
// Developer:	Tom Chaparas
// Date:		November 10, 2018
// Purpose:		Implementation file for LinkedListClass.h
//              Create, fill, navigate, delete linked list

#include "stdafx.h"
#include "LinkedListClass.h"


LinkedListClass::LinkedListClass()
{
}

LinkedListClass::~LinkedListClass()
{
	while (firstNode != nullptr)
	{
		NodeClass* tempNode;
		tempNode = firstNode;
		firstNode = firstNode->GetNextNode();
		delete tempNode;
	}
}

// add a new node to the end of the list
void LinkedListClass::Append(string strIn)
{
	NodeClass* newNode = new NodeClass;

	newNode->SetString(strIn);

	newNode->SetNextNode(nullptr);
	newNode->SetPrevNode(nullptr);

	if (firstNode == nullptr)
	{
		firstNode = newNode;
		lastNode = newNode;
	}
	else
	{
		lastNode->SetNextNode(newNode);
		newNode->SetPrevNode(lastNode);
		lastNode = newNode;
	}
	currentNode = newNode;
}

// insert a new node in front of the currentNode
void LinkedListClass::Insert(string strIn)
{
	NodeClass* newNode = new NodeClass;

	newNode->SetString(strIn);

	newNode->SetNextNode(nullptr);
	newNode->SetPrevNode(nullptr);

	if (currentNode == firstNode)	// if inserting at the beginning of the list
	{
		firstNode->SetPrevNode(newNode);
		newNode->SetNextNode(firstNode);
		firstNode = newNode;
	}
	else	// somewhere in the middle of the list
	{
		newNode->SetNextNode(currentNode);
		newNode->SetPrevNode(currentNode->GetPrevNode());
		currentNode->SetPrevNode(newNode);
		newNode->GetPrevNode()->SetNextNode(newNode);
	}

	currentNode = newNode;
}

// delete the node at the current location, changes curent location to next node
void LinkedListClass::Delete()
{
	NodeClass* tempNode = currentNode;
	
	if (firstNode != lastNode)	// if this is not the only node in the list
	{
		if (currentNode == firstNode)	// if this is the 1st node
		{
			currentNode->GetNextNode()->SetPrevNode(nullptr);
			firstNode = currentNode->GetNextNode();
			currentNode = firstNode;
		}
		else if (currentNode == lastNode) // if this is the last node
		{
			currentNode->GetPrevNode()->SetNextNode(nullptr);
			lastNode = currentNode->GetPrevNode();
			currentNode = lastNode;
		}
		else // this node in in the middle of the list
		{
			currentNode->GetPrevNode()->SetNextNode(currentNode->GetNextNode());
			currentNode->GetNextNode()->SetPrevNode(currentNode->GetPrevNode());
			currentNode = currentNode->GetNextNode();
		}
	}

	delete tempNode;
}

void LinkedListClass::Next()
{
	currentNode = currentNode->GetNextNode();
}

void LinkedListClass::Previous()
{
	currentNode = currentNode->GetPrevNode();
}

NodeClass * LinkedListClass::GetFirstNode()
{
	return firstNode;
}

NodeClass * LinkedListClass::GetLastNode()
{
	return lastNode;
}

NodeClass * LinkedListClass::GetCurrentNode()
{
	return currentNode;
}

void LinkedListClass::SetCurrentNode(NodeClass * inNode)
{
	currentNode = inNode;
}
