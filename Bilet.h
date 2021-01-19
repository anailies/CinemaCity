#pragma once
#include <iostream>
#include <list>
#include<iostream>
#include<fstream>
#include <string>
#include "Loc.h"
#include <utility>

using namespace std;

class Bilet {

private:
    const int idBilet;
    int tarifAchitat;
    int idSala;
    int idProgram;
    int idLoc;
    int* reduceri;
    int numarReduceri;

    static string numeCinema;
    char* numeCumparator;

public:
    enum Reduceri { student = 1, pensionar = 2, copil = 3, special = 4, normal = 5 };
    //constructor implicit
    Bilet(int idBilet) : idBilet(idBilet) {
        this->tarifAchitat = 0;
        this->idSala = 0;
        this->idLoc = 0;
        this->idProgram = 0;
        this->tarifAchitat = 0;
        this->numarReduceri = 0;
        this->reduceri = nullptr;
        this->numeCumparator = nullptr;
    }

    Bilet(int idBilet, int idSala, int idProgram, int idLoc, double tarifAchitat) :idBilet(idBilet)
    {
        this->tarifAchitat = 0;
        this->idSala = idSala;
        this->idLoc = idLoc;
        this->idProgram = idProgram;
        this->tarifAchitat = tarifAchitat;
        this->numarReduceri = 0;
        this->reduceri = nullptr;
        this->numeCumparator = nullptr;

    }

