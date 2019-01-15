/*Name: Ýbrahim
Surname: Karahan
Nu: 150160550
Debugging with SSH: g++ Source.cpp -std=c++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

int mod = 17863; // keeping size of size of m
int mod2 = 21929; // keeping size of size of m

class Vocab{ // keeping the value of vocab.txt
public:
	string value; // keeping the string
	int hashIndex;
	int key; // keeping line number as a key
	bool placed;
};

class Search{ // keeping the value of search.txt
public:
	string value; // keeping the string
	int key; // keeping line number as a key
	int hashIndex;
};

Vocab *vocabArray = new Vocab[13423];
Vocab *hashTable = new Vocab[100000]; // this the optimum number for hash table
Search *searchArray = new Search[13423];

void makeEmpty(Vocab array[]){ // make the array empty and make easy for isEmpty
	for (int i = 0; i < 100000; i++)
	{
		array[i].value = " ";
		array[i].hashIndex = 0;
		array[i].key = 0;
		array[i].placed = false;
	}
}

int hash1(int key, int mod){ // linear hash func
	int resultOfHash;
	resultOfHash = key % mod;
	return resultOfHash;
}

int hash2(int key, int mod){ // double hash func
	int resultOfHash;
	int p = 5;
	resultOfHash = p - (key % p);
	return resultOfHash;
}

int universalHash(int key,int mod){ // universal hash func 
	int index = 0;
	int decomposition[3];
	int randomA[3];
	int universalHash = 0;
	while (key > 0) { // decomposition the number 
		int num = key % 100;
		decomposition[index] = num;
		key /= 100;
		index++;
	}
	if (index == 2){ // if number has two number
		decomposition[2] = 0;
	}
	else if (index == 1){  // if number has one number
		decomposition[1] = 0;
		decomposition[2] = 0;
	}
	else if (index == 0){ // if number has no number for example keu value is 0
		decomposition[0] = 0;
		decomposition[1] = 0;
		decomposition[2] = 0;
	}
	for (int i = 0; i < 3; i++)
	{
		randomA[i] = rand() % mod-1;
	}
	for (int i = 0; i < 3; i++)
	{
		universalHash += (decomposition[i] * randomA[i]) % mod;
	}
	return universalHash;
}

bool isEmpty(Vocab  array[], int hash){ // control array for given index is empty or not 
	if (array[hash].placed == false)
		return true;
	else
		return false;
}

bool find1(Search search, Vocab hashTable){ // find search on hashtable
	if (search.hashIndex == hashTable.hashIndex && search.value == hashTable.value){
		return true;
	}
	else{
		return false;
	}
}

bool find2(Search search, Vocab hashTable){ // just for writing linear search 
	if (search.value == hashTable.value){
		return true;
	}
	else{
		return false;
	}
}

void linearHashing(Vocab array[], int size, int mod){ // linear hashing 
	int sumOfcollusion = 0;
	int collution = 0;
	makeEmpty(hashTable); //  prepare hashtable 
	for (int i = 0; i < size; i++)
	{
		vocabArray[i].hashIndex = hash1(vocabArray[i].key, mod); // find hash value
		if (isEmpty(hashTable, vocabArray[i].hashIndex)){
			hashTable[vocabArray[i].hashIndex].value = vocabArray[i].value;
			hashTable[vocabArray[i].hashIndex].hashIndex = vocabArray[i].hashIndex;
			hashTable[vocabArray[i].hashIndex].key = vocabArray[i].key;
			hashTable[vocabArray[i].hashIndex].placed = true;
			vocabArray[i].placed = true;
			//cout << "array is empty and element is located to hash table." << endl;
		}
		else{
			//cout << "index is full." << endl;
			while (!isEmpty(hashTable, vocabArray[i].hashIndex + collution)){ // increment collution until find
				collution++;
			}
			//cout << "collusion is solved" << endl;
			//cout << "collution number:" << collution << endl;
			hashTable[vocabArray[i].hashIndex + collution].value = vocabArray[i].value;
			hashTable[vocabArray[i].hashIndex + collution].hashIndex = vocabArray[i].hashIndex;
			hashTable[vocabArray[i].hashIndex + collution].key = vocabArray[i].key;
			hashTable[vocabArray[i].hashIndex + collution].placed = true;
			vocabArray[i].placed = true;
		}
		sumOfcollusion = sumOfcollusion + collution;
	}
	cout << "Collusion Number For Linear Hashing:" << sumOfcollusion << endl;
}

void linearSearching(Search searchArray[], Vocab hashTable[], int sizeOfSearch, int sizeOfHashtable, int mod){ // linear searching
	int sumOfcollusion = 0;
	for (int i = 0; i < sizeOfSearch; i++)
	{
		int search_index = hash1(searchArray[i].key, mod); // find hash value
		searchArray[i].hashIndex = search_index;
		if (find1(searchArray[i], hashTable[search_index])){
			//cout << "element is found on index:" << search_index << endl;
		}
		else{
			for (int j = 0; j < sizeOfHashtable; j++)
			{
				sumOfcollusion++;
				if (searchArray[i].value == hashTable[j].value){
					break;
				}
				else if (sumOfcollusion == sizeOfHashtable){ 
					cout << "this word "<< searchArray[i].value <<" is not in the vocab.txt" << endl;
				}
				/*while (!find(searchArray[i], hashTable[search_index + collution])){ // Under normal circumtances of working hash function this part search the array 
					collution++;                                                      // but in the homework hash did not work properly.
				if (search_index + collution > sizeOfHashtable - 1){
					//cout << "this word is not in the  vocab.txt ." << endl;
					break;
				}
			    }*/
			}
		}
		
	}
	cout << "Collusion Number For Linear Hash Searching:" << sumOfcollusion << endl;
}

