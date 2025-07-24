#pragma once
#include <string>
#include <memory> // For std::shared_ptr
#include "State.hpp"
#include "Board.hpp" // For Board reference in draw_on_board
#include "Command.hpp" // For on_command

/**
 * Piece - A game piece, with internal state and an ID.
 */
class Piece {
private:
    std::string piece_id;
    std::shared_ptr<State> current_state; // Current state of the piece
    std::map<std::string, std::shared_ptr<State>> all_states; // All possible states for this piece
    bool is_alive_val; // Internal flag for alive status
    std::pair<int, int> current_cell_pos; // Current logical cell position (row, col)

public:
    Piece(const std::string& id, const std::pair<int, int>& initial_cell); // Initializer for Piece
    
    // Add a state to the piece's state machine
    void add_state(const std::string& state_name, std::shared_ptr<State> state);
    // Set initial state
    void set_initial_state(const std::string& state_name);

    void on_command(const Command& cmd, int now_ms); // Handle commands
    void update(int now_ms); // Update piece based on its current state
    void draw_on_board(Board& board, int now_ms); // Draw piece on board
    
    // Getters
    const std::string& get_id() const { return piece_id; }
    bool is_alive() const { return is_alive_val; }
    void set_alive(bool alive) { is_alive_val = alive; }
    std::pair<int, int> get_cell_pos() const;
    void set_cell_pos(int r, int c); // Set the piece's logical cell position
};