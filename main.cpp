#include <cstring>
#include <iostream>
#include <vector>

const std::string GREEN = "\x1b[32m";
const std::string RED = "\x1b[31m";
const std::string YELLOW = "\x1b[33m";
const std::string BLUE = "\x1b[34m";
const std::string RESET = "\x1b[0m";

void reset_color() { std::cout << RESET; }
void set_color_yellow() { std::cout << YELLOW; }

void display_board(std::vector<std::vector<std::string>> &board) {
    std::string v_divider = std::string(23, '=');
    std::string letters = "    0 1 2 3 4 5 6 7";

    std::cout << letters << std::endl;
    std::cout << v_divider << std::endl;
    int count = 0;

    for (int i = 0; i < board.size(); i++) {
        std::vector<std::string> row = board[i];

        std::cout << i << " | ";

        std::string line = "";
        for (int j = 0; j < row.size(); j++) {
            std::string column = row[j];
            if (column == "X") {
                set_color_yellow();
            }

            std::cout << column << " ";

            if (j == 7) {
                reset_color();
            }
        }

        std::cout << "| " << i;

        std::cout << std::endl;
    }

    std::cout << v_divider << std::endl;
    std::cout << letters << std::endl;
}

void help_message(int option) {
    if (option == 1) {
        std::cout << "\n\nSelecting a piece\n";
        std::cout << "1. Look to the left or right and select a number.\n";
        std::cout << "2. After selecting a number on the left side, select a "
            "number on the bottom.\n";
        std::cout
            << "\nFor example, to move the left most pawn you must enter '60' "
            "and to move it 2 cells up, enter '40'.\n\n";
    }
}

bool move_piece(std::vector<std::vector<std::string>> &board, bool& is_green_turn) {
    std::cout << "\nIt is ";
    if (is_green_turn) {
        std::cout << GREEN << "green's" << RESET << " move.\n";
        is_green_turn = false;
    } else {
        std::cout << BLUE << "blue's" << RESET << " move.\n";
        is_green_turn = true;
    }

    std::string piece_to_move;
    std::cout << "\nSelect the piece to move: ";
    getline(std::cin, piece_to_move);

    if (piece_to_move == "?") {
        help_message(1);
        return false;
    } else if (piece_to_move == "Q") {
        return true;
    }

    std::string move_piece_to;
    std::cout << "Move piece to where? ";
    getline(std::cin, move_piece_to);

    std::cout << std::endl;

    if (move_piece_to == "?") {
        help_message(1);
        return false;
    } else if (move_piece_to == "Q") {
        return true;
    }

    const char *piece = piece_to_move.c_str();
    // converts char ch = '5' to int num = 5;
    int piece_x = piece[0] - '0';
    int piece_y = piece[1] - '0';

    const char *new_cell = move_piece_to.c_str();
    int cell_x = new_cell[0] - '0';
    int cell_y = new_cell[1] - '0';

    // TODO: This doesn't work all the time. It's weird.
    std::string empty = YELLOW + "X" + RESET;
    std::string &ori_piece = board[piece_x][piece_y];
    if (ori_piece == "X") {
        std::cout << "\nTry again. You are " << RED << "not" << RESET << " allowed to move an empty cell.\n";
        is_green_turn = !(is_green_turn == true);

        return false;
    }


    std::string &replace_piece = board[cell_x][cell_y];
    if (replace_piece == BLUE + "K" + RESET) {
        std::cout << "Game, set, match! Victory goes to " << GREEN << "green" << RESET << "!\n" << std::endl;
        return true;
    }

    if (replace_piece == GREEN + "K" + RESET) {
        std::cout << "Game, set, match! Victory goes to " << BLUE << "blue" << RESET << "!\n" << std::endl;
        return true;
    }

    replace_piece = ori_piece;
    ori_piece = empty;

    return false;
}

void game() {
    bool is_green_turn = true;
    std::vector<std::vector<std::string>> board = {
        {BLUE + "C" + RESET, BLUE + "B" + RESET, BLUE + "k" + RESET, BLUE + "K" + RESET, BLUE + "Q" + RESET, BLUE + "k" + RESET, BLUE + "B" + RESET, BLUE + "C" + RESET},
        {BLUE + "P" + RESET, BLUE + "P" + RESET, BLUE + "P" + RESET, BLUE + "P" + RESET, BLUE + "P" + RESET, BLUE + "P" + RESET, BLUE + "P" + RESET, BLUE + "P" + RESET},
        {"X", "X", "X", "X", "X", "X", "X", "X"},
        {"X", "X", "X", "X", "X", "X", "X", "X"},
        {"X", "X", "X", "X", "X", "X", "X", "X"},
        {"X", "X", "X", "X", "X", "X", "X", "X"},
        {GREEN + "P" + RESET, GREEN + "P" + RESET, GREEN + "P" + RESET, GREEN + "P" + RESET, GREEN + "P" + RESET, GREEN + "P" + RESET, GREEN +"P" + RESET, GREEN + "P" + RESET},
        {GREEN + "C" + RESET, GREEN + "B" + RESET, GREEN + "k" + RESET, GREEN + "K" + RESET, GREEN + "Q" + RESET, GREEN + "k" + RESET, GREEN + "B" + RESET, GREEN + "C" + RESET},
    };

    std::cout << "\n1. Your pieces are in " << GREEN << "green" << RESET << ". Your opponent's pieces are in " << BLUE << "blue" << RESET << ".\n";
    std::cout
        << "2. Unoccupied cells are marked with a yellow '\x1b[33mX\x1b[0m'\n";
    std::cout << "3. If at any point you have no idea what to do type "
        "'\x1b[31m?\x1b[0m' and "
        "press ENTER.\n";
    std::cout << "4. You can quit at any point in the game by pressing CTRL+c or a "
        "capital '" << RED << "Q" << RESET << "'\n\n";

    bool has_game_ended = false;
    while (!has_game_ended) {
        display_board(board);
        has_game_ended = move_piece(board, is_green_turn);
    }
}

int main() { game(); }