void doubleHashing(Vocab array[], int size, int mod){ // double hashing 
	int collution = 0;
	int sumOfcollusion = 0;
	makeEmpty(hashTable); // prepare hashtable
	for (int i = 0; i < size; i++)
	{
		vocabArray[i].hashIndex = hash1(vocabArray[i].key, mod); // find hash value
		if (isEmpty(hashTable, vocabArray[i].hashIndex)){
			hashTable[vocabArray[i].hashIndex].value = vocabArray[i].value;
			hashTable[vocabArray[i].hashIndex].hashIndex = vocabArray[i].hashIndex;
			hashTable[vocabArray[i].hashIndex].key = vocabArray[i].key;
			hashTable[vocabArray[i].hashIndex].placed = true;
			vocabArray[i].placed = true;
			//cout << "array is empty and it is located." << endl;
		}
		else{
			//cout << "collosuion occured" << endl;
			int d_hash = hash2(vocabArray[i].key, mod);
			int double_index = (vocabArray[i].hashIndex + (collution*d_hash)); // find double hash value when collusion occured
			while (!isEmpty(hashTable, double_index)){ // increment collution until find
				collution++;
				double_index = (vocabArray[i].hashIndex + (collution*d_hash));
			}
			//cout << "collusion is solved" << endl;
			hashTable[double_index].value = vocabArray[i].value;
			hashTable[double_index].hashIndex = vocabArray[i].hashIndex;
			hashTable[double_index].key = vocabArray[i].key;
			hashTable[double_index].placed = true;
			vocabArray[i].placed = true;
		}
		sumOfcollusion = sumOfcollusion + collution;
	}
	cout << "Collusion Number For Double Hashing:" << sumOfcollusion << endl;
}

