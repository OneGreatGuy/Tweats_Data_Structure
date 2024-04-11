#include <iostream>
#include <string>
using namespace std;

struct XPost {
	int postedTime;
	string xContents;
	int likes;
	XPost* left;
	XPost* right;
};


class BST {
private:
	XPost* root;
	int size;
	
	XPost* createPost(float time, string content, int likes);
public:
	BST();
	~BST();
	void BST_destructor(XPost* current);

	void insertPost(float time, string content, int likes);

	void insertHelper(XPost* rt, XPost* pst);

	void displayPosts();

	void displayHelper(XPost* rt);
	
	XPost* mostPopular(); 

	void mostPopularHelper(XPost* rt, XPost*& mostLiked);
};
