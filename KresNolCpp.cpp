#include <iostream>
#include <string>
#include <time.h>

char getSymbol();
void generateGameField(const char arr[]);
void makeMove(char arr[], char symbol, char opponentSymbol);
void enemyMove(char arr[], char symbol, char opponentSymbol);
bool checkForWin(const char arr[], char symbol);
bool checkForDraw(const char arr[]);

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(NULL));

    char symbol = getSymbol();
    char opponentSymbol;
    if (symbol == 'x')
        opponentSymbol = 'o';
    else
        opponentSymbol = 'x';
    char c1 = '1',
        c2 = '2',
        c3 = '3',
        c4 = '4',
        c5 = '5',
        c6 = '6',
        c7 = '7',
        c8 = '8',
        c9 = '9';
    char gameField[] = { c1, c2, c3, c4, c5, c6, c7, c8, c9 };
    generateGameField(gameField);

    makeMove(gameField, symbol, opponentSymbol);

    return 0;
}

char getSymbol() {
    std::cout << "Добро пожаловать в игру крестики нолики!" << std::endl;

    char symbol;

    std::cout << "Выберите x или o" << std::endl;
    std::cin >> symbol;

    return symbol;
}

void generateGameField(const char arr[]) {
    for (int i = 0; i < 9; i++) {
        std::cout << arr[i] << " ";
        if ((i + 1) % 3 == 0) std::cout << std::endl;
    }
}
void makeMove(char arr[], char symbol, char opponentSymbol) {
    while (true) {
        std::cout << "Your move: ";
        char move;
        std::cin >> move;

        for (int i = 0; i < 9; i++) {
            if (move == arr[i]) {
                arr[i] = symbol;
                generateGameField(arr);
                if (checkForWin(arr, symbol)) {
                    std::cout << "Победа!" << std::endl;
                    exit(0);
                }
                else if (checkForDraw(arr)) {
                    std::cout << "Ничья!" << std::endl;
                    exit(0);
                }
                else {
                    enemyMove(arr, symbol, opponentSymbol);
                }
                break;
            }
        }
        std::cout << "Invalid move! Please try again." << std::endl;
    }
}

void enemyMove(char arr[], char symbol, char opponentSymbol) {
    while (true) {
        int randomNum = 1 + rand() % 9;
        char move = static_cast<char>(randomNum);

        if (arr[move] != 'x' && arr[move] != 'o') {
            arr[move] = opponentSymbol;
            std::cout << "Ход пк:" << std::endl;
            generateGameField(arr);
            if (checkForWin(arr, opponentSymbol)) {
                std::cout << "Выйграл пк!" << std::endl;
                exit(0);
            }
            else if (checkForDraw(arr)) {
                std::cout << "Ничья!" << std::endl;
                exit(0);
            }
            else {
                makeMove(arr, symbol, opponentSymbol);
            }
            break;
        }
    }
}

bool checkForWin(const char arr[], char symbol) {
    for (int i = 0; i < 9; i += 3)
        if (arr[i] == symbol && arr[i + 1] == symbol && arr[i + 2] == symbol)
            return true;

    for (int i = 0; i < 3; i++)
        if (arr[i] == symbol && arr[i + 3] == symbol && arr[i + 6] == symbol)
            return true;

    if ((arr[0] == symbol && arr[4] == symbol && arr[8] == symbol) ||
        (arr[2] == symbol && arr[4] == symbol && arr[6] == symbol))
        return true;

    return false;
}

bool checkForDraw(const char arr[]) {
    for (int i = 0; i < 9; i++) {
        if (arr[i] != 'x' && arr[i] != 'o') {
            return false;
        }
    }
    return true;
}