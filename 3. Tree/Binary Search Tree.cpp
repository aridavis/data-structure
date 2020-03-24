#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	int value;
	node *left, *right;
};

// Membuat Node Kosong
node *createNode(int value){
	node *temp = (node*)malloc(sizeof(node));
	temp->left = temp->right = NULL;
	temp->value = value;
	return temp;
}

node* push(node *root, int val){
	
	//Menandakan kalau dia ga punya anak lagi
	if( root == NULL){
		return createNode(val);
	}
	
	//Seandainya value lebih kecil dibanding node sekarang
	else if(val < root->value){
		root->left = push(root->left, val);
	}
	
	else if(val > root->value){
		root->right = push(root->right, val);
	}
	// Seandainya datanya sama, maka tidak ada yang diubah
	return root;
}

// Untuk Delete Data, kita perlu mencari successor atau deccessor

struct node *findPredecessor(node *root){
	root = root->left;
	while(root && root->right != NULL){
		root = root->right;
	}
	return root;
}

struct node *pop(node *root, int val){
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
		// Jikalau data ditemukan
		// ada 3 kondisi
		
		//Kalau hanya ada anak kanan
		if(root->left == NULL){
			node *temp = root->right;
			free(root);
			return temp;
		}
		// Kalau hanya ada anak kiri
		else if(root->right == NULL){
			node *temp = root->left;
			free(root);
			return root->left;
		}
		
		// 2 Kondisi di Atas, berlaku untuk jika kedua anaknya kosong
		
		// Ini jika dia punya 2 anak
		else{
			// Kita harus mengganti nilai root sekarang dengan predecessor si root
			// Predecessor adalah anak terkanan dari anak kiri si root
			// Successor adalah anak terkiri dari anak kanan si root
			// Kalo kurang ngerti, semoga ini membantu, Root adalah Kakek, anak kiri / anak kanan adalah Bapak,
			// anak terkiri / anak terkanan adalah anak cucu si Root
			
		
			node *temp = findPredecessor(root);
			root->value = temp->value;
			root->left = pop(root->left, temp->value);
			
			// di sini saya menggunakan predecessor, seandainya saya menggunakan succesor
			// maka yang saya pop adalah root->right
		}
		return root;
	}
}

// Untuk Output terbagi menjadi 3
// Inorder, Preorder dan Postorder
// Perbedaannya adalah peletakan printf

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
	root = push(root, 12);
	root = push(root, 13);
	root = push(root, 15);
	root = push(root, 20);
	root = push(root, 17);
	root = push(root, 25);
	root = push(root, 18);
	root = push(root, 19);
	inorder(root);
	return 0;
}
