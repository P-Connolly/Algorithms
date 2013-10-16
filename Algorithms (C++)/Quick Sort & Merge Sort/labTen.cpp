//Paul Connolly
//X00081023
//Lab 10
#include <iostream>
#include <string>
using namespace std;

int* quickSort(int table[], int size)
{
	//Counters used to remember the size of the new arrays, and to help asign values to them within loops.
	int lCount = 0;
	int gCount = 0;
	int eCount = 0;
	//Will hold the resulting combined array.
	int *result = new int[size];
	//Base case
	if(size <= 1)
	{
		return table;
	}
	//Default pivot value is the second last element in the array
	int pivot = table[size - 1];
	//This for loop below would be unnecessary if we were to use vectors, rather than array's in this example. It is used to find the appropriate size of the new arrays.
	for(int x = 0;x < size;x++)
	{
		if(table[x] < pivot)
		{
			lCount++;
		}
		else if(table[x] > pivot)
		{
			gCount++;
		}
		else
		{
			eCount++;
		}
	}

	int *lesser = new int[lCount];
	int *greater = new int[gCount];
	int *equal = new int[eCount];
	//Resetting counters, now using them to hold final size and to aid input into the array.
	lCount = 0;
	gCount = 0;
	eCount = 0;
	//Basicly, if value is less than pivot, insert into lesser array, if greater, insert into greater array, else input into equal array.
	for(int x = 0;x < size;x++)
	{
		if(table[x] < pivot)
		{
			lesser[lCount] = table[x];
			lCount++;
		}
		else if(table[x] > pivot)
		{
			greater[gCount] = table[x];
			gCount++;
		}
		else
		{
			equal[eCount] = table[x];
			eCount++;
		}
	}
	//Then repeat the process until base case is met, using recursion.
	lesser = quickSort(lesser,lCount);
	greater = quickSort(greater,gCount);
	//Second counter is used to aid insertion into resulting array.
	int lCount2 = 0;
	int gCount2 = 0;
	int eCount2 = 0;
	//The 3 array's are now inserted into the result array.
	for(int x = 0;x < lCount;x++)
	{

		result[x] = lesser[lCount2];
		lCount2++;
	}
	for(int x = lCount;x < lCount+eCount;x++)
	{

		result[x] = equal[eCount2];
		eCount2++;
	}
	for(int x = lCount+eCount;x < size;x++)
	{

		result[x] = greater[gCount2];
		gCount2++;
	}
	//Array returned.
	return result;

}

int* merge(int left[], int right[], int lLength, int rLength)
{
	//Resulting array used to hold final array to be returned.
	int *result = new int[lLength+rLength];
	//Counters used to aid in insertion and used to store final size of each new array.
	int count = 0;
	int count1 = 0;
	int count2 = 0;
	//Basicly, if count is lesser than the total size of the entered array, continue on.
	while(count < lLength+rLength)
	{
		//If BOTH arrays are still not filled, then use this if statement.
		if(count1 < lLength && count2 < rLength)
		{
			//if left is less than right, insert this first into the result array, then increment the left count.
			if(left[count1] < right[count2])
			{
				result[count] = left[count1];
				count1++;
			}
			else //Opposite
			{
				result[count] = right[count2];
				count2++;
			}
		}
		//If left count is not full, then insert the rest of left into the result array, as the right side must be already inserted.
		else if(count1 < lLength)
		{
			result[count] = left[count1];
			count1++;
		}
		//Opposite to last comment.
		else if(count2 < rLength)
		{
			result[count] = right[count2];
			count2++;
		}
		//Increment result counter
		count++;
	}
	return result;
}
//This function halfs array's until the base case is met.
int* mergeSort(int arrayToSort[],int startIndex, int lengthToSort)
{

	int firstCount = 0;
	int secondCount = 0;
	int tempStart = startIndex;
	int *s1;
	int *s2;
	int mod = 0;
	//Used to check if the length of the array is an even number, if not the size of the left and right arrays, won't be equal.
	if(lengthToSort % 2 > 0)
	{
		mod = 1;
	}
	int arraySize1 = lengthToSort/2;
	int arraySize2 = lengthToSort/2 + mod;
	//base case
	if(lengthToSort < 2)
	{
		return arrayToSort;
	}

	else
	{
		//
		s1 = new int[arraySize1];	
		s2 = new int[arraySize2];
		//These two for loops simply half the entered array into two smaller arrays. Thats it.
		for(int x = 0;x < arraySize1;x++)
		{

			s1[firstCount] = arrayToSort[tempStart];

			tempStart++;
			firstCount++;
		}

		for(int i = 0;i < arraySize2;i++)
		{

			s2[secondCount] = arrayToSort[tempStart];

			tempStart++;
			secondCount++;
		}
		//The process is then repeated, when the resulting arrays are used are arguements and mergesort function is called recursively.
		s1 = mergeSort(s1,0,arraySize1);
		s2 = mergeSort(s2,0,arraySize2);

	}

	//The merge function is then called to combine said arrays, and sort them.
	return merge(s1,s2,arraySize1,arraySize2);


};




int main()
{
	const int size = 10;
	//One array for mergesort, one for quick sort.
	int arraySortMerge[size] = {3,2,1,8,7,6,5,4,9,10};
	int arraySortQuick[size] = {3,2,1,8,7,6,5,4,9,10};
	int *y;
	int *x;
	//Merge Sort before-After
	cout << "Merge-sort algorithm:" << endl;
	for(int x = 0;x < size;x++)
	{
		cout << "Unsorted: " << arraySortMerge[x] << endl;
	}

	cout << endl;
	//Mergesort called
	y = mergeSort(arraySortMerge,0,size);

	for(int x = 0;x < size;x++)
	{
		cout << "Sorted: " << y[x] << endl;
	}
	//Quick Sort before-after
	cout << endl << "Quick-sort algorithm: " << endl;
	for(int x = 0;x < size;x++)
	{
		cout << "Unsorted: " << arraySortQuick[x] << endl;
	}
	cout << endl;
	//Quicksort called
	x = quickSort(arraySortQuick,size);
	for(int i = 0;i < size;i++)
	{
		cout << "Sorted: " << x[i] << endl;
	}
	system("pause");
	return 0;
};

