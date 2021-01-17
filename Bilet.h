#pragma once
#include <iostream>
#include <string>
#include "Loc.h"
#include "Sala.h"

using namespace std;

class Bilet {

private:
	const int idBilet;
	double tarifAchitat;
	int idSala;
	int idProgram;
	int* reduceri;
	int numarReduceri;

	Loc* loc;

	static string numeCinema;
	char* numeCumparator;

public:
	enum Reduceri { student = 1, pensionar = 2, copil = 3, special = 4 };
	//constructor implicit
	Bilet() :idBilet(0)
	{
		this->tarifAchitat = 0;
		this->idSala = 0;
		this->idProgram = 0;
		this->numarReduceri = 0;
		this->reduceri = nullptr;
		this->numeCumparator = nullptr;
		this->loc = nullptr;
	}

	Bilet(int idBilet, int* reduceri, int numarReduceri, Loc* loc, int idSala, int idProgram, double tarifAchitat, char* numeCumparator) : idBilet(idBilet)
	{

		this->tarifAchitat = tarifAchitat;
		this->idSala = idSala;
		this->idProgram = idProgram;

		if (numeCumparator != NULL) {
			this -> numeCumparator = new char[strlen(numeCumparator) + 1];
			strcpy_s(this ->numeCumparator, strlen(numeCumparator) + 1, numeCumparator);
		}

		if (reduceri != nullptr && numarReduceri > 0) {
			this->numarReduceri = numarReduceri;

			for (int i = 0; i < numarReduceri; i++)
			{
				this->reduceri[i] = reduceri[i];
			}
		}
		else {
			this->reduceri = nullptr;
		}

		if (loc != nullptr) {
			this->loc = loc;
		}
		else {
			this ->loc = nullptr;
		}
	}

	//copy constructor
	Bilet(const Bilet& b) : idBilet(b.idBilet) {

		this->tarifAchitat = b.tarifAchitat;
		this->idSala = b.idSala;
		this->idProgram = b.idProgram;

		if (b.numeCumparator != NULL) {
			numeCumparator = new char[strlen(b.numeCumparator) + 1];
			strcpy_s(numeCumparator, strlen(b.numeCumparator) + 1, b.numeCumparator);
		}
		else {
			numeCumparator = nullptr;
		}

		if (b.loc != NULL) {
			this->loc = b.loc;
		}
		else {
			loc = nullptr;
		}

		if (b.reduceri != nullptr && b.numarReduceri > 0) {
			this->numarReduceri = b.numarReduceri;

			for (int i = 0; i < numarReduceri; i++)
			{
				this->reduceri[i] = b.reduceri[i];
			}
		}
		else {
			this->reduceri = nullptr;
		}
	}

	~Bilet() {
		if (loc != nullptr) {
			delete[] loc;
		}
		if (numeCumparator != nullptr) {
			delete[] numeCumparator;
		}

		if (reduceri != nullptr) {
			delete[] reduceri;
		}
	}

	Bilet& operator=(const Bilet& b) {
		if (loc != nullptr) {
			delete[] loc;
		}

		if (numeCumparator != nullptr) {
			delete[] numeCumparator;
		}

		if (reduceri != nullptr) {
			delete[] reduceri;
		}

		this->tarifAchitat = b.tarifAchitat;
		this->idSala = idSala;

		if (b.numeCumparator != NULL) {
			numeCumparator = new char[strlen(b.numeCumparator) + 1];
			strcpy_s(numeCumparator, strlen(b.numeCumparator) + 1, b.numeCumparator);
		}
		else {
			numeCumparator = nullptr;
		}

		if (loc != NULL) {
			this->loc = b.loc;
		}
		else {
			loc = nullptr;
		}
		
		if (b.reduceri != nullptr && b.numarReduceri > 0) {
			this->numarReduceri = b.numarReduceri;

			for (int i = 0; i < numarReduceri; i++)
			{
				this->reduceri[i] = b.reduceri[i];
			}
		}
		else {
			this->reduceri = nullptr;
		}

		this->idSala = b.idSala;
		this->idProgram = b.idProgram;

		return *this;
	}


	void setReduceri(const int* reduceri, int numarReduceri) {
		if (this->reduceri == nullptr) {
			delete[] reduceri;
		}

		if (reduceri != nullptr && numarReduceri > 0) {
			this->numarReduceri = numarReduceri;

			for (int i = 0; i < numarReduceri; i++)
			{
				this->reduceri[i] = reduceri[i];
			}
		}
		else {
			this->reduceri = nullptr;
			this->numarReduceri = 0;
		}
	}

	void setNumeCumparator(const char* nume) {
		if (this->numeCumparator != nullptr) {
			delete[] this->numeCumparator;
		}
		if (nume != NULL) {
			this->numeCumparator = new char[strlen(nume) + 1];
			strcpy_s(this->numeCumparator, strlen(nume) + 1, nume);
		}
		else {
			this->numeCumparator = nullptr;
		}
	}

	void setLoc(Loc* loc) {
		if (this->loc != nullptr) {
			delete[] loc;
		}
		if (loc != nullptr) {
			this->loc = loc;
		}
		else {
			this->loc = nullptr;
		}
	}

	void setTarifAchitat(double tarif) {
		this->tarifAchitat = tarif;
	}

	double getTarif() {
		return tarifAchitat;
	}

	char* getNumeCumparator() {
		return numeCumparator;
	}

	Loc* getLoc() {
		return loc;
	}

	int getIdSala() {
		return idSala;
	}

	int getIdProgram() {
		return idProgram;
	}

	void setIdProgram(int id) {
		this->idProgram = id;
	}

	void setIdSala(int id) {
		this->idSala = id;
	}

	static void setNumeCinema(string nume) {
		Bilet::numeCinema = nume;
	}

	static string getNumeCinema() {
		return numeCinema;
	}

	bool operator! () {
		return loc != nullptr;
	}

	Bilet operator++(int i) {
		Bilet copie = *this;
		this->tarifAchitat += i;
		return *this;
	}

	Bilet operator--(int i) {
		Bilet copie = *this;
		this->tarifAchitat -= i;
		return *this;
	}

	Bilet operator-(int i) {
		if (i >= 0.0) {
			Bilet copie = *this;
			copie.tarifAchitat -= i;
			return copie;
		}
		else {
			//throw 500;
		}
	}

	Bilet operator+(int i) {
		if (i >= 0.0 && i <= 500) {
			Bilet copie = *this;
			copie.tarifAchitat += i;
			return copie;
		}
		else {
			//throw 500;
		}
	}

	string operator[] (int index)
		// throw (exception)
	{

	}

	explicit operator int() {
		return idBilet;
	}

	char* operator()() {
		return numeCumparator;
	}

	friend ostream& operator<<(ostream&, Bilet);
	friend istream& operator>>(istream&, Bilet&);
};

ostream& operator<<(ostream& out, Bilet b) {
	out << b.idBilet << endl;
	out << "detinator : " << endl;
	out << b.numeCumparator << endl;
	out << "program : ";
	out << b.idProgram << endl;

	return out;
}

istream& operator>>(istream& in, Bilet& b) {

	cout << "Introduceti numele cumparatorului: ";
	string buffer;
	in >> ws;
	getline(in, buffer);
	b.numeCumparator = new char[buffer.length() + 1];
	strcpy_s(b.numeCumparator, buffer.length() + 1, buffer.c_str());

	cout << "Introduceti id-ul salii filmului: ";
	in >> b.idSala;

	cout << "Introduceti id-ul programului: ";
	in >> b.idProgram;

	return in;
}

