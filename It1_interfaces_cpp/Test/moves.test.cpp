#include "../Moves.hpp"
#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

// ���� ����� ���� ���� ����
void write_temp_moves_file(const std::string& path) {
    std::ofstream out(path);
    out << "Knight: 2,1; 1,2; -2,1; -1,-2;\n";
    out << "Rook: 0,1; 1,0; 0,-1; -1,0;\n";
}

// ����� ����� ����� ���� ����
TEST(MovesTest, LoadRulesFromFile) {
    std::string path = "temp_moves.txt";
    write_temp_moves_file(path);

    Moves moves(path, { 8, 8 }); // ��� 8x8

    auto result = moves.get_moves(3, 3);

    // ���� ������ ������ ������
    EXPECT_FALSE(result.empty());
    EXPECT_NE(std::find(result.begin(), result.end(), std::make_pair(5, 4)), result.end()); // Knight move 2,1
    EXPECT_NE(std::find(result.begin(), result.end(), std::make_pair(3, 4)), result.end()); // Rook move 0,1

    std::filesystem::remove(path);
}

// ����� ����� ����� ��� ��� ���
TEST(MovesTest, IsMoveValidPositive) {
    std::string path = "temp_moves.txt";
    write_temp_moves_file(path);
    Moves moves(path, { 8, 8 });

    EXPECT_TRUE(moves.is_move_valid("Knight", 3, 3, 5, 4)); // dx=2, dy=1
    EXPECT_TRUE(moves.is_move_valid("Rook", 4, 4, 4, 5));   // dx=0, dy=1

    std::filesystem::remove(path);
}

// ����� ����� �� �����
TEST(MovesTest, IsMoveValidNegative) {
    std::string path = "temp_moves.txt";
    write_temp_moves_file(path);
    Moves moves(path, { 8, 8 });

    EXPECT_FALSE(moves.is_move_valid("Knight", 3, 3, 4, 4)); // dx=1, dy=1 - �� ����
    EXPECT_FALSE(moves.is_move_valid("Rook", 4, 4, 5, 5));   // dx=1, dy=1 - �� ����

    std::filesystem::remove(path);
}

// ����� ����� ������ ����� �� ����
TEST(MovesTest, LoadInvalidFile) {
    Moves moves("non_existing.txt", { 8, 8 });
    auto result = moves.get_moves(0, _
