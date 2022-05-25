// Tetris.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <random>
#include <ctime>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <chrono>
#include <thread>
#include <map>
#include "Figure.h"

using namespace std;

int counterRotate = 0;
int counterRotatePre = counterRotate;

char gamePole[40][20];
char gamePoleMemory[40][20];

string listFigure[]{ "O", "I", "S", "Z", "L", "J", "T" };

void windowPole() {//Окно игрового поля
    system("mode con cols=50 lines=50");
    SetConsoleTitleA("TETRIS");
}

bool checkGamePole() {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 20; j++) {
            if (gamePoleMemory[i][j] == 'O' ||
                gamePoleMemory[i][j] == 'T' ||
                gamePoleMemory[i][j] == 'J' ||
                gamePoleMemory[i][j] == 'L' ||
                gamePoleMemory[i][j] == 'Z' ||
                gamePoleMemory[i][j] == 'S' ||
                gamePoleMemory[i][j] == 'I')
            {
                return true;
            }
        }
    }
    return false;
}

void zGamePoleMemory() {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 20; j++) {
            gamePoleMemory[i][j] = gamePole[i][j];
        }
    }
}

void zGamePole() {

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 20; j++) {
            //if (!checkGamePole) {
            //    gamePole[i][j]='.';
            //}
            gamePole[i][j] = '.';
        }
    }
}

Figure randomFigureSpawn() {
    srand(time(NULL));
    Figure fig(0, rand() % 18+1, listFigure[rand() % 7]);
    return fig;
}

