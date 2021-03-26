#include<iostream>
#include<cmath>
using std::cout;
using std::endl;

void selection_sort(int s[], int size);
void swap(int& first_var, int& second_var);

int main()
{
	int size = 10;
	int array[size] = {0};

	cout << "Array: ";
	for(int i = 0; i < size; i++)
	{
		array[i] = rand() % 10;
		cout << array[i] << " ";
	}
	cout << endl;

	selection_sort(array, size);

	cout << "Array: ";
	for(int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;

	return 0;
}

void selection_sort(int s[], int size)
{
	int min;

	for(int i = 0; i < size; i++)
	{
		min = i;
		for(int j = i + 1; j < size; j++)
			if(s[j] < s[min])
				min = j;
		swap(s[i], s[min]);
	}
}

void swap(int& first_var, int& second_var)
{
	int temp = 0;

	temp = first_var;
	first_var = second_var;
	second_var = temp;
}
