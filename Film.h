#include <iostream>
#include <string>
using namespace std;

class Film {

private:
    char* numeFilm;
    int durataFilmMinute;
    double tarif;
    int varstaMinima;
    string descriere;
    int* genuri;
    int nrGenuri = 0;
    const int idFilm;
    static string numeCinema;

public:
    enum GenFilm { comedie = 1, romantic = 2, scifi = 3 };

    Film(int idFilm) :idFilm(idFilm)
    {
        durataFilmMinute = 0;
        tarif = 0.0;
        varstaMinima = 0;
        numeFilm = nullptr;
        genuri = nullptr;
    }

    Film(int idFilm, int* genuri, double tarif, int varstaMinima, char* numeFilm, int durataFilmMinute, string descriere, int nrGenuri) : idFilm(idFilm)
    {
        this->descriere = descriere;
        this->tarif = tarif;
        this->durataFilmMinute = durataFilmMinute;

        if (numeFilm != NULL) {
            this->numeFilm = new char[strlen(numeFilm) + 1];
            strcpy_s(this->numeFilm, strlen(numeFilm) + 1, numeFilm);
        }
        else {
            numeFilm = nullptr;
        }

        if (varstaMinima > 0 && varstaMinima <= 21) {
            this->varstaMinima = varstaMinima;
        }

        if (genuri != nullptr && nrGenuri > 0) {
            this->genuri = new int[nrGenuri];
            for (int i = 0; i < nrGenuri; i++)
            {
                if (genuri[i] >= 1 && genuri[i] <= 3) {
                    this->genuri[i] = genuri[i];

                }
                else {
                    //gen invalid
                }
            }
            this->nrGenuri = nrGenuri;
        }
        else {
            genuri = nullptr;
            nrGenuri = 0;
        }
    }

    //copy constructor
    Film(const Film& f) : idFilm(f.idFilm) {

        if (f.numeFilm != nullptr) {
            numeFilm = new char[strlen(f.numeFilm) + 1];
            strcpy_s(numeFilm, strlen(f.numeFilm) + 1, f.numeFilm);
        }
        else {
            numeFilm = nullptr;
        }

        descriere = f.descriere;
        tarif = f.tarif;
        durataFilmMinute = f.durataFilmMinute;
        varstaMinima = f.varstaMinima;

        if (f.genuri != nullptr && f.nrGenuri > 0) {
            genuri = new int[f.nrGenuri];
            nrGenuri = f.nrGenuri;
            for (int i = 0; i < nrGenuri; i++)
            {
                if (f.genuri[i] >= 1 && f.genuri[i] <= 3) {
                    genuri[i] = f.genuri[i];

                }
                else {
                    //gen invalid
                }
            }
        }
        else {
            genuri = nullptr;
            nrGenuri = 0;
        }
    }

    ~Film() {
        clean();
    }

    Film& operator=(const Film& f) {
        clean();

        if (f.numeFilm != nullptr) {
            numeFilm = new char[strlen(f.numeFilm) + 1];
            strcpy_s(numeFilm, strlen(f.numeFilm) + 1, f.numeFilm);
        }
        else {
            numeFilm = nullptr;
        }

        descriere = f.descriere;
        tarif = f.tarif;
        varstaMinima = f.varstaMinima;
        durataFilmMinute = f.durataFilmMinute;

        if (f.genuri != nullptr && f.nrGenuri > 0) {
            genuri = new int[f.nrGenuri];
            nrGenuri = f.nrGenuri;
            for (int i = 0; i < nrGenuri; i++)
            {
                if (f.genuri[i] >= 1 && f.genuri[i] <= 3) {
                    genuri[i] = f.genuri[i];

                }
                else {
                    //gen invalid
                }
            }
        }
        else {
            genuri = nullptr;
            nrGenuri = 0;
        }

        return *this;
    }

    double getTarif() {
        return this->tarif;
    }

    void clean() {
        if (genuri != nullptr) {
            delete[] genuri;
        }
        if (numeFilm != nullptr) {
            delete[] numeFilm;
        }
    }

    void setNume(const char* numeFilm) {
        if (this->numeFilm != nullptr) {
            delete[] numeFilm;
        }

        if (numeFilm != nullptr) {
            this->numeFilm = new char[strlen(numeFilm) + 1];
            strcpy_s(this->numeFilm, strlen(numeFilm) + 1, numeFilm);
        }
        else {
            this->numeFilm = nullptr;
        }
    }

