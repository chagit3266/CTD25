#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "Command.hpp"
#include "Moves.hpp"
#include "Physics.hpp"
#include "Graphics.hpp"

//מצב כלי, עם מעבר בין מצבים ע"י אירועים.
class State {
private:
    std::string name; // Name of this state (e.g., "idle", "move")
    Moves moves;
    Graphics graphics;
    Physics physics;
    std::map<std::string, State*> transitions; // Map event type to next state
    Command current_command; // Command that led to or is being processed by this state

public:
    State() = default; // Default constructor
    State(const std::string& name, const Moves& m, const Graphics& g, const Physics& p);

    void set_transition(const std::string& event_type, State* target_state); // Set a transition to another state
    void reset(const Command& cmd); // Reset state based on a command
    bool can_transition(int now_ms) const; // Check if a transition is possible
    State* get_next_state(const Command& cmd, int now_ms); // Get the next state based on command and time
    State* update(int now_ms); // Update internal components (graphics, physics)
    Command get_command() const; // Get the last command that affected this state

    // Getters for internal components
    const Moves& get_moves() const { return moves; }
    Graphics& get_graphics() { return graphics; } // Non-const to allow updates
    Physics& get_physics() { return physics; }    // Non-const to allow updates
    const std::string& get_name() const { return name; }
};