void doubleHashSearching(Search searchArray[], Vocab hashTable[], int sizeOfsearch, int sizeOfHashtable, int mod){ // double hash search
	int collution = 0;
	int sumOfcollusion = 0;
	for (int i = 0; i < sizeOfsearch; i++)
	{
		int search_index = hash1(searchArray[i].key, mod); // find hash value 
		searchArray[i].hashIndex = search_index;
		if (find1(searchArray[i], hashTable[search_index])){
			//cout << "element is found on index:" << search_index << endl;
		}
		else{
			for (int j = 0; j < sizeOfHashtable; j++)
			{
				sumOfcollusion++;
				if (searchArray[i].value == hashTable[j].value){
					break;
				}
				else if (sumOfcollusion == sizeOfHashtable){
					cout << "this word "<< searchArray[i].value << " is not in the vocab.txt" << endl;
				}
			}
		}
		/*else{
			int d_hash = hash2(vocabArray[i].key, mod);  // Under normal circumtances of working hash function this part search the array 
			                                               // but in the homework hash did not work properly.
			int double_index = (vocabArray[i].hashIndex + (collution*d_hash)); // find double hash value when collusion occured
			if (!find1(searchArray[i], hashTable[search_index + collution])){ // increment collution until find
				//cout << "element is found on index:" << search_index << endl;
			}
		}*/
	}
	cout << "Collusion Number For Double Hash Searching:" << sumOfcollusion << endl;
}

void universalHashing(Vocab array[], int size,int mod){ // universal hashing 
	int collution = 0;
	int sumOfcollusion = 0;
	makeEmpty(hashTable); // prepare hashtable 
	for (int i = 0; i < size; i++)
	{
		vocabArray[i].hashIndex = universalHash(vocabArray[i].key,mod); // find hash value
		if (isEmpty(hashTable, vocabArray[i].hashIndex)){
			hashTable[vocabArray[i].hashIndex].value = vocabArray[i].value;
			hashTable[vocabArray[i].hashIndex].hashIndex = vocabArray[i].hashIndex;
			hashTable[vocabArray[i].hashIndex].key = vocabArray[i].key;
			hashTable[vocabArray[i].hashIndex].placed = true;
			vocabArray[i].placed = true;
		}
		else{
			//cout << "index is full." << endl;
			while (!isEmpty(hashTable, vocabArray[i].hashIndex + collution)){  // increment collution until find
				collution++;
			}
			//cout << "collusion is solved" << endl;
			hashTable[vocabArray[i].hashIndex + collution].value = vocabArray[i].value;
			hashTable[vocabArray[i].hashIndex + collution].hashIndex = vocabArray[i].hashIndex;
			hashTable[vocabArray[i].hashIndex + collution].key = vocabArray[i].key;
			hashTable[vocabArray[i].hashIndex + collution].placed = true;
			vocabArray[i].placed = true;
		}
		sumOfcollusion = sumOfcollusion + collution;
	}
	cout << "Collusion Number For Universal Hashing:" << sumOfcollusion << endl;
}

void universalSearching(Search searchArray[], Vocab hashTable[], int sizeOfSearch, int sizeOfHashtable,int mod){ // universal searching 

	int sumOfcollusion = 0;
	for (int i = 0; i < sizeOfSearch; i++)
	{
		int collution = 0;
		int search_index = universalHash(searchArray[i].key,mod); // find hash value 
		searchArray[i].hashIndex = search_index;
		if (find1(searchArray[i], hashTable[search_index])){
			//cout << "element is found on index:" << search_index << endl;
		}
		else{
			for (int j = 0; j < sizeOfHashtable; j++)
			{
				sumOfcollusion++;
				if (searchArray[i].value == hashTable[j].value){
					break;
				}
				else if (sumOfcollusion == sizeOfHashtable){
					cout << "this word "<< searchArray[i].value << " is not in the vocab.txt" << endl;
				}
				/*while (!find(searchArray[i], hashTable[search_index + collution])){ // Under normal circumtances of working hash function this part search the array
				collution++;                                                      // but in the homework hash did not work properly.
				if (search_index + collution > sizeOfHashtable - 1){
				//cout << "this word is not in the  vocab.txt ." << endl;
				break;
				}
				}*/
			}
		}
	}
	cout << "Collusion Number For Universal Hash Searching:" << sumOfcollusion << endl;
}
void printVocabArray(Vocab array[], int size){ // just for controlling
	for (int i = 0; i < size; i++)
	{
		cout << "value:" << array[i].value << " key:" << array[i].key << " hash:" << array[i].hashIndex << " placed:" << array[i].placed << endl;
	}
}

