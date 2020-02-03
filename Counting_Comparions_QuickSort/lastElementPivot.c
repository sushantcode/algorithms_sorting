#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int totalCount = 0;

void FillArray(FILE *readFH, int arr[100000])
{
	char fileLine[20];
	int i = 0;
	while(fgets(fileLine, sizeof(fileLine), readFH) != NULL)
	{
		arr[i] = atoi(fileLine);
		i++;
	}
	fclose(readFH);
}

int partition(int arr[],int left,int pivot,int right) {
    int i = left + 1;
    int temp;
    int j;
    for (j = left + 1; j < right; j++) {
        if (arr[j] < pivot) {
            temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
            i++;
        }
    }
    temp = arr[i - 1];
    arr[i - 1] = arr[left];
    arr[left] = temp;
    return i - 1;
}


int quickSort(int arr[10000], int left, int right) {

    if (right <= left)
        return 0;

    int pivot = arr[right -1];
    arr[right - 1] = arr[left];
    arr[left] = pivot;
    int i = partition(arr,left,pivot,right);
    totalCount += (right - left - 1);
    quickSort(arr,left,i);
    quickSort(arr,i + 1,right);
    return totalCount;
}

int main()
{
    int arr[10000];
    FILE *readFH = fopen("in.txt", "r");
	FillArray(readFH, arr);
    printf("The number of inversions are: %d \n", quickSort(arr, 0, 10000));
    return 0;
}
