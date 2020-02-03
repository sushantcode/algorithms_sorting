#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *OpenFile(int argc, char *argv[])
{
	char filename[20];
	if(argc == 2)
	{
		strcpy(filename, argv[1]);
	}
	else{
		printf("File is missing. Enter the filename: ");
		scanf(" %s", &filename);
		getchar();
	}
	FILE *readFH = fopen(filename, "r");
	while(readFH == NULL)
	{
		printf("\n\nEnter the new filename: ");
		scanf(" %s", &filename);
		getchar();
		readFH = fopen(filename, "r");
	}
	return readFH;
}

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

long long int countSplitInversion(int arr[100000], int l, int mid, int r)
{
    int tmpArr[r-l+1];
    int i=l,j=mid+1,k=0;
    long long int splitInversion=0;
    while(i<=mid&&j<=r)
    {
        if(arr[i]<arr[j])
        {
            tmpArr[k]=arr[i];
            i++;
            k++;
        }
        else
        {
            tmpArr[k]=arr[j];
            splitInversion+= (mid+1-i);
            j++;
            k++;
        }
    }
    while(i<=mid)
    {
        tmpArr[k]=arr[i];
        i++;
        k++;
    }
    while(j<=r)
    {
        tmpArr[k]=arr[j];
        j++;
        k++;
    }
    for(int m=l;m<=r;m++)
    {
        arr[m]=tmpArr[m-l];
    }
    return splitInversion;
}

long long int countInversionAndSort(int arr[100000], int first, int last)
{
    if(first<last)
    {
        int mid = first+last;
        mid/=2;
        long long int x=countInversionAndSort(arr,first,mid);
        long long int y=countInversionAndSort(arr,mid+1,last);
        long long int z=countSplitInversion(arr,first,mid,last);
        return x+y+z;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int arr[100000];
    FILE *readFH = OpenFile(argc, argv);
	FillArray(readFH, arr);
    printf("The number of inversions are: %lld \n", countInversionAndSort(arr,0,100000));
    return 0;
}
