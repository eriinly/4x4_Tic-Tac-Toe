#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

//global variables
string board[4][4] = {{"1","2","3","4"},{"5","6","7","8"},{"9","10","11","12"},{"13","14","15","16"}};
int x = 0, y = 0;
const int x_player = 1, o_player = 2;
int game_num = 0;
int spots_left = 16;

void game();
// PURPOSE: Displays the introduction and ending of the game
//     INPUTS: None
//     RETURNS: Nothing to return

void display_board();
// PURPOSE: Displays the array as a tic-tac-toe board
//     INPUTS: None
//     RETURNS: Nothing to return

void start();
// PURPOSE: Initializes the game
//     INPUTS: None
//     RETURNS: Nothing to return

int turn(int player, int move);
// PURPOSE: Handles individual player turns
//     INPUTS: player - x and o player
//             move - move that each player makes
//     RETURNS: Returns move

void update_board(int player, int move);
// PURPOSE: Updates board with X or O after player makes move
//     INPUTS: player - x and o player
//             move - move that each player makes
//     RETURNS: Nothing to return

bool check_valid(int move);
// PURPOSE: Checks if move is valid
//     INPUTS: move
//     RETURNS: Returns true or false if move is valid or not

bool check_win();
// PURPOSE: Checks if there is a vertical, horizontal, or diagonal combination of four Xs or four Os
//     INPUTS: None
//     RETURNS: Returns true or false depending if win is detected

void reset_board();
// PURPOSE: Resets board after game finishes
//     INPUTS: None
//     RETURNS: Nothing to return

int main() {
    game();
    return 0;
}

void display_board() {
    //[INPUT] iterates through the x and y components of array
    cout << setw(55)<< "       |       |       |       " << endl;
    for (x = 0; x < 4; x++) {
        cout << setw(27);
        for (y = 0; y < 4; y++) {
            //[OUTPUT] console outputs board
            if (y==3) {
                cout << "   " << board[x][y];
            }
            else if (board[x][y].size() > 1 ) {
                cout << "   " << board[x][y] << "  |";
            }
            else {
                cout << "   " << board[x][y] << "   |";
            }
        }
        if (x!=3) {
            cout << endl << setw(55) << "_______|_______|_______|_______" << endl;
            cout << setw(55) << "       |       |       |       " << endl;
        }
        else {
            cout << endl << setw(55) << "       |       |       |       " << endl;
            cout << endl;
        }
    }
    cout << endl;
}

void game() {
    bool play = true;
    int answer = 0;

    // Outputs introductory statement
    cout << setw(58) << "Welcome to the 4x4 Tic-Tac-Toe Game!" << endl
         << setw(55) << "Player 1 (X)  -  Player 2 (O) " << endl << endl;

    while (play == true) {

        // Call functions to display board and start game
        display_board();
        start();

        // User inputs if they want to play again or not
        cout << "Would you like to play again? Enter 1 for yes or any key for no." << endl;
        cin >> answer;

        if (answer == 1) {
            game_num ++; // Game number increases if player wants to play another game
            reset_board(); // Call functions to reset game board
            cout << endl;
        }

        else {
            cout << "Thanks for playing!" << endl;
            play = false; // Exits loop
        }
    }
}

void start() {
    // Initialize corresponding variables
    int x_move(0), o_move(0);
    bool win = false;

    // Generate number of events
    cout << "To play, each player must enter the number of the desired location they would like to mark." << endl << endl;

    while (win == false) {
        if (game_num % 2 == 0) {
            x_move = turn(x_player, x_move); // x player move
            win = check_win(); // check if x player wins

            if (win == false) {
                o_move = turn(o_player, o_move); // if x player did not win, o player goes
                win = check_win(); // check if o player wins
            }
        }

        // for the first game, x player goes first and changes as games continue on
        else if (game_num % 2 != 0) {
            o_move = turn(o_player, o_move);
            win = check_win();

            if (win == false) {
                x_move = turn(x_player, x_move);
                win = check_win();
            }
        }
    }
}

