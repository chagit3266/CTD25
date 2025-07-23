#pragma once
#include <string>
#include <vector>

//מהווה מכולת נתונים
class Command {
public:
    int timestamp;               // זמן במילישניות מאז תחילת המשחק
    std::string piece_id;        // מזהה הכלי
    std::string type;            // סוג הפקודה: "Move", "Jump" וכו'
    std::vector<std::string> params; // פרמטרים נוספים (למשל מיקום)

    Command() = default;
    Command(int ts, const std::string& id, const std::string& t, const std::vector<std::string>& p)
        : timestamp(ts), piece_id(id), type(t), params(p) {
    }
};