#include <iostream>
#include <string>
#include "minHeapify.hpp"
#include "hash.hpp"

using namespace std;

#define QUIT 9

void displayMenu() {
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "0: Exit" << endl;
	cout << "1: Build minHeap" << endl;
	cout << "2: Build linked hash table" << endl;
	cout << "3: Add XUser" << endl;
	cout << "4: Add post by user" << endl;
	cout << "5: Display all tweets" << endl;
	cout << "6: Display all users" << endl;
	cout << "7: Display all posts by user" << endl;
	cout << "8: Display the most liked post" << endl;
	cout << "9: Performance metrics" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

tweet* getTweet(ifstream& infile) 
{
	int print = 0;
	char c;
	string quote;
	tweet* newTweet = new tweet;
	if (print) cout << "newTweet: " << endl;

	//Get time
	string tempTime;
	getline(infile, tempTime, ',');
	tempTime.erase(0,6);
	if (print) cout << "\tpostedTimeString: " << tempTime << endl;
	newTweet->postedTime = stof(tempTime);
	if (print) cout << "\tpostedTime: " << newTweet->postedTime << endl;
	//Get content
	if (infile.peek() == '"') {
		infile.get(c);
		if (infile.peek() == '"') {
			infile.get(c);
			if (infile.peek() == '"') {
				infile.get(c);

				if (infile.peek() == '"') { // internal quote?
					infile.get(c);
					if (infile.peek() == '"') {
						infile.get(c);
						getline(infile, quote, '"');
						while (infile.peek() == '"')
							getline(infile, quote, '"');
					}
				} 
				newTweet->tweetContent = quote;
				getline(infile, quote, '"');
				newTweet->tweetContent.append(quote);
				if (print) cout << "\tcontent: " << newTweet->tweetContent << endl;
				infile.get(c);
				while (c == '"')
					infile.get(c);
			}
		}
	}
	//Get username
	getline(infile, newTweet->username, ',');
	if (print) cout << "\tusername: " << newTweet->username << endl;
	//Get userBio
	if (infile.peek() == '"') {
		infile.get(c);
		if (infile.peek() == '"') {
			infile.get(c);
			if (infile.peek() == '"') {
				infile.get(c);
				getline(infile, quote, '"');
				newTweet->userBio.append(quote);
				//cout << "\tbio: " << newTweet->userBio << endl;
				infile.get(c);
				while (c == '"')
					infile.get(c);
			} else {
				infile.get(c);
				while (c == '"')
					infile.get(c);
			}
		}
	}
	//Get likes
	string tempLikes;
	getline(infile, tempLikes);
	if (print) cout << "\ttempLikes: " << tempLikes << endl;
	newTweet->likes = stoi(tempLikes);
	if (print) cout << "\tlikes: " << newTweet->likes << endl;
	return newTweet;
}

void parseCSV(string filename, MinHeap* myHeap) 
{
	ifstream infile;
	infile.open(filename);
	string tweetLine;
	getline(infile, tweetLine); // clear header 
	tweet* newTweet;
	while (infile.peek() != -1) {
		newTweet = getTweet(infile);

		myHeap->push(newTweet);
	}
}


int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "Incorrect number of arguments" << endl;
		return 1;
	}
	string filename = argv[1];

	int ch = 0;
	float prev = 0;
	string chs;
	string user;
	MinHeap* myHeap = new MinHeap();
	HashTable* myHT = new HashTable();
	while (ch != QUIT) {
		displayMenu();
		cout << "Select menu option >> ";
		ch = 0;
		getline(cin, chs);
		if (chs != "" && chs.front() >= 48 && chs.front() <= 57) 
			ch = stoi(chs);
		switch (ch) {
			case 0: {
				cout << "Goodbye!" << endl;
				return 0;
			}
			case 1:	{ // Build minHeap
				cout << "Parsing Twitter database (" << filename << ") into MinHeap" << endl;
				parseCSV(filename, myHeap);
				break;
			}
			case 2: { // Build linked hash table
				if (myHeap->size() == 0) {
					cout << "Build heap first..." << endl;
					break;
				}
				while (myHeap->size() > 0) 
				{
					tweet* twt = myHeap->pop();
					XUser* xu = myHT->searchUser(twt->username);
					if (!xu)
						xu = myHT->insertUser(twt->username, twt->userBio);
					xu->postCount++;
					xu->bst->insertPost(twt->postedTime, twt->tweetContent, twt->likes);
				}
				break;
			} 
			case 3: { // Add XUser
				cout << "Adding new XUser..." << endl;
				cout << "\tProvide XUser name >> ";
				string username;
				getline(cin, username);
				cout << "\tProvide XUser bio >> ";
				string userBio;
				getline(cin, userBio);
				myHT->insertUser(username, userBio);
				break;
			}
			case 4: { // Add post by user
				cout << "Enter username: ";
				getline(cin, user);
				XUser* xu = myHT->searchUser(user);
				if (!xu) {
					cout << "Invalid user, try again..." << endl;
					break;
				}
					
				int time = 1;
				int likes = 0;
				cout << "Enter post content: ";
				string content;
				getline(cin, content);
				xu->postCount++;
				xu->bst->insertPost(time, content, likes);
				break;
			}
			case 5: { // Display all tweets
				if (myHeap->size() == 0) {
					cout << "Build heap first..." << endl;
					break;
				}
				myHeap->printHeap();
				prev = 0;
				for (int i=0; i<10; i++) {
					tweet* twt = myHeap->pop();
					if (prev > twt->postedTime)	{
						cout << "Heap out of order: " << prev << " > " << twt->postedTime << endl;
						return 1;
					}
					prev = twt->postedTime;
				}
				break;
			}
			case 6: { // Display all users
				myHT->printUsers();
				break;
			}
			case 7: { // Display all posts by user
				cout << "Enter username: ";
				getline(cin, user);
				myHT->printAllPostByUser(user);
				break;
			}
			case 8: {
				myHT->printMostLikedPost();
				break;
			}
			case 9: {
				cout << "Performance Metrics: " << endl << endl;

				cout << "-> minHeap: " << endl;
				cout << "\t|capacity: " << myHeap->cap() << endl;
				cout << "\t|currentSize: " << myHeap->size() << endl << endl;

				cout << "-> hashTable: " << endl;
				cout << "\t|collisions: " << myHT->collisions() << endl;
				cout << "\t|longestChain: " << myHT->longestChain() << endl;
				break;
			}

			default:
				cout << "Enter a valid option" << endl;
				break;
		}

	}
	

	return 0;
}
