#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


struct Word // структура, содержащая информацию об одной строке словаря, то есть, слово и варианты его перевода
{
	string eng; // само слово в словаре
	string *rus; // массив, в котором содержатся строки - варианты перевода слова
	int leng; // число переводов этого слова
	int realL; // по сути, позволяет создать массив слов-переводов с запасом, чтобы слишком часто не создавать новых массивов при добавлении новых переводов
	string *temp_rus; // временный словарь на тот случай, если все таки запас закончится и придется перекинуть в него все существующие переводы слова для расширения текущего массива, содержащего переводы
};

class Dictionary
{
	Word *ArrDict; //массив слов словаря
	Word *temp_ArrDict; //временный массив слов, аналогично масиву переводов
	int count; // длина словаря
	int realCount; // запас длины словаря, аналогично запасу словаря переводов
	
public:
	void ProverkaVvodaRus(const string& _str); // методы, необходимые
	void ProverkaVvodaEng(const string& _str); // для проверки ввода пользователем слов аглийского и русского алфавитов, в них приисходит возбуждение исключений
	void AddWord(const string& _eng); // добывление строки в словарь
	Word copy(const Word& _wrd); // копирование строки словаря
	void ChangeTranslate(int _count, const string& _str, int cnt); // замена одного из переводов слова в словаре
	void AddTranslate(const string& _str, int _count); //добавление перевода слова
	void ShowTranslate(int _count); // показывает варианты перевода слова
	int GetCount() const; // возвращает текущую длину словаря
	int FindWord(const string& _str); // функция поиска слова в словаре
	Dictionary(); // конструктор по умолчанию
	Dictionary(const string& _eng, const string& _rus); // с параметрами
	Dictionary(const Dictionary& _dict); // копирования
	~Dictionary(); // деструктор
	Dictionary& operator= (const Dictionary& dict); // перегрузка операции присваивания
	Dictionary& operator+= (const Dictionary& _dict); // перегрузка операции объединения словарей
	friend istream& operator>> (istream& stream, Dictionary& _dict); // перегрузка операции ввода из потока
	friend ostream& operator<< (ostream& stream, const Dictionary& _dict); // вывода в поток
};