    void setTarif(double tarif) {
        if (tarif >= 0.0 && tarif <= 500) {
            this->tarif = tarif;
        }
    }

    char* getNume() {
        return numeFilm;
    }

    void setDurataFilm(int minute) {
        if (minute > 0 && minute < 600) {
            durataFilmMinute = minute;
        }
    }

    int getDurataFilmMinute() {
        return durataFilmMinute;
    }


    void setDescriere(string descriere) {
        if (!descriere.empty()) {
            this->descriere = descriere;
        }
    }

    void setVarstaMinima(int varsta) {
        if (varsta > 0 && varsta <= 21) {
            this->varstaMinima = varsta;
        }
    }

    string getDescriere() {
        return descriere;
    }

    void setGenuri(const int* genuri, int nrGenuri) {
        if (this->genuri != nullptr) {
            delete[] this->genuri;
        }

        if (genuri != nullptr && nrGenuri > 0) {
            this->genuri = new int[nrGenuri];
            this->nrGenuri = nrGenuri;
            for (int i = 0; i < nrGenuri; i++)
            {
                if (genuri[i] >= 1 && genuri[i] <= 3) {
                    this->genuri[i] = genuri[i];

                }
                else {
                    //gen invalid
                }
            }
        }
        else {
            this->genuri = nullptr;
            this->nrGenuri = 0;
        }

    }

    int* getGenuri() {
        return genuri;
    }

    static void setNumeCinema(string nume) {
        Film::numeCinema = nume;
    }

    static string getNumeCinema() {
        return numeCinema;
    }

    void deleteFilm(int id1) {
        ifstream f("filme.bin", ios::binary);
        ofstream of("filme2.bin", ios::app);

        int fileId;

        while (f.read((char*)&idFilm, sizeof(idFilm))) {
            if (idFilm != id1) {
                int pos = f.tellg();

                string buffer = "";
                char c = 0;
                while ((c = f.get()) != 0)
                {
                    buffer += c;
                }
                delete[] numeFilm;
                numeFilm = new char[buffer.length() + 1];
                strcpy_s(numeFilm, buffer.length() + 1, buffer.c_str());

                f.read((char*)&varstaMinima, sizeof(varstaMinima));
                f.read((char*)&durataFilmMinute, sizeof(durataFilmMinute));
                f.read((char*)&nrGenuri, sizeof(nrGenuri));
                f.read((char*)&tarif, sizeof(tarif));

                int length = 0;
                f.read((char*)&length, sizeof(length));
                char* aux = new char[length];
                f.read(aux, length);
                descriere = aux;

                delete[] genuri;
                genuri = new int[nrGenuri];
                for (int i = 0; i < nrGenuri; i++)
                {
                    f.read((char*)&genuri[i], sizeof(genuri[i]));
                }

                int pos2 = f.tellg();

                of.write((char*)&idFilm, sizeof(idFilm));

                of.write(numeFilm, (long long)strlen(numeFilm) + 1);

                of.write((char*)&varstaMinima, sizeof(varstaMinima));
                of.write((char*)&durataFilmMinute, sizeof(durataFilmMinute));
                of.write((char*)&nrGenuri, sizeof(nrGenuri));
                of.write((char*)&tarif, sizeof(tarif));

                for (int i = 0; i < nrGenuri; i++)
                {
                    of.write((char*)&genuri[i], sizeof(genuri[i]));
                }

                int length1 = descriere.length() + 1;
                of.write(descriere.c_str(), length1);
            }
        }

        of.close();
        f.close();

        if (remove("filme.bin") != 0)
            cout << "Fisierul a fost sters" << endl;

        if (rename("filme2.bin", "filme.bin") != 0)
            cout << "Fisierul a fost modificat";
    }


    void serializare() {
        fstream of("filme.bin", ios::binary | ios::app);

        of.write((char*)&idFilm, sizeof(idFilm));

        of.write(numeFilm, (long long)strlen(numeFilm) + 1);

        of.write((char*)&varstaMinima, sizeof(varstaMinima));
        of.write((char*)&durataFilmMinute, sizeof(durataFilmMinute));
        of.write((char*)&nrGenuri, sizeof(nrGenuri));
        of.write((char*)&tarif, sizeof(tarif));

        for (int i = 0; i < nrGenuri; i++)
        {
            of.write((char*)&genuri[i], sizeof(genuri[i]));
        }

        int length = descriere.length() + 1;
        of.write(descriere.c_str(), length);

        of.close();
    }

