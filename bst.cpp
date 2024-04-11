#include "bst.hpp"

BST::BST() {
	root = nullptr;
	size = 0;
}
void BST::BST_destructor(XPost* current){
    if(!current){
        return;
    }
    BST_destructor(current->left);
    BST_destructor(current->right);
    delete current;
    current = nullptr;
    return;
}
BST::~BST() {
	BST_destructor(root);
}

XPost* BST::createPost(float time, string content, int likes) 
{
	XPost* post = new XPost;
	post->likes = likes;
	post->postedTime = time;
	post->xContents = content;
	post->left = nullptr;
	post->right = nullptr;
	return post;
}

void BST::insertPost(float time, string content, int likes) 
{
	XPost* post = createPost(time, content, likes);
	if(!root){
		root = post;
		return;
	}
	insertHelper(root,post);
}

void BST::insertHelper(XPost* rt, XPost* pst) 
{
	if(rt->postedTime >= pst->postedTime){
		if(rt->left){
			return insertHelper(rt->left, pst);
		}else{
			rt->left = pst;
		}
	}else{
		if(rt->right){
			return insertHelper(rt->right, pst);
		}else{
			rt->right = pst;
		}
		
	}
	return;
}

void BST::displayPosts() 
{
	displayHelper(root);
}

void BST::displayHelper(XPost* rt) // Inorder Traversal
{
	if(!rt){
		return;
	}
	displayHelper(rt->left);
	cout<< "time: " << rt->postedTime << endl;
	cout << "likes: " << rt-> likes << endl;
	cout << "XConents: " << rt->xContents << endl;
	displayHelper(rt->right);
}

XPost* BST::mostPopular() 
{
	XPost* most_liked = root;
	mostPopularHelper(root, most_liked);
	return most_liked;
}

void BST::mostPopularHelper(XPost* rt, XPost*& mostLiked) 
{
	if(rt == nullptr){
		return;
	}
	mostPopularHelper(rt->left, mostLiked);
	if(rt->likes > mostLiked->likes){
		mostLiked = rt;
	}
	mostPopularHelper(rt->right, mostLiked);
	return;
}
