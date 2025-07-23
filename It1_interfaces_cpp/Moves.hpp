#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <utility> // for std::pair
#include <tuple>

//טוענת את חוקי התנועה מקובץ, בודקת חוקיות.
class Moves {

private:
   
    void load_rules(const std::string& txt_path);
    std::pair<int, int> board_dims;
    std::vector<std::pair<int, int>> moves;//התנועות האפשריות לכלי הנוכחי

public:
    Moves(const std::string& txt_path, std::pair<int, int> dims);//מקבלת את רשימת הצעדים ואת גבולות הלוח
    
    std::vector<std::pair<int, int>> get_moves(int r, int c) const;
};