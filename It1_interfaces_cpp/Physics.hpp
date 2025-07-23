#pragma once
#include <optional>
#include "Command.hpp"

//מחשבת תזוזות, תפיסות, מיקום.
class Physics {
public:
    Physics();

    void reset();


    // מחזיר פקודה חדשה במידה ויש שינוי מצב או אירוע
    std::optional<Command> reset(int now_ms);

    void update_position(int now_ms);

    // TODO: מיקום מדויק, תזוזות, התנגשויות
};
