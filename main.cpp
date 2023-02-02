#include <cstring>
#include <iostream>
#include <vector>

const std::string GREEN = "\x1b[32m";
const std::string RED = "\x1b[31m";
const std::string YELLOW = "\x1b[33m";
const std::string BLUE = "\x1b[34m";
const std::string RESET = "\x1b[0m";

std::string blue_text(std::string logo) { return BLUE + logo + RESET; }

std::string red_text(std::string text) { return RED + text + RESET; }

std::string green_text(std::string logo) { return GREEN + logo + RESET; }

std::string yellow_text(std::string logo) { return YELLOW + logo + RESET; }

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
            std::cout << column << " ";
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

bool parse_input(std::string str, bool &is_green_turn) {
    if (str.length() > 2) {
        std::cout << "That is an invalid cell.\n";
        is_green_turn = true;
        return false;
    } else if (str == "?") {
        help_message(1);
        return false;
    } else if (str == "Q") {
        return true;
    } else {
        return false;
    }
}

bool move_piece(std::vector<std::vector<std::string>> &board,
        bool &is_green_turn) {
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

    if (parse_input(piece_to_move, is_green_turn)) {
        return true;
    }

    std::string move_piece_to;
    std::cout << "Move piece to where? ";
    getline(std::cin, move_piece_to);

    std::cout << std::endl;

    if (parse_input(move_piece_to, is_green_turn)) {
        return true;
    }

    const char *piece = piece_to_move.c_str();
    // converts char ch = '5' to int num = 5;
    int piece_x = piece[0] - '0';
    int piece_y = piece[1] - '0';

    const char *new_cell = move_piece_to.c_str();
    int cell_x = new_cell[0] - '0';
    int cell_y = new_cell[1] - '0';

    std::string empty = YELLOW + "X" + RESET;
    std::string &ori_piece = board[piece_x][piece_y];
    if (ori_piece == "X") {
        std::cout << "\nTry again. You are " << red_text("not")
            << " allowed to move an empty cell.\n";
        is_green_turn = !(is_green_turn == true);

        return false;
    }

    std::string &replaced_piece = board[cell_x][cell_y];
    if (replaced_piece == blue_text("K")) {
        std::cout << "Game, set, match! Victory goes to " << green_text("green")
            << "!\n congratulations!\n"
            << std::endl;
        return true;
    } else if (replaced_piece == green_text("K")) {
        std::cout << "Game, set, match! Victory goes to " << blue_text("blue")
            << "!\n"
            << std::endl;
        return true;
    }

    replaced_piece = ori_piece;
    ori_piece = empty;

    return false;
}

std::vector<std::string> row(const std::vector<std::string>& pieces, std::string color) {
    auto row = pieces;

    for(auto& v : row) {
        v = color + v + RESET;
    }

    return row;
}

std::vector<std::vector<std::string>> create_board() {
    const std::vector<std::string> valuable_pieces = { "C", "B", "k", "K", "Q", "k", "B", "C" };
    const std::vector<std::string> pawns(8, "P");

    std::vector<std::vector<std::string>> board(8, std::vector<std::string>(8, "X"));  

    board[0] = row(valuable_pieces, BLUE);
    board[1] = row(pawns, BLUE);
    board[6] = row(pawns, GREEN);
    board[7] = row(valuable_pieces, GREEN);

    return board;
}

void game() {
    bool is_green_turn = true;
    std::vector<std::vector<std::string>> board = create_board();

    std::cout << "\n1. Your pieces are in " << green_text("green")
        << ". Your opponent's pieces are in " << blue_text("blue") << ".\n";
    std::cout << "2. Unoccupied cells are marked with a yellow '"
        << yellow_text("X") << "'.\n";
    std::cout << "3. If at any point you have no idea what to do type '"
        << red_text("?") << "' and press ENTER.\n";
    std::cout
        << "4. You can quit at any point in the game by pressing CTRL+c or a "
        "capital '"
        << red_text("Q") << "'\n\n";

    bool has_game_ended = false;
    while (!has_game_ended) {
        display_board(board);
        has_game_ended = move_piece(board, is_green_turn);
    }
}

int main() { game(); }
