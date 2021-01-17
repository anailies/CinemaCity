// CinemaCity.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Program.h"
#include "Bilet.h"
#include "CinemaCity.h"
#include <iostream>

const string Program::regexData = "^([0]\\d|[1][0-2])\\/([0-2]\\d|[3][0-1])\\/([2][01]|[1][6-9])\\d{2}(\\s([0-1]\\d|[2][0-3])(\\:[0-5]\\d){1,2})?$";
const int Loc::discount = 10;

int main()
{
    Sala sala;
    cin >> sala;
    cout << sala;

    Loc loc;
    cin >> loc;
    cout << loc;


    Film film;
    cin >> film;
    cout << film;


    Bilet bilet;
    cin >> bilet;
    cout << bilet;


    Program program;
    cin >> program;
    cout << program;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
