// CPP program to implement hashing with chaining
#include<iostream>
#include<sstream>
#include "hash.hpp"
using namespace std;

HashTable::HashTable()
{
	XUser** hasharray = new XUser*[26];
	for(int i = 0; i < 26; i++){
		hasharray[i] = nullptr;
	}
	this->table = hasharray;
	this->tableSize = 26;
	this->numCollision = 0;
}

XUser* HashTable::createUser(string username, string userBio)
{
	BST* temp = new BST();
	XUser* user = new XUser;
	user->bst = temp;
	user->userBio = userBio;
	user->username = username;
	user->postCount = 0;
	user->next = nullptr;
	return user;
}

unsigned int HashTable::hashFunction(string username)
{
	unsigned int location = 0;
	for(char character : username){
		location = location + character;
	}
	location = location % tableSize;
	return location;
}


//function to insert a new user into hash table (posts inserted separately)
XUser* HashTable::insertUser(string username, string userBio)
{
	XUser* user = createUser(username, userBio);
	unsigned int location = hashFunction(username);
	XUser* temp = table[location];
	while(temp != nullptr)
	{
		if(temp->username == username){
			return NULL;
		}
		temp = temp->next;
	}
	if(table[location] == nullptr){
		table[location] = user;
		return user;
	}else{
		user->next = table[location];
		table[location] = user;
		numCollision = numCollision + 1;
		return user;
	}
}

XUser* HashTable::searchUser(string username){
	unsigned int location = hashFunction(username);
	XUser* user = table[location];
	while(user){
		if(user->username == username){
			return user;
		}
		user = user->next;
	}
	return NULL;
}

void HashTable::printUsers(){
	XUser* user;
	for(int i = 0; i < tableSize; i++){
		cout << i << "|";
		user = table[i];
		while(user){
			cout << user->username<< "-->";
			user = user->next;
		}
		cout<<user<<endl;
	}
}

void HashTable::printAllPostByUser(string username) 
{
	XUser* user = searchUser(username);
	if(!user){
		cout<<"User does not exit, try again..."<<endl;
		return;
	}
	cout<<user->username << ":" << endl;
	cout << "| userBio:" << user->userBio << endl;
	cout << "| postCount:" << user->postCount << endl;
	cout << "| Posts:" << endl;
	user->bst->displayPosts();
	return;
}

void HashTable::printMostLikedPost() 
{
	XUser* temp_user;
	XPost* liked = nullptr;
	XPost* post;
	XUser* user;
	for(int i = 0; i < tableSize; i++){
		temp_user = table[i];
		while(temp_user){
			post = temp_user->bst->mostPopular();
			if(liked){
				if(post->likes > liked->likes){
					user = temp_user;
					liked = temp_user->bst->mostPopular();
				}
			}else{
				liked = post;
			}
			temp_user = temp_user -> next;
		}
	}
	cout<< " Most liked post by:" << user->username << endl;
	cout << "| userBio:" << user->userBio << endl;
	cout << "| postCount:" << user->postCount << endl;
	cout << "| Post:" << endl;
	cout << liked->postedTime << ":" << endl;
	cout <<"__| likes:" << liked->likes << endl;
	cout << "__| " << liked->xContents << endl;

}

int HashTable::longestChain() 
{
	int longest = 0;
	int count = 0;
	XUser* temp_user;
	for(int i = 0; i < tableSize; i++){
		temp_user = table[i];
		count = 0;
		while(temp_user){
			count = count + 1;
			temp_user = temp_user -> next;
		}
		if(count > longest){
			longest = count;
		}
	}
	return longest;
}
    
