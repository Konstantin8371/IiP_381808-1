#include "Octal.h"
// конструктор по умолчанию
Octal::Octal()
{
	size = 0;
	lng = 0;
	octa = 0;
}
// конструктор с задаваемым размером массива
Octal::Octal(int _size)
{
	lng = size = _size;
	octa = new unsigned char[size];
	for (int i = 0; i < lng; ++i)
		octa[i] = 0;
}
// конструктор преобразования типа из строки
Octal::Octal(const string& _str)
{
	lng = size = _str.length();
	octa = new unsigned char[size];
	for (int i = 0; i < lng; ++i)
		if (_str[lng - 1 - i] - '0' >= 0 && _str[lng - 1 - i] - '0' < 8)
			octa[i] = _str[lng - 1 - i] - '0';
		else
			throw Exeption(strNOTOCTA, lng - i); // возбуждение исключения в случае, если неверно введен символ восьмеричного числа
}
// конструктор копирования
Octal::Octal(const Octal& _oct)
{
	lng = size = _oct.size;
	octa = new unsigned char[size];
	for (int i = 0; i < lng; ++i)
		octa[i] = _oct.octa[i];

}
// функция, которая позволяет выбрать длины наименьшего и наибольшего чисел и возвращает через параметры эти длины и указатели на большее и меньшее восьмеричные числа
void find_min_max(unsigned char* octa, unsigned char* _octa, int lng, int _lng, int* mins, int* maxs, unsigned char** max_a, unsigned char** min_b)
{
	
	if (lng < _lng)
	{
		*mins = lng;
		*min_b = octa;
		*max_a = _octa;
		*maxs = _lng;
	}
	else
	{
		*mins = _lng;
		*min_b = _octa;
		*max_a = octa;
		*maxs = lng;
	}
	return;
}
// перегрузка оператора присваивания
Octal& Octal::operator= (const Octal& _oct)
{
	if (this != &_oct)
	{
		if (lng != _oct.lng)
		{
			lng = size = _oct.size;
			delete[] octa;
			octa = new unsigned char[size];
		}
		for (int i = 0; i < lng; ++i)
			octa[i] = _oct.octa[i];
	}
	return *this;
}
// перегрузка арифметических оператотров
// +
Octal Octal::operator+ (const Octal& _oct)
{
	int mins, maxs; // длины большего и меньшего числа
	unsigned char *max_a, *min_b; // указатели на большее и меншее числа
	find_min_max(octa, _oct.octa, lng, _oct.lng, &mins, &maxs, &max_a, &min_b);
	Octal tmp(maxs + 1); // создаем объект класса с длиной наибольшего числа + 1, то есть, с запасом на появление еще одного разряда восьмеричного числа при переходе
	int pls = 0; // переход от суммы двух цифр разряда в следующий 
	for (int i = 0; i < mins; ++i) // происходит сложение меньшего числа с большим, пока меньшее не закончится
	{
		tmp.octa[i] = (octa[i] + _oct.octa[i] + pls) % 8;
		pls = (octa[i] + _oct.octa[i] + pls) / 8;
	}
	if (_oct.lng != lng) // дальше, если длины двух чисел не равны, мы просто сносим оставшуюся часть большего числа, проверяя переход в следующий разряд
	{
		for (int i = mins; i < maxs; ++i)
		{
			tmp.octa[i] = (max_a[i] + pls) % 8;
			pls = (max_a[i] + pls) / 8;
			
		}
		if (pls == 0) // смотрим на последний переход, если он равен нулю, то фактическую длину числа делаем равной длине наибольшего из слагаемых
		{
			tmp.lng = maxs;
		}
		else // иначе оставляем на один разряд больше, присваивая ему значение 1
		{
			tmp.octa[maxs] = 1;
			pls = 0;
		}
	}
	else
	{
		if (pls == 0)
		{
			tmp.lng = mins;
		}
		else
		{
			tmp.lng = mins + 1;
			tmp.octa[mins] = 1;
			pls = 0;
		}
	}
	return tmp;
}
//начало аналогично с оператором +
Octal Octal::operator- (const Octal& _oct)
{
	int mins, maxs;
	unsigned char *max_a, *min_b;
	find_min_max(octa, _oct.octa, lng, _oct.lng, &mins, &maxs, &max_a, &min_b);
	Octal tmp(maxs);
	unsigned char pls = 0; // занимаем из старшего разряда
	for (int i = 0; i < mins; ++i) // вычитание из большего меньшего, пока меньшее не заканчивается
	{
		
		if (octa[i] - pls < _oct.octa[i])
		{
			tmp.octa[i] = octa[i] - pls + 8 - _oct.octa[i];
			pls = 1;
		}
		else
		{
			tmp.octa[i] = octa[i] - pls - _oct.octa[i];
			pls = 0;
		}
	}
	if (lng != _oct.lng) // и если длины чисел не равны, то сносим оставшуюся часть большего числа
	{
		for (int i = mins; i < maxs; ++i)
		{
			if (lng < _oct.lng) // если длина числа, из которого вычитают будет меньше длины вычитаемого (по сути, вычитаем из 0)
			{
				tmp.octa[i] = 8 - (_oct.octa[i] + pls);
				pls = 1;
			}
			else // сносим оставшиеся разряды числа из которого вычитаем, проверяя, занимаем мы из старших разрядов или нет
			{
				if (octa[i] - pls < 0)
				{
					tmp.octa[i] = octa[i] - pls + 8;
					pls = 1;
				}
				else
				{
					tmp.octa[i] = octa[i] - pls;
					pls = 0;
				}
			}
		}
	}
	return tmp;
}
// начало аналогично с оператором +
Octal Octal::operator* (const Octal& _oct)
{
	int mins, maxs;
	unsigned char *max_a, *min_b;
	find_min_max(octa, _oct.octa, lng, _oct.lng, &mins, &maxs, &max_a, &min_b);
	Octal tmp(maxs + mins); // длину числа, которое получится в результате умножения берем с запасом + 1, в случае появления нового при переходе из последнего
	for (int i = 0; i < mins; ++i) // производим умножение большего числа на отдельные цифры меньшего, начиная с 1-ой со смещением на 1 разряд и просто складываем эти произведения
	{
		unsigned char pls = 0; //перенос в старший разряд
		Octal trnst(maxs + i + 1); // длина результата каждого произведения с учетом смещения на 1 разряд и запасом для появления нового разряда
		int j = 0;
		while(j < i) // обнуляем младщие разряды, с которых сместились
		{
			trnst.octa[j] = 0;
			j++;
		}
		int k = 0;
		for (j; j < maxs + i; j++) // умножение юольшего числа на отдельные цифры меньшего, начиная с 1-ой
		{
			if ((max_a[k] * min_b[i] + pls) < 8) // без переноса
			{
				trnst.octa[j] = max_a[k] * min_b[i] + pls;
				pls = 0;
			}
			else // в случае переноса в старший разряд
			{
				unsigned char ff = max_a[k] * min_b[i] + pls;
				while (ff - 8 >= 0)
					ff -= 8;
				trnst.octa[j] = ff;
				pls =((max_a[k] * min_b[i] + pls) / 8);
			}
			k++;
		}
		if (pls != 0) // проверяем, появился ли новый старший разряд, если да, то заполняем его, если нет, то фактическую длину произведения приравниваем к длине большего множителя
		{
			trnst.octa[maxs + i] = pls;
			pls = 0;
		}
		else
		{
			trnst.lng = trnst.size - 1;
		}
		tmp = tmp + trnst; // сумма произведений
		
	}
	
	return tmp;
}
// перегрузка операторов сравнения
bool Octal::operator== (const Octal& _oct)
{
	if (lng != _oct.lng) return false;
	for (int i = 0; i < _oct.lng; ++i)
	{
		if (octa[i] != _oct.octa[i])
			return false;
	}
	return true;
}

