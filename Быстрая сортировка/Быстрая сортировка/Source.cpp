#include <iostream>
#include <vector>

using std::cout;
using std::vector;

template <typename T> vector<T> QuickSort(vector<T> &mas);

int main() {
	setlocale(LC_ALL, "ru");
	vector<int> vec = { 53,425,6345,313,25,65,64,234,33,11,732,63,634,43,67,23,65 };

	//vector<char> vec = { 'a','c','d','d','n','s','x','t','w','o','h' };

	cout << "Исходный массив: \n";

	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << ' ';

	vec = QuickSort(vec);

	cout << "\nОтсортированный массив: \n";

	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << ' ';

	return 0;
}

template <typename T> vector<T> QuickSort(vector<T>& mas) {
	if (mas.size() < 2)
		return mas;

	T pivot;
	size_t pivot_index = (mas.size() - 1) / 2;
	vector<T> left_mas, right_mas;

	pivot = mas[pivot_index];

	for (size_t i = 0; i < mas.size(); i++) {
		if (i == pivot_index) continue;

		if (mas[i] < pivot)
			left_mas.push_back(mas[i]);
		else
			right_mas.push_back(mas[i]);
	}	

	left_mas = QuickSort(left_mas);
	right_mas = QuickSort(right_mas);
	
	left_mas.push_back(pivot);
	left_mas.insert(left_mas.end(), right_mas.begin(), right_mas.end());


	return left_mas;
}