    void deserializare() {
        ifstream f("filme.bin", ios::binary);

        int id = idFilm;

        while (f.read((char*)&idFilm, sizeof(idFilm))) {
            if (idFilm == id) {
                int pos = f.tellg();

                string buffer = "";
                char c = 0;
                while ((c = f.get()) != 0) {
                    buffer += c;
                }
                delete[] numeFilm;
                numeFilm = new char[buffer.length() + 1];
                strcpy_s(numeFilm, buffer.length() + 1, buffer.c_str());

                f.read((char*)&varstaMinima, sizeof(varstaMinima));
                f.read((char*)&durataFilmMinute, sizeof(durataFilmMinute));
                f.read((char*)&nrGenuri, sizeof(nrGenuri));
                f.read((char*)&tarif, sizeof(tarif));
                
                delete[] genuri;
                genuri = new int[nrGenuri];
                for (int i = 0; i < nrGenuri; i++) {
                    f.read((char*)&genuri[i], sizeof(genuri[i]));
                }

                int length = 0;
                f.read((char*)&length, sizeof(length));
                char* aux = new char[length];
                f.read(aux, length);
                descriere = aux;

                break;
            }
        }
       // printMovie();
        f.close();
    }

    void printMovie() {
        cout << "Numele Filmului: ";
        cout << numeFilm << endl;

        cout << "Durata Filmului: ";
        cout << durataFilmMinute << endl;

        cout << "Descrierea Filmului: ";
        cout << descriere << endl;

        cout << "Genurile Filmului: ";
        int* genuri = getGenuri();
        for (int i = 0; i < nrGenuri; i++) {
            int gen = genuri[i];

            if (gen == Film::GenFilm::comedie) {
                cout << "Comedie ";
            }

            else if (gen == Film::GenFilm::romantic) {
                cout << "Romantic ";
            }

            else if (gen == Film::GenFilm::scifi) {
                cout << "Scifi ";
            }
        }

        cout << "Id-ul filmului: ";
        cout << idFilm << endl;

        cout << "Tariful filmului: ";
        cout << tarif << endl;

        cout << "Varsta minima film: ";
        cout << varstaMinima << endl;

    }


    static void printMovie(Film* f) {
        cout << "Numele Filmului: ";
        cout << f->numeFilm << endl;

        cout << "Durata Filmului: ";
        cout << f->durataFilmMinute << endl;

        cout << "Descrierea Filmului: ";
        cout << f->descriere << endl;

        cout << "Genurile Filmului: ";
        int* genuri = f->getGenuri();
        for (int i = 0; i < f->nrGenuri; i++) {
            int gen = f->genuri[i];

            if (gen == Film::GenFilm::comedie) {
                cout << "Comedie ";
            }

            else if (gen == Film::GenFilm::romantic) {
                cout << "Romantic ";
            }

            else if (gen == Film::GenFilm::scifi) {
                cout << "Scifi ";
            }
        }

        cout << "Id-ul filmului: ";
        cout << f->idFilm << endl;

        cout << "Tariful filmului: ";
        cout << f->tarif << endl;

        cout << "Varsta minima film: ";
        cout << f->varstaMinima << endl;

    }

    bool operator! () {
        return numeFilm != nullptr;
    }

    Film operator++(int i) {
        Film copie = *this;
        this->varstaMinima++;
        return *this;
    }

    Film operator++() {
        this->varstaMinima++;
        return *this;
    }

    Film operator-(int tarif) {
        if (tarif >= 0.0 && tarif <= 500) {
            Film copie = *this;
            copie.tarif -= tarif;
            return copie;
        }
        else {
            //throw 500;
        }
    }

    Film operator+(int tarif) {
        if (tarif >= 0.0 && tarif <= 500) {
            Film copie = *this;
            copie.tarif += tarif;
            return copie;
        }
        else {
            //throw 500;
        }
    }

