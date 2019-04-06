#include "Dictionary.h"

Dictionary::Dictionary() // конструктор по умолчанию
{
	count = 0;
	realCount = 0;
	ArrDict = new Word[realCount];
	
	
}

Dictionary::Dictionary(const Dictionary& _dict) // копирования
{
	count = _dict.count;
	realCount = _dict.realCount;
	
	for (int i = 0; i < count; ++i)
	{
		ArrDict[i] = copy(_dict.ArrDict[i]);
	}
}

Dictionary::Dictionary(const string& _eng, const string& _rus) // с параметрами
{
	count = 0;
	realCount = 0;
	AddWord(_eng);
	AddTranslate(_rus, count);
	
}

Dictionary::~Dictionary() // деструктор
{
	if (count > 0)
	{
		for (int i = 0; i < count; ++i)
		{
			delete[] ArrDict[i].rus;
		}
	}
	delete[] ArrDict;
	count = 0;
	realCount = 0;
}

Word Dictionary::copy (const Word& _wrd) // копирует все поля структуры word, то есть, копирует значения одной строки словаря
{
	Word word;
	word.eng = _wrd.eng;
	word.leng = _wrd.leng;
	word.realL = _wrd.realL;
	word.rus = new string[word.realL];
	for (int i = 0; i < word.leng; ++i)
		word.rus[i] = _wrd.rus[i];
	return word;
}

void Dictionary::AddWord(const string& _eng) // добавляет новое слово в словарь 
{
	
	if (count > 0)
	{ 
		if (count == realCount) // проверяет, не закончился ли выделенный под слова в словаре запас
		{                       // если закончился, то создает временный словарь, копирует туда все существующие на данный момент слова, затем расширяет исходный словарь и добавляет туда новое слово   
			temp_ArrDict = new Word[count];
			for (int i = 0; i < count; ++i)
			{
				temp_ArrDict[i] = copy(ArrDict[i]);
			}
			count++;
			realCount += 50;
			delete[] ArrDict;
			ArrDict = new Word[realCount];
			for (int i = 0; i < count - 1; ++i)
			{
				ArrDict[i] = copy(temp_ArrDict[i]);
			}
			ArrDict[count - 1].eng = _eng;
			ArrDict[count - 1].leng = 0;
			ArrDict[count - 1].realL = 0;
			ArrDict[count - 1].rus = new string[ArrDict[count - 1].realL];


			for (int i = 0; i < count - 1; ++i)
			{
				delete[] temp_ArrDict[i].rus;
			}
			delete[] temp_ArrDict;
		}
		else // если же запас еще есть, то просто добавляет новое слово
		{
			count++;
			ArrDict[count - 1].eng = _eng;
			ArrDict[count - 1].leng = 0;
			ArrDict[count - 1].realL = 0;
			ArrDict[count - 1].rus = new string[ArrDict[count - 1].realL];
		}
	}
	else if (count == 0) // для случая, если это первое слово
	{
		count++;
		realCount += 50;
		ArrDict = new Word[realCount];
		ArrDict[count - 1].eng = _eng;
		ArrDict[count - 1].leng = 0;
		ArrDict[count - 1].realL = 0;
		ArrDict[count - 1].rus = new string[ArrDict[count - 1].realL];
	}	
}

void Dictionary::AddTranslate(const string& _str, int _count) // дейтвует аналогично функции добавления нового слова
{
	
	if (ArrDict[_count].leng == ArrDict[_count].realL)
	{
		ArrDict[_count].temp_rus = new string[ArrDict[_count].leng];
		for (int i = 0; i < ArrDict[_count].leng; ++i)
		{
			ArrDict[_count].temp_rus[i] = ArrDict[_count].rus[i];
		}
		ArrDict[_count].leng++;
		ArrDict[_count].realL += 50;
		delete[] ArrDict[_count].rus;
		ArrDict[_count].rus = new string[ArrDict[_count].realL];
		for (int i = 0; i < ArrDict[_count].leng - 1; ++i)
		{
			ArrDict[_count].rus[i] = ArrDict[_count].temp_rus[i];
		}
		ArrDict[_count].rus[ArrDict[_count].leng - 1] = _str;

		delete[] ArrDict[_count].temp_rus;
	}
	else
	{
		ArrDict[_count].leng++;
		ArrDict[_count].rus[ArrDict[_count].leng - 1] = _str;

	}
	if (ArrDict[_count].leng == 0)
	{
		ArrDict[_count].leng++;
		ArrDict[_count].realL += 50;
		ArrDict[_count].rus = new string[ArrDict[_count].realL];
		ArrDict[_count].rus[ArrDict[_count].leng - 1] = _str;
	}
}

