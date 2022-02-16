#include "timestables.h"
#include "arrays.h"

void generateTable(int num, int *table) {
	int i;
	for (i = 0; i < MAX_TABLE_SIZE; i++) {
		table[i] = i * num;
	}
}

//changes the address of where the pointer for tables is.
void printTables(int **tables) {
	int i;
	for (i = 0; i < MAX_TIMES_TABLE;i++) {
		printTable(i,tables[i]);
	}
}

void printTable(int num, int *table) {
	printf("%-2d times table\n--------------\n", num);
	int i;
	for (i = 0; i < MAX_TABLE_SIZE; i++) {
		printf("%-2d * %-2d = %d\n", num, i, *(table+i));
	}
	printf("\n");

	double meanValue = mean(MAX_TABLE_SIZE, table);
	printf("The mean for this table is %f\n\n", meanValue);
}