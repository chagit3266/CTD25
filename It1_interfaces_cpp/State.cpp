#include "State.hpp"


State::State(const std::string& name, const Moves& m, const Graphics& g, const Physics& p)
    : name(name), moves(m), graphics(g), physics(p) {
}

void State::set_transition(const std::string& event_type, State* target_state) {
    transitions[event_type] = target_state;
}

void State::reset(const Command& cmd) {
    current_command = cmd;
    graphics.reset(cmd);
    physics.reset(cmd);
}

bool State::can_transition(int now_ms) const {
    // Logic for when a state can transition.
    // For example, an animation must finish, or a physics movement must complete.
    // For now, simple example:
    if (graphics.is_finished() && !physics.is_moving()) {
        return true;
    }
    return false; // Default: cannot transition if animation/movement not finished
}

State* State::get_next_state(const Command& cmd, int now_ms) {
    auto it = transitions.find(cmd.get_type());
    if (it != transitions.end() && can_transition(now_ms)) {
        // If there's a specific transition for this command type and we can transition
        return it->second;
    }
    // If no specific transition or cannot transition, stay in current state
    return this;
}

State* State::update(int now_ms) {
    graphics.update(now_ms);
    physics.update(now_ms);
    return this; // For now, return this state. State machine logic will decide next state
}

Command State::get_command() const {
    return current_command;
}
bool State::can_transition(int now_ms) const {
    // לממש לפי מצב ספציפי
    return false;
}
