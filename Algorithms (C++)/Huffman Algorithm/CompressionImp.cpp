//ADS2 CA1 Paul Connolly X00081023
#include<iostream>
#include<string>
#include<fstream>
#include<istream>
#include <map>
#include <utility>
#include "CompressionHead.h"
using namespace std;

int count = 0;


//This function is used to call the getCode(HuffNode) function, although first it checks if the node is null before doing so.
string HuffNode::getCode(){

	treeBinary = "";
	binary = "";

    if(root == nullptr){
		cout << "root is null";
        return "";
    }
    else
	{
		
		 
        HuffNode *node = root;
        return getCode(node);

    }
}
//Pre-order traversal occurs here, basicly it checks if the node is null, if not it will check if the left node is empty
//if not it will recursively call getNode(HuffNode), however first it will add the 0 character to the binary string 
//to represent that it has continued left through the tree. If the right node is not null it will do the same step, however it will add the 1 character to 
//represent it has continued right through the tree. If both the left and right nodes are empty, it is a leaf node and will return the character
//associated with this node and the binary that this character is now represented by. Every time it goes up a level in the tree
//it will remove one character from the binary representing each step it has taken through the tree.
string HuffNode::getCode(HuffNode *aNode)
{
	    if(aNode == 0)
	    {
	     	return "";
	    }
		if(aNode->myLeft != 0 || aNode->myRight != 0)
		{
				treeBinary = treeBinary + "0"; //Tree Embedding purposes@@@@Part of Task 8@@@@ explained more in main.
		}

	
		if(aNode->myLeft != 0)
		{
		binary = binary + "0";
		
		getCode(aNode->myLeft);
		
		}
		if(aNode->myRight != 0)
		{
		binary = binary + "1";
		
		getCode(aNode->myRight);
		 
		}
		
		
		if(aNode->myRight == nullptr && aNode->myLeft == nullptr)
		{
		treeBinary = treeBinary + "1" + aNode->myChar; //Tree Embedding purposes@@@@Part of Task 8@@@@ explained more in main.
		
		mainMap[aNode->myChar] = binary;
		
		}
		
		
		binary = binary.substr(0, binary.size()-1);
		return "";

	
}


//AUTO GEN TREE

//Overloaded constructor here
HuffNodeAuto::HuffNodeAuto(char character, HuffNodeAuto *left, HuffNodeAuto *right)
{

	myChar = character;
	myLeft = left;
	myRight = right;

}

HuffNodeAuto* HuffNodeAuto::createTree(string treeCode)
{

	//If character = "1" then then return a new node, and set its symbol value to the next value in the reader
	//also set the left and right nodes to null, as 1 represents a leaf node.
		if(treeCode[count] == '1')
		{
			if(count != treeCode.size()-1)
			{
				
				count++;

				if(count!= treeCode.size()-1)
				{
				count++;
				}
				else
				{
				return new HuffNodeAuto(treeCode[count], 0, 0);
				}
				return new HuffNodeAuto(treeCode[count-1], 0, 0);
				
			}
			else
			{
				return 0;
			}
		
		}
		//if character is equal to "0" then create 2 new nodes representing the right and left
		//nodes that will be added to the current node that is to be returned. Also run the function recursively within the left and right node before addition.
		else if(treeCode[count] == '0')
		{
			if(count != treeCode.size()-1)
			{
			count++;
			HuffNodeAuto *newLeft = createTree(treeCode);
			HuffNodeAuto *newRight = createTree(treeCode);
			
			return new HuffNodeAuto(0, newLeft, newRight);
			}
			else
			{
				return 0;
			}
			
		}
		
}
//The below code is just the same pre-order traversal code used in the above functions as part of the HuffNode class, so I will not
//have to explain them again.
string HuffNodeAuto::getCode(){

	treeBinary = "";
	binary = "";

    if(root == nullptr){
		cout << "root is null";
        return "";
    }
    else
	{
		
		 
        HuffNodeAuto *node = root;
        return getCode(node);

    }
}

string HuffNodeAuto::getCode(HuffNodeAuto *aNode)
{
	
	    if(aNode == 0)
	    {
	     	return "";
	    }
		if(aNode->myLeft != 0 || aNode->myRight != 0)
		{
				treeBinary = treeBinary + "0"; //Tree Embedding purposes
		}
		
	
		if(aNode->myLeft != 0)
		{
		binary = binary + "0";
		
		getCode(aNode->myLeft);
		
		}
		if(aNode->myRight != 0)
		{
		binary = binary + "1";
		
		getCode(aNode->myRight);
		 
		}
		
		
		if(aNode->myRight == nullptr && aNode->myLeft == nullptr)
		{
		treeBinary = treeBinary + "1" + aNode->myChar; //Tree embedding purposes
		mainMap[aNode->myChar] = binary;
		
		}
		
		
		binary = binary.substr(0, binary.size()-1);
		return "";

	
}


