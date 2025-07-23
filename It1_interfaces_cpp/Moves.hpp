#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <utility> // for std::pair
#include <tuple>

//����� �� ���� ������ �����, ����� ������.
class Moves {

private:
   
    void load_rules(const std::string& txt_path);
    std::pair<int, int> board_dims;
    std::vector<std::pair<int, int>> moves;//������� �������� ���� ������

public:
    Moves(const std::string& txt_path, std::pair<int, int> dims);//����� �� ����� ������ ��� ������ ����
    
    std::vector<std::pair<int, int>> get_moves(int r, int c) const;
};