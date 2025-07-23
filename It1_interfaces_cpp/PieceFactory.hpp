#pragma once
#include <string>
#include <memory>
#include <filesystem>
#include "Board.hpp"
#include "Piece.hpp"
#include "State.hpp"

class PieceFactory {
public:
    PieceFactory(Board& board, const std::filesystem::path& pieces_root);

    std::shared_ptr<Piece> create_piece(const std::string& p_type, std::pair<int, int> cell);

private:
    Board& board;
    std::filesystem::path root;

    std::shared_ptr<State> build_state_machine(const std::filesystem::path& piece_dir);
};