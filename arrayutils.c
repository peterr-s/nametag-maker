#include "arrayutils.h"

char** merge_sort(char** to_sort, size_t ct)
{
	// if empty or trivially sorted, return input
	if(ct <= 1)
		return to_sort;
	
	// else split in half and sort each half
	size_t split = ct / 2;
	char** a1 = merge_sort(to_sort, split);
	char** a2 = merge_sort(&to_sort[split], ct - split);
	
	// return the halves merged
	return merge(a1, a2, split, ct - split);
}

char** merge(char** a1, char** a2, size_t l1, size_t l2)
{
	// make array
	char** merged = malloc((l1 + l2) * sizeof(char*));
	
	// track position in each array, always comparing current element
	unsigned int i = 0,
		i1 = 0,
		i2 = 0;
	while(i1 < l1 && i2 < l2)
		merged[i++] = (strcmp(a1[i1], a2[i2]) < 0) ? a1[i1++] : a2[i2++];
	while(i1 < l1)
		merged[i++] = a1[i1++];
	while(i2 < l2)
		merged[i++] = a2[i2++];
	
	return merged;
}