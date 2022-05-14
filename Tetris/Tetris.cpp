// Tetris.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Random>
#include <ctime>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <chrono>
#include <thread>
#include "Figure.h"

using namespace std;

char gamePole[40][20];

string listFigure[]{"O", "I", "S", "Z", "L", "J", "T"};

void windowPole() {//Окно игрового поля
    system("mode con cols=50 lines=50");
    SetConsoleTitleA("TETRIS");
}

void zGamePole() {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 20; j++) {
            gamePole[i][j] = '.';
        }
    }
}

void spawnFig(string name,int X,int Y) {

    HANDLE handle;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);

    srand(time(NULL));

    if (name == "O") {
        //SetConsoleTextAttribute(handle,rand()%14+1);
        gamePole[X][Y] = 'O';
        gamePole[X][Y + 1] = 'O';
        gamePole[X + 1][Y] = 'O';
        gamePole[X + 1][Y + 1] = 'O';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "I") {
        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
        gamePole[X][Y] = 'I';
        gamePole[X + 1][Y] = 'I';
        gamePole[X + 2][Y] = 'I';
        gamePole[X + 3][Y] = 'I';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "S") {
        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
        gamePole[X][Y] = 'S';
        gamePole[X][Y + 1] = 'S';
        gamePole[X + 1][Y] = 'S';
        gamePole[X + 1][Y - 1] = 'S';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "Z") {
        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
        gamePole[X][Y] = 'Z';
        gamePole[X][Y-1] = 'Z';
        gamePole[X+1][Y] = 'Z';
        gamePole[X+1][Y+1] = 'Z';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "L") {
        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
        gamePole[X][Y] = 'L';
        gamePole[X+1][Y] = 'L';
        gamePole[X + 2][Y] = 'L';
        gamePole[X + 2][Y + 1] = 'L';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "J") {
        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
        gamePole[X][Y] = 'J';
        gamePole[X + 1][Y] = 'J';
        gamePole[X + 2][Y] = 'J';
        gamePole[X + 2][Y - 1] = 'J';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "T") {
        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
        gamePole[X][Y] = 'T';
        gamePole[X + 1][Y] = 'T';
        gamePole[X + 1][Y-1] = 'T';
        gamePole[X + 1][Y + 1] = 'T';
        //SetConsoleTextAttribute(handle, 15);
    }
}

Figure randomFigureSpawn() {
    srand(time(NULL));
    Figure fig(0, rand() % 20, listFigure[rand() % 7]);
    return fig;
}

bool checkPole() {
        for (int j = 0; j < 20; j++) {
            if (gamePole[39][j] == 'O' ||
                gamePole[39][j] == 'T' ||
                gamePole[39][j] == 'J' ||
                gamePole[39][j] == 'L' ||
                gamePole[39][j] == 'Z' ||
                gamePole[39][j] == 'S' ||
                gamePole[39][j] == 'I') {
                return true;
                break;
            }
        }
        return false;
}

void moveFigure() {
    for (int i = 39; i >= 0; i--) {
        for (int j = 19; j >= 0; j--) {
            if (gamePole[i][j] == 'O' ||
                gamePole[i][j] == 'T' ||
                gamePole[i][j] == 'J' ||
                gamePole[i][j] == 'L' ||
                gamePole[i][j] == 'Z' ||
                gamePole[i][j] == 'S' ||
                gamePole[i][j] == 'I') 
            {
                gamePole[i + 1][j] = gamePole[i][j];
                gamePole[i][j] = '.';
            }
        }
    }
}

void outGamePole() {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 20; j++) {
            cout << gamePole[i][j];
        }
        cout << '\n';
    }
}

int main()
{
    //system("color 02");

    windowPole();//Вызов функции окна игрового поля

    Figure figure = randomFigureSpawn();

    zGamePole();

    spawnFig(figure.nameFigure, figure.cordX, figure.cordY);
    //for (int i = 0; i < 40; i++) {
    //    for (int j = 0; j < 20; j++) {
    //        cout << gamePole[i][j];
    //    }
    //    cout << '\n';
    //}
    /*for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 20; j++) {
            cout << gamePole[i][j];
        }
        cout << '\n';
    }*/
    while (true) {
        if (checkPole()) {
            cout << "DONE!";
            break;
        }
        else {
            moveFigure();
            outGamePole();
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
