#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
	int size(250);
	int* array(new int[size]);
	for (int i(0); i < size; i++) array[i] = rand() % size + 0;
	auto initial(high_resolution_clock::now());
	auto final(high_resolution_clock::now());
	for (int i(0); i < size; i++)cout << array[i] << ' ';
	cout  << "\n\nTime Taken : " << duration_cast<microseconds>(final - initial).count() << " microseconds\n";
}