#pragma once
#include <string>
#include <memory>
#include "Command.hpp"
#include "State.hpp"
#include "Physics.hpp"
#include "Graphics.hpp"

// יחידת משחק שמנהלת את המצב (State), הפיזיקה והגרפיקה שלה.
class Piece {
public:
    Piece(const std::string& id,
        std::shared_ptr<State> state);

    void reset(int start_ms);
    void update(int now_ms);

    void on_command(const Command& cmd);

    std::string get_id() const;

    // ציור / מיקום נוכחי
    void draw();

private:
    std::string piece_id;
    std::shared_ptr<State> current_state;
};
