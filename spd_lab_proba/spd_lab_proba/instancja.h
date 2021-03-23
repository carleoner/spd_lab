#pragma once
#ifndef INSTANCJA_H
#define INSTANCJA_H
#include "RandomNumberGenerator.h"
#include "zadanie.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class instancja
{
public:
	instancja();
	~instancja();
	void wypiszTablice();
	//vector<zadanie> Schrage();
	void Schrage();

	int rozmiar;
	

private:
	vector <zadanie> wektor;
};

instancja::instancja()
{
	long ziarno;
	long suma = 0;
	cout << "Wprowadz ziarno losowania: ";
	cin >> ziarno;
	RandomNumberGenerator generator = RandomNumberGenerator(ziarno);

	cout << "Wprowadz rozmiar problemu: ";
	cin >> rozmiar;

	for (int i = 0; i < rozmiar; i++) {
		wektor.push_back(zadanie());
		wektor[i].j = i + 1;
	}
	for (int i = 0; i < rozmiar; i++) {
		wektor[i].p = generator.nextInt(1, 29);
		suma += wektor[i].p;
	}
	for (int i = 0; i < rozmiar; i++) {
		wektor[i].r = generator.nextInt(1, suma);
	}
	for (int i = 0; i < rozmiar; i++) {
		wektor[i].q = generator.nextInt(1, suma);
	}
}

instancja::~instancja()
{
}

void instancja::wypiszTablice() {

	cout << endl << "j: ";
	for (int i = 0; i < rozmiar; i++)
		cout << wektor[i].j << " ";
	cout << endl << "r: ";
	for (int i = 0; i < rozmiar; i++)
		cout << wektor[i].r << " ";
	cout << endl << "p: ";
	for (int i = 0; i < rozmiar; i++)
		cout << wektor[i].p << " ";
	cout << endl << "q: ";
	for (int i = 0; i < rozmiar; i++)
		cout << wektor[i].q << " ";
}

static bool compare_r(const zadanie& a, const zadanie& b) {
	return a.r < b.r;
}
static bool compare_q(const zadanie& a, const zadanie& b) {
	return a.q > b.q;
}

//vector<zadanie> instancja::Schrage() {
void instancja::Schrage() {
	long time = 0;
	int cmax = 0;
	
	//sortowanie po r - czas przygotowania
	sort(wektor.begin(), wektor.end(), compare_r);

	vector <zadanie> G;
	vector <zadanie> N;
	for (int i = 0; i < rozmiar; i++)
		N.push_back(wektor[i]);
	vector <zadanie> pi;

	time = wektor[0].r;

	while (!G.empty() || !N.empty()) {
		while (!N.empty() && N[0].r <= time) {
			G.push_back(N[0]);
			N.erase(N.begin());
		}
		if (!G.empty()) {
			sort(G.begin(), G.end(), compare_q);
			pi.push_back(G[0]);
			time = time + G[0].p;
			cmax = fmax(cmax, time + G[0].q);
			G.erase(G.begin());
		}
		else
			time = N[0].r;
	}

	cout << endl << cmax << endl;

	cout << endl << "j: ";
	for (int i = 0; i < rozmiar; i++)
		cout << pi[i].j << " ";
	cout << endl << "r: ";
	for (int i = 0; i < rozmiar; i++)
		cout << pi[i].r << " ";
	cout << endl << "p: ";
	for (int i = 0; i < rozmiar; i++)
		cout << pi[i].p << " ";
	cout << endl << "q: ";
	for (int i = 0; i < rozmiar; i++)
		cout << pi[i].q << " ";

	//return pi;

}


#endif // !INSTANCJA_H