    string operator[] (int index)
        // throw (exception)
    {
        if (genuri != nullptr && index >= 0 && index <= nrGenuri) {
            int gen = genuri[index];
            if (gen == 1) {
                return "comedie";
            }
            else if (gen == 2) {
                return "romantic";
            }
            else if (gen == 3) {
                return "scifi";
            }
        }
    }

    explicit operator int() {
        return durataFilmMinute;
    }

    char* operator()() {
        return numeFilm;
    }

    static int generateId() {
        ifstream f("filme.bin", ios::binary);
        f.seekg(0, ios::end);
        int pos = f.tellg();

        if (pos > 0) {
            int size = pos / sizeof(Film);
            return size + 1;
        }
        else {
            return 1;
        }
        f.close();
    }

    static void printeazaToateFilmele() {
        ifstream f("filme.bin", ios::binary | ios::in);

        int idFilm;

        while (f.read((char*)&idFilm, sizeof(idFilm))) {

            Film* film = new Film(idFilm);

            string buffer = "";
            char c = 0;
            while ((c = f.get()) != 0) {
                buffer += c;
            }

            film->numeFilm = new char[buffer.length() + 1];
            strcpy_s(film->numeFilm, buffer.length() + 1, buffer.c_str());

            f.read((char*)&film->varstaMinima, sizeof(varstaMinima));
            f.read((char*)&film->durataFilmMinute, sizeof(durataFilmMinute));
            f.read((char*)&film->nrGenuri, sizeof(nrGenuri));
            f.read((char*)&film->tarif, sizeof(tarif));

            film->genuri = new int[film->nrGenuri];
            for (int i = 0; i < film->nrGenuri; i++) {
                f.read((char*)&film->genuri[i], sizeof(film->genuri[i]));
            }

            int length = 0;
            f.read((char*)&length, sizeof(length));
            char* aux = new char[length];
            f.read(aux, length);
            film->descriere = aux;

            printMovie(film);
            delete film;
        }

        f.close();
    }

    friend ostream& operator<<(ostream&, Film);
    friend istream& operator>>(istream&, Film&);
};

ostream& operator<<(ostream& out, Film f) {
    out << "Numele Filmului: ";
    out << f.numeFilm << endl;

    out << "Durata Filmului: ";
    out << f.durataFilmMinute << endl;

    out << "Descrierea Filmului: ";
    out << f.descriere << endl;

    out << "Genurile Filmului: ";
    int* genuri = f.getGenuri();
    for (int i = 0; i < f.nrGenuri; i++) {
        int gen = f.genuri[i];

        if (gen == Film::GenFilm::comedie) {
            cout << "Comedie ";
        }

        else if (gen == Film::GenFilm::romantic) {
            cout << "Romantic ";
        }

        else if (gen == Film::GenFilm::scifi) {
            cout << "Scifi ";
        }
    }

    out << "Id-ul filmului: ";
    out << f.idFilm << endl;

    out << "Tariful filmului: ";
    out << f.tarif << endl;

    out << "Varsta minima film: ";
    out << f.varstaMinima << endl;

    return out;
}

istream& operator>>(istream& in, Film& f) {
    cout << "Introduceti numele filmului: ";
    string buffer;
    in >> ws;
    getline(in, buffer);
    f.numeFilm = new char[buffer.length() + 1];
    strcpy_s(f.numeFilm, buffer.length() + 1, buffer.c_str());

    cout << "Introduceti durata filmului (in minute): ";
    in >> f.durataFilmMinute;

    cout << "Introduceti numarul de genuri: ";
    in >> f.nrGenuri;

    if (f.nrGenuri > 0) {
        f.genuri = new int[f.nrGenuri];

        for (int i = 0; i < f.nrGenuri; i++) {
            cout << "Introduceti genul filmului, \nIntroduceti 1 (pentru Comedie), 2 (pentru Romantic) sau 3(pentru Scifi): ";
            in >> f.genuri[i];
        }
    }
    else {
        f.nrGenuri = 0;
        f.genuri = nullptr;
    }

    cout << "Introduceti varsta minima: ";
    in >> f.varstaMinima;
    f.varstaMinima++;

    cout << "Introduceti tariful filmului: ";
    in >> f.tarif;

    cout << "Introduceti descrierea filmului: ";
    in >> ws;
    getline(in, f.descriere);

    return in;
}

