#include <iostream>
using std::cout;

template <typename T> bool binary_search(T mas[], size_t size, T number);

int main() {
	setlocale(LC_ALL, "ru");

	int mas[] = { 1,2,3,4,5,6,7,8,9,10 };

	int number = 11;

	if (binary_search(mas, 10, number)) cout << "В массиве содержится число" << number;
	else cout << "Заданное число не было найдено в массиве! ";


}

template <typename T> bool binary_search(T mas[], size_t size, T number) {
	int low, mid, high;

	low = 0;
	high = size-1;

	while (low <= high) {
		mid = (low + high) / 2;
		if (mas[mid] == number) {
			return true;
		}
		else if (mas[mid] > number) {
			high = mid - 1;
		}
		else if (mas[mid] < number) {
			low = mid + 1;
		}
	}

	return false;
}