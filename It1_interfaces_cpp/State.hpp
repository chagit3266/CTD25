#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "Command.hpp"
#include "Moves.hpp"
#include "Physics.hpp"
#include "Graphics.hpp"

//מצב כלי, עם מעבר בין מצבים ע"י אירועים.
class State : public std::enable_shared_from_this<State> {
public:
    State(std::shared_ptr<Moves> moves,
        std::shared_ptr<Graphics> graphics,
        std::shared_ptr<Physics> physics);

    void set_transition(const std::string& event, std::shared_ptr<State> target);

    void reset(const Command& cmd);

    std::shared_ptr<State> update(int now_ms);

    std::shared_ptr<State> process_command(const Command& cmd, int now_ms);

    bool can_transition(int now_ms) const;

private:
    std::unordered_map<std::string, std::shared_ptr<State>> transitions;

    std::shared_ptr<Moves> moves;
    std::shared_ptr<Graphics> graphics;
    std::shared_ptr<Physics> physics;
};
