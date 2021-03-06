//POP 2019-01-17 projekt 2 Wozniak Mateusz IBM 3 175610 Visual Studio 2017

#include "pch.h"
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

void plik();
void wzor(string, string, int, string);
void wykres(float*, int);
void zmiana(string, string&);
void zera(string&, string&);
int rezultat(float*, int, string);
void asci(int*, int*, string, string, int);
double mianownik(int*, int);

int main()
{
	plik();
}

void plik()
{
	string raz, uno, dwa, dos, S, P, nazwa1, nazwa2;
	ifstream plik1, plik2;
	dwa = "";
	raz = "";
	cout << "Podaj nazwe pierwszego pliku: ";
	cin >> nazwa1;
	cout << "Podaj nazwe drugiego pliku: ";
	cin >> nazwa2;
	plik1.open(nazwa1, ios::in);
	plik2.open(nazwa2, ios::in);
	system("cls");
	if (plik1.good() == false || plik2.good() == false)
	{
		cout << "Nie mozna otworzyc pliku!";
		exit(0);
	}
	while (!plik1.eof())
	{
		getline(plik1, uno);
		raz += uno;
	}
	while (!plik2.eof())
	{
		getline(plik2, dos);
		dwa += dos;
	}
	zmiana(raz, S);
	zmiana(dwa, P);
	zera(S, P);

	int M = S.length();

	wzor(S, P, M, nazwa2);

	plik1.close();
	plik2.close();
}

void wzor(string S, string P, int M, string nazwa2)
{
	float *wynik;
	wynik = new float[M];
	int *asci_S; 
	asci_S = new int[M];
	int *asci_P;
	asci_P = new int[M];
	asci(asci_S, asci_P, S, P, M);
	double suma, sumS, sumP;
	for (int n = -(M / 2); n <= (M / 2); n++)
	{
		suma = 0;
		for (int m = -(M / 2); m <= M / 2; m++) //licznik 
		{
			if ((n - m) >= -(M / 2) && (n - m) <= (M / 2)) //sprawdzenie czy nie wsporzedna nie wychodzi poza obszar stringa
			{
				suma += asci_S[(M / 2) + m] * asci_P[(M / 2) + n - m];
			}
		}	
		sumS = mianownik(asci_S, M);
		sumP = mianownik(asci_P, M);
		double CC;
		CC = suma / sqrt(sumS * sumP);
		wynik[(M / 2 + n)] = CC;
	}
	
	delete[] asci_P;
	delete[] asci_S;
	rezultat(wynik, M, nazwa2);
	wykres(wynik, M);
	delete[] wynik;

}

void wykres(float* wynik, int M)
{

	cout << setw(4);
	cout << "n";
	cout << "|                                      CC = 0.5--> O" << endl;
	for (int i = M - 1; i >= 0; i--)
	{
		
		cout << setw(4) << -(M / 2) + i;
		cout << "|";
			for (int j = 0; j < wynik[i] * 100; j++)
			{
				cout << "#";
			}
			if(wynik[i]*100 <= 50) cout << setw(51 - (wynik[i] * 100)) << "O";
			cout << "  CC[" << -(M / 2) + i << "] = " << wynik[i];
		cout << endl;
		cout << setw(5);
		cout << "|" <<setw(51) << "O" << endl;
	}
}

void zmiana(string raz, string& S)   //na male litery + usuwa spacje
{
	transform(raz.begin(), raz.end(), raz.begin(), ::tolower);
	for (int i = 0; i < raz.length(); i++)
	{
		if (!isalpha(raz[i]) && !((int)raz[i] > 47 && (int)raz[i] < 58))
		{
			raz[i] = ' ';
		};
	}

	S = "";
	char buf;
	stringstream ss(raz);
	while (ss >> buf) S += buf;
	
}

void zera(string& S, string& P) //dodaje zera do krotszego, jak parzyscie to wydluzyc
{
	int a = S.length();
	int b = P.length();


	if (a > b)
	{
		if (a % 2 == 0)
		{
			S += '0';
			a += 1;
		}
		for (int i = b; i <= a-1; i++)
		{
			P += '0';
		}
	}
	else if (a < b)
	{
		if (b % 2 == 0)
		{
			P += '0';
			b += 1;
		}
		for (int i = a ; i <= b-1; i++)
		{
			S += '0';
		}
	}
	else if (a == b && a%2 == 0)
	{
		S += '0';
		P += '0';
		a += 1;
		b += 1;
	}
}

int rezultat(float* wynik, int M, string nazwa2) 
{
	for (int i = 0; i < M; i++)
	{
		if (wynik[i] > 0.5)
		{
			cout << "PLIK " << nazwa2 << " TO PLAGIAT!!!" << endl << endl;

			return 0;
		}
	}
	cout << "PLIK" << nazwa2 << "NIE JEST PLAGIATEM" << endl;

	return 0;
}

void asci(int* asci_S, int* asci_P, string S, string P, int M) //zmiana na liczby 
{
	for (int i = 0; i < M; i++)
	{
		asci_S[i] = (int)S[i];
		asci_P[i] = (int)P[i];
	}
}

double mianownik(int* asci, int M)
{
	double sum = 0;
	for (int m = -(M / 2); m <= (M / 2); m++) //minownik
	{
		sum += asci[(M / 2) + m] * asci[(M / 2) - m];
	}

	return sum;
}