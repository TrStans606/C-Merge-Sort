#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function returns an int just to exit early
void compare(int* compare_list,int middle, int smallest_size,int size) {
	int i,j,shift;

	int start = middle - smallest_size;
	int end = (middle + smallest_size <= size) ? middle + smallest_size : size;

	//covers the edge case where a list has only one element
	if (end == middle) {
		return;
	}
	int array1_size = middle-start;
	int array2_size = end-middle;
    int* store_list1 = (int*)malloc(sizeof(int)*array1_size);
	int* store_list2 = (int*)malloc(sizeof(int)*array2_size);

	if (store_list1 == NULL || store_list2 == NULL) {
		printf("Memory Failed to allocate.\n");
		exit(EXIT_FAILURE);
	}

	// copies each sorted bit to a new array for comparison
	// arraysize will always be used
	j=0;
	for (i=start; i < middle;i++) {
		store_list1[j] = compare_list[i];
		j++;
	}
	j=0;
	for (i=middle; i < end;i++) {
		store_list2[j] = compare_list[i];
		j++;
	}

	//shift varible for handling writing to the left of the array
    shift = 0;
	//comparison of two elements
	i=0;
	j=0;
	while (i < array1_size) {
		if (store_list1[i] <= store_list2[j]) {
			compare_list[start+shift] = store_list1[i];
			i++;
			shift++;
		} else if (store_list2[j] < store_list1[i]) {
			compare_list[start+shift] = store_list2[j];
			j++;
			shift++;
		}
		//checks for when list 2 sorts before list 1
		if (j >= array2_size ) {
			while(i < array1_size){
				compare_list[start+shift] = store_list1[i];
				i++;
				shift++;
			}
		}
	}
	//checks for when list 1 sorts before list 2
	while (j < array2_size) {
		compare_list[start+shift] = store_list2[j];
		j++;
		shift++;
	}
	free(store_list1);
	free(store_list2);
}

//handles the merging 
void listmerge(int *list_input,int size) {
    int i,runs;
    int merge_size = 1;
	int breakpoint;
    while (merge_size < size) {
		breakpoint =merge_size;
        runs = (size%merge_size*2==0) ? size/(merge_size*2) : size/(merge_size*2)+1;
        for (i=0;i<runs;i++){
			compare(list_input,breakpoint,merge_size,size);

			breakpoint += (merge_size * 2);
			if (breakpoint > size) {
				breakpoint = size;
			}
        }

		merge_size *= 2;
    }
}

int main() {
	srand(time(NULL));
    int n, i;
	n = rand()  % 50 + 1;
	printf("Initial Array size %d is: ",n);
    int listA[n];
	// int* listA = (int*)malloc(sizeof(int)*n);
	for (i=0;i<n;i++) {
		listA[i] = rand() % 100 + 1;
		if (i != n-1) {
			printf("%d,",listA[i]);
		} else {
			printf("%d\n",listA[i]);
		}
	}

    listmerge(listA,n);

	printf("Final list is \n");
	for (i=0;i<n;i++){
		if (i != n-1) {
			printf("%d,",listA[i]);
		} else {
			printf("%d",listA[i]);
		}
	}
	printf("\n");
    return(0);
}
