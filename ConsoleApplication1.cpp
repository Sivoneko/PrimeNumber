#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
#include <time.h>
using namespace std;

typedef unsigned long long ull;

vector<ull> SortNumbers(ull, ull);

bool CheckPalindrom(ull);

map<ull, pair<ull, ull>> FindBestPalindrom(vector<ull>);

int main()
{
	double t1 = clock();
	vector<ull> Primes = SortNumbers(10000, 99999);
	map<ull, pair<ull, ull>> Found = FindBestPalindrom(Primes);
	map<ull, pair<ull, ull>>::iterator Output = Found.begin();
	double t2 = clock() - t1;


	cout << "Polindrom: " << Output->first << endl;
	cout << "First multiplier: " << Output->second.first << " Second multiplier: " << Output->second.second << endl;
	cout << t2 / CLOCKS_PER_SEC << endl;
	system("pause");
	return 0;
}

//ищем все возможные простые числа от 10000 до 99999
vector<ull> SortNumbers(ull first, ull last)
{
	vector<ull> mda; // заполним вектор полученными простыми числами
	bool check = true;
	for (ull j(first); j < last; j++)
	{
		check = true;

		for (ull i = 2; i <= sqrt(j); i++) {
			if (j % i == 0) {
				//n  не простое, так как делится на i
				check = false;
				break;
			}
		}

		// n простое.
		if (check == true)
		{
			mda.push_back(j);
		}
	}
	return mda;
}
//проверяем относится ли число к полиндрому
bool CheckPalindrom(ull palindrom)
{
	ull z, y, x = 0;
	y = palindrom; z = y;
	while (y > 0)
	{
		x = x * 10 + y % 10;
		y /= 10;
	}
	if (z == x)
	{
		return true;
	}
	return false;
}
//умножаем наши 5-ти значные уже полученные простые числа и проверяем является ли полученное число полиндромом
map<ull, pair<ull, ull>> FindBestPalindrom(vector<ull> numbers)
{
	ull maxPol = 0;
	long long k = 0; // записываем в k индекс последнего множителя при котором мы получили максимальный полиндром
					 // ниже него идти нет смысла, поскольку все полученные числа будут меньше нашего полиндрома
	ull firstMultiplier = 0, SecondMultiplier = 0;
	for (unsigned int i(k); i < numbers.size(); i++) //начинаем перемножать с конца (с самых больших простых чисел)
	{
		for (unsigned int j(i); j < numbers.size(); j++)
		{
			ull a = (numbers[i] * numbers[j]);
			if (CheckPalindrom(a))
			{
				if (maxPol < a)
				{
					maxPol = a;
					firstMultiplier = numbers[i];
					SecondMultiplier = numbers[j]; 
					k = j;
					break;
				}
			}
		}
	}
	map<ull, pair<ull, ull>> returned;
	returned[maxPol] = make_pair(firstMultiplier, SecondMultiplier);
	return returned;

}