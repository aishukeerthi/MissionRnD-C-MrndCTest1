/*
Given an array which has two arithmetic sequences and 
one geometric sequence (in any order).
Copy indexes where each sequence starts and ends into an Array and return it.

Note : Each sequence will be of atleast LENGTH 3,and The sequences can be overlapping

Ex : 1, 3, 5, 7, 2, 4, 8, 16 18 20, output is [0, 3, 7, 9, 4, 7]
Ex : 1 ,2, 4, 8, 12, 16, 21, 26     output is [2, 5, 5, 7, 0, 3]
Ex : 10 15 20 30 50 70 100 200 400 800  output is [0, 2, 3, 5, 6, 9]

The final_arr[0], final_arr[1] values in final array  
will be start and end indexes of First A.P in the Original Array

The final_arr[2], final_arr[3] values in final array  
will be start and end indexes of Second A.P 

The final_arr[4], final_arr[5] values in final array  
will be start and end indexes of First  G.P (Only)

Input: Array and Length of Array
Output : New Array which has 6 integers , which denote the (start,end) indexes .

Note : All elements in the array will be part of atleast 1 sequence .
Two A.P cannot start at same index . 

Difficulty : Medium
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int findap(int *Arr, int len, int index, int *end_ap)
{
	int i, count = 0;
	for (i = index; i < len - 2; i++)
	{
		if (Arr[i + 1] - Arr[i] == Arr[i + 2] - Arr[i + 1])
		{
			count = 1;
			*end_ap = i + 2;
		}
		else
			break;
	}
	return count;
}
int findgp(int *Arr, int len, int index, int *end_gp)
{
	int i, count = 0;
	for (i = index; i < len - 2; i++)
	{
		if ((Arr[i + 1] / Arr[i]) == (Arr[i + 2] / Arr[i + 1]))
		{
			count = 1;
			*end_gp = i + 2;
		}
		else
			break;
	}
	return count;
}



int * find_sequences(int *arr, int len){

	int *final_array = (int *)malloc(sizeof(int) * 6);

	int start_ap = 0, end_ap, start_gp, end_gp;
	int is_second_ap = 0;
	int start_index = 0, end_index = 0, temp;
	//Return final array which has 6indexes [AP1_S,AP1_E,AP2_S,AP2_E,GP1_S,GP2_E]

	while (end_index != len - 1)
	{
		if (findap(arr, len, start_index, &end_index))
		{
			//printf("It's an AP from %d\n", start_index);
			start_ap = start_index;
			end_ap = end_index;
			if (!is_second_ap)
			{
				final_array[0] = start_ap;
				final_array[1] = end_ap;
			}
			else
			{
				final_array[2] = start_ap;
				final_array[3] = end_ap;
			}
			is_second_ap = 1;
			//printf("AP indices are %d, %d\n", start_ap, end_ap);
			start_index = end_index;
			if (!findap(arr, len, start_index, &temp) && !findgp(arr, len, start_index, &temp))
				start_index++;
		}
		else if (findgp(arr, len, start_index, &end_index))
		{
			//printf("It's a GP from %d\n", start_index);
			start_gp = start_index;
			end_gp = end_index;
			//printf("GP indices are %d, %d\n", start_gp, end_gp);
			final_array[4] = start_gp;
			final_array[5] = end_gp;
			start_index = end_index - 1;
			if (!findap(arr, len, start_index, &temp))
			{
				start_index++;
				if (!findap(arr, len, start_index, &temp))
				{
					start_index++;
				}
			}

		}
		else
		{
			return NULL;
			//printf("FUCKING ERROR, start_index is %d\n", start_index);
		}


	}
	return final_array;
}
