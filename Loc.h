#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;

class Loc {

private:
	int id;
	int rand;
	int coloana;
	bool ocupat;

	const static int discount;
	char* tipDiscount;
	bool aplicaDiscount;

	int* randuriDezavantajate;
	int numarRanduri;

public:

	Loc() :id(0) {
		this->rand = 0;
		this->coloana = 0;
		this->numarRanduri = 0;
		this->randuriDezavantajate = nullptr;
		this->tipDiscount = nullptr;
	}

	Loc(int rand, int* randuriDezavantajate, char* tipDiscount, bool ocupat, bool aplicaDiscount, int numarRanduri, int coloana) : id(id) {
		this->ocupat = ocupat;
		this->aplicaDiscount = aplicaDiscount;
		setRand(rand);
		setColoana(coloana);

		if (randuriDezavantajate != nullptr && numarRanduri > 0) {
			this->randuriDezavantajate = new int[numarRanduri];
			this->numarRanduri = numarRanduri;
			for (int i = 0; i < numarRanduri; i++) {
				this->randuriDezavantajate[i] = randuriDezavantajate[i];
			}
		}
		else {
			this->randuriDezavantajate = nullptr;
			this->numarRanduri = 0;
		}

		if (tipDiscount != nullptr) {
			this->tipDiscount = new char[strlen(tipDiscount) + 1];
			strcpy_s(this->tipDiscount, strlen(tipDiscount) + 1, tipDiscount);
		}
		else {
			this->tipDiscount = nullptr;
		}
	}

	void setAplicaDiscount(bool aplica) {
		this->aplicaDiscount = aplica;
	}

	bool getAplicaDiscount() {
		return this->aplicaDiscount;
	}

	void setId(int id) {
		this->id = id;
	}

	void setRanduriDezavantajate(const int* randuri, int numarRanduri) {
		if (this->randuriDezavantajate != nullptr) {
			delete[] this->randuriDezavantajate;
		}

		if (randuri != nullptr && numarRanduri > 0) {
			this->randuriDezavantajate = new int[numarRanduri];
			this->numarRanduri = numarRanduri;
			for (int i = 0; i < numarRanduri; i++) {
				randuriDezavantajate[i] = randuri[i];
			}
		}
		else {
			randuriDezavantajate = nullptr;
			this->numarRanduri = 0;
		}
	}

	int* getRanduriDezavantajate() {
		return randuriDezavantajate;
	}


	static int getDiscount() {
		return discount;
	}

	void setTipDiscount(const char * discount) {
		if (this->tipDiscount != nullptr) {
			delete[] tipDiscount;
		}

		if (discount != nullptr) {
			this->tipDiscount = new char[strlen(discount) + 1];
			strcpy_s(this->tipDiscount, strlen(discount) + 1, discount);
		}

		else {
			this->tipDiscount = nullptr;
		}
	}

	char* getTipDiscount() {
		return tipDiscount;
	}

	void setRand(int rand) {
		if (rand >= 0) {
			this->rand = rand;
		}
	}

	void setNumarRanduri(int nrRanduri) {
		if (nrRanduri > 0) {
			this->numarRanduri = nrRanduri;
		}
	}

	void setColoana(int coloana) {
		if (coloana >= 0) {
			this->coloana = coloana;
		}
	}

	int getColoana() {
		return coloana;
	}

	int getRand() {
		return rand;
	}

	void setOcupat(bool ocupat) {
		this->ocupat = ocupat;
	}

	bool getOcupat() {
		return ocupat;
	}

	int getId() {
		return id;
	}

	//copy constructor
	Loc(const Loc& l) : id(l.id) {
		setRand(l.rand);
		setColoana(l.coloana);
		this->ocupat = l.ocupat;
		this->aplicaDiscount = l.aplicaDiscount;

		if (l.tipDiscount != nullptr) {
			int len = strlen(l.tipDiscount) + 1;
			tipDiscount = new char[len];
			strcpy_s(tipDiscount, len, l.tipDiscount);
		}
		else {
			tipDiscount = nullptr;
		}

		if (l.randuriDezavantajate != nullptr && l.numarRanduri > 0) {
			this->randuriDezavantajate = new int[l.numarRanduri];
			this->numarRanduri = l.numarRanduri;
			for (int i = 0; i < l.numarRanduri; i++) {
				this->randuriDezavantajate[i] = l.randuriDezavantajate[i];
			}
		}
		else {
			this->randuriDezavantajate = nullptr;
		}
	}

