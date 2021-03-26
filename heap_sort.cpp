#include<iostream>
#include<cmath>
#include<ctime>
using std::cout;
using std::endl;

void swap(int& first_var, int& second_var);
void heapify(int array[], int size, int i);
void make_heap(int array[], int size);
void heap_sort(int array[], int size);
void output(int array[], int size);

int main()
{
	int size = 10;
	int array[size] = {0};
	
	srand(time(0));
	for(int i = 0; i < size; i++)
		array[i] = rand() % 30;

	cout << "Before sorting\n";
	output(array, size);
	heap_sort(array, size);
	cout << "After sorting\n";
	output(array, size);

	return 0;
}

void swap(int& first_var, int& second_var)
{
	int temp = 0;

	temp = first_var;
	first_var = second_var;
	second_var = temp;
}

void heapify(int array[], int size, int i)
{
	int largest = i, left_child = 2*i + 1, right_child = 2*i + 2;

	if(left_child < size && array[left_child] > array[largest])
		largest = left_child;

	if(right_child < size && array[right_child] > array[largest])
		largest = right_child;

	if(largest != i)
	{
		swap(array[i], array[largest]);
		heapify(array, size, largest);
	}
}

void make_heap(int array[], int size)
{
	for(int i = size/2 - 1; i >= 0; i--)
		heapify(array, size, i);
}

void heap_sort(int array[], int size)
{
	make_heap(array, size);

	for(int i = size - 1; i >= 0; i--)
	{
		swap(array[0], array[i]);
		heapify(array, i, 0);
	}
}

void output(int array[], int size)
{
	cout << "The array: ";
	for(int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
}
