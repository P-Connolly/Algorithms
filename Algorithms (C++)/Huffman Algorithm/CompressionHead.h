//ADS2 CA1 Paul Connolly X00081023
#include<iostream>
#include<string>
#include<fstream>
#include<istream>
#include <map>
#include <utility>

using namespace std;

class HuffNode;



 class HuffNode
{
public:
	//Friend class compare to be used by priority queue
	friend class Compare;
	string getCode();//get code to be used to traverse the tree and assign binary to each character in data.txt file.
	string getCode(HuffNode *aNode);
	map<char, string>mainMap;//map used to store characters and binary.
	map<char, string>::iterator iter1;

	string treeBinary;//Used for task 8, stores tree information
	string binary;//Used to store the steps taken through the tree while traversing it.
	char myChar;
	int myFreq;


	HuffNode *root, *myLeft, *myRight;

};


 //This method is used internally by the priority queue to compare node's member values and determine their correct positions in the queue.
 class Compare
 {
	 public:

		 bool operator()(const HuffNode* node2, const HuffNode* node1) 
			{
				return node1->myFreq  < node2->myFreq;
			};

 };

 //AUTO GEN TREE - similar to above

 class HuffNode;



 class HuffNodeAuto
{
public:



	friend class Compare;
	HuffNodeAuto();
	HuffNodeAuto(char character, HuffNodeAuto *left, HuffNodeAuto *right);
	HuffNodeAuto* createTree(string);

	string getCode();
	string getCode(HuffNodeAuto *aNode);

	map<char, string>mainMap;
	map<char, string>::iterator iter;

	string treeBinary;
	string binary;
	char myChar;
	int myFreq;


	HuffNodeAuto *root, *myLeft, *myRight;

};

