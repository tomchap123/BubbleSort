// Module:		NodeClass.cpp
// Project:		CIS023_F2018_HW18
// Developer:	Tom Chaparas
// Date:		November 10, 2018
// Purpose:		Implementation file for NodeClass.h
//

#include "stdafx.h"
#include "NodeClass.h"

NodeClass::NodeClass()
{
}


NodeClass::~NodeClass()
{
}

void NodeClass::SetString(string strIn)
{
	strText = strIn;
}

string NodeClass::GetString()
{
	return strText;
}

void NodeClass::SetNextNode(NodeClass * pIn)
{
	nextNode = pIn;
}

void NodeClass::SetPrevNode(NodeClass * pIn)
{
	prevNode = pIn;
}

NodeClass * NodeClass::GetNextNode()
{
	return nextNode;
}

NodeClass * NodeClass::GetPrevNode()
{
	return prevNode;
}

