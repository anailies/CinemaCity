// CinemaCity.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Program.h"
#include "Bilet.h"
#include "Sala.h"
#include <iostream>

const string Program::regexData = "[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1]) (2[0-3]|[01][0-9]):[0-5][0-9]";
const int Loc::discount = 10;


int main()
{

	cout << Film::generateId();

	cout << "**********CINEMA CITY*****************" << endl;
	cout << "Alegeti una din optiunile de mai jos: " << endl;

	int optiune;
	cout << "1 - Emitere bilet" << endl;
	cout << "2 - Program" << endl;
	cout << "Orice alt caracter - Exit" << endl;
	cin >> optiune;

	while (optiune == 1 || optiune == 2) {
		if (optiune == 1) {
			int idFilm;
			int idProgram;
			int idSala;
			int idLoc;

			cout << "Va rugam alegeti un film";
			Film::printeazaToateFilmele();

			cout << "Introduceti id-ul filmului";
			cin >> idFilm;

			cout << "Filmul este disponibil in urmatoarele zile";
			Program::printProgramFilm(idFilm);

			cout << "Va rugam alegeti id-ul programului";
			cin >> idProgram;
			Program* program = new Program(idProgram);
			program->deserializare();

			idSala = program->getIdSala();
			Sala* sala = new Sala(idSala);
			sala->deserializare();

			int* bileteVandute = Bilet::getBileteVandutePentruProgram(idProgram).first;
			int bileteVanduteSize = Bilet::getBileteVandutePentruProgram(idProgram).second;

			sala->printLocuriLibere(bileteVandute, bileteVanduteSize);

			cout << "Va rugam alegeti id-ul locului";
			cin >> idLoc;

			Film* film = new Film(idFilm);
			film->deserializare();

			Bilet* bilet = new Bilet(Bilet::generateId(), idSala, idProgram, idLoc, film->getTarif());
			cin >> *bilet;


			cout << "**********CINEMA CITY*****************";
			cout << "Alegeti una din optiunile de mai jos: ";
			cout << "1 - Emitere bilet";
			cout << "2 - Program";
			cout << "Orice alt caracter - Exit";
			cin >> optiune;

			delete bilet;
			delete film;
			delete program;
			delete sala;
	
		}
		else if (optiune == 2) {
			Program::printeazaTotProgramul();


			cout << "**********CINEMA CITY*****************";
			cout << "Alegeti una din optiunile de mai jos: ";
			cout << "1 - Emitere bilet";
			cout << "2 - Program";
			cout << "Orice alt caracter - Exit";
			cin >> optiune;
		}
	}
};





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
