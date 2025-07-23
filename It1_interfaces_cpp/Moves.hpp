#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <utility> // for std::pair
#include <tuple>

//טוענת את חוקי התנועה מקובץ, בודקת חוקיות.
class Moves {
public:
    Moves(const std::string& txt_path, std::pair<int, int> dims);
    std::vector<std::pair<int, int>> get_moves(int r, int c) const;

    bool is_move_valid(const std::string& piece_type, int from_r, int from_c, int to_r, int to_c) const;

private:
    void load_rules(const std::string& txt_path);

    std::pair<int, int> board_dims;
    std::unordered_map<std::string, std::vector<std::pair<int, int>>> rules; // מיפוי סוג כלי -> תזוזות מותרות
};