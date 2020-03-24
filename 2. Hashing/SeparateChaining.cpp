#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Hash Table
// Kita katakan, hashTable kita butuh size sebanyak 26 
// Karena Separate Chaining adalah metode hashing dengan menggunakan linked list
// Itu berarti kita harus menyediakan 26 head


struct node{
	char name[50];
	//Kita gunakan single linked list saja
	node *next;
}*head[26], *tail[26];

//Membuat Node Kosong
node *createNode(char *name){
	node *temp = (node*)malloc(sizeof(node));
	temp->next = NULL;
	strcpy(temp->name, name);
	return temp;
}

// Hash Function
int hashFunction(char *name){
	
	// Kita katakan, size dari hashTable itu harusnya 26
	// Kita Katakan Function Kita adalah
	// F(x) = (SUM_ASCII * 2) % 26
	// Kita modulokan dengan 26 karena size dari hashTable harusnya 26
	// Dengan kita modulo 26, hasil dari hash function ini pastilah antara 0 sampai 25
	
	int totalAscii = 0;
	int nameLen = strlen(name);
	for(int i = 0 ; i < nameLen ; i++){
		totalAscii += name[i];
	}	
	return (totalAscii * 2) % 26;
	
	// Baca kodingan insertData, kalian pasti mengerti
}

void pushTail(int headIndex, char *name){
	
	node* newData = createNode(name);
	
	if(head[headIndex] == NULL){
		head[headIndex] = tail[headIndex] = newData;
	}
	
	else{
		tail[headIndex]->next = newData;
		tail[headIndex] = newData;
	}
}

void insertData(char *name){
	// Kita Cari Dulu Hasil Hashingnya
	int hashIndex = hashFunction(name);
	
	// Barulah kita validasi
	// Selagi head[index] keiisi, maka kita tinggal push tail saja.
	pushTail(hashIndex, name);
}

void printHashTable(){
	// Di sini, kita print hanya yang berisi ya..
	for(int i = 0; i < 26; i++){
		if (head[i] != NULL){
			printf("Index %d:\n", i);
			
			// Kita print semua isi head[index]
			node *current = head[i];
			while (current){
				printf("   - %s\n", current->name);
				current = current->next;
			}
			printf("\n");
		}
	}
}

int main(){
	
	insertData("Ari Davis");
	insertData("sivaD irA");
	insertData("Davis");
	insertData("Fugo");
	insertData("Defa");
	printHashTable();
	
	return 0;
}