void spawnFig(Figure fig) {

    string name = fig.nameFigure;
    int X = fig.cordX;
    int Y = fig.cordY;

    //if (fig.rotatePos >= 4) {
    //    fig.rotatePos = 0;
    //}

    int RP = fig.rotatePos;

    /*HANDLE handle;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);

    srand(time(NULL));*/

    if (name == "O") {
        //SetConsoleTextAttribute(handle,rand()%14+1);
        gamePole[X][Y] = 'O';
        gamePole[X][Y + 1] = 'O';
        gamePole[X + 1][Y] = 'O';
        gamePole[X + 1][Y + 1] = 'O';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "I" && (RP == 0 || RP == 2)) {
        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
        gamePole[X][Y] = 'I';
        gamePole[X + 1][Y] = 'I';
        gamePole[X + 2][Y] = 'I';
        gamePole[X + 3][Y] = 'I';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "I" && (RP == 1 || RP == 3)) {
        gamePole[X][Y] = 'I';
        gamePole[X][Y + 1] = 'I';
        gamePole[X][Y + 2] = 'I';
        gamePole[X][Y - 1] = 'I';
    }
    if (name == "S" && (RP == 0 || RP == 2)) {
        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
        gamePole[X][Y] = 'S';
        gamePole[X][Y + 1] = 'S';
        gamePole[X + 1][Y] = 'S';
        gamePole[X + 1][Y - 1] = 'S';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "S" && (RP == 1 || RP == 3)) {
        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
        gamePole[X][Y] = 'S';
        gamePole[X + 1][Y] = 'S';
        gamePole[X + 1][Y + 1] = 'S';
        gamePole[X + 2][Y + 1] = 'S';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "Z" && (RP == 0 || RP == 2)) {
        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
        gamePole[X][Y] = 'Z';
        gamePole[X][Y - 1] = 'Z';
        gamePole[X + 1][Y] = 'Z';
        gamePole[X + 1][Y + 1] = 'Z';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "Z" && (RP == 1 || RP == 3)) {
        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
        gamePole[X][Y] = 'Z';
        gamePole[X + 1][Y] = 'Z';
        gamePole[X + 1][Y - 1] = 'Z';
        gamePole[X + 2][Y - 1] = 'Z';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "L" && RP == 0) {
        gamePole[X][Y] = 'L';
        gamePole[X + 1][Y] = 'L';
        gamePole[X + 2][Y] = 'L';
        gamePole[X + 2][Y + 1] = 'L';
    }
    if (name == "L" && RP == 1) {
        gamePole[X][Y] = 'L';
        gamePole[X + 1][Y] = 'L';
        gamePole[X][Y + 1] = 'L';
        gamePole[X][Y + 2] = 'L';
    }
    if (name == "L" && RP == 2) {
        gamePole[X][Y] = 'L';
        gamePole[X][Y - 1] = 'L';
        gamePole[X + 1][Y] = 'L';
        gamePole[X + 2][Y] = 'L';
    }
    if (name == "L" && RP == 3) {
        gamePole[X][Y] = 'L';
        gamePole[X - 1][Y] = 'L';
        gamePole[X][Y - 1] = 'L';
        gamePole[X][Y - 2] = 'L';
    }
    if (name == "J" && RP == 0) {
        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
        gamePole[X][Y] = 'J';
        gamePole[X + 1][Y] = 'J';
        gamePole[X + 2][Y] = 'J';
        gamePole[X + 2][Y - 1] = 'J';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "J" && RP == 1) {
        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
        gamePole[X][Y] = 'J';
        gamePole[X + 1][Y] = 'J';
        gamePole[X][Y + 1] = 'J';
        gamePole[X][Y + 2] = 'J';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "J" && RP == 2) {
        gamePole[X][Y] = 'J';
        gamePole[X][Y + 1] = 'J';
        gamePole[X + 1][Y] = 'J';
        gamePole[X + 2][Y] = 'J';
    }
    if (name == "J" && RP == 3) {
        gamePole[X][Y] = 'J';
        gamePole[X + 1][Y] = 'J';
        gamePole[X][Y - 1] = 'J';
        gamePole[X][Y - 2] = 'J';
    }
    if (name == "T" && RP == 0) {
        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
        gamePole[X][Y] = 'T';
        gamePole[X + 1][Y] = 'T';
        gamePole[X + 1][Y - 1] = 'T';
        gamePole[X + 1][Y + 1] = 'T';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "T" && RP == 1) {
        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
        gamePole[X][Y] = 'T';
        gamePole[X + 1][Y] = 'T';
        gamePole[X - 1][Y] = 'T';
        gamePole[X][Y + 1] = 'T';
        //SetConsoleTextAttribute(handle, 15);
    }
    if (name == "T" && RP == 2) {
        gamePole[X][Y] = 'T';
        gamePole[X][Y + 1] = 'T';
        gamePole[X][Y - 1] = 'T';
        gamePole[X + 1][Y] = 'T';
    }
    if (name == "T" && RP == 3) {
        gamePole[X][Y] = 'T';
        gamePole[X + 1][Y] = 'T';
        gamePole[X - 1][Y] = 'T';
        gamePole[X][Y - 1] = 'T';
    }
}

void checkcheck() {
    for (int i = 39; i >= 35; i--) {
        for (int j = 0; j < 20; j++) {
            if (gamePole[i][j] == 'O' ||
                gamePole[i][j] == 'T' ||
                gamePole[i][j] == 'J' ||
                gamePole[i][j] == 'L' ||
                gamePole[i][j] == 'Z' ||
                gamePole[i][j] == 'S' ||
                gamePole[i][j] == 'I')
            {
                gamePole[i][j] = 'X';
            }
        }
    }
}

bool checkPolePoint() {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 20; j++) {
            if ((gamePole[i][j] == 'O' ||
                gamePole[i][j] == 'T' ||
                gamePole[i][j] == 'J' ||
                gamePole[i][j] == 'L' ||
                gamePole[i][j] == 'Z' ||
                gamePole[i][j] == 'S' ||
                gamePole[i][j] == 'I')&&(gamePole[i+1][j]=='X'))
            {
                return true;
                break;
            }
        }
    }
    return false;
}

bool checkPole() {
    for (int j = 0; j < 20; j++) {
        if ((gamePole[39][j] == 'O' ||
            gamePole[39][j] == 'T' ||
            gamePole[39][j] == 'J' ||
            gamePole[39][j] == 'L' ||
            gamePole[39][j] == 'Z' ||
            gamePole[39][j] == 'S' ||
            gamePole[39][j] == 'I'))
        {
            checkcheck();
            if (checkPolePoint()) {
                return true;
                break;
            }
        }
    }
    return false;
}

