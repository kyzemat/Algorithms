#include <iostream>
#include <vector>
using std::cout;
using std::vector;

//Рекурсивная функция суммирования элементов вектора
template <typename T> T SumFunc(vector<T> mas);

//Рекурсивная функция подсчета элементов вектора
template <typename T> int CountElement(vector<T> mas);


//Рекурсивная функция поиска максимального элемента в векторе
template <typename T> T MaxElement(vector<T> mas);

/*	Вроде бы программа робит, но проблема здесь в том, что 
	пока будет выполняться этот код насозадется такое 
	огромное количество копий моего исходного вектора
	что стек может тупо переполниться.

	Можно, конечно сделать две функции, одна будет принимать 
	в себя просто массив, а вторая уже будет рекурсивной
	но мне чуток впадлу сейчас это писать. Но это я к тому,
	что как решить проблему я знаю. Просто передавать параметр по
	константной ссылке, а вторым аргументом индекс. Правда такой
	подход мало чем отличается по методу программирования от итеративного
	но не суть важно!
	*/	
int main() {
	vector<int> vec = { 1,2,3,4,5,55,7,8,9 };

	cout << SumFunc(vec) << '\n';

	cout << CountElement(vec) << '\n';

	cout << MaxElement(vec);

	return 0;
}

template <typename T> T SumFunc(vector<T> mas) {
	/*	Я прекрасно понимаю, что размер массива даже чисто теоретически 
		не может оказаться меньше нуля, просто решил написать так,
		на всякий
	*/
	if (mas.size() <= 0)
		return 0;

	T temp = mas.back();
	mas.pop_back();
	return temp + SumFunc(mas);
}

template <typename T> int CountElement(vector<T> mas) {
	if (mas.size() <= 0)
		return 0;
	mas.pop_back();
	return 1 + CountElement(mas);
}

template <typename T> T MaxElement(vector<T> mas) {
	if (mas.size() <= 1)
		return mas[0];

	if (mas[0] < mas[1])
		mas.erase(mas.begin());
	else
		mas.erase(mas.begin()+1);

	return MaxElement(mas);
}