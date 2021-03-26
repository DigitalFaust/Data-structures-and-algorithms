#include<iostream>
#include<cmath>
#include<ctime>
using std::cout;
using std::endl;

void output(int array[], int size);
void merge_sort(int array[], int left, int right);
void merge(int array[], int left, int middle, int right);

int main()
{
	int size = 10;
	int array[size] = {0};

	for(int i = 0; i < size; i++)
		array[i] = rand() % 30;

	cout << "Before sorting\n";
	output(array, size);
	merge_sort(array, 0, (size - 1));
	cout << "After sorting\n";
	output(array, size);

	return 0;
}

void output(int array[], int size)
{
	for(int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
}

void merge_sort(int array[], int left, int right)
{
	if(left < right)
	{
		int middle = (left + right)/2;
		merge_sort(array, left, middle);
		merge_sort(array, (middle + 1), right);
		merge(array, left, middle, right);
	}
}

void merge(int array[], int left, int middle, int right)
{
	int lsa_size = middle - left + 1; // size of the left subarray
	int rsa_size = right - middle; // size of the right subarray
	int lsa[lsa_size], rsa[rsa_size];

	for(int i = 0; i < lsa_size; i++)
		lsa[i] = array[left + i];
	for(int i = 0; i < rsa_size; i++)
		rsa[i] = array[middle + 1 + i];

	int i = 0, j = 0, k = left;
	while(i < lsa_size && j < rsa_size)
	{
		if(lsa[i] <= rsa[j])
		{
			array[k] = lsa[i];
			i++;
		}
		else
		{
			array[k] = rsa[j];
			j++;
		}
		k++;
	}

	while(i < lsa_size)
	{
		array[k] = lsa[i];
		i++;
		k++;
	}

	while(j < rsa_size)
	{
		array[k] = rsa[j];
		j++;
		k++;
	}
}
