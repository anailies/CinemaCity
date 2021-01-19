#pragma once
#pragma once
#include <iostream>
#include <regex>
#include <fstream>
#include "Bilet.h"
#include <string>

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
    Program(int idProgram) :idProgram(idProgram)
    {
        this->bileteVandute = nullptr;
        this->tipProgram = nullptr;

    }

    Program(int idProgram, int idFilm, int idSala, int* bileteVandute, char* tipProgram, int numarBileteVandute, string data) : idProgram(idProgram)
    {

        this->idProgram = idProgram;
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
            this->tipProgram = nullptr;
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
            this->bileteVandute = nullptr;
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

    void deleteProgram(int id1) {
        ifstream f("programe.bin", ios::binary);
        ofstream of("programe2.bin", ios::app);

        int fileId;

        while (f.read((char*)&idProgram, sizeof(idProgram))) {
            if (fileId != id1) {
                int pos = f.tellg();
                f.read((char*)&idFilm, sizeof(idFilm));
                f.read((char*)&idSala, sizeof(idSala));
                f.read((char*)&numarBileteVandute, sizeof(numarBileteVandute));

                int length = 0;
                f.read((char*)&length, sizeof(length));
                char* aux = new char[length];
                f.read(aux, length);
                data = aux;

                string buffer = "";
                char c = 0;
                while ((c = f.get()) != 0)
                {
                    buffer += c;
                }
                delete[] tipProgram;
                tipProgram = new char[buffer.length() + 1];
                strcpy_s(tipProgram, buffer.length() + 1, buffer.c_str());

                delete[] bileteVandute;
                bileteVandute = new int[numarBileteVandute];
                for (int i = 0; i < numarBileteVandute; i++)
                {
                    f.read((char*)&bileteVandute[i], sizeof(bileteVandute[i]));
                }

                int pos2 = f.tellg();

                of.write((char*)&idProgram, sizeof(idProgram));
                of.write((char*)&idFilm, sizeof(idFilm));
                of.write((char*)&idSala, sizeof(idSala));
                of.write((char*)&numarBileteVandute, sizeof(numarBileteVandute));

                int lengthData = data.length() + 1;
                of.write(data.c_str(), lengthData);

                of.write(tipProgram, (long long)strlen(tipProgram) + 1);

                for (int i = 0; i < numarBileteVandute; i++)
                {
                    of.write((char*)&bileteVandute[i], sizeof(bileteVandute[i]));
                }
            }
        }

        of.close();
        f.close();

        if (remove("programe.bin") != 0)
            cout << "Fisierul a fost sters" << endl;

        if (rename("programe.bin", "programe.bin") != 0)
            cout << "Fisierul a fost modificat";
    }


    void serializare() {
        remove("programe.bin");

        fstream of("programe.bin", ios::binary | ios::app);

        of.write((char*)&idProgram, sizeof(idProgram));
        of.write((char*)&idFilm, sizeof(idFilm));
        of.write((char*)&idSala, sizeof(idSala));
        of.write((char*)&numarBileteVandute, sizeof(numarBileteVandute));

        int lengthData = data.length() + 1;
        of.write(data.c_str(), lengthData);

        of.write(tipProgram, (long long)strlen(tipProgram) + 1);

        for (int i = 0; i < numarBileteVandute; i++)
        {
            of.write((char*)&bileteVandute[i], sizeof(bileteVandute[i]));
        }

        of.close();
    }

    void deserializare() {
        ifstream f("programe.bin", ios::binary);

        int id;

        while (f.read((char*)&id, sizeof(id))) {
            if (id == idProgram) {
                int pos = f.tellg();
                cout << "pos 1 : " << pos;
                this->idProgram = id;
                f.read((char*)&idFilm, sizeof(idFilm));
                f.read((char*)&idSala, sizeof(idSala));
                f.read((char*)&numarBileteVandute, sizeof(numarBileteVandute));

                int length = 0;
                f.read((char*)&length, sizeof(length));
                char* aux = new char[length];
                f.read(aux, length);
                data = aux;

                string buffer = "";
                char c = 0;
                while ((c = f.get()) != 0)
                {
                    buffer += c;
                }
                delete[] tipProgram;
                tipProgram = new char[buffer.length() + 1];
                strcpy_s(tipProgram, buffer.length() + 1, buffer.c_str());

                delete[] bileteVandute;
                bileteVandute = new int[numarBileteVandute];
                for (int i = 0; i < numarBileteVandute; i++)
                {
                    f.read((char*)&bileteVandute[i], sizeof(bileteVandute[i]));
                }
                break;
            }
        }
        f.close();
    }


    static int generateId() {
        ifstream f("programe.bin", ios::binary);
        f.seekg(0, ios::end);
        int pos = f.tellg();

        if (pos > 0) {
            int size = pos / sizeof(Program);
            return size + 1;
        }
        else {
            return 1;
        }
    }

    static void printeazaTotProgramul() {
        ifstream f("programe.bin", ios::binary);

        int id;

        while (f.read((char*)&id, sizeof(id))) {

            Program* program = new Program(id);

                int pos = f.tellg();
                program->idProgram = id;
                f.read((char*)&program->idFilm, sizeof(idFilm));
                f.read((char*)&program->idSala, sizeof(idSala));
                f.read((char*)&program->numarBileteVandute, sizeof(numarBileteVandute));

                int length = 0;
                f.read((char*)&length, sizeof(length));
                char* aux = new char[length];
                f.read(aux, length);
                program->data = aux;

                string buffer = "";
                char c = 0;
                while ((c = f.get()) != 0)
                {
                    buffer += c;
                }
                delete[] program->tipProgram;
                program->tipProgram = new char[buffer.length() + 1];
                strcpy_s(program->tipProgram, buffer.length() + 1, buffer.c_str());

                delete[] program->bileteVandute;
                program->bileteVandute = new int[program->numarBileteVandute];
                for (int i = 0; i < program->numarBileteVandute; i++)
                {
                    f.read((char*)&program->bileteVandute[i], sizeof(bileteVandute[i]));
                }
                printProgram(program);
                delete program;
        }
        f.close();
    }

    static void printProgram(Program* p) {
        cout << "id-ul programului : " << endl;
        cout << p -> idProgram << endl;

        cout << "data programului : " << endl;
        cout << p -> data << endl;

        cout << "id film : " << endl;
        cout << p -> idFilm << endl;

        cout << "bilete vandute film : " << endl;
        for (int i = 0; i < p -> numarBileteVandute; i++) {
            cout << p ->bileteVandute[i];
            cout << " ";
        }

        cout << "id sala : " << endl;
        cout << p->idSala << endl;
    }

    static void printProgramFilm(int idFilm) {
        ifstream f("filme.bin", ios::binary);

        int id;

        while (f.read((char*)&id, sizeof(id))) {

            Program* program = new Program(id);
            program->deserializare();
            if (program->idFilm == id) {
                cout << program;
            }
            delete program;
        }

        f.close();
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
    out << p.idFilm << endl;

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

    cout << "Introduceti data programului: ";
    in >> ws;
    string data;
    getline(in, data);
    p.setData(data);

    cout << "Introduceti id-ul filmului: ";
    in >> p.idFilm;

    cout << "Introduceti id-ul salii: ";
    in >> p.idSala;

    cout << "Introduceti tipul programului: ";

    string buffer;
    in >> ws;
    getline(in, buffer);
    p.tipProgram = new char[buffer.length() + 1];
    strcpy_s(p.tipProgram, buffer.length() + 1, buffer.c_str());

    p.bileteVandute = Bilet::getBileteVandutePentruProgram(p.getIdProgram()).first;

    return in;
}