	~Loc() {

		if (randuriDezavantajate != nullptr) {
			delete[] randuriDezavantajate;
		}

		if (tipDiscount != nullptr) {
			delete[] tipDiscount;
		}
	}


	Loc& operator=(const Loc& l) {
		if (randuriDezavantajate != nullptr) {
			delete[] randuriDezavantajate;
		}

		if (tipDiscount != nullptr) {
			delete[] tipDiscount;
		}

		setRand(l.rand);
		setColoana(l.coloana);
		this->ocupat = l.ocupat;
		this->aplicaDiscount = l.aplicaDiscount;

		if (l.randuriDezavantajate != nullptr && l.numarRanduri > 0) {
			randuriDezavantajate = new int[l.numarRanduri];
			this->numarRanduri = l.numarRanduri;
			for (int i = 0; i < l.numarRanduri; i++) {
				this->randuriDezavantajate[i] = l.randuriDezavantajate[i];
			}
		}
		else {
			this->randuriDezavantajate = nullptr;
		}

		if (l.tipDiscount != nullptr) {
			this->tipDiscount = new char[strlen(l.tipDiscount) + 1];
			strcpy_s(this->tipDiscount, strlen(l.tipDiscount) + 1, l.tipDiscount);
		}
		else {
			this->tipDiscount = nullptr;
		}

		return *this;
	}

	bool operator! () {
		return ocupat;
	}

	Loc operator++(int i) {
		Loc copie = *this;
		this->rand++;
		return *this;
	}

	Loc operator++() {
		this->rand++;
		return *this;
	}

	Loc operator--() {
		this->rand--;
		return*this;
	}

	Loc operator-(int coloana) {
		if (coloana >= 0) {
			Loc copie = *this;
			copie.coloana -= coloana;
			return copie;
		}
		else {
			throw exception("coloana nu exista");
		}
	}

	Loc operator+(int coloana) {
		if (coloana >= 0) {
			Loc copie = *this;
			copie.coloana += coloana;
			return copie;
		}
		else {
			throw exception("coloana nu exista");
		}
	}

	bool operator[] (int rand)
	{
		if (randuriDezavantajate != nullptr && rand >= 0 && rand <= numarRanduri) {
			for (int i = 0; i < numarRanduri; i++) {
				if (randuriDezavantajate[i] == rand) {
					return true;
				}
			}
			return false;
		}
	}

	explicit operator int() {
		return coloana;
	}


	friend ostream& operator<<(ostream&, Loc);
	friend istream& operator>>(istream&, Loc&);
};


ostream& operator<<(ostream& out, Loc l) {
	cout << "\nRand: ";
	out << l.rand << endl;

	cout << "Coloana: ";
	out << l.coloana << endl;

	cout << "Ocupat: ";
	out << l.ocupat << endl;

	if (l.aplicaDiscount) {
		cout << "Discount: ";
		out << l.discount << endl;

		out << "Se aplica discountul: ";
		out << l.tipDiscount;
		out << "In valoare de: ";
		out << l.discount;
	}

	return out;
}


istream& operator>>(istream& in, Loc& l) {

	cout<< "Introduceti id-ul locului: ";
	in>>l.id;

	cout << "Introduceti randul locului: (numeric) ";
	in >> l.rand;

	cout << "Introduceti coloana locului: (numeric) ";
	in >> l.coloana;

	cout << "Introduceti numarul de coloane dezavantajate: ";
	in >> l.numarRanduri;

	if (l.randuriDezavantajate != nullptr) {
		delete[] l.randuriDezavantajate;
	}

	if (l.numarRanduri > 0) {	

		l.randuriDezavantajate = new int[l.numarRanduri];

		for (int i = 0; i < l.numarRanduri; i++) {
			cout << "Introduceti randul dezavantajat (numeric): ";
			in >> l.randuriDezavantajate[i];
		}

	}
	else {
		l.numarRanduri = 0;
		l.randuriDezavantajate = nullptr;
	}

	cout << "Acest loc beneficiaza de discount?: pentru da introudceti 1 / pentru nu introduceti 0 ";
	in >> l.aplicaDiscount;

	if (l.aplicaDiscount) {
		cout << "Introduceti o denumire pentru discount: ";
		string buffer;
		in >> ws;
		getline(in, buffer);
		l.tipDiscount = new char[buffer.length() + 1];
		strcpy_s(l.tipDiscount, buffer.length() + 1, buffer.c_str());
	}
	
	return in;
}

