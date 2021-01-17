#pragma once
#pragma once
#include <iostream>
#include <regex>
#include <string>
#include "Loc.h"
#include "Sala.h"

using namespace std;
using std::regex;

class Program {

private:
	int idProgram;
	int idFilm;
	int idSala;
	int* bileteVandute;
	int numarBileteVandute;

	static const string regexData;
	string data;
	char* tipProgram;

public:
	//constructor implicit
	Program() :idProgram(0)
	{
		this->bileteVandute= nullptr;
		this->tipProgram = nullptr;

	}

	Program(int idProgram, int idFilm, int idSala, int* bileteVandute, char* tipProgram, int numarBileteVandute, string data) : idProgram(idProgram)
	{

		this->idProgram= idProgram;
		this->idFilm = idFilm;
		this->idSala = idSala;

		if (bileteVandute != NULL && numarBileteVandute > 0) {
			this->bileteVandute = new int[numarBileteVandute];
			for (int i = 0; i < numarBileteVandute; i++)
			{
				this->bileteVandute[i] = bileteVandute[i];
			}
			this->numarBileteVandute = numarBileteVandute;
		}
		else {
			bileteVandute = nullptr;
			numarBileteVandute = 0;
		}

		if (tipProgram != NULL) {
			this->tipProgram = new char[strlen(tipProgram) + 1];
			strcpy_s(this->tipProgram, strlen(tipProgram) + 1, tipProgram);
		}
		else {
			this-> tipProgram = nullptr;
		}

		if (!data.empty()) {
			setData(data);
		}

	}

	//copy constructor
	Program(const Program& p) : idProgram(p.idProgram) {

		this->idProgram = p.idProgram;
		this->idFilm = p.idFilm;
		this->idSala = p.idSala;

		if (p.bileteVandute != NULL && p.numarBileteVandute > 0) {
			this->bileteVandute = new int[p.numarBileteVandute];
			for (int i = 0; i < p.numarBileteVandute; i++)
			{
				this->bileteVandute[i] = p.bileteVandute[i];
			}
			this->numarBileteVandute = p.numarBileteVandute;
		}
		else {
			bileteVandute = nullptr;
			numarBileteVandute = 0;
		}

		if (p.tipProgram != NULL) {
			this->tipProgram = new char[strlen(p.tipProgram) + 1];
			strcpy_s(this->tipProgram, strlen(p.tipProgram) + 1, p.tipProgram);
		}
		else {
			this->tipProgram = nullptr;
		}

		if (!p.data.empty()) {
			setData(p.data);
		}
	
	}


	Program& operator=(const Program& p) {
		if (bileteVandute != nullptr) {
			delete[] bileteVandute;
		}

		if (tipProgram != nullptr) {
			delete[] tipProgram;
		}

		this->idProgram = p.idProgram;
		this->idFilm = p.idFilm;
		this->idSala = p.idSala;

		if (p.bileteVandute != NULL && p.numarBileteVandute > 0) {
			this->bileteVandute = new int[p.numarBileteVandute];
			for (int i = 0; i < p.numarBileteVandute; i++)
			{
				this->bileteVandute[i] = p.bileteVandute[i];
			}
			this->numarBileteVandute = p.numarBileteVandute;
		}
		else {
			bileteVandute = nullptr;
			numarBileteVandute = 0;
		}

		if (p.tipProgram != NULL) {
			this->tipProgram = new char[strlen(p.tipProgram) + 1];
			strcpy_s(this->tipProgram, strlen(p.tipProgram) + 1, p.tipProgram);
		}
		else {
			this->tipProgram = nullptr;
		}

		if (!p.data.empty()) {
			setData(p.data);
		}

		if (p.tipProgram != NULL) {
			this->tipProgram = new char[strlen(p.tipProgram) + 1];
			strcpy_s(this->tipProgram, strlen(p.tipProgram) + 1, p.tipProgram);
		}
		else {
			this->tipProgram = nullptr;
		}

		return *this;
	}


	~Program() {
		if (bileteVandute != nullptr) {
			delete[] bileteVandute;
		}

	}

	void setBileteVandute(const int* bileteVandute, int numarBileteVandute) {
		if (this->bileteVandute != nullptr) {
			delete[] bileteVandute;
		}
		if (bileteVandute != NULL && numarBileteVandute > 0) {
			this->bileteVandute = new int[numarBileteVandute];
			for (int i = 0; i < numarBileteVandute; i++)
			{
				this->bileteVandute[i] = bileteVandute[i];
			}
			this->numarBileteVandute = numarBileteVandute;
		}
		else {
			this-> bileteVandute = nullptr;
			this->numarBileteVandute = 0;
		}
	}

