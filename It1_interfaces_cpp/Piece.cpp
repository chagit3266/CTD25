#include "Piece.hpp"
#include <iostream> // For debugging

Piece::Piece(const std::string& id, const std::pair<int, int>& initial_cell)
    : piece_id(id), is_alive_val(true), current_cell_pos(initial_cell) {
    // Initial state will be set by PieceFactory
}

void Piece::add_state(const std::string& state_name, std::shared_ptr<State> state) {
    all_states[state_name] = state;
}

void Piece::set_initial_state(const std::string& state_name) {
    auto it = all_states.find(state_name);
    if (it != all_states.end()) {
        current_state = it->second;
        // The reset command here can be a "startup" command or empty
        current_state->reset(Command(0, piece_id, "INIT", {})); 
    } else {
        throw std::runtime_error("Initial state '" + state_name + "' not found for piece " + piece_id);
    }
}

void Piece::on_command(const Command& cmd, int now_ms) {
    if (!current_state) return;

    // Check for transition to a new state based on the command
    State* next_state_ptr = current_state->get_next_state(cmd, now_ms);

    if (next_state_ptr && next_state_ptr != current_state.get()) {
        // Transition to new state
        current_state = all_states.at(next_state_ptr->get_name()); // Get shared_ptr back
        current_state->reset(cmd); // Reset the new state with the command
    } else {
        // If no state transition, apply command to current state's physics/graphics
        current_state->reset(cmd); // Reset implicitly means applying the command
    }
}

void Piece::update(int now_ms) {
    if (!current_state || !is_alive_val) return;

    current_state->update(now_ms); // Update internal state (graphics, physics)
    
    // Update the logical cell position based on physics (if piece is moving)
    current_cell_pos = current_state->get_physics().get_cell_pos();

    // Check for transitions that occur after update (e.g., animation finished)
    // For example, if a "Move" animation finishes, transition back to "Idle"
    if (current_state->get_name() == "move" && current_state->get_graphics().is_finished() && !current_state->get_physics().is_moving()) {
        auto it_idle = all_states.find("idle");
        if (it_idle != all_states.end()) {
            current_state = it_idle->second;
            // Optionally, reset idle state with a "finished_move" command or empty
            current_state->reset(Command(now_ms, piece_id, "FINISHED_MOVE", {}));
        }
    }
}

void Piece::draw_on_board(Board& board, int now_ms) {
    if (!current_state || !is_alive_val) return;

    Img current_piece_img = current_state->get_graphics().get_img();
    
    // Use physics' pixel position for drawing
    std::pair<int, int> pixel_pos = current_state->get_physics().get_pixel_pos();

    // Adjust pixel position to top-left corner for drawing (assuming pixel_pos is center)
    int draw_x = pixel_pos.first - board.get_cell_W_pix() / 2;
    int draw_y = pixel_pos.second - board.get_cell_H_pix() / 2;

    current_piece_img.draw_on(board.get_img(), draw_x, draw_y);
}

std::pair<int, int> Piece::get_cell_pos() const {
    // Return the logical cell position of the piece
    return current_cell_pos;
}

void Piece::set_cell_pos(int r, int c) {
    current_cell_pos = {r, c};
}