int checkPoint() {

    int checkCount = 0;

    for (int i = 39; i >= 0; i--) {
        checkCount = 0;
        for (int j = 0; j < 20; j++) {
            if (gamePole[i][j]!='.') {
                checkCount++;
            }
        }
        if (checkCount == 20) {
            return i;
            break;
        }
        if (checkCount == 0) {
            return 50;
            break;
        }
    }
    return 0;
}

Figure moveFigure(Figure fig,string name) {
    if (name == "base") {
        fig.cordX++;
        zGamePole();
        spawnFig(fig);
    }
    if (name == "right") {
        fig.cordY++;
        zGamePole();
        spawnFig(fig);
    }
    if (name == "left") {
        fig.cordY--;
        zGamePole();
        spawnFig(fig);
    }
    return fig;
}

//void moveFigure() {
//    for (int i = 39; i >= 0; i--) {
//        for (int j = 19; j >= 0; j--) {
//            if (gamePole[i][j] == 'O' ||
//                gamePole[i][j] == 'T' ||
//                gamePole[i][j] == 'J' ||
//                gamePole[i][j] == 'L' ||
//                gamePole[i][j] == 'Z' ||
//                gamePole[i][j] == 'S' ||
//                gamePole[i][j] == 'I') 
//            {
//                gamePole[i + 1][j] = gamePole[i][j];
//                gamePole[i][j] = '.';
//            }
//        }
//    }
//}

Figure presKey(char k,Figure fig) {

    if (k == 'a') {
       fig = moveFigure(fig, "left");
    }
    if (k == 'd') {
        fig = moveFigure(fig, "right");
    }
    if (k == 'w') {
        fig.onePlus();
        zGamePole();
        spawnFig(fig);
    }

    return fig;
}

void outGamePole() {
    _COORD XY{ 0, 0 };
    HANDLE A = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < 40; i++) {
        XY.Y = i;
        for (int j = 0; j < 20; j++) {
            XY.X = j;
            SetConsoleCursorPosition(A, XY);
            if (gamePoleMemory[i][j] == 'I' ||
                gamePoleMemory[i][j] == 'J' ||
                gamePoleMemory[i][j] == 'L' ||
                gamePoleMemory[i][j] == 'O' ||
                gamePoleMemory[i][j] == 'S' ||
                gamePoleMemory[i][j] == 'Z' ||
                gamePoleMemory[i][j] == 'T'||
                gamePoleMemory[i][j] == 'X')
            {
                gamePole[i][j] = 'X';
            }
            cout << gamePole[i][j];
        }
    }
}

void editPole(int I) {
    for (int j = 19; j >= 0; j--) {
        gamePole[checkPoint()][j] = '.';
    }
    while (checkPoint() != 50) {
        for (int i = 39; i >= 0; i--) {
            for (int j = 19; j >= 0; j--) {
                if ((gamePole[i][j] == 'O' ||
                    gamePole[i][j] == 'T' ||
                    gamePole[i][j] == 'J' ||
                    gamePole[i][j] == 'L' ||
                    gamePole[i][j] == 'Z' ||
                    gamePole[i][j] == 'S' ||
                    gamePole[i][j] == 'I')&&(i<39)) 
                {
                    gamePole[i + 1][j] = gamePole[i][j];
                    gamePole[i][j] = '.';
                }
            }
        }
    }
}

