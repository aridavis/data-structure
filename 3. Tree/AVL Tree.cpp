#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	int value;
	node *left, *right;
	
	//Tambahin Height
	int height;
};

// Tambahan Buat AVL
int findMax(int a, int b){
	return a > b ? a : b;
}

int getHeight(node *root){
	// Kita Pake function ini, karena jikalau root kita NULL,
	// Codingan kita akan error karena dia mengakses memori yang belum teralokasikan
	
	if(root != NULL){
		return root->height;
	}
	return 0;
}


// Sebelum kalian makin bingung apa itu rotate,
// Saya beritahu dulu, Rotate itu bukan berarti kita muter treenya
// Tapi, kita hanya mengganti left sama rightnya
// Lihat Gambar yang sudah saya kasih

node *rightRotate(node *y){
	node *x = y->left;
	node *t2 = x->right;
	
	// Ganti Kiri Kanannya
	
	x->right = y;
	y->left = t2;
	
	// Update Height lagi
	y->height = findMax(getHeight(y->left), getHeight(y->right)) + 1;
	x->height = findMax(getHeight(x->left), getHeight(x->right)) + 1;
	
	return x;
}

node *leftRotate(node *x){
	node *y = x->right;
	node *t2 = y->left;
	
	x->right = t2;
	y->left = x;
	
	y->height = findMax(getHeight(y->left), getHeight(y->right)) + 1;
	x->height = findMax(getHeight(x->left), getHeight(x->right)) + 1;
	
	return y;
}

// Mencari Keseimbangan untuk menentukan apakah tree harus di rotate atau tidak
int getBalance(node *root){
	if(root == NULL){
		return 0;
	}
	return getHeight(root->left) - getHeight(root->right);
}




node *createNode(int value){
	node *temp = (node*)malloc(sizeof(node));
	temp->left = temp->right = NULL;
	temp->value = value;
	
	//Tambahin Inisialisasi Height
	temp->height = 1;
	
	return temp;
}

// Step Push
// 1. Insert BST Biasa
// 2. Update Height
// 3. Balancekan Data

node* push(node *root, int val){
	
	if( root == NULL){
		return createNode(val);
	}
	
	else if(val < root->value){
		root->left = push(root->left, val);
	}
	
	else if(val > root->value){
		root->right = push(root->right, val);
	}
	else {
		// Supaya tidak ada duplikat, di sini kita harus masukin ke dalam else
		// Kalau di codingan BST saya, saya tidak masukin ke else
		return root;	
	}
	
	root->height = 1 + findMax(getHeight(root->left), getHeight(root->right));
	
	int balance = getBalance(root);
	
	if (balance > 1 && val < root->left->value){
		return rightRotate(root);
	}
	else if(balance < -1 && val > root->right->value){
		return leftRotate(root);
	}
	else if(balance > 1 && val > root->left->value){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	else if(balance < -1 && val < root->right->value){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}

node *findPredecessor(node *root){
	root = root->left;
	while(root && root->right != NULL){
		root = root->right;
	}
	return root;
}

node *pop(node *root, int val){
	if (root == NULL){
		return NULL;
	}
	else if(val < root->value){
		root->left = pop(root->left, val);
	}
	else if(val > root->value){
		root->right = pop(root->right, val);
	}
	else{

		if(root->left == NULL){
			node *temp = root->right;
			free(root);
			return temp;
		}
		else if(root->right == NULL){
			node *temp = root->left;
			free(root);
			return root->left;
		}

		else{
			node *temp = findPredecessor(root);
			root->value = temp->value;
			root->left = pop(root->left, temp->value);
		}
		return root;
	}
	
	// Ini sama seperti Insert
		
	if (root == NULL){
		return NULL;
	}

	root->height = 1 + findMax(getHeight(root->left), getHeight(root->right));
	
	int balance = getBalance(root);
	
	if (balance > 1 && val < root->left->value){
		return rightRotate(root);
	}
	else if(balance < -1 && val > root->right->value){
		return leftRotate(root);
	}
	else if(balance > 1 && val > root->left->value){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	else if(balance < -1 && val < root->right->value){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}

void inorder(node* root){
	if(root != NULL){
		inorder(root->left);
		printf("%d\n", root->value);
		inorder(root->right);
	}
}

void preorder(node* root){
	if(root != NULL){
		printf("%d\n", root->value);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(node* root){
	if(root != NULL){
		postorder(root->left);
		postorder(root->right);
		printf("%d\n", root->value);
	}
}

int main(){
	node *root = NULL;
	root = push(root, 1);
	root = push(root, 2);
	root = push(root, 3);
	root = push(root, 4);
	root = push(root, 5);
	root = pop(root, 2);
	inorder(root);
	return 0;
}
