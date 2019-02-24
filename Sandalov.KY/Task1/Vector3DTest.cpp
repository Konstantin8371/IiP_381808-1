#include "Vector3D.h"
#include <conio.h>
#include <locale>
using namespace std;

int main() {

	setlocale(LC_ALL, "Russian");
	Vector3D v1, v2;
	// Vvodim znacheniya koordinat nachalnoy i conechnoy tochek, vvod vektorov iz potoka
	cout << "Vvedite v1(x1 x2 y1 y2 z1 z2): ";
	cin >> v1;
	cout << "Vvedite v2(x1 x2 y1 y2 z1 z2): ";
	cin >> v2;
	cout << "v1:" << endl << v1 << endl;
	cout << "v2:" << endl << v2 << endl;
	//summa dvuh vektorov i prisvaivanie rezultata tretyemu + vivod v potok
	Vector3D v3 = v1 + v2;
	cout << "Summa vektorov v1 v2 (=v3)" << endl;
	cout << v3 << endl;
	// operaciya prisvaivaniya
	Vector3D v4 = v3;
	cout << "Vektor v4 = v1 + v2(=v3)" << endl;
	cout << v4 << endl;
	// raznost' vectorov
	Vector3D v5 = v1 - v2;
	cout << "Raznost' vektorov v1 v2 (=v5)" << endl;
	cout << v5 << endl;
	//proizvedenie
	Vector3D v6 = v1 * v2;
	cout << "Proizvedenie vektorov v1 v2 (=v6)" << endl;
	cout << v6 << endl;
	//proizvedenie na chislo
	Vector3D v7 = v1 * 2;
	cout << "Proizvedenie vektora v1 i chisla 2 (=v7)" << endl;
	cout << v7 << endl;
	// operatori sravneniya
	if (v1 == v2)
		cout << "v1 = v2" << endl;
	else cout << "v1 != v2" << endl;
	if (v1 < v7)
		cout << "v1 < v7" << endl;
	else cout << "v1 >= v7" << endl;
	_getch();
	return 0;
}

