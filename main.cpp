/*
    This is a simple tictactoe game based on terminal and written in C++
    Source code was written by Mysterious blob for a public github repository
    The source code includes headers: iostream and conio.h for I/O purposes
    Hope you find it interesting

    Date written: January 2, 2022 
*/

#include <iostream> // Basic I/O
#include <conio.h> // getch() function

//Print out the game board
void display(char *board)
{
    system("cls"); // Clear the screen

/* Expected otput
   |   |
   |   |
   |   |
-----------
   |   |
   |   |
   |   |
-----------
   |   |
   |   |
   |   |
*/

    std::cout 
        << "   |   |\n"
        << " " << board[0] << " | " << board[1] << " | " << board[2] << "\n"
        << "   |   |\n"
        << "------------\n"
        << "   |   |\n"
        << " " << board[3] << " | " << board[4] << " | " << board[5] << "\n"
        << "   |   |\n"
        << "------------\n"
        << "   |   |\n"
        << " " << board[6] << " | " << board[7] << " | " << board[8] << "\n"
        << "   |   |\n";
}

//Get input from the user
int input(const bool &player)
{
    char choice;
    while(true)
    {
        std::cout << "Please enter your choice player " << (player ? "1":"2") << ": ";
        choice = getch();
        std::cout << "\n";

        if(choice > 48 && choice < 58) // Range of number between 1 and 9 in the ascii table
            return choice - 48; // Input will be converted to the respective int
        else
            std::cout << "Input must be a number between 1 and 9!\n";
    }
}

// Do core game logic
bool logic(char *const &board, bool &player, bool &tie)
{
    int choice;

    // Make sure the tile inputted is empty
    do
    { 
        choice = input(player);
        if(choice > 6) // Indexing
            choice -= 7;
        else if(choice > 3)
            choice -= 1;
        else
            choice += 5;

        if(board[choice] != 32)
            std::cout << "The tile must be empty!\n";
    } while(board[choice] != 32);

    board[choice] = (player ? 'X' : 'O');

    // Horizontal wins
    if(board[0] == board[1] && board[1] == board[2] && (board[2] == 'X' || board[2] == 'O') )
        return false;
    else if(board[3] == board[4] && board[4] == board[5] && (board[5] == 'X' || board[5] == 'O') )
        return false;
    else if(board[6] == board[7] && board[7] == board[8] && (board[8] == 'X' || board[8] == 'O') )
        return false;

    // Vertical wins
    else if(board[0] == board[3] && board[3] == board[6] && (board[6] == 'X' || board[6] == 'O') )
        return false;
    else if(board[1] == board[4] && board[4] == board[7] && (board[7] == 'X' || board[7] == 'O') )
        return false;
    else if(board[2] == board[5] && board[5] == board[8] && (board[8] == 'X' || board[8] == 'O') )
        return false;
    
    // Diagonal wins
    else if(board[0] == board[4] && board[4] == board[8] && (board[8] == 'X' || board[8] == 'O') )
        return false;
    else if(board[2] == board[4] && board[4] == board[6] && (board[6] == 'X' || board[6] == 'O') )
        return false;
    
    // Tie logic
    else
    {
        bool found = false;
        for (size_t i = 0; i < 9 && !found; i++)
            if(board[i] == ' ')
                found = true;

        tie = !found; // Set tie to true if ' ' wasn't found

        if(tie)
            return false;
    }

    player = !player;
    return true;
}

int main()
{
    bool player; // True == player 1 / False == player 2
    bool tie; // True == tie / False == someone won
    char *board; // Array of chars

    char choice;
    do
    {
        //Setup
        player = true;
        tie = false;
        board = new char[9]{32, 32, 32, 32, 32, 32, 32, 32, 32};

        // Game loop
        do 
        { 
            display(board);
        } while(logic(board, player, tie));
        display(board); // Display the newest board

        if(!tie) // Output win/lose/tie
            std::cout << "Player " << (player ? "1" : "2") << " won!\n";
        else
            std::cout << "We got a tie!\n";

        // Replay validation loop
        while(true)
        {
            std::cout << "\nDo you want to play again? (y/n)";
            choice = getch();
            std::cout << "\n";

            if(choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N')
                break;
            else
                std::cout << "Wrong input!\n";
        }

        delete [] board; // Free heap memory
    } while(choice != 'n' && choice != 'N');

    std::cout << "\nQuitting...\n"; // quit message
    return 0;
}