#include <iostream>
#include <fstream>
using namespace std;

bool PERMIT = true;

void gameMaker(char place[3][3], int input, int turn)
{
    cout << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << " | ";
        for (int j = 0; j < 3; j++)
        {
            if ((i * 3 + j) + 1 == input && (place[i][j] == 'X' || place[i][j] == 'O')) // Player1
            {
                PERMIT = false;
            }
            else if ((i * 3 + j) + 1 == input && turn == 1) // Player1
            {
                place[i][j] = 'X';
            }
            else if ((i * 3 + j) + 1 == input && turn == 2) // Player2
            {
                place[i][j] = 'O';
            }
            cout << place[i][j] << " | ";
        }
        cout << endl;
    }
}

void fileUpdate(string player, int k)
{
    int a = 0, b = 0, c = 0;
    if (k == 1)
    { // win
        a++;
    }
    if (k == 2)
    { // draw
        b++;
    }
    if (k == 3)
    { // lose
        c++;
    }
    bool isRepetitive = false;
    string item;
    string winCount;
    string drawCount;
    string loseCount;

    fstream SBF;
    SBF.open("Scoreboard.txt");
    fstream write("Scoreboard.txt");

    while (SBF >> item)
    {
        write << item << endl;
        if (item == player)
        {
            isRepetitive = true;
            SBF >> winCount;
            SBF >> drawCount;
            SBF >> loseCount;
            write << stoi(winCount) + a << endl
                  << stoi(drawCount) + b << endl
                  << stoi(loseCount) + c << endl;
        }
    }
    if (!isRepetitive)
    {
        write << player << endl
              << a << endl
              << b << endl
              << c;
    }

    SBF.close();
}

bool winCheck(char place[3][3], string player1, string player2)
{
    char c = 'X';
    for (int i = 0; i < 2; i++)
    {
        // Vertical
        int col = 0, row = 0;
        for (row = 0; row < 3; row++)
        {
            if (place[col][row] == c && place[col + 1][row] == c && place[col + 2][row] == c)
            {
                if (c == 'X')
                {
                    cout << player1 << " Won" << endl;
                    fileUpdate(player1, 1);
                    fileUpdate(player2, 3);
                    return false;
                }
                else if (c == 'O')
                {
                    cout << player2 << " Won" << endl;
                    fileUpdate(player2, 1);
                    fileUpdate(player1, 3);
                    return false;
                }
            }
        }

        // Horizontal
        col = 0, row = 0;
        for (col = 0; col < 3; col++)
        {
            if (place[col][row] == c && place[col][row + 1] == c && place[col][row + 2] == c)
            {
                if (c == 'X')
                {
                    cout << player1 << " Won" << endl;
                    fileUpdate(player1, 1);
                    fileUpdate(player2, 3);
                    return false;
                }
                else if (c == 'O')
                {
                    cout << player2 << " Won" << endl;
                    fileUpdate(player2, 1);
                    fileUpdate(player1, 3);
                    return false;
                }
            }
        }

        // Diagonal+
        col = 0, row = 0;
        if (place[col][row] == c && place[col + 1][row + 1] == c && place[col + 2][row + 2] == c)
        {
            if (c == 'X')
            {
                cout << player1 << " Won" << endl;
                fileUpdate(player1, 1);
                fileUpdate(player2, 3);
                return false;
            }
            else if (c == 'O')
            {
                cout << player2 << " Won" << endl;
                fileUpdate(player2, 1);
                fileUpdate(player1, 3);
                return false;
            }
        }

        // Diagonal-
        if (place[col][row + 2] == c && place[col + 1][row + 1] == c && place[col + 2][row] == c)
        {
            if (c == 'X')
            {
                cout << player1 << " Won" << endl;
                fileUpdate(player1, 1);
                fileUpdate(player2, 3);
                return false;
            }
            else if (c == 'O')
            {
                cout << player2 << " Won" << endl;
                fileUpdate(player2, 1);
                fileUpdate(player1, 3);
                return false;
            }
        }
        c = 'O';
    }
    return true;
}

void scoreboard()
{
    string item;
    string winCount;
    string drawCount;
    string loseCount;

    fstream SBFA;
    SBFA.open("Scoreboard.txt");

    while (SBFA >> item && !SBFA.eof())
    {
        SBFA >> winCount;
        SBFA >> drawCount;
        SBFA >> loseCount;
        cout << item << " :"
             << " Win = " << winCount << ", Draw = " << drawCount << ", Lose = " << loseCount << endl;
    }
    SBFA.close();
}

int main()
{
    char place[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    bool gameOn = true;
    bool gamePlay = true;
    int mode = 0;
    int turn = 1;
    int input = 0;
    string player1 = "";
    string player2 = "";
    cout << "Welcome to Menu !" << endl;

    while (gameOn)
    {
        if (mode == 0)
        {
            gamePlay = true;
            turn = 1;
            input = 0;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    place[i][j] = 49 + (i * 3 + j); // char(49) : 1
                }
            }
            cout << "\n1) Start game " << endl;
            cout << "2) Scoreboard " << endl;
            cout << "3) Exit " << endl;
            cin >> mode;
        }

        else if (mode == 1)
        {
            cout << "First Player's Name"
                 << " : ";
            cin >> player1;
            cout << "Second Player's Name"
                 << " : ";
            cin >> player2;

            int totalT = 0;
            gameMaker(place, input, turn);

            while (gamePlay)
            {
                turn = (totalT % 2 + 1);

                if (turn == 1)
                {
                    // Input player1 :
                    cout << player1 << " : ";
                    cin >> input;
                    while (input > 9 || input < 0)
                    {
                        cout << "Please Enter a Valid Number (1 to 9) : ";
                        cin >> input;
                    }
                }
                else if (turn == 2)
                {
                    // Input player2 :
                    cout << player2 << " : ";
                    cin >> input;
                    while (input > 9 || input < 0)
                    {
                        cout << "Please Enter a Valid Number (1 to 9) : ";
                        cin >> input;
                    }
                }

                // Output
                gameMaker(place, input, turn);
                if (PERMIT == false)
                {
                    cout << "NOT AVAILABLE ! " << endl;
                    totalT--;
                    PERMIT = true;
                }

                // Result Checking :
                gamePlay = winCheck(place, player1, player2);
                if (totalT == 8 && gamePlay == true)
                {
                    fileUpdate(player1, 2);
                    fileUpdate(player2, 2);
                    cout << "\tDRAW " << endl;
                    gamePlay = false;
                }

                totalT++;
            }
            mode = 0;
        }

        else if (mode == 2)
        {
            scoreboard();
            mode = 0;
        }

        else if (mode == 3)
        {
            cout << "\n\tThanks for playing " << char(3);
            gameOn = false;
        }

        else
        {
            cout << "Please Enter a Valid Number (1, 2, 3) : ";
            cin >> mode;
        }
    }
}

/*/<< KOOSHAN RADMEHR >>/*/