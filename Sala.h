#pragma once
#include <iostream>
#include <string>
#include "Loc.h"
#include <fstream>
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
	int* idLocuri;
	int nrLocuriOcupate;

	int* randuriDezavantajate;
	int numarRanduriDezavantajate;

	static string numeCinema;

	void setLocuri(const int coloane, const int randuri) {
		if (coloane != 0 && randuri != 0) {

			numarLocuri = coloane * randuri;
			this->idLocuri = new int[numarLocuri];

			int x = 0;

			for (int i = 1; i < randuri + 1; i++) {
				for (int j = 1; j < coloane + 1; j++) {
					int id = stoi(to_string(idSala) + to_string(i) + to_string(j));
					this-> idLocuri[x] = id;

					Loc* loc = new Loc();

					loc -> setId(stoi(to_string(idSala) + to_string(i) + to_string(j)));
					loc -> setRand(i);
					loc-> setColoana(j);
					loc->setRanduriDezavantajate(randuriDezavantajate, numarRanduriDezavantajate);

					/*
					int * randuriDezavantajate1 = new int[numarRanduriDezavantajate];

					for (int i = 0; i < numarRanduriDezavantajate; i++) {
						randuriDezavantajate1[i] = randuriDezavantajate[i];

					loc-> setRanduriDezavantajate(randuriDezavantajate1, numarRanduriDezavantajate);

					}
					*/

					loc-> setOcupat(false);

					char* tipDiscount;

					string niciundiscount = "niciun discount";
					tipDiscount = new char[niciundiscount.length() + 1];
					strcpy_s(tipDiscount, niciundiscount.length() + 1, niciundiscount.c_str());

					loc -> setTipDiscount(tipDiscount);
					loc-> serializare();

					delete[] tipDiscount;

					x++;
				}
			}

			cout << "numar locuri x";
			cout << x << endl;

			int size = coloane * randuri;
			cout << "numar locuri ";
			cout << size << endl;

			for (int i = 0; i < numarLocuri; i++) {
				cout << "id: " << idLocuri[i] << " ";
			}
		}
		else {
			this->idLocuri = nullptr;
			this->numarLocuri =0;
		}
	}

	void setLocuriSalaMica() {
		this->numarLocuri = 5 * 5;
		this->numarRanduriDezavantajate = 1;
		this->randuriDezavantajate = new int[] { 1 };
		setLocuri(5, 5);
	}

	void setLocuriSalaMedie() {
		this->numarLocuri = 10 * 10;
		this->numarRanduriDezavantajate = 3;
		this->randuriDezavantajate = new int[] { 1, 2, 3 };
		setLocuri(10, 10);
	}

	void setLocuriSalaMare() {
		this->numarLocuri = 20 * 20;
		this->numarRanduriDezavantajate = 4;
		this->randuriDezavantajate = new int[] { 1, 2, 19, 20 };
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
			this->idLocuri = nullptr;
			this->randuriDezavantajate = nullptr;
		}
	}