    Bilet(int idBilet, int idLoc, int* reduceri, int numarReduceri, Loc* loc, int idSala, int idProgram, double tarifAchitat, char* numeCumparator) : idBilet(idBilet)
    {

        this->tarifAchitat = tarifAchitat;
        this->idSala = idSala;
        this->idLoc = idLoc;
        this->idProgram = idProgram;

        if (numeCumparator != nullptr) {
            this->numeCumparator = new char[strlen(numeCumparator) + 1];
            strcpy_s(this->numeCumparator, strlen(numeCumparator) + 1, numeCumparator);
        }
        else {
            this->numeCumparator = nullptr;
        }

        if (reduceri != nullptr && numarReduceri > 0) {
            this->numarReduceri = numarReduceri;
            this->reduceri = new int[numarReduceri];
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

    //copy constructor
    Bilet(const Bilet& b) : idBilet(b.idBilet) {

        this->tarifAchitat = b.tarifAchitat;
        this->idSala = b.idSala;
        this->idProgram = b.idProgram;
        this->idLoc = b.idLoc;

        if (b.numeCumparator != NULL) {
            numeCumparator = new char[strlen(b.numeCumparator) + 1];
            strcpy_s(numeCumparator, strlen(b.numeCumparator) + 1, b.numeCumparator);
        }
        else {
            numeCumparator = nullptr;
        }


        if (b.reduceri != nullptr && b.numarReduceri > 0) {
            this->numarReduceri = b.numarReduceri;
            this->reduceri = new int[numarReduceri];

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

        if (numeCumparator != nullptr) {
            delete[] numeCumparator;
        }

        if (reduceri != nullptr) {
            delete[] reduceri;
        }
    }

    Bilet& operator=(const Bilet& b) {

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


        if (b.reduceri != nullptr && b.numarReduceri > 0) {
            this->numarReduceri = b.numarReduceri;
            this->reduceri = new int[numarReduceri];

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

    void deleteFilm() {
        ifstream f("bilete.bin", ios::binary);
        ofstream of("bilete2.bin", ios::app);

        int fileId = idBilet;

        while (f.read((char*)&idBilet, sizeof(idBilet))) {
            if (idBilet != fileId) {
                int pos = f.tellg();
                f.read((char*)&tarifAchitat, sizeof(tarifAchitat));
                f.read((char*)&idSala, sizeof(idSala));
                f.read((char*)&idProgram, sizeof(idProgram));
                f.read((char*)&idLoc, sizeof(idLoc));
                f.read((char*)&numarReduceri, sizeof(numarReduceri));

                string buffer = "";
                char c = 0;
                while ((c = f.get()) != 0)
                {
                    buffer += c;
                }
                delete[] numeCumparator;
                numeCumparator = new char[buffer.length() + 1];
                strcpy_s(numeCumparator, buffer.length() + 1, buffer.c_str());

                delete[] reduceri;
                reduceri = new int[numarReduceri];
                for (int i = 0; i < numarReduceri; i++)
                {
                    f.read((char*)&reduceri[i], sizeof(reduceri[i]));
                }

                int pos2 = f.tellg();

                of.write((char*)&idBilet, sizeof(idBilet));
                of.write((char*)&tarifAchitat, sizeof(tarifAchitat));
                of.write((char*)&idSala, sizeof(idSala));
                of.write((char*)&idProgram, sizeof(idProgram));
                of.write((char*)&idLoc, sizeof(idLoc));
                of.write((char*)&numarReduceri, sizeof(numarReduceri));

                of.write(numeCumparator, (long long)strlen(numeCumparator) + 1);

                for (int i = 0; i < numarReduceri; i++)
                {
                    of.write((char*)&reduceri[i], sizeof(reduceri[i]));
                }
            }
        }

        of.close();
        f.close();

        if (remove("bilete.bin") != 0)
            cout << "Fisierul a fost sters" << endl;

        if (rename("bilete2.bin", "bilete.bin") != 0)
            cout << "Fisierul a fost modificat";
    }


    void serializare() {
        fstream of("bilete.bin", ios::binary | ios::app);

        of.write((char*)&idBilet, sizeof(idBilet));
        of.write((char*)&tarifAchitat, sizeof(tarifAchitat));
        of.write((char*)&idSala, sizeof(idSala));
        of.write((char*)&idProgram, sizeof(idProgram));
        of.write((char*)&idLoc, sizeof(idLoc));
        of.write((char*)&numarReduceri, sizeof(numarReduceri));

        of.write(numeCumparator, (long long)strlen(numeCumparator) + 1);

        for (int i = 0; i < numarReduceri; i++)
        {
            of.write((char*)&reduceri[i], sizeof(reduceri[i]));
        }

        of.close();
    }

    void deserializare() {
        ifstream f("filme.bin", ios::binary);

        int id;

        while (f.read((char*)&id, sizeof(id))) {
            if (idBilet == id) {
                int pos = f.tellg();
                f.read((char*)&tarifAchitat, sizeof(tarifAchitat));
                f.read((char*)&idSala, sizeof(idSala));
                f.read((char*)&idProgram, sizeof(idProgram));
                f.read((char*)&idLoc, sizeof(idLoc));
                f.read((char*)&numarReduceri, sizeof(numarReduceri));

                string buffer = "";
                char c = 0;
                while ((c = f.get()) != 0)
                {
                    buffer += c;
                }
                delete[] numeCumparator;
                numeCumparator = new char[buffer.length() + 1];
                strcpy_s(numeCumparator, buffer.length() + 1, buffer.c_str());

                delete[] reduceri;
                reduceri = new int[numarReduceri];
                for (int i = 0; i < numarReduceri; i++)
                {
                    f.read((char*)&reduceri[i], sizeof(reduceri[i]));
                }
                break;
            }
        }
        f.close();
    }

    static int getNumarTotalBilete() {
        return generateId() - 1;
    }

    static int generateId() {
        ifstream f("filme.bin", ios::binary);
        f.seekg(0, ios::end);
        int pos = f.tellg();

        if (pos > 0) {
            int size = pos / sizeof(Bilet);
            return size + 1;
        }
        else {
            return 1;
        }
    }


    static pair<int*, int> getBileteVandutePentruProgram(int programId) {
        ifstream f("filme.bin", ios::binary);

        int id;

        std::list<int> bilete;

        while (f.read((char*)&id, sizeof(id))) {

            Bilet* bilet = new Bilet(id);
            bilet->deserializare();
            if (bilet->idProgram == programId) {
                bilete.push_back(bilet->getId());
            }
            delete bilet;
        }
      
        int* bileteVandute = new int[bilete.size()];
        int i = 0;
        for (int bilet : bilete) {
            bileteVandute[i] = bilet;
            i++;
        }

        f.close();

        pair<int*, char> pair;

        pair.first = bileteVandute;
        pair.second = i;

        return pair;
    }

    void setIdLoc(int idLoc) {
        this->idLoc = idLoc;
    }

    int getIdLoc() {
        return this->idLoc;
    }

    int getId() {
        return this->idBilet;
    }

    void setReduceri(const int* reduceri, int numarReduceri) {
        if (this->reduceri == nullptr) {
            delete[] reduceri;
        }

        if (reduceri != nullptr && numarReduceri > 0) {
            this->numarReduceri = numarReduceri;
            this->reduceri = new int[numarReduceri];
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


    void setTarifAchitat(double tarif) {
        this->tarifAchitat = tarif;
    }

    double getTarif() {
        return tarifAchitat;
    }

    char* getNumeCumparator() {
        return numeCumparator;
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
        return idLoc != 0;
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
    out << "id loc : ";
    out << b.idLoc << endl;

    return out;
}

istream& operator>>(istream& in, Bilet& b) {

    cout << "Introduceti numele cumparatorului: ";
    string buffer;
    in >> ws;
    getline(in, buffer);
    b.numeCumparator = new char[buffer.length() + 1];
    strcpy_s(b.numeCumparator, buffer.length() + 1, buffer.c_str());

    cout << "In care dintre urmatoarele categorii student = 1, pensionar = 2, copil = 3, special = 4, normal = 5 ";
    cout << "Introduceti numarul de categorii: ";
    in >> b.numarReduceri;

    b.reduceri = new int[b.numarReduceri];

    bool discountAplicat = false;
    for (int i = 0; i < b.numarReduceri; i++) {
        cout << "Introduceti categoria: ";
        cout << "Introduceti randul dezavantajat (numeric): ";
        in >> b.reduceri[i];
        if (i != 5 && !discountAplicat) {
            cout << "Aveti o reducere de: " << Loc::getDiscount();
        }
    }
   
    cout << "BILET EMIS";

    return in;
}

