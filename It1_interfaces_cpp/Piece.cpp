#include "Piece.hpp"

Piece::Piece(const std::string& id,
    std::shared_ptr<State> state)
    : piece_id(id),
    current_state(state),
{
}

void Piece::reset(int start_ms) {
    current_state->reset(Command{ start_ms, piece_id, "Reset", {} });
    physics->reset();
    graphics->reset();
}

void Piece::update(int now_ms) {
    // עדכון פיזיקה ואנימציה, שינוי מצב במידת הצורך
    auto new_state = current_state->update(now_ms);
    if (new_state != nullptr && new_state != current_state) {
        current_state = new_state;
    }
}

void Piece::on_command(const Command& cmd) {
    auto new_state = current_state->process_command(cmd, cmd.timestamp);
    if (new_state != nullptr) {
        current_state = new_state;
    }
}

std::string Piece::get_id() const {
    return piece_id;
}

void Piece::draw() {
    graphics->draw();
}
