#include "Moves.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Moves::Moves(const std::string& txt_path, std::pair<int, int> dims) : board_dims(dims) {
    load_rules(txt_path);
}

void Moves::load_rules(const std::string& txt_path) {
    std::ifstream file(txt_path);
    if (!file.is_open()) {
        std::cerr << "Error opening moves file: " << txt_path << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;

        // דוגמה לשורה: Knight: 2,1; 1,2; -2,1;
        std::istringstream iss(line);
        std::string piece_type;
        std::getline(iss, piece_type, ':');

        std::string moves_str;
        std::getline(iss, moves_str);

        std::vector<std::pair<int, int>> deltas;

        std::istringstream moves_stream(moves_str);
        std::string move_token;
        while (std::getline(moves_stream, move_token, ';')) {
            std::istringstream pair_stream(move_token);
            std::string dx_str, dy_str;

            if (std::getline(pair_stream, dx_str, ',') && std::getline(pair_stream, dy_str)) {
                try {
                    int dx = std::stoi(dx_str);
                    int dy = std::stoi(dy_str);
                    deltas.emplace_back(dx, dy);
                }
                catch (...) {
                    // התעלם אם לא ניתן להמיר למספרים
                }
            }
        }

        rules[piece_type] = deltas;
    }
}

std::vector<std::pair<int, int>> Moves::get_moves(int r, int c) const {
    // מחזיר את כל התזוזות האפשריות מכל סוג כלי מהתא (r,c)
    std::vector<std::pair<int, int>> moves;
    for (const auto& [type, deltas] : rules) {
        for (auto [dx, dy] : deltas) {
            int nr = r + dx;
            int nc = c + dy;
            if (nr >= 0 && nr < board_dims.first && nc >= 0 && nc < board_dims.second) {
                moves.emplace_back(nr, nc);
            }
        }
    }
    return moves;
}
