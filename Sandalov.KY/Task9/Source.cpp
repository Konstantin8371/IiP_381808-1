#include "Triangle.h"
#include "locale"

int main() {
	setlocale(LC_ALL, "Russian");
	Triangle first(3, 4, 5);
	string a = "Yes", b = "No";
	string c;
	cout << "Хотители вы поменять стороны треугольника на другие (Текущие 3, 4, 5)?\nВведите 'Yes' или 'No'\n";
	cin >> c;
	double da, db, dc;
	if (c == "Yes")
	{
		cout << "Введите новые длины сторон:\n";
		cin >> da >> db >> dc;
		first.resize(da, db, dc);
	}
	if (first.true_triangle())
	{
		first.type_of_triangle();
		cout << "Периметр треугольника = " << first.perimetr() << " и его площадь = " << first.ploshad();
	}


	return 0;
}