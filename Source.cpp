#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

void heapify(int* arr, int size, int node) {
	int l(node * 2 + 1), r((node + 1) * 2), larg(node);
	if (l <= size && arr[l] > arr[larg])larg = l;
	if (r <= size && arr[r] > arr[larg])larg = r;
	if (node != larg) {
		swap(arr[larg], arr[node]);
		heapify(arr, size, larg);
	}
}

int partition(int* arr, int lb, int ub) {
	int start(lb), end(ub), pivot(arr[lb]);
	while (start < end) {
		while (arr[start] <= pivot)start++;
		while (arr[end] > pivot)end--;
		if (start < end)swap(arr[start], arr[end]);
	}
	if (arr[end] != arr[lb])swap(arr[lb], arr[end]);
	return end;
}

void swap(int& x, int& y) {
	x = x ^ y;
	y = x ^ y;
	x = x ^ y;
}

void bsort(int* arr, int size) {
	for (int i(0); i < size; i++) {
		bool swapped(false);
		for (int j(0); j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1])swap(arr[j], arr[j + 1]);
			swapped = true;
		}
		if (!swapped)return;
	}
}

void isort(int* arr, int size) {
	for (int i(1); i < size; i++) {
		int j(i);
		while (j > 0 && arr[j] < arr[j - 1]) {
			swap(arr[j],arr[j - 1]);
			j--;
		}
	}
}

void ssort(int* arr, int size) {
	for (int i(0); i < size; i++) {
		int pos(i);
		for (int j(i + 1); j < size; j++)
			if (arr[j] < arr[pos])pos = j;
		if (pos != i)swap(arr[i], arr[pos]);
	}
}

void qsort(int* arr, int lb,int ub) {
	if (lb < ub) {
		int pos(partition(arr, lb, ub));
		qsort(arr, lb, pos - 1);
		qsort(arr,pos+1,ub);
	}
}

void hsort(int* arr, int size) {
	for (int i(size / 2 - 1); i >= 0; i--)heapify(arr, size, i);
	for (int j(size - 1); j >= 1; j--) {
		swap(arr[0], arr[j]);
		heapify(arr, j - 1, 0);
	}
}

void call_function(int call_index, int size, int* arr) {
	char names[9][15] = { "Bubble Sort ","Insertion Sort","Selection Sort","Quick Sort","Heap Sort","Merge Sort","Counting Sort","Radix Sort","Bucket Sort" };
	for (int i(0); i < size; i++) arr[i] = rand() % size + 0;
	auto initial(high_resolution_clock::now());
	switch (call_index)
	{
	case 1:bsort(arr, size);
		break;
	case 2:isort(arr, size);
		break;
	case 3:ssort(arr, size);
		break;
	case 4:qsort(arr, 0, size - 1);
		break;
	case 5:hsort(arr, size);
		break;
	}
	auto final(high_resolution_clock::now());
	auto duration(duration_cast<microseconds>(final - initial).count());
	cout << "\n\nTime Taken by " << names[call_index - 1] << ": ";
	cout << duration << " microseconds\n";
}

int main() {
	int size(250);
	int* array(new int[size]);
	for (int i(1); i <= 5; i++)call_function(i, size, array);
	cout << "\n\nThe Sorted Array is : \n\n";
	for (int i(0); i < size; i++)cout << array[i] << ' ';
	cout << endl;
}