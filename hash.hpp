#ifndef HASH_HPP
#define HASH_HPP

#include <string>
#include <fstream>
#include "bst.hpp"
using namespace std;

/*
// MUST BE LARGE ENOUGH FOR DATA SET
*/
#define M YOUR_TABLE_SIZE_VALUE_HERE

struct XUser {
	string username; 
	string userBio;
	int postCount;
	XUser* next;
	BST* bst;
};

class HashTable
{
private:
    int tableSize;  // No. of buckets (linked lists)
    // Pointer to an array containing buckets (bucket is pointer to XUser struct)
    XUser* *table;
    
    XUser* createUser(string username, string userBio);
    
    int numCollision;
public:
    HashTable();  // Constructor
	~HashTable();

	int collisions() {
		return numCollision;
	}

	/* 
	// TODO
	//   The following functions are to be completed by you
	*/
    unsigned int hashFunction(string key);
    
	XUser* insertUser(string username, string userBio);

	XUser* searchUser(string username);
    
    void printUsers();

	void printAllPostByUser(string username);

	void printMostLikedPost();

	int longestChain();
    
};

#endif
