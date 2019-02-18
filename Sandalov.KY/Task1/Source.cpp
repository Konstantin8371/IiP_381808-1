#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <math.h>
// Версия 2: Добавлен комментприй 
int stinint(const char str[]) //перевод строкового представления числа в числовое(int)
{
	int res = 0;
	while (*str)
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return res;
}
int main()
{
	int m, n = 0, i = 0;
	char str[15] = "111001";
	m = stinint(str);
	printf("%d\n", m);
	while (m != 0)
	{
		n = n + ((m % 10) * int(pow(2, i)));
		m = m / 10;
		i++;
	}
	printf("%d", n); 
	getchar();
	getchar();
}