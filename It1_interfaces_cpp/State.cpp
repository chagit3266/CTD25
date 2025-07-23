#include "State.hpp"

State::State(std::shared_ptr<Moves> m,
    std::shared_ptr<Graphics> g,
    std::shared_ptr<Physics> p)
    : moves(std::move(m)), graphics(std::move(g)), physics(std::move(p)) {
}

void State::set_transition(const std::string& event, std::shared_ptr<State> target) {
    transitions[event] = target;
}

void State::reset(const Command& cmd) {
    graphics->reset();
    physics->reset();
}

std::shared_ptr<State> State::update(int now_ms) {
    graphics->reset(now_ms);
    auto cmd = physics->reset(now_ms);
    if (cmd.has_value()) {
        return process_command(cmd.value(), now_ms);
    }
    return shared_from_this();
}

std::shared_ptr<State> State::process_command(const Command& cmd, int now_ms) {
    auto it = transitions.find(cmd.type);
    if (it == transitions.end()) return nullptr;

    it->second->reset(cmd);
    return it->second;
}

bool State::can_transition(int now_ms) const {
    // לממש לפי מצב ספציפי
    return false;
}
