#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>
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
		this->ocupat = false;
		this->tipDiscount = nullptr;
		this->aplicaDiscount = false;
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


	/*
	UPDATE NOT WORKING
	*/
	void update(int id1) {
		ifstream f("loc2.bin", ios::binary);
		fstream of("loc3.bin", ios::app);

		of.write((char*)&id, sizeof(id));
		of.write((char*)&coloana, sizeof(coloana));
		of.write((char*)&rand, sizeof(rand));

		of.write(tipDiscount, (long long)strlen(tipDiscount) + 1);
		of.write((char*)&numarRanduri, sizeof(numarRanduri));

		for (int i = 0; i < numarRanduri; i++)
		{
			of.write((char*)&randuriDezavantajate[i], sizeof(randuriDezavantajate[i]));
		}
		//f.close();

		int fileId;

		while (f.read((char*)&fileId, sizeof(fileId))) {
			if (fileId != id1) {
				int pos = f.tellg();
				f.read((char*)&coloana, sizeof(coloana));
				f.read((char*)&rand, sizeof(rand));

				string buffer = "";
				char c = 0;
				while ((c = f.get()) != 0)
				{
					buffer += c;
				}
				delete[] tipDiscount;
				tipDiscount = new char[buffer.length() + 1];
				strcpy_s(tipDiscount, buffer.length() + 1, buffer.c_str());

				f.read((char*)&numarRanduri, sizeof(numarRanduri));
				delete[] randuriDezavantajate;
				randuriDezavantajate = new int[numarRanduri];
				for (int i = 0; i < numarRanduri; i++)
				{
					f.read((char*)&randuriDezavantajate[i], sizeof(randuriDezavantajate[i]));
				}
				int pos2 = f.tellg();

				of.write((char*)&id, sizeof(id));
				of.write((char*)&coloana, sizeof(coloana));
				of.write((char*)&rand, sizeof(rand));

				of.write(tipDiscount, (long long)strlen(tipDiscount) + 1);
				of.write((char*)&numarRanduri, sizeof(numarRanduri));

				for (int i = 0; i < numarRanduri; i++)
				{
					of.write((char*)&randuriDezavantajate[i], sizeof(randuriDezavantajate[i]));
				}
			}
		}

		of.close();
		f.close();

		if (remove("loc2.bin") != 0)
			cout << "Fisierul a fost sters" << endl;

		if (rename("loc3.bin", "loc2.bin") != 0)
			cout << "Fisierul a fost modificat";
	}

	int getNumarRanduri() {
		return numarRanduri;
	}

	void deleteLoc (int id1) {
		ifstream f("loc2.bin", ios::binary);
		ofstream of("loc3.bin", ios::app);

		int fileId;

		while (f.read((char*)&fileId, sizeof(fileId))) {
			if (fileId != id1) {
				int pos = f.tellg();
				f.read((char*)&coloana, sizeof(coloana));
				f.read((char*)&rand, sizeof(rand));

				string buffer = "";
				char c = 0;
				while ((c = f.get()) != 0)
				{
					buffer += c;
				}
				delete[] tipDiscount;
				tipDiscount = new char[buffer.length() + 1];
				strcpy_s(tipDiscount, buffer.length() + 1, buffer.c_str());

				f.read((char*)&numarRanduri, sizeof(numarRanduri));
				delete[] randuriDezavantajate;
				randuriDezavantajate = new int[numarRanduri];
				for (int i = 0; i < numarRanduri; i++)
				{
					f.read((char*)&randuriDezavantajate[i], sizeof(randuriDezavantajate[i]));
				}
				int pos2 = f.tellg();

				of.write((char*)&id, sizeof(id));
				of.write((char*)&coloana, sizeof(coloana));
				of.write((char*)&rand, sizeof(rand));

				of.write(tipDiscount, (long long)strlen(tipDiscount) + 1);
				of.write((char*)&numarRanduri, sizeof(numarRanduri));

				for (int i = 0; i < numarRanduri; i++)
				{
					of.write((char*)&randuriDezavantajate[i], sizeof(randuriDezavantajate[i]));
				}
			}
		}

		of.close();
		f.close();

		if (remove("loc2.bin") != 0)
			cout << "Fisierul a fost sters" << endl;

		if (rename("loc3.bin", "loc2.bin") != 0)
			cout << "Fisierul a fost modificat";
	}

 
	void serializare() {
		fstream f("loc2.bin", ios::binary | ios::app);

		f.write((char*)&id, sizeof(id));
		f.write((char*)&coloana, sizeof(coloana));
		f.write((char*)&rand, sizeof(rand));

		f.write(tipDiscount, (long long)strlen(tipDiscount) + 1);
		f.write((char*)&numarRanduri, sizeof(numarRanduri));

		for (int i = 0; i < numarRanduri; i++)
		{
			f.write((char*)&randuriDezavantajate[i], sizeof(randuriDezavantajate[i]));
		}
		f.close();
	}

	void deserializare(fstream f, int id) {

		int fileId;

		while (f.read((char*)&fileId, sizeof(fileId))) {
			if (fileId == id) {

				this->id = fileId;
				f.read((char*)&coloana, sizeof(coloana));
				f.read((char*)&rand, sizeof(rand));

				string buffer = "";
				char c = 0;
				while ((c = f.get()) != 0)
				{
					buffer += c;
				}
				delete[] tipDiscount;
				tipDiscount = new char[buffer.length() + 1];
				strcpy_s(tipDiscount, buffer.length() + 1, buffer.c_str());

				f.read((char*)&numarRanduri, sizeof(numarRanduri));
				delete[] randuriDezavantajate;
				randuriDezavantajate = new int[numarRanduri];
				for (int i = 0; i < numarRanduri; i++)
				{
					f.read((char*)&randuriDezavantajate[i], sizeof(randuriDezavantajate[i]));
				}
			}
		}
		f.close();

		cout<<this;
	}

	void deserializare(int id) {
		ifstream f("loc2.bin", ios::binary);
		
		int fileId;

		while (f.read((char*)&fileId, sizeof(fileId))) {
			if (fileId == id) {

				this->id = fileId;
				f.read((char*)&coloana, sizeof(coloana));
				f.read((char*)&rand, sizeof(rand));

				string buffer = "";
				char c = 0;
				while ((c = f.get()) != 0)
				{
					buffer += c;
				}
				delete[] tipDiscount;
				tipDiscount = new char[buffer.length() + 1];
				strcpy_s(tipDiscount, buffer.length() + 1, buffer.c_str());

				f.read((char*)&numarRanduri, sizeof(numarRanduri));
				delete[] randuriDezavantajate;
				randuriDezavantajate = new int[numarRanduri];
				for (int i = 0; i < numarRanduri; i++)
				{
					f.read((char*)&randuriDezavantajate[i], sizeof(randuriDezavantajate[i]));
				}
			}
		}
		f.close();
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
	else {
		string niciundiscount = "niciun discount";
		l.tipDiscount = new char[niciundiscount.length() + 1];
		strcpy_s(l.tipDiscount, niciundiscount.length() + 1, niciundiscount.c_str());
	}
	
	return in;
}