//void rotateFigure(Figure fig,int i) {
//
//    if (fig.rotatePos >= 4) {
//        fig.rotatePos = 0;
//    }
//
//    string name = fig.nameFigure;
//    
//    int X = fig.cordX;
//    int Y = fig.cordY;
//
//    if ((name == "O")) {
//        //SetConsoleTextAttribute(handle,rand()%14+1);
//        gamePole[X][Y] = 'O';
//        gamePole[X][Y + 1] = 'O';
//        gamePole[X + 1][Y] = 'O';
//        gamePole[X + 1][Y + 1] = 'O';
//        //SetConsoleTextAttribute(handle, 15);
//    }
//    if (name == "I"&&(fig.rotatePos==1||fig.rotatePos==3)) {
//        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
//        gamePole[X][Y] = 'I';
//        gamePole[X][Y+1] = 'I';
//        gamePole[X][Y+2] = 'I';
//        gamePole[X][Y-1] = 'I';
//        //SetConsoleTextAttribute(handle, 15);
//    }
//    if (name == "S") {
//        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
//        gamePole[X][Y] = 'S';
//        gamePole[X+1][Y] = 'S';
//        gamePole[X + 1][Y+1] = 'S';
//        gamePole[X + 2][Y + 1] = 'S';
//        //SetConsoleTextAttribute(handle, 15);
//    }
//    if (name == "Z") {
//        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
//        gamePole[X][Y] = 'Z';
//        gamePole[X+1][Y] = 'Z';
//        gamePole[X + 1][Y-1] = 'Z';
//        gamePole[X + 2][Y - 1] = 'Z';
//        //SetConsoleTextAttribute(handle, 15);
//    }
//    if (name == "L") {
//        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
//        gamePole[X][Y] = 'L';
//        gamePole[X + 1][Y] = 'L';
//        gamePole[X][Y+1] = 'L';
//        gamePole[X][Y + 2] = 'L';
//        
//        //gamePole[X][Y] = 'L';
//        //gamePole[X][Y-1] = 'L';
//        //gamePole[X+1][Y] = 'L';
//        //gamePole[X+2][Y] = 'L';
//
//        //gamePole[X][Y] = 'L';
//        //gamePole[X + 1][Y] = 'L';
//        //gamePole[X][Y - 1] = 'L';
//        //gamePole[X][Y - 2] = 'L';
//        //SetConsoleTextAttribute(handle, 15);
//    }
//    if (name == "J") {
//        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
//        gamePole[X][Y] = 'J';
//        gamePole[X + 1][Y] = 'J';
//        gamePole[X][Y+1] = 'J';
//        gamePole[X][Y + 2] = 'J';
//
//        //gamePole[X][Y] = 'J';
//        //gamePole[X][Y+1] = 'J';
//        //gamePole[X+1][Y] = 'J';
//        //gamePole[X+2][Y] = 'J';
//
//        //gamePole[X][Y] = 'J';
//        //gamePole[X+1][Y] = 'J';
//        //gamePole[X][Y - 1] = 'J';
//        //gamePole[X][Y - 2] = 'J';
//
//        //SetConsoleTextAttribute(handle, 15);
//    }
//    if (name == "T") {
//        //SetConsoleTextAttribute(handle, rand() % 14 + 1);
//        gamePole[X][Y] = 'T';
//        gamePole[X + 1][Y] = 'T';
//        gamePole[X - 1][Y] = 'T';
//        gamePole[X][Y + 1] = 'T';
//
//        //gamePole[X][Y] = 'T';
//        //gamePole[X][Y+1] = 'T';
//        //gamePole[X][Y - 1] = 'T';
//        //gamePole[X + 1][Y] = 'T';
//
//        //gamePole[X][Y] = 'T';
//        //gamePole[X + 1][Y] = 'T';
//        //gamePole[X - 1][Y] = 'T';
//        //gamePole[X][Y - 1] = 'T';
//        //SetConsoleTextAttribute(handle, 15);
//    }
//}

int main()
{
    //system("color 02");

    windowPole();//Вызов функции окна игрового поля
    
    zGamePole();
    zGamePoleMemory();

    while (true) {

        bool flag = true;

        Figure figure = randomFigureSpawn();

        spawnFig(figure);
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

        while (flag) {
            char key;
            while (!_kbhit()&&flag)
            {
                if (checkPole()) {
                    //cout << "DONE!";
                    zGamePoleMemory();
                    flag = false;
                    //this_thread::sleep_for(chrono::milliseconds(100));
                }
                //else if(checkPoint()>0) {
                //    editPole(checkPoint());
                //}
                else {
                    figure = moveFigure(figure, "base");
                    outGamePole();
                    this_thread::sleep_for(chrono::milliseconds(200));
                }
            }
            if (flag) {
                key = _getch();

                figure = presKey(key, figure);
            }
        }
    }
}