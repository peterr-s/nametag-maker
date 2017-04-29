#include <string.h>
#include "arrayutils.h"

class** merge_sort_class(class** to_sort, size_t ct)
{
	// if empty or trivially sorted, return input
	if(ct <= 1)
		return to_sort;
	
	// else split in half and sort each half
	size_t split = ct / 2;
	class** a1 = merge_sort_class(to_sort, split);
	class** a2 = merge_sort_class(&to_sort[split], ct - split);
	
	// return the halves merged
	return merge_class(a1, a2, split, ct - split);
}

class** merge_class(class** a1, class** a2, size_t l1, size_t l2)
{
	// make array
	class** merged = malloc((l1 + l2) * sizeof(class*));
	
	// track position in each array, always comparing current element
	unsigned int i = 0,
		i1 = 0,
		i2 = 0;
	while(i1 < l1 && i2 < l2)
		merged[i++] = (strcmp(a1[i1]->name, a2[i2]->name) < 0) ? a1[i1++] : a2[i2++];
	while(i1 < l1)
		merged[i++] = a1[i1++];
	while(i2 < l2)
		merged[i++] = a2[i2++];
	
	return merged;
}

class* find_class(class** array, size_t len, char* query)
{
	// if there are no elements (possible because of rounding)
	if(len == 0)
		return NULL;
	
	// if there's just one element it's the last possible option
	if(len == 1)
		return strcmp(array[0]->name, query) ? array[0] : NULL;
	
	size_t index = len / 2;
	int comp = strcmp(array[index]->name, query);
	
	if(comp < 0)
		return find_class(array, index, query);
	else if(comp > 0)
		return find_class(&array[index], len - index, query);
	else
	{
		// backtrack to first occurrence
		while(!strcmp(query, array[index - 1]->name))
			index--;
		return array[index];
	}
}