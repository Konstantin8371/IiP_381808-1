#include "Vector3D.h"
#include <conio.h>
#include <locale>
using namespace std;

int main() {

	setlocale(LC_ALL, "Russian");
	Vector3D v1, v2;
	// Vvodim znacheniya koordinat nachalnoy i conechnoy tochek, vvod vektorov iz potoka
	cout << "Vvedite v1(x2 y2 z2): ";
	cin >> v1;
	cout << "Vvedite v2(x2 y2 z2): ";
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
	double s = v1 * v2;
	cout << "Skalyarnoe proizvedenie vektorov v1 v2 (=v6)" << endl;
	cout << s << endl;
	//proizvedenie skalyara na vector
	double a = 0.5;
	Vector3D v7 = a * v1;
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

