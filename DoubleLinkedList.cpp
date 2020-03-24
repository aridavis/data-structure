#include<stdio.h>
#include<stdlib.h> // Library Untuk Malloc Nanti

struct node{
	int value;
	node *next, *prev;
}*head, *tail; // Pendeklarasian Head Tail dari sebuah list


// Untuk mendefine sebuah node baru
// Ini adalah sebuah langkah yang bernama "Extract Method"
// Karena kita membuat sebuah data bertipe node*, maka kita harus membuat function yang return typenya node*
node* createNode(int value){
	
//	Untuk menginisialisasikan Sebuah node* kosong 
	node* temp = (node*)malloc(sizeof(node)); 
	
	temp->value = value;
	temp->next = NULL;
	temp->prev = NULL;
	
	return temp;
}

void pushHead(int value){
	//Flownya
	//   [Data Baru]          [Head]<->[]<->[]
	//   [Data Baru]  <->     [Head]<->[]<->[]
	//   [Head]       <->     [Head Lama]<->[]<->[]   (Memindahakan posisi head ke yang data baru)
	
	node* newData = createNode(value);
	
	if(head == NULL) {   //Bisa juga ditulis, if (!head)
		head = tail = newData;
	}
	else{
		newData->next = head;
		head->prev = newData;
		head = newData;
	}
}


void pushTail(int value){
	// Flownya
	// []<->[]<->[Tail]   <->  [Data Baru]
	// []<->[]<->[Tail]   <->  [Data Baru]
	// []<->[]<->[Tail Lama]<->[Tail]      (Memindahkan posisi tail ke data yang baru)
	
	node* newData = createNode(value);
	
	if(head == NULL){
		head = tail = newData;
	}
	else{
		tail->next = newData;
		newData->prev = tail;
		tail = newData;
	}
}

void pushMid(int val){
	// Push Mid, kita akan menginput data secara sorted atau bisa dengan kondisi lainnya
	// Di sini kita coba yang sorted
	// Kita harus transversalkan semua node yang sudah ada
	// Kita siapkan satu variable sementara
	
	node *newData = createNode(val);
	
	// Ada 4 kondisi, boleh di analisa kodingannya
	
	if(head == NULL){
		head = tail = newData;
	}
	else if(val < head->value){
		pushHead(val);
	}
	else if(val >= tail->value){
		pushTail(val);
	}
	else{
		// Kalau kondisi di atas tidak terpenuhi, itu berarti kita harus transversalkan satu per satu
		// Flownya
		// [Data Baru : 10]     [1]<->[5]<->[12]<->[15]
		// [1]<->[5]<->[Data Baru : 10]<->[12]<->[15]
		
		node *currentNode = head;
		
		while(currentNode != NULL){
			if(currentNode->next->value > val){
				newData->next = currentNode->next;
				newData->prev = currentNode;
				currentNode->next->prev = newData;
				currentNode->next = newData;
				break;
			}	
			currentNode = currentNode->next;
		}	
	}
	
	
	
}

void popHead(){
	// Kita harus validasikan beberapa hal
	
	if(head == NULL){
		return;
	}
	else if(head == tail){
		head = tail = NULL;
		free(head); 
		free(tail);
	}
	else{
		// [Head]<->[Data Setelah Head]
		// [Head]   [Data Setelah Head]
		// X[Head Lama]   [Head]
		
		node *headNext = head->next;
		head->next = headNext->prev = NULL;
		free(head);
		head = headNext;
	}
}

void popTail(){
	if(head == NULL){
		return;
	}
	else if(head == tail){
		head = tail = NULL;
		free(head); 
		free(tail);
	}
	else{
		// [Data Sebelum Tail]<->[Tail]
		// [Data Sebelum Tail] [Tail]
		// [Tail]   X[Tail Lama]
		
		//Untuk mendapatkan data sebelum tail, kita harus mentransversalkan datanya
		
		node *currentNode = head;
		while(currentNode){
			if(currentNode->next == tail){
				currentNode->next = NULL;
				tail->prev = NULL;
				free(tail);
				tail = currentNode;
				break;
			}
			currentNode = currentNode->next;
		}
	}
}

void popMid(int value){
	if(head == NULL){
		return;
	}
	else if(head == tail){
		head = tail = NULL;
		free(head); 
		free(tail);
	}
	else{
		// [X] -> [Data Yang Mau Dihapus] <-> [Y]
		
		// Langsung Sambungkan X dengan Y
		// [X]              <->             [Y]
		//	 X[Data Yang Mau Dihapus]
		
		//Untuk mendapatkan data sebelum tail, kita harus mentransversalkan datanya
		
		node *currentNode = head;
		
		//Kita harus validasikan curr->next tidak sama dengan null
		//Karena mungkin saja data tidak ditemukan, dan kita sudah berada di tail
		
		while(currentNode->next != NULL){
			if(currentNode->next->value == value){
				currentNode->next->next->prev = currentNode;
				currentNode->next = currentNode->next->next;
				currentNode->next->prev = currentNode;
			}
			currentNode = currentNode->next;
		}
	}
}

void printAll(){
	
	//By Logic, untuk ngeprint semua, kita bisa mentransversalkan semua datanya dari head sampai ke tail
	// Ini berarti, kita harus menyiapkan sebuah node sementara
	node* currentNode = head;
	
	//Selagi currentNode tersebut tidak null, berarti datanya masih ada
	while(currentNode != NULL){
		printf("%d\n", currentNode->value);
		currentNode = currentNode->next;
	}
}



int main(){
	
/*	pushMid(10);
	pushMid(7);
	pushMid(12);
	pushMid(9);
	pushMid(11);*/

	printAll();
	
	return 0;
}
