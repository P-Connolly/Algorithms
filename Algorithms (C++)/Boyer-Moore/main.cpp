//X00081023
//Paul Connolly
//ADS 2 Lab 9

#include <string>
#include <map>
#include <iterator>
#include <iostream>
using namespace std;


void preProcess(string text, string pattern,map<char, int> &pString,map<char, int> &tString, int &max)
{
	
	map<char, int>::iterator pIter;
	map<char, int>::iterator tIter;

	char character = ' ';
	//Used to jump when character in the text matches SOME character in the pattern and not the back character
	for(int x = 0;x < pattern.length();x++)
	{
		character = pattern[x];
		pString[character] = x;
	}
	//Used to find the best starting point
	for(int x = 0;x < text.length();x++)
	{
		
		character = text[x];

		if(tString[character] == NULL)
		{
		tString[character] = x;
		}
	}
	//getting max start distance
		
	for (tIter = tString.begin(); tIter != tString.end(); tIter++)
	{
		for (pIter = pString.begin(); pIter != pString.end(); pIter++)
		{
			if(tIter->first == pIter->first)
			{
				if(max < tIter->second)
				max = tIter->second;
			}
		}
	}

};

int postProcess(string text, string pattern,map<char, int> &pString, int &max)
{
	
	string changingPattern = pattern;
	int size = pattern.size() - 1;
	int patternChecker = 0;
	int check = 0;
	map<char, int>::iterator iter;


	for(int x = max;x < text.length();x)
	{
		//Character matches last character in pattern
		if(changingPattern.back() == text[x])
		{
			
			int foundCount = 0;
			x = x - 1;
			//temp string used here
			changingPattern = changingPattern.substr(0, changingPattern.size()-1);
			changingPattern.back();
			for(int z = 0;z<(pattern.size() - 1);z++)
			{
				

				if(changingPattern.back() == text[x])
				{

					
					x = x - 1;			
					
					changingPattern = changingPattern.substr(0, changingPattern.size()-1);
				
					foundCount++;
					//If pattern found
					if(foundCount == pattern.size() - 1)
					{
						
						x++;
						cout << "First Character of pattern in the text: " <<text[x] << endl;
						return x;
					}
					
				}
				else
				{
					//If mismatched, jump size of pattern
					changingPattern = pattern;
					x = x + pattern.size();
					z = pattern.size();
					
				}
				
			}
		}

		else
		{
			
			//Loop to check if the text checked is infact a letter in the pattern at all
			bool noMatch = true;
			for (iter = pString.begin(); iter != pString.end(); iter++)
			{
				if(iter->first == text[x])
				{
					
					noMatch = false;
					x = x + (pattern.size() - iter->second - 1);
				}
			}
			//statement to jump the size of the pattern if there is no match at all
			if(noMatch == true)
			{
				
				x = x + pattern.size() - 1;
			}
		}
		
	}

	

		return -1;
};




int main()
{
	int max = 0;
	string text = "peter piper picked a peck of pickled";
	string pattern = "pickle";
	cout << "Text searched: " << text << endl;
	cout << "Pattern used: " << pattern << endl;
	map<char, int> pString;
	map<char, int> tString;
	cout << endl << "Pre-Process and post-process running..." << endl << endl;
	cout << "Result: " << endl;
	preProcess(text, pattern, pString, tString, max);
	cout << "Starting index point based on pre-process: " << max << endl;
	cout << "Index: " << postProcess(text, pattern, pString, max) << endl;


	system("pause");
	return 0;
}


/*Rules 
Occurance One: If mismatched completely jump the size of the pattern from the position checked
Occurance Two: if one character matches a character in the pattern, jump the size of the pattern minus the location of the character matched
*/