	void setTipProgram(const char* tipProgram) {
		if (this->tipProgram != nullptr) {
			delete[] tipProgram;
		}
		if (tipProgram != nullptr) {
			this->tipProgram = new char[strlen(tipProgram) + 1];
			strcpy_s(this->tipProgram, strlen(tipProgram) + 1, tipProgram);
		}
		else {
			this->tipProgram = nullptr;
		}
	}

	void setIdSala(int idSala) {
		if (idSala > 0) {
			this->idSala = idSala;
		}
	}

	void setIdFilm(int idFilmf) {
		if (idFilm > 0) {
			this->idFilm = idFilm;
		}
	}

	void setData(string data) {

		if (std::regex_match(data, std::regex(regexData))) {
				this->data = data;
		}
		else {
			throw exception("regex incorect");
		}
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

	bool operator! () {
		return bileteVandute != nullptr;
	}

	Program operator++(int idBilet) {

		this->numarBileteVandute++;
		int* bilete = new int[numarBileteVandute];

		for (int i = 0; i < numarBileteVandute; ++i)
		{
			if (i != numarBileteVandute) {
				bilete[i] = bileteVandute[i];
			}
			else {
				bilete[i] = idBilet;
			}
		}
		this->bileteVandute = bilete;
		//TODO CHECK
		delete[] bilete;
		return *this;
	}

	Program operator--(int idBilet) {
		this->numarBileteVandute--;
		int* bilete = new int[numarBileteVandute];

		for (int i = 0; i < numarBileteVandute; ++i)
		{
			if (i != idBilet) {
				bilete[i] = bileteVandute[i];
			}
		}
		delete[] bileteVandute;
		this->bileteVandute = bilete;
		delete[] bilete;

		return *this;
	}


	Program operator-(int idBilet) {
		Program copie = *this;
		copie.numarBileteVandute--;
		int* bilete = new int[numarBileteVandute];

		for (int i = 0; i < numarBileteVandute; ++i)
		{
			if (i != idBilet) {
				bilete[i] = bileteVandute[i];
			}
		}
		delete[] copie.bileteVandute;
		copie.bileteVandute = bilete;
		delete[] bilete;

		return copie;
	}

	Program operator+ (int idBilet) {
		Program copie = *this;
		copie.numarBileteVandute++;
		int* bilete = new int[numarBileteVandute];

		for (int i = 0; i < numarBileteVandute; ++i)
		{
			if (i != numarBileteVandute) {
				bilete[i] = bileteVandute[i];
			}
			else {
				bilete[i] = idBilet;
			}
		}
		delete[] copie.bileteVandute;
		copie.bileteVandute = bilete;
		delete[] bilete;

		return copie;
	}

	int operator[] (int index) throw (exception)
	{
		if (index >= 0 && index < numarBileteVandute && bileteVandute != nullptr)
		{
			return bileteVandute[index];
		}
		else
		{
			throw exception("index gresit");
		}
	}

	explicit operator int() {
		return idProgram;
	}

	string operator()() {
		return data;
	}

	friend ostream& operator<<(ostream&, Program);
	friend istream& operator>>(istream&, Program&);
};

ostream& operator<<(ostream& out, Program p) {
	out << "id-ul programului : " << endl;
	out << p.idProgram << endl;

	out << "data programului : " << endl;
	out << p.data << endl;

	out << "id film : " << endl;
	out << p.idFilm<< endl;

	out << "bilete vandute film : " << endl;
	for (int i = 0; i < p.numarBileteVandute; i++) {
		out << p.bileteVandute[i];
		out << " ";
	}

	out << "id sala : " << endl;
	out << p.idSala << endl;

	return out;
}

istream& operator>>(istream& in, Program& p) {

	cout << "Introduceti id-ul programului: ";
	in >> p.idProgram;

	cout << "Introduceti data programului: ";
	in >> ws;
	string data;
	getline(in, data);
	p.setData(data);

	cout << "Introduceti id-ul filmului: ";
	in >> p.idFilm;

	cout << "Introduceti id-ul salii: ";
	in >> p.idSala;

	return in;
}

