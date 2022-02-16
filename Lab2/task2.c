// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// 
// (c) Martin Porcheron
//     m.a.w.porcheron@swansea.ac.uk
// -----------------------------------------------------

#include "timestables.h"
#include "arrays.h"

int main(int argc , char *argv[]) {
	int *arPntr[MAX_TABLE_SIZE]; // error possible segmentation	

	int i;
	for (i = 0; i <= MAX_TIMES_TABLE;i++){
		
		arPntr[i] = (int*) malloc(MAX_TABLE_SIZE * sizeof(int));

		generateTable(i, arPntr[i]);

	}
	printTables(arPntr);

	int j;
	for (j = 0; j <= MAX_TIMES_TABLE;i++){
		free(arPntr[j]);//Im freeing the pointer to the pointer but not the memory inside times.
	}

	return 0;
}