bool Octal::operator!= (const Octal& _oct)
{
	return !(*this == _oct);
}

bool Octal::operator> (const Octal& _oct)
{
	if (lng > _oct.lng)
	{
		return true;
	}
	if (lng < _oct.lng)
	{
		return false;
	}
	for (int i = lng - 1; i >= 0; --i)
	{
		if (octa[i] > _oct.octa[i])
			return true;
	}
	return false;

}

bool Octal::operator<= (const Octal& _oct)
{
	return !(*this > _oct);
}

bool Octal::operator< (const Octal& _oct)
{
	if (lng < _oct.lng)
	{
		return true;
	}
	if (lng > _oct.lng)
	{
		return false;
	}
	for (int i = lng - 1; i >= 0; --i)
	{
	if (octa[i] < _oct.octa[i])
		return true;	
	}
	return false;
}

bool Octal::operator>= (const Octal& _oct)
{
	return !(*this < _oct);
}
// перегрузка операторов поточного ввода-вывода
ostream& operator<< (ostream& stream, const Octal& _oct)
{
	if (_oct.octa[_oct.lng - 1] != 0) //при выводе проверяем наличие нулей на местах старших разрядов
	{
		for (int i = _oct.lng - 1; i >= 0; --i)
		{
			stream << (int)_oct.octa[i];
		}
		cout << endl;
	}
	else // и если они там стоят, то убираем лишние при выводе, то есть, просто не выводим их
	{
		int i = _oct.lng - 1;
		while (_oct.octa[i] == 0 && i >= 1)
		{
			i--;
		}
		for (int j = i; j >= 0; --j)
		{
			stream << (int)_oct.octa[j];
		}
		cout << endl;
	}
	return stream;
}

istream& operator>> (istream& stream, Octal& _oct)
{
	string str;
	stream >> str;
	_oct = str;
	return stream;
}
// деструктор
Octal::~Octal()
{
	lng = size = 0;
	delete[] octa;
}
