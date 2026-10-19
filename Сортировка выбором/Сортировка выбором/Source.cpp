#include <iostream>
using std::cout;

template <typename T> void SelectionSort(T mas[],size_t size);


int main() {
	int mas[] = { 3,10,2,7,9,8,11,24,64,22,31 };
	size_t mas_size = sizeof(mas) / sizeof(mas[0]);

	for (size_t i = 0; i < mas_size; i++) cout << mas[i] << ' ';

	SelectionSort(mas, mas_size);

	cout << "\n\n";

	for (size_t i = 0; i < mas_size; i++) cout << mas[i] << ' ';

	return 0;
}

template <typename T> void SelectionSort(T mas[], size_t size) {
	T temp;
	size_t min_index;


	for (size_t i = 0; i < size; i++) {
		min_index = i;
		for (size_t j = i+1; j < size; j++) {
			if (mas[min_index] > mas[j])
				min_index = j;
		}
		temp = mas[i];
		mas[i] = mas[min_index];
		mas[min_index] = temp;
	}
}
