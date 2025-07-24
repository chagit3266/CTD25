#pragma once
#include <filesystem>
#include <unordered_map>
#include <string>
#include <memory> // For shared_ptr
#include "Board.hpp"
#include "Piece.hpp"
#include "State.hpp"
#include "GraphicsFactory.hpp"
#include "PhysicsFactory.hpp"
#include "Moves.hpp"

/**
 * PieceFactory manages loading and creation of pieces by their type.
 */
class PieceFactory {
private:
    std::shared_ptr<Board> board_;
    std::filesystem::path pieces_root_;
    // Store templates/blueprints of states, as each piece needs its own instance
    std::unordered_map<std::string, std::shared_ptr<State>> state_templates;
    GraphicsFactory graphics_factory;
    PhysicsFactory physics_factory;

public:
    PieceFactory(std::shared_ptr<Board> b, const std::filesystem::path& root);

    // Load all piece configurations and states from the pieces_root directory
    void load_piece_configs();

    // Create a specific piece at a given cell on the board
    std::shared_ptr<Piece> create_piece(const std::string& p_type, std::pair<int, int> cell);

private:
    // Helper to build a state machine from a piece's directory
    std::shared_ptr<State> build_state_from_dir(const std::filesystem::path& state_dir, const std::pair<int, int>& board_cell_dims);
};