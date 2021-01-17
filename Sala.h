#pragma once
#include <iostream>
#include <string>
#include "Loc.h"
#include "Film.h"
using namespace std;

class Sala {

public:
	enum GenSala { clasic = 1, VIP = 2, Luxury = 3 };
	enum DimensiuneSala { mica = 1, medie = 2, mare = 3 };

private:
	const int idSala;
	int numarLocuri;
	char* numeSala;
	int adaosSala;
	int genSala;
	int dimensiuneSala;
	Loc* locuri;
	int nrLocuriOcupate;

	int* randuriDezavantajate;
	int numarRanduriDezavantajate;

	static string numeCinema;

	void setLocuri(const int coloane, const int randuri) {
		if (coloane != 0 && randuri != 0) {

			locuri = new Loc[coloane * randuri];
			this->numarLocuri = coloane * randuri;

			int x = 0;

			for (int i = 0; i < randuri; i++) {
				for (int j = 0; j < coloane; j++) {
					locuri[x].setId(stoi(to_string(idSala) + to_string(i) + to_string(j)));
					locuri[x].setRand(i);
					locuri[x].setColoana(j);
					locuri[x].setRanduriDezavantajate(randuriDezavantajate, numarRanduriDezavantajate);
					locuri[x].setOcupat(false);
					locuri[x].setNumarRanduri(randuri);
					x++;
				}
			}

			cout << "numar locuri x";
			cout << x << endl;

			int size = coloane * randuri;
			cout << "numar locuri ";
			cout << size << endl;

			for (int i = 0; i < numarLocuri; i++) {
				cout << locuri[i].getColoana();
				cout << locuri[i].getRand() << endl;
			}
		}
		else {
			this->locuri = nullptr;
			this->numarLocuri =0;
		}
	
	}

	void setLocuriSalaMica() {
		this->numarLocuri = 5 * 5;
		this->numarRanduriDezavantajate = 1;
		this->randuriDezavantajate = new int[] { 0 };
		setLocuri(5, 5);
	}

	void setLocuriSalaMedie() {
		this->numarLocuri = 10 * 10;
		this->numarRanduriDezavantajate = 3;
		this->randuriDezavantajate = new int[] { 0, 1, 2 };
		setLocuri(10, 10);
	}

	void setLocuriSalaMare() {
		this->numarLocuri = 20 * 20;
		this->numarRanduriDezavantajate = 5;
		this->randuriDezavantajate = new int[] { 0, 1, 2, 19, 20 };
		setLocuri(20, 20);
	}

	int getNumarRanduriDezavantajate() {
		return numarRanduriDezavantajate;
	}

	void setLocuriInFunctieDeDimensiune() {

		if (dimensiuneSala == Sala::DimensiuneSala::mica) {
			setLocuriSalaMica();
		}
		else if (dimensiuneSala == Sala::DimensiuneSala::medie) {
			setLocuriSalaMedie();
		}
		else if (dimensiuneSala == Sala::DimensiuneSala::mare) {
			setLocuriSalaMare();
		}
		else {
			this->locuri = nullptr;
			this->randuriDezavantajate = nullptr;
		}
	}

public:

	Sala() : idSala(0) {
		numeSala = nullptr;
		locuri = nullptr;
		randuriDezavantajate = nullptr;
	}

	Sala(char* numeSala, int gensala, int dimensiuneSala) : idSala(idSala) {

		this->locuri = nullptr;
		this->genSala = gensala;
		this->locuri = nullptr;

		setAdaos();

		if (numeSala != NULL) {
			this -> numeSala = new char[strlen(numeSala) + 1];
			strcpy_s(this ->numeSala, strlen(numeSala) + 1, numeSala);
		}
		else {
			numeSala = nullptr;
		}

		this->dimensiuneSala = dimensiuneSala;
		this->randuriDezavantajate = nullptr;
		setLocuriInFunctieDeDimensiune();
	}

	//copy constructor
	Sala(const Sala& s) : idSala(s.idSala) {

		if (s.numeSala != NULL) {
			numeSala = new char[strlen(s.numeSala) + 1];
			strcpy_s(numeSala, strlen(s.numeSala) + 1, s.numeSala);
		}
		else {
			numeSala = nullptr;
		}

		this -> genSala = s.genSala;
		this-> adaosSala = s.adaosSala;
		this-> dimensiuneSala = s.dimensiuneSala;

		setLocuriInFunctieDeDimensiune();

		if (s.randuriDezavantajate != nullptr) {
			this->randuriDezavantajate = s.randuriDezavantajate;
		}
		else {
			this->randuriDezavantajate = nullptr;
		}

		this->numarRanduriDezavantajate = s.numarRanduriDezavantajate;
	}

	~Sala() {
		if (locuri != nullptr) {
			delete[] locuri;
		}

		if (numeSala != nullptr) {
			delete[] numeSala;
		}

		if (randuriDezavantajate != nullptr) {
			delete[] randuriDezavantajate;
		}
	}