int turn(int player, int move) {
    bool invalid_input = false;

    while (invalid_input == false) {
        cout << "Player " << player << ", what is your move? ";
        cin >> move; // User inputs move
        invalid_input = check_valid(move); // If move is valid, exit loop
    }

    spots_left --; // Spaces left on the board decreases as players make moves
    update_board(player, move); // Updates the board with x or y
    return move;
}

// checks if the move is valid
bool check_valid(int move) {

    // disect the array location of move
    int move_row = (move - 1) / 4;
    int move_col = (move - 1) % 4;

    // move must be within available locations of the board
    if (move >=1 && move <=16) {
        // checks if spot is taken by marker
        if (board[move_row][move_col] == "X" || board[move_row][move_col] == "O") {
            cout << "That spot is taken! Try again." << endl;
            return false;
        }
        else {
            return true; // it should check if space is taken after if its valid and then return true
        }
    }
    else {
        // output if location picked is beyond what is available
        cout << "That is not a location on the board. Try again!" << endl;
        return false;
    }
}

//updates board after player makes move
void update_board(int player, int move){
    bool found_value = false;
    string player_marker;

    // Set player marker according to player number
    if (player == 1){
        player_marker = "X";
    }
    else if (player == 2) {
        player_marker = "O";
    }

    // variable used to convert int to string
    string string_move;
    stringstream player_move;
    player_move << move;
    player_move >> string_move;

    // updates board with markers according to move
    while (found_value == false) {
        for (x = 0; x < 4; x++) {
            for (y = 0; y < 4; y++) {
                if (board[x][y] == string_move) {
                    board[x][y] = player_marker;
                    found_value = true;
                }
            }
        }
    }
    // displays board in format
    display_board();
}

bool check_win() {
    int counter = 0;

    // check rows for wins
    for (counter = 0; counter < 4; counter++){
        if (board[counter][0] == "X" && board[counter][1] == "X" && board[counter][2] == "X" && board[counter][3] == "X") {
            cout << "Player 1 has won!" << endl;
            return true;
        }
        else if (board[counter][0] == "O" && board[counter][1] == "O" && board[counter][2] == "O" && board[counter][3] == "O") {
            cout << "Player 2 has won!" << endl;
            return true;
        }
    }

    // check columns for wins
    for (counter = 0; counter < 4; counter ++) {
        if (board[0][counter] == "X" && board[1][counter] == "X" && board[2][counter] == "X" && board[3][counter] == "X") {
            cout << "Player 1 has won!" << endl;
            return true;
        }
        else if (board[0][counter] == "O" && board[1][counter] == "O" && board[2][counter] == "O" && board[3][counter] == "O") {
            cout << "Player 2 has won!" << endl;
            return true;
        }
    }

    // check diagonals for wins
    if (board[0][0] == "X" && board[1][1] == "X" && board[2][2] == "X" && board[3][3] == "X") {
        cout << "Player 1 has won!" << endl;
        return true;
    }
    else if (board[0][0] == "O" && board[1][1] == "O" && board[2][2] == "O" && board[3][3] == "O") {
        cout << "Player 2 has won!" << endl;
        return true;
    }
    else if (board[0][3] == "X" && board[1][2] == "X" && board[2][1] == "X" && board[3][0] == "X") {
        cout << "Player 1 has won!" << endl;
        return true;
    }
    else if (board[0][3] == "O" && board[1][2] == "O" && board[2][1] == "O" && board[3][0] == "O") {
        cout << "Player 2 has won!" << endl;
        return true;
    }
    // If no spots are left and no wins detected, then it is a tie
    else if (spots_left == 0) {
        cout << "It's a tie!" << endl;
        return true;
    }
    else {
        return false;
    }

}

void reset_board() {
    int counter = 0;
    string string_counter;

    // iterates through numbers to reset board
    for (x = 0; x < 4; x++){
        for (y = 0; y < 4; y++) {
            counter++;

            // variable used to convert int to string since board is string
            stringstream space_counter;
            space_counter << counter;
            space_counter >> string_counter;

            board[x][y] = string_counter;
        }
    }
}