void Dictionary::ChangeTranslate(int _count, const string& _str, int cnt) //функция меняет заданный перевод заданного слова словаря
{
	for (int i = 0; i < _str.length(); ++i) // возбуждение исключения для случая ввода русских слов
	{
		if (_str[i] > 32)
			throw 2;
	}
	for (int i = 0; i < ArrDict[_count].leng; ++i) //выбирает перевод заданного слова с нужным индексом и затем заменяет его 
	{
		cout << i + 1 << ") " << ArrDict[_count].rus[i] << endl;
	}
	int count;
	ArrDict[_count].rus[cnt - 1] = _str;
}

void Dictionary::ShowTranslate(int _count) // выводит варианты перевода заданного слова на экран
{
	for (int i = 0; i < ArrDict[_count].leng; ++i)
	{
		cout << endl << i + 1 << ") " << ArrDict[_count].rus[i];
	}
	cout << endl;
}

int Dictionary::GetCount() const // возвращает текущую длину словаря
{
	return count;
}

int Dictionary::FindWord(const string& _str) // функция возвращает индекс слова в словаре, если оно там содержится и -1 в противном случае 
{
	
	for (int i = 0; i < count; ++i)
	{
		if (_str == ArrDict[i].eng)
		{			
			return i;
		}
	}
	return -1;
}

Dictionary& Dictionary::operator= (const Dictionary& dict) // перегрузка операции присваивания
{
	if (this != &dict)
	{
		if (count < dict.count)
		{
			ArrDict = new Word[dict.count];
		}
		count = dict.count;
		for (int i = 0; i < count; ++i)
		{
			ArrDict[i] = copy(dict.ArrDict[i]);
		}
	}
	return *this;
}

Dictionary& Dictionary::operator+= (const Dictionary& _dict) // перегрузка операции объединения словарей
{
	temp_ArrDict = new Word[count];
	for (int i = 0; i < count; ++i)
	{
		temp_ArrDict[i] = copy(ArrDict[i]);
	}
	int cnt = count + _dict.count;
	ArrDict = new Word[cnt];
	for (int i = 0; i < count; ++i)
	{
		ArrDict[i] = copy(temp_ArrDict[i]);
	}
	for (int i = count; i < cnt; ++i)
	{
		ArrDict[i] = copy(_dict.ArrDict[i - count]);
	}
	count = cnt;
	return *this;
}

istream& operator>> (istream& stream, Dictionary& _dict) // перегрузка операции ввода из потока
{
	string eng;
	string rus;

	char str[256];
	char ch = 0;
	stream.getline(str, 256);
	if(stream.getline(str, 256, ':'))
		do
		{
			stream.get(ch);
			eng = str;
			_dict.AddWord(eng);

			while (stream.getline(str, 256, ';'))
			{
				rus = str;
				_dict.AddTranslate(rus, _dict.count - 1);
				stream.get(ch);
				if (ch == '\n')
					break;
			}
		} while (stream.getline(str, 256, ':'));
	return stream;
}

ostream& operator<< (ostream& stream, const Dictionary& _dict) // вывода в поток
{
	stream << "\"Dictionary\" ver. 1.2";
	for (int j = 0; j < _dict.count; ++j)
	{
		stream << endl << "Word: " << _dict.ArrDict[j].eng << "; Translate: ";
		for (int i = 0; i < _dict.ArrDict[j].leng; ++i)
		{
			if (i < _dict.ArrDict[j].leng - 1)
				stream << _dict.ArrDict[j].rus[i] << ", ";
			else
				stream << _dict.ArrDict[j].rus[i] << ";";
		}
	}
	return stream;
}

void Dictionary::ProverkaVvodaRus(const string& _str)
{
	for (int i = 0; i < _str.length(); ++i)
	{
		if (_str[i] > 32)
			throw 2; // возбуждение исключения для случая ввода русских слов
	}
	
}

void Dictionary::ProverkaVvodaEng(const string& _str)
{
	for (int i = 0; i < _str.length(); ++i)
	{
		if (_str[i] < 65 || (_str[i] > 90 && _str[i] < 97) || _str[i] > 122)
			throw 1; // возбуждение исключения для случая ввода английских слов
	}
}