void printSearchArray(Search array[], int size){ // just for controlling
	for (int i = 0; i < size; i++)
	{
		cout << "value:" << array[i].value << " key:" << array[i].key << " hash:" << array[i].hashIndex << endl;
	}
}

int main(int argc, char *argv[])
{
	int sizeOfVocab = 0;
	int sizeOfSearch = 0;
	int sizeOfHashTable = 100000; // this is the optimum size for hash table
	string vocabFileName; // keeping the filname
	string searchFileName; // keeping the filname
	string vocab; // keeping the word in vocab.txt
	string search; // keeping the word in search.txt
	vocabFileName = argv[1]; // taking the argument
	searchFileName = argv[2]; // taking the argument
	ifstream excelFileVocab(vocabFileName); // file is opened for reading from vocab.txt
	if (excelFileVocab.is_open())
	{
		for (int i = 0; i < 13423; i++)
		{
			getline(excelFileVocab, vocab);
			vocabArray[i].value = vocab;
			vocabArray[i].key = i;
			vocabArray[i].hashIndex = 0;
			vocabArray[i].placed = false;
			sizeOfVocab++;
		}
		excelFileVocab.close();
	}
	else {
		cout << "Excel file is not opened." << endl;
	}

	ifstream excelFileSearch(searchFileName); // file is opened for reading from search.txt
	if (excelFileSearch.is_open())
	{	
		for (int i = 0; i < 13423; i++)
		{
			getline(excelFileSearch, search);
			searchArray[i].value = search;
			searchArray[i].key = i;
			searchArray[i].hashIndex = 0;
			sizeOfSearch++;
		}
		excelFileSearch.close();
	}
	else {
		cout << "Excel file is not opened." << endl;
	}
	cout << "Hash Number(M):" << mod << endl;
	cout << "Linear Hashing & Searching" << endl;
	linearHashing(vocabArray, sizeOfVocab, mod);
	linearSearching(searchArray, hashTable, sizeOfSearch, sizeOfHashTable, mod);
	cout << "**************************************" << endl;
	cout << "Double Hashing & Searching" << endl;
	doubleHashing(vocabArray, sizeOfVocab, mod);
	doubleHashSearching(searchArray, hashTable, sizeOfSearch, sizeOfHashTable, mod);
	cout << "**************************************" << endl;
	cout << " Universal Hashing & Searching" << endl;
	universalHashing(vocabArray, sizeOfVocab,mod);
	universalSearching(searchArray, hashTable, sizeOfSearch, sizeOfHashTable,mod);
	cout << endl;
	cout << endl;
	cout << "Hash Number(M):" << mod2 << endl;
	cout << "Linear Hashing & Searching" << endl;
	linearHashing(vocabArray, sizeOfVocab, mod);
	linearSearching(searchArray, hashTable, sizeOfSearch, sizeOfHashTable, mod);
	cout << "**************************************" << endl;
	cout << "Double Hashing & Searching" << endl;
	doubleHashing(vocabArray, sizeOfVocab, mod);
	doubleHashSearching(searchArray, hashTable, sizeOfSearch, sizeOfHashTable, mod);
	cout << "**************************************" << endl;
	cout << "Universal Hashing & Searching" << endl;
	universalHashing(vocabArray, sizeOfVocab,mod2);
	universalSearching(searchArray, hashTable, sizeOfSearch, sizeOfHashTable,mod2);

	return 0;
}
