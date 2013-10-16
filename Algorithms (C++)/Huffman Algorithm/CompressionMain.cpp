//ADS2 CA1 Paul Connolly X00081023
#include<iostream>
#include<string>
#include<fstream>
#include<istream>
#include <map>
#include<utility>
#include<queue>
#include <limits>
#include<bitset>
#include <vector>
#include"CompressionHead.h"
using namespace std;


//This method was used to help bug checking and understand what was going on throughout the program by allowing the use of cout and "<<" operator on the nodes. It is no longer needed.
ostream& operator<<(std::ostream os, const HuffNode& obj) 
{ 
	// write obj to stream
	return os;
};
//This method is repeatedly used to create txt files and write string values to said files.
void createFile(string filename, string filecode)
{
	ofstream myfile;
	myfile.open (filename);
	myfile <<  filecode;
	myfile.close();
};


int main()
{
	//Creating a map here, and an iterator for said map. The map will contain the characters and the frequency in which the characters occur.
	//The iterator is used to iterate throughout the map and manipulate the maps entire contents.
	map<char, int> characters;
	map<char, int>::iterator iter;

	
	char ch;
	fstream fin("data.txt", fstream::in);
	//declaring priority queue here.
	priority_queue<HuffNode*, vector<HuffNode*>, Compare > treeQueue;
	//While loop assigns each character in the data text file and assigns them to the characters map.
	while (fin >> noskipws >> ch) 
	{ 
		characters[ch] = characters[ch]++;	//@@@@@@@@@@@@@@@@@@@@@TASK 1 HERE@@@@@@@@@@@@@@@

	}
	if (fin.is_open())
	{
	
	fin.close();
	//The for loop below iterates throughout the character map and creates nodes for each character.
	for(iter = characters.begin(); iter !=  characters.end(); iter++)
	{

		HuffNode *attach = new HuffNode();
		attach->myChar = iter->first;
		attach->myFreq = characters[iter->first];
		attach->myLeft = NULL;
		attach->myRight = NULL;
		attach->root = attach;
	//The pointer to the dynamicly created node is then assigned to the priority queue.
		treeQueue.push(attach);

	}

	

	//I used the pseudo-code from the "Slides to Explain Huffman" to help understand this process, as you can see the comments directly correlate
	//with the relating section for this part of the development of the tree.

	while (treeQueue.size() > 1)//While priority queue contains two or more nodes 
	{
		//@@@@@@@@@@@@@@@@@@@TASK 2 HERE@@@@@@@@@@@@@@@@@
		int left;
		int right;

		HuffNode *attach = new HuffNode(); 

		attach->root = attach;
		
		//Dequeue node and make it left subtree
		left = treeQueue.top()->myFreq;
		attach->myLeft = treeQueue.top();
		treeQueue.pop();
		

		//Dequeue next node and make it right subtree
		right = treeQueue.top()->myFreq;
		attach->myRight =  treeQueue.top();
		treeQueue.pop();


		//Frequency of new node equals sum of frequency of left and right children
		attach->myFreq = left + right;

		//Enqueue new node back into queue
		treeQueue.push(attach);



	}

	//Now that the tree has been created I can now call the remaining node on the queue, and use the getCode() method.
	//This will cause a pre-order traversal to be performed on the tree. 
	treeQueue.top()->getCode(); //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@TASK 3 HERE@@@@@@@@@@@@@@@@@
	//This method will be use the map member of top node allotcated to the queue to be filled with the 
	//various characters and the binary code associated with each character.
	string encoded = "";

	char chData;
	//The data text file is then read again, and each character is used as the key within the map
	//This allows the relating binary code to this character to be added to the encoded string
	//and this is repeated until the end of the characters.
	fstream finData("data.txt", fstream::in);
	while (finData >> noskipws >> chData) 
	{ 
		encoded = encoded + treeQueue.top()->mainMap[chData];  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@TASK 4 HERE@@@@@@@@@@@@@@@@@
	}
	//New file is created containing the converted binary text.(saved in ascii format NOT COMPRESSED, though this was not required by the task)
	createFile("encoded.txt", encoded);


	char chEncoded;
	string binaryTotal = "";
	string decode = "";
	//The encoded file of 1's and 0's is now decoded.
	//This is done by iterating through the top nodes member map, and comparing the binary value within that map
	//with a string that is generated based on the binary code, this string add 0's and 1's to its value
	//until this value is equal to a binary value in the map, once found the string value is clear and continues to add values until the end of the file.
	fstream finEncoded("encoded.txt", fstream::in);
	while (finEncoded >> noskipws >> chEncoded) 
	{ 
		
		binaryTotal = binaryTotal + chEncoded;

		for(treeQueue.top()->iter1 = treeQueue.top()->mainMap.begin(); treeQueue.top()->iter1 !=  treeQueue.top()->mainMap.end(); treeQueue.top()->iter1++)
		{
			if(treeQueue.top()->iter1->second  != binaryTotal)
			{
				
			}
			else         //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@TASK 5 HERE@@@@@@@@@@@@@@@@@
			{
				
				binaryTotal = "";
				decode = decode + treeQueue.top()->iter1->first;
			}
		}


	}

	createFile("decoded.txt", decode);
	//This completes task 5.

//START OF COMPRESSION WRITING.....................................................................................................................................................................................................................

	//To compress, the encoded string of 1's and 0's representing the data text file
	//is first sized, to ensure that it can be divided in 8-bit chunks, if not 0 values are added to the file until it does.
	//(basicly can it be divided by 8 without a remainder)
	int size = encoded.size();
	int division =  size % 8;
	division = 8 - division;
	
	if(division > 0)
	{
		for(int x = 0;x < division; x++)
		{
			
			encoded = encoded + "0";
		}
	}
	
	

	

	string eightBits = "";
	ofstream output("compressed.txt", ios::out | ios::binary );
	string treeBinaryData = treeQueue.top()->treeBinary;//AUTO GENERATING TREE @@@@@@@@<--- LINE PART OF TASK 8@@@@@@
	//This is part of task here, here I have used the treeBinary member function of the top node of the priority queue to
	//create a sequence of ascii text which will represent the tree which will be embedded.
	//A simplistic explaination of this is the following: If the node is a leaf node, then the '1' character will be added to the text
	//also, the symbol of said leaf node will be added also. If the node is a not a leaf not a 0 is added, for further explaination see the implementation cpp file.
	//I then add this text representing the tree to the compressed file, to be used later in task 8. This is stored is pure ascii format
	//so for it to be properly used it should be used along with a large data file as it adds much overhead in the way of bytes.
	//the § symbol is used to represent the end of tree text, but any rare symbol could be used also.
	output << treeBinaryData + "§";//@@@@@@@@<--- LINE PART OF TASK 8@@@@@@



	//To generate the compressed code I converted the encoded string after confirming it was divisable by 8 
	//This was done by taking 8 characters iteratively and converting them to 8 bit format and then writing them 
	//to the compressed.txt file.
	for(int x = 0; x < encoded.size(); x++)
	{
		
		eightBits = eightBits + encoded[x];
		if(eightBits.size() == 8)
		{
			
			bitset<8> header_bits(eightBits.c_str());
			output.write( reinterpret_cast<char *>(&header_bits), 1);//@@@@@@@TASK 6@@@@@@@@@
			eightBits = "";
		}
	}
	 output.close();
	    


//END OF COMPRESSION WRITING..................................................................................................................................................................................................................................................
//START OF COMPRESSION READING..................................................................................................................................................................................................................................................
	
	string asciiToBinary;
	string allbinary = "";
	string binary1 = "";
	 ifstream::pos_type size1;
	 char * memblock;
	 //Here the compressed file is opened directly in binary, this allows the binary code to be read and added to a string, away from its current ascii format of
	 //seemingly random symbols. This is then added to a string which then will later convert the binary.
	 ifstream file ("compressed.txt", ios::in|ios::binary|ios::ate);
	 if (file.is_open())
    {
    size = file.tellg();
    memblock = new char [size];
	
    file.seekg (0, ios::beg);
    file.read (memblock, size);
    file.close();
	//This task example is seperate from task 8, so I am purposely coding in methods for the decompression process to ignore the embedded tree.
 string treeEndWatch = "";
 bool treeEnded= false;
for(int x = 0;x < size ; x++)
{
		treeEndWatch =  memblock[x];
		//memblock is the actual ascii character being read as it is in the file
		if(treeEnded)
		{
	    bitset<8> code (memblock[x]);// and here is the ascii character being convert to 8 0's and 1's which that character represents
		asciiToBinary = asciiToBinary + code.to_string();
		}
		if(treeEndWatch == "§")//Basicly if the tree code has ended THEN start converting the ascii to binary, as the tree text is irrelevant to this task(task 7)
		{
			treeEnded = true;
		}

	}


    delete[] memblock;
  }
  else cout << "Unable to open file";
//FILE DECOMPRESSED

  createFile("decompressedBinary.txt", asciiToBinary);

  char chDeCom;
	string binaryTotalDeCom = "";
	string decodeDeCom = "";
	//Here the binary file is read and converted back to character which these binary digits represent using the top node of the queue's member map.
	//It uses the exact same method that was done before to convert the encoded.txt file, so I will not explain it again(TASK 5).
	fstream fin21("decompressedBinary.txt", fstream::in);
	while (fin21 >> noskipws >> chDeCom) 
	{ 
		
		binaryTotalDeCom = binaryTotalDeCom + chDeCom;
		
		for(treeQueue.top()->iter1 = treeQueue.top()->mainMap.begin(); treeQueue.top()->iter1 !=  treeQueue.top()->mainMap.end(); treeQueue.top()->iter1++)
		{
			if(treeQueue.top()->iter1->second  != binaryTotalDeCom)
			{
				
			}
			else						//@@@@@@@@@@@@@@@@@@@@@@@@@@@TASK 7@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			{
				
				binaryTotalDeCom = "";
				decodeDeCom = decodeDeCom + treeQueue.top()->iter1->first;
				
			}
		}


	}

	createFile("decompressed.txt", decodeDeCom);

//			REST OF TASK 8 HERE
	string extractedTree = "";
	bool extractionComplete = false;
	char chCompressed;
	fstream finCompressed("compressed.txt", fstream::in);

	//The first step is to create the string containing the actual code used to create the tree automaticly based off that text.
	//Extracting tree generation code from text file
	while (finCompressed >> noskipws >> chCompressed) 
	{ 
	//Basicly, if the reader has not passed the § symbol, continue adding it to the extracted tree string, otherwise stop adding
	//as the tree text has been passed.
		if(chCompressed != '§' && extractionComplete == false)
		{
		extractedTree =   extractedTree + chCompressed ;
		}
		if(chCompressed == '§')
		{
		extractionComplete = true;
		}
	}
	finCompressed.close();


	//New node created will act as the top node of the tree

	HuffNodeAuto *newTree = new HuffNodeAuto(' ',NULL,NULL);  
	//the tree text is then inserted into the HuffNodeAuto member function createTree, see implementation cpp file for further explaination.
	newTree = newTree->createTree(extractedTree);
	//Now that the tree has be generated based off the extracted text from the compressed file we must do a pre-order traversal
	//to determine the symbols and appropriate binary code that are assigned to those symbols(GetCode function).
	newTree->root = newTree;
	newTree->getCode();




	//DECODING USING AUTO TREE
	//We will now reuse the decompressBinary.txt file as there is no point to converting the compressed file again
	//as this can be done without the use of any tree.

	//I will not explain much about below as we are just reusing code used in task 7, only with the tree generated from text instead of the 
	//tree on top of the priority queue.
	char chDeCompressedBinary;
	string binaryTotalAuto = "";
	string decodeAuto = "";
	fstream finDeCompressedBinary("decompressedBinary.txt", fstream::in);
	//Now using the auto tree we will 
	while (finDeCompressedBinary >> noskipws >> chDeCompressedBinary) 
	{ 
		
		binaryTotalAuto = binaryTotalAuto + chDeCompressedBinary;

		for(newTree->iter = newTree->mainMap.begin(); newTree->iter !=  newTree->mainMap.end(); newTree->iter++)
		{
			if(newTree->iter->second  != binaryTotalAuto)
			{
				
			}
			else//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@TASK 8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			{
				
				binaryTotalAuto = "";
				decodeAuto = decodeAuto + newTree->iter->first;
			}
		}


	}

	createFile("decompressedAutoVersion.txt", decodeAuto);
	cout << "Compression and decompression complete." << endl;
	}
	else
	{
		cout << "Please create a data.txt file in the same directory as this program, to run this program and fill it with text." << endl;
		}
	system("pause");
	return 0;

}

