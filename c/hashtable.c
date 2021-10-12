#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person*)(0xFFFFFFFFFFFFFFFFUL)

typedef struct {
	char name[MAX_NAME];
	int age;
} person;

person * hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
	int length = strnlen(name, MAX_NAME);
	unsigned int hash_value = 0;
	for (int i = 0; i < length; i++) {
		hash_value += name[i];
		hash_value = hash_value * name[i] % TABLE_SIZE;
	}
	return hash_value;
}

void init_hash_table() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hash_table[i] = NULL;
	}
}

void print_table() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hash_table[i] == NULL) {
			printf("\t%i\t----\n", i);
		}
		else if (hash_table[i] == DELETED_NODE) {
			printf("\t%i\t---<deleted>\n", i);
		}
		else {
			printf("\t%i\t%s\n", i, hash_table[i]->name);
		}
	}
}

// inserts person into hash table
bool hash_table_insert(person *p) {
	if (p == NULL) return false;
	int index = hash(p->name);
	for (int i = 0; i < TABLE_SIZE; i++) {
		int try = (i + index) % TABLE_SIZE;
		if (hash_table[try] == NULL ||
			hash_table[try] == DELETED_NODE) {
			hash_table[try] = p;
			return true;
		}
	}
	return false;
}

// deletes person from hash table
person *hash_table_delete(char *name) {
	int index = hash(name);
	for (int i = 0; i < TABLE_SIZE; i++) {
		int try = (index + i) % TABLE_SIZE;
		if (hash_table[try] == NULL) {
			return NULL;
		}
		if (hash_table[try] == DELETED_NODE) continue;
		if (strncmp(hash_table[index]->name, name, TABLE_SIZE)==0) {
				person *tmp = hash_table[try];
				hash_table[try] = DELETED_NODE;
				return tmp;
		}
	}
	return NULL;
}

//find a person in the table by name
person *hash_table_lookup(char *name) {
	int index = hash(name);
	for (int i = 0; i < TABLE_SIZE; i++) {
		int try = (index + i) % TABLE_SIZE;
		if (hash_table[try] == NULL) {
			return false;
		}
		if (hash_table[try] == DELETED_NODE) continue;
		if (strncmp(hash_table[try]->name, name, TABLE_SIZE)==0) {
				return hash_table[try];
		}
	}
		return NULL;
}

int main() {
	init_hash_table();

	person jacob = {.name = "Jacob", .age = 256};
	person thomas = {.name = "Thomas", .age = 200};
	person farrukh = {.name = "Farrukh", .age = 25};
	person arthur = {.name = "Arthur", .age = 38};
	person tim = {.name = "Tim", .age = 256};
	person george = {.name = "George", .age = 200};
	person tu = {.name = "Tu", .age = 25};
	person alex = {.name = "Alex", .age = 30};
	person marsha = {.name = "Marsha", .age = 250};
	person aaron = {.name = "Aaron", .age = 37};
	person yun = {.name = "Yun", .age = 10};
	person lane = {.name = "Lane", .age = 55};
	
	hash_table_insert(&jacob);
	hash_table_insert(&thomas);
	hash_table_insert(&farrukh);
	hash_table_insert(&arthur);
	hash_table_insert(&tim);
	hash_table_insert(&tu);
	hash_table_insert(&george);
	hash_table_insert(&alex);
	hash_table_insert(&marsha);
	hash_table_insert(&aaron);
	hash_table_insert(&yun);
	hash_table_insert(&lane);

	print_table();

	person *tmp = hash_table_lookup("Arthur");
	if (tmp == NULL) {
		printf("Not found\n");
	}
	else {
		printf("%s = %u\n", tmp->name, tmp->age);
	}
	tmp = hash_table_lookup("Lane");
	if (tmp == NULL) {
		printf("Not found\n");
	}
	else {
		printf("%s = %u\n", tmp->name, tmp->age);
	}
	tmp = hash_table_lookup("Tim");
	if (tmp == NULL) {
		printf("Not found\n");
	}
	else {
		printf("%s\n", tmp->name);
	}

	hash_table_delete("Arthur");
	hash_table_delete("Thomas");

	tmp = hash_table_lookup("Arthur");
	if (tmp == NULL) {
		printf("Not found\n");
	}	else {
		printf("%s\n", tmp->name);
	}

	print_table();

	return 0;
}
