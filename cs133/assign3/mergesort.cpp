#include <iostream>
/*
 * mergesort.cpp
 * Implementation of a bitonic mergesort
 */

 /* merge(input, size, output, asc)
	Merge the two halves of the array input (which has size elements) into
	output. If asc is true, then the output array should be in ascending order;
	otherwise it should be descending.
 */
void merge(int* input, int size, int* output, bool output_asc) {
	int k = 0;      // Beginning of output
	if (output_asc) { //ascending
		int i = 0;      // Beginning of left half
		int j = size -1; // Beginning of right half
		while (i < size / 2 && j >= size /2) {
			output[k++] = input[i] < input[j] ? input[i++] : input[j--];
		}
		while (i < size / 2) {
			output[k] = input[i];
			k++;
			i++;
		}

		while (j >= size/2) {
			output[k] = input[j];
			
			k++;
			j--;
		}
	}
	else {//descending
		int i = size / 2 - 1;
		int j = size / 2;
		while (i >= 0 && j < size) {
			output[k++] = input[i] > input[j] ? input[i--] : input[j++];
		}
		while (i >= 0) {
			output[k++] = input[i--];
		}
		while (j < size) {
			output[k++] = input[j++];
		}
	}
}


/* mergesort(input, size, output, asc)
   Mergesort the input array (with size elements) into the output array. If
   asc is true, the output array should be sorted ascending, otherwise it should
   be descending.
*/
void mergesort(int* input, int size, int* output, bool output_asc) {
	if (size == 0) {
		return;
	}
	else if (size == 1) {
		output[0] = input[0];
	}
	else {
		int mid = size / 2;
		mergesort(input, mid, output, true);
		mergesort(input + mid, size - mid, output + mid, false);
		for (int i = 0; i < size; ++i) {
			input[i] = output[i];
		}
		merge(input, size, output, output_asc);
	}
}


/* mergesort(input, size)
   Sorts size elements in the array pointed to by input, using the MergeSort
   algorithm. Output is returned as a newly allocated array, which the caller
   is responsible for freeing.
*/
int* mergesort(int* input, int size) {
	int* output = new int[size];
	mergesort(input, size, output, true);
	return output;
}
