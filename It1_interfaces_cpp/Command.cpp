// Command.hpp
#pragma once

#include <string>
#include <vector>

class Command {
public:
    int timestamp;                         // אלפיות שנייה מתחילת המשחק
    std::string piece_id;                  // מזהה החלק
    std::string type;                      // סוג הפקודה: "Move", "Jump", וכו'
    std::vector<std::string> params;       // נתוני הפקודה (למשל: {"e2", "e4"})

    // בנאי
    Command(int timestamp,
            const std::string& piece_id,
            const std::string& type,
            const std::vector<std::string>& params)
        : timestamp(timestamp),
          piece_id(piece_id),
          type(type),
          params(params) {}

    // בנאי ברירת מחדל
    Command() : timestamp(0), piece_id(""), type("") {}
};