	Sala& operator=(const Sala& s) {
		if (locuri != nullptr) {
			delete[] locuri;
		}

		if (numeSala != nullptr) {
			delete[] numeSala;
		}

		if (randuriDezavantajate != nullptr) {
			delete[] randuriDezavantajate;
		}

		if (s.numeSala != NULL) {
			numeSala = new char[strlen(s.numeSala) + 1];
			strcpy_s(numeSala, strlen(s.numeSala) + 1, s.numeSala);
		}
		else {
			numeSala = nullptr;
		}

		genSala = s.genSala;
		this->adaosSala = s.adaosSala;
		dimensiuneSala = s.dimensiuneSala;


		if (s.locuri != nullptr && s.numarLocuri > 0) {
			locuri = s.locuri;
			numarLocuri = s.numarLocuri;
		}
		else {
			locuri = nullptr;
			numarLocuri = 0;
		}

		if (s.randuriDezavantajate != nullptr) {
			this->randuriDezavantajate = s.randuriDezavantajate;
		}
		else {
			this->randuriDezavantajate = nullptr;
		}

		this->numarRanduriDezavantajate = s.numarRanduriDezavantajate;

		return *this;
	}

	void setAdaos() {
		if (genSala == 1) {
			adaosSala = 0;
			}
		else if (genSala == 2) {
			adaosSala = 100;
		}
		else if (genSala == 3) {
			adaosSala = 300;
		}
	}

	void setGenSala(int genSala) {
		this->genSala;
		setAdaos();
	}

	void setNume(char* numeSala) {
		if (this->numeSala != nullptr) {
			delete[] this->numeSala;
		}
		if (numeSala != nullptr) {
			this->numeSala = new char[strlen(numeSala) + 1];
			strcpy_s(this->numeSala, strlen(numeSala) + 1, numeSala);
		}
		else {
			this->numeSala = nullptr;
		}
	}


	void setRanduriDezavantajate(int * randuri, int numarLocuri) {
		if (this-> randuriDezavantajate != nullptr) {
			delete[]this-> randuriDezavantajate;
		}

		if (randuri != nullptr && numarLocuri > 0) {
			randuriDezavantajate = randuri;
			this->numarLocuri = numarLocuri;
		}
		else {
			this->randuriDezavantajate = nullptr;
		}
	}

	char* getNume() {
		return numeSala;
	}


	static void setNumeCinema(string nume) {
		Sala::numeCinema = nume;
	}

	static string getNumeCinema() {
		return numeCinema;
	}

	bool operator! () {
		return genSala != 1;
	}

	bool operator+(int numarLocuriOcupate) {
		return numarLocuri - numarLocuriOcupate > 0;
	}

	Sala operator++() {
		this->adaosSala += 10;
		return *this;
	}

	Sala operator--() {
		this->adaosSala -= 10;
		return *this;
	}

	void printLocuriLibere(Loc* locuriOcupate, int size) {
		if (locuri != nullptr && numarLocuri > 0) {
			for (int i = 0; i < nrLocuriOcupate; i++) {
				for (int j = 0; j < numarLocuri; j++) {
					if (locuriOcupate[i].getRand() == locuri[j].getRand() && locuriOcupate[i].getColoana() == locuri[j].getColoana()) {
						locuri[j].setOcupat(true);
						break;
					}
				}
			}

			for (int i = 0; i < numarLocuri; i++) {
				if (locuri[i].getColoana() == 0) {
					cout << "\n";
				}
				if (locuri[i].getOcupat()) {
					cout << "| X X |";
					locuri[i].setOcupat(false);
				}
				else {
					cout << "| " + to_string(locuri[i].getRand()) + to_string(locuri[i].getColoana()) + " |";
				}
			}
		}
	}

	void operator[] (int idLoc)
	{
		for (int i = 0; i < numarLocuri; i++) {
			if (locuri[i].getColoana() == 0) {
				cout << "\n";
			}

			if (idLoc == locuri[i].getId()) {
				cout << " XX ";
			}
			else {
				cout << "| " + to_string(locuri[i].getRand()) + to_string(locuri[i].getColoana()) + " |";

			}
		}
	}

	explicit operator int() {
		return numarLocuri;
	}


	friend ostream& operator<<(ostream&, Sala);
	friend istream& operator>>(istream&, Sala&);

};

ostream& operator<<(ostream& out, Sala s) {
	out << "Nume sala: " << endl;
	out << s.numeSala << endl;

	out << "Numar locuri: " << endl;
	out << s.numarLocuri << endl;

	out << "Adaos sala: " << endl;
	out << s.adaosSala<< endl;

	out << "Gen sala: " << endl;
	if (s.genSala == Sala::GenSala::clasic) {
		out << "clasic";
	}
	else if (s.genSala == Sala::GenSala::VIP) {
		out << "VIP";
	}
	else if (s.genSala == Sala::GenSala::Luxury) {
		out << "Luxury";
	}
	out << s.genSala << endl;

	return out;
}


istream& operator>>(istream& in, Sala& s) {

	cout << "Introduceti o noua sala ";

	cout << "Introduceti numele salii ";
	string buffer;
	in >> ws;
	getline(in, buffer);
	s.numeSala = new char[buffer.length() + 1];
	strcpy_s(s.numeSala, buffer.length() + 1, buffer.c_str());

	cout << "Introduceti tipul salii: (1) - mica / (2) - medie / (3) - mare";
	in >> s.dimensiuneSala;

	cout << "Introduceti tipul salii: (1) - clasis / (2) - VIP / (3) - Luxury} ";
	in >> s.genSala;
	s.setAdaos();

	cout << "Adaos ";
	cout<< s.adaosSala;

	return in;
};