public:

	Sala(int id) : idSala(id) {
		numeSala = nullptr;
		idLocuri = nullptr;
		randuriDezavantajate = nullptr;
	}

	Sala(char* numeSala, int gensala, int dimensiuneSala) : idSala(idSala) {

		this->idLocuri = nullptr;
		this->genSala = gensala;
		this->idLocuri = nullptr;

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
		if (idLocuri != nullptr) {
			delete[] idLocuri;
		}

		if (numeSala != nullptr) {
			delete[] numeSala;
		}

		if (randuriDezavantajate != nullptr) {
			delete[] randuriDezavantajate;
		}
	}

	static int generateId() {
		ifstream f("sala.bin", ios::binary);
		f.seekg(0, ios::end);
		int pos = f.tellg();

		if (pos > 0) {
			int size = pos / sizeof(Sala);
			return size + 1;
		}
		else {
			return 1;
		}
			
	}

	Sala& operator=(const Sala& s) {
		if (idLocuri != nullptr) {
			delete[] idLocuri;
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


		if (s.idLocuri != nullptr && s.numarLocuri > 0) {
			idLocuri = s.idLocuri;
			numarLocuri = s.numarLocuri;
		}
		else {
			idLocuri = nullptr;
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
			this->randuriDezavantajate = new int[numarRanduriDezavantajate];
			this->numarRanduriDezavantajate = numarLocuri;
			for (int i = 0; i < numarLocuri; i++) {
				randuriDezavantajate[i] = randuri[i];
			}
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

	bool isOcupat(int* locuriOcupate, int size, int id) {
		for (int i = 0; i < size; i++) {
			if (locuriOcupate[i] == id) {
				return true;
			}
		}
	}

	int genereazaIdLoc(int coloana, int rand) {
		return stoi(to_string(idSala) + to_string(coloana) + to_string(rand));
	}

	void printLocuriLibere(int* locuriOcupate, int bileteVanduteSize) {
		if (idLocuri != nullptr && numarLocuri > 0) {
			for (int i = 0; i < nrLocuriOcupate; i++) {
				for (int j = 0; j < numarLocuri; j++) {
					int idLoc = genereazaIdLoc(i, j);
					if (isOcupat(locuriOcupate, bileteVanduteSize, idLoc)) {
						cout << "| X X |";
						break;
					}
					else {
						cout << "| "<< idLoc << " |";
					}
				}
			}

		}
	}

	void operator[] (int idLoc)
	{
		/*
		* for (int i = 0; i < numarLocuri; i++) {
			if (idLocuri[i] == 0) {
				cout << "\n";
			}

			if (idLoc == locuri[i].getId()) {
				cout << " XX ";
			}
			else {
				cout << "| " + to_string(locuri[i].getRand()) + to_string(locuri[i].getColoana()) + " |";

			}
		}
		*/		

	}

	explicit operator int() {
		return numarLocuri;
	}


	friend ostream& operator<<(ostream&, Sala);
	friend istream& operator>>(istream&, Sala&);


	void deleteSala(int id1) {
		ifstream f("sala.bin", ios::binary);
		ofstream of("sala2.bin", ios::app | ios::binary);

		int fileId;

		while (f.read((char*)&idSala, sizeof(idSala))) {
			if (fileId != idSala) {
				int pos = f.tellg();
				
				f.read((char*)&numarLocuri, sizeof(numarLocuri));
				f.read((char*)&adaosSala, sizeof(adaosSala));
				f.read((char*)&genSala, sizeof(genSala));

				string buffer = "";
				char c = 0;
				while ((c = f.get()) != 0)
				{
					buffer += c;
				}
				delete[] numeSala;
				numeSala = new char[buffer.length() + 1];
				strcpy_s(numeSala, buffer.length() + 1, buffer.c_str());

				delete[] idLocuri;
				idLocuri = new int[numarLocuri];
				for (int i = 0; i < numarLocuri; i++)
				{
					f.read((char*)&idLocuri[i], sizeof(idLocuri[i]));
				}
				int pos2 = f.tellg();

				of.write((char*)&idSala, sizeof(idSala));
				of.write((char*)&numarLocuri, sizeof(numarLocuri));
				of.write((char*)&adaosSala, sizeof(adaosSala));
				of.write((char*)&genSala, sizeof(genSala));

				of.write(numeSala, (long long)strlen(numeSala) + 1);

				for (int i = 0; i < numarLocuri; i++)
				{
					of.write((char*)&idLocuri[i], sizeof(idLocuri[i]));
				}
			}
		}

		of.close();
		f.close();

		if (remove("sala.bin") != 0)
			cout << "Fisierul a fost sters" << endl;

		if (rename("sala2.bin", "sala.bin") != 0)
			cout << "Fisierul a fost modificat";
	}


	void serializare() {
		fstream of("loc2.bin", ios::binary | ios::app);

		of.write((char*)&idSala, sizeof(idSala));
		of.write((char*)&numarLocuri, sizeof(numarLocuri));
		of.write((char*)&adaosSala, sizeof(adaosSala));
		of.write((char*)&genSala, sizeof(genSala));

		of.write(numeSala, (long long)strlen(numeSala) + 1);

		for (int i = 0; i < numarLocuri; i++)
		{
			of.write((char*)&idLocuri[i], sizeof(idLocuri[i]));
		}
		of.close();
	}

	void deserializare() {
		ifstream f("loc2.bin", ios::binary);

		int fileId = idSala;;

		while (f.read((char*)&idSala, sizeof(idSala))) {
			if (fileId == idSala) {

				f.read((char*)&numarLocuri, sizeof(numarLocuri));
				f.read((char*)&adaosSala, sizeof(adaosSala));
				f.read((char*)&genSala, sizeof(genSala));

				string buffer = "";
				char c = 0;
				while ((c = f.get()) != 0)
				{
					buffer += c;
				}
				delete[] numeSala;
				numeSala = new char[buffer.length() + 1];
				strcpy_s(numeSala, buffer.length() + 1, buffer.c_str());

				delete[] idLocuri;
				idLocuri = new int[numarLocuri];
				for (int i = 0; i < numarLocuri; i++)
				{
					f.read((char*)&idLocuri[i], sizeof(idLocuri[i]));
				}
				int pos2 = f.tellg();
			}
		}
		f.close();
	}

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
	s.setLocuriInFunctieDeDimensiune();

	cout << "Introduceti tipul salii: (1) - clasis / (2) - VIP / (3) - Luxury} ";
	in >> s.genSala;
	s.setAdaos();

	cout << "Adaos ";
	in>> s.adaosSala;

	return in;
};

