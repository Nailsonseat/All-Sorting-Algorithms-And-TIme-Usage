#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

void merge(int* arr, int lb, int mid, int ub) {
	int i(lb), j(mid + 1), k(lb), * ret(new int[ub - lb + 1]);
	while (i <= mid && j <= ub) {
		if (arr[i] <= arr[j])ret[k++ - lb] = arr[i++];
		else ret[k++ - lb] = arr[j++];
	}
	if (i > mid)while (j <= ub)ret[k++ - lb] = arr[j++];
	else while (i <= mid) ret[k++ - lb] = arr[i++];
	for (int l(lb); l <= ub; l++)arr[l] = ret[l - lb];
	delete[]ret;
}

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

void csort(int* arr, int size, int base) {
	int count[10] = { 0 }, * ret(new int[size]);
	for (int i(0); i < size; i++)count[(arr[i] / base) % 10]++;
	for (int i(1); i < 10; i++)count[i] += count[i - 1];
	for (int i(size - 1); i >= 0; i--)ret[--count[(arr[i] / base) % 10]] = arr[i];
	for (int i(0); i < size; i++)arr[i] = ret[i];
	delete[]ret;
}

void isort(vector<float>arr, int size) {
	for (int i(1); i < size; i++) {
		int j(i);
		while (j > 0 && arr[j] < arr[j - 1]) {
			swap(arr[j], arr[j - 1]);
			j--;
		}
	}
}

void swap(int& x, int& y) {
	x = x ^ y;
	y = x ^ y;
	x = x ^ y;
}

void busort(float* f_arr, int size) {
	vector <vector<float>> buckets;
	buckets.resize(size);
	for (int i(0); i < size; i++)
		buckets[floor(size * f_arr[i])].push_back(f_arr[i]);
	for (int i(0); i < size; i++)
		isort(buckets[i], buckets[i].size());
	int index(0);
	for (auto val1 : buckets)
		for (auto val2 : val1)
			f_arr[index++] = val2;
}

void rsort(int* arr, int size) {
	int max(arr[0]);
	for (int i(1); i < size; i++)
		if (arr[i] > max)max = arr[i];
	for (int base = 1; max / base > 0; base *= 10)
		csort(arr, size, base);
}

void csort(int* arr, int size, int lb, int ub) {
	int* count(new int[ub - lb]()), * ret(new int[size]);
	for (int i(0); i < size; i++)count[arr[i]]++;
	for (int i(1); i < ub - lb; i++)count[i] += count[i - 1];
	for (int i(size - 1); i >= 0; i--)ret[--count[arr[i]]] = arr[i];
	for (int i(0); i < size; i++)arr[i] = ret[i];
	delete[]count;
	delete[]ret;
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

void msort(int* arr, int lb, int ub) {
	int mid((ub + lb) / 2);
	if (lb < ub) {
		msort(arr, lb, mid);
		msort(arr, mid + 1, ub);
		merge(arr, lb, mid, ub);
	}
}

void call_function(int call_index, int size, int* arr, float* f_arr, long long* time) {
	if (call_index == 9)
		for (int i(0); i < size; i++)f_arr[i] = arr[i] / 1000.0;
	auto initial(high_resolution_clock::now());
	ios_base::sync_with_stdio(false);
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
	case 6:msort(arr, 0, size - 1);
		break;
	case 7:csort(arr, size, 0, 1000);
		break;
	case 8:rsort(arr, size);
		break;
	case 9:
		busort(f_arr, size);
		break;
	}
	auto final(high_resolution_clock::now());
	time[call_index - 1] = duration_cast<microseconds>(final - initial).count();
}

int main() {
	int size(250), range_l(0), range_u(1000), print_width[9] = { 10,8,8,12,13,12,9,12,11 };
	char names[9][15] = { "Bubble Sort ","Insertion Sort","Selection Sort","Quick Sort","Heap Sort","Merge Sort","Counting Sort","Radix Sort","Bucket Sort" };
	cout << "Size of the array being sorted " << size;
	cout << "\nEach element ranging between " << range_l << " to " << range_u << endl;
	int* array(new int[size]), * backup(new int[size]);
	long long* time(new long long[9]());
	float* f_array(new float[size]());
	for (int i(0); i < size; i++) backup[i] = rand() % range_u + range_l;
	for (int i(1); i <= 9; i++) { 
		if(!(i==9))for (int j(0); j < size; j++)array[j] = backup[j];
		call_function(i, size, array, f_array, time);
	}
	cout << "\nThe Sorted Array is : \n\n";
	for (int i(0); i < size; i++)cout << array[i] << ' ';
	cout << "\n\nThe Sorted decimal values array is : \n\n";
	for (int i(0); i < size; i++)cout << f_array[i] << ' ';
	cout << "\n\nTime Data : \n";
	
	for (int i(0); i < 9; i++) {
		cout << endl << i + 1 << "-Time Taken by " << names[i] << setw(print_width[i]) << ":   ";
		cout << time[i];
		cout << " microseconds";
	}
	cout << endl << endl;
}