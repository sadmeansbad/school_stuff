#include <iostream>
#include <time.h> 
#include <windows.h>
#include <string>


using namespace std;

int pY, pX, botX, botY; //playerX, playerY
int test[3][3]; //creating the table

void map_out() 
{
    system("cls");
    cout << "  1 2 3" << endl;
    for (int y = 0; y < 3; y++) 
    {
        cout << y + 1 << " ";
        for (int x = 0; x < 3; x++) 
        {
            if (test[y][x] == 0) 
            {
                cout << "# ";
            }
            else if (test[y][x] == 1) cout << "X ";

            else cout << "O ";
            
        } cout << endl;
    }

}

int readOnlyInt()
{
    string s;
    int i;
    cin >> s;

    try 
    {
        i = stoi(s);
    }
    catch (std::invalid_argument) 
    {
        i = 0;
    }

    return i;
}

//player's move
void player_input(int symbol) 
{
    bool ok = false;
    string sX, sY;
    do
    {
        cout << "Horizontal position X(1,2,3): "; 
        pX = readOnlyInt();

        pX = pX - 1;
        cout << "Vertical position Y(1,2,3): ";
        
        pY = readOnlyInt();
        pY = pY - 1;

        
        if ((pY < 0 || pY > 2) || (pX < 0 || pX > 2)) //checks if value is supported
        {
            cout << "Unsupported value" << endl;
        }
        else
        {
            if (test[pY][pX] == 0) //checks if place is used by some symbol
            {
                test[pY][pX] = symbol;
                ok = true;
            }
            else
            {
                cout << "This position is already in use" << endl;
            }

        }
       
    } while (!ok);

    pY = 0;
    pX = 0;
}

//bot's "AI"
void bot(int symbol) 
{
    do
    {
        botX = rand() % 3;
        botY = rand() % 3;
    } while (test[botY][botX] != 0);
    test[botY][botX] = symbol;
}

void initiation() 
{
    for (int y = 0; y < 3; y++) 
    {
        for (int x = 0; x < 3; x++) 
        {
            test[y][x] = 0;
        }
    }
}

//Checks if there is a winner
bool check(int symbol) 
{
    if ((test[0][0] == symbol && test[0][1] == symbol && test[0][2] == symbol) ||
        (test[1][0] == symbol && test[1][1] == symbol && test[1][2] == symbol) ||
        (test[2][0] == symbol && test[2][1] == symbol && test[2][2] == symbol) ||
        (test[0][2] == symbol && test[1][1] == symbol && test[2][0] == symbol) ||
        (test[0][0] == symbol && test[1][0] == symbol && test[2][0] == symbol) ||
        (test[0][1] == symbol && test[1][1] == symbol && test[2][1] == symbol) ||
        (test[0][2] == symbol && test[1][2] == symbol && test[2][2] == symbol) ||
        (test[0][0] == symbol && test[1][1] == symbol && test[2][2] == symbol))
    {
        return true;
    }
    else return false;
}

//Asks about symbol
bool ask_type_x() 
{
    string typ;
    do 
    {
        cout << "Pick your symbol (X/O): ";
        cin >> typ;
        system("cls");
    } while (typ != "x" && typ != "X" && typ != "o" && typ != "O");
    if (typ == "x" || typ == "X") return true;
    else return false;
}

//asks about remach
bool stay() 
{
    string if_stay;
    do 
    {
        cout << "Play again? (y/n): ";
        cin >> if_stay;
        if (if_stay == "y" || if_stay == "Y") 
        {
            return true;
            break;
        }
        else if (if_stay == "n" || if_stay == "N") 
        {
            return false;
            break;
        }
        else system("cls");
    }while (true);
}

int main() 
{
    bool if_end = true, wasWinner = false;

    srand(time(NULL)); 


    cout << "Tic Tac Toe \n \n";

    do { 

        initiation();

        
        if (ask_type_x()) {
            for (int ruch = 0; ruch < 5; ruch++)
            {
                map_out();

                player_input(1);
                map_out();
                if (check(1))
                {
                    cout << endl << "You won" << endl;
                    wasWinner = true;
                    break;
                }

                if (ruch < 4) {
                    bot(2);
                    map_out();

                    if (check(2))
                    {
                        cout << endl << "You lost" << endl;
                        wasWinner = true;
                        break;
                    }
                }


            }
        }
        else {

            for (int action = 0; action < 5; action++)
            {

                bot(1);
                map_out();

                if (check(1))
                {
                    cout << endl << "You lost" << endl;
                    wasWinner = true;
                    break;
                }
                if (action < 4) {



                    player_input(2);
                    map_out();
                    if (check(2))
                    {
                        cout << endl << "You won" << endl;
                        wasWinner = true;
                        break;
                    }

                }

            }
        }
        if (!wasWinner) cout << endl << "Draw" << endl;
        if_end = stay();
    } while (if_end);
    
    return 0;
}
