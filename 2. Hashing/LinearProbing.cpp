#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Hash Table
// Karena kita hanya mau ngestore nama, maka kita siapkan saja hashTable String
// Kita siapkan sebesar 10000, karena ini adalah linear probing;
// Silahkan baca Simple Hashing Theory.pdf kalo belum mengerti

char hashTable[10000][100];

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

void insertData(char *name){
	// Kita Cari Dulu Hasil Hashingnya
	int hashIndex = hashFunction(name);
	
	// Barulah kita validasi
	// Selagi table[index] keiisi, maka kita akan tambahkan index sebanyak 26, 
	// sebagaimana 26 adalah size sebenarnya dari hashTable ini.
	// Tetapi karena adanya linear probing, maka kita harus siapin space lebih di hashTable
	// Seandainya kalian menambahkan indexnya lebih dari 26, takutnya malah akan mempersulit 
	// proses masukin data ke hashTablenya, karena indexnya berantakan
	while(strcmp(hashTable[hashIndex], "") != 0){
		hashIndex += 26;
	}
	
	strcpy(hashTable[hashIndex], name);
}

void printHashTable(){
	// Di Sini, kita akan mengoutputkan semua table tersebut berdasarkan index sesungguhnya.
	// Dan Outputnya hanya yang berisi
	for(int i = 0; i < 26; i++){
		int hashIndex = i;
		
		if(strcmp(hashTable[i], "") != 0){
			printf("Index %d:\n", i);
			while(strcmp(hashTable[hashIndex], "") != 0){
				printf("   - %-20s dengan index : %d\n", hashTable[hashIndex], hashIndex);
				hashIndex += 26;
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
