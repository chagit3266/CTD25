#include "Physics.hpp"

Physics::Physics() {}

void Physics::reset() {
    // איפוס פיזיקה
}

//void Physics::reset(int now_ms) {
//    // איפוס מבוסס זמן
//}

std::optional<Command> Physics::reset(int now_ms) {
    // בדוק אם יש אירוע לשדר חזרה כפקודה
    return std::nullopt;
}

void Physics::update_position(int now_ms) {
    // עדכון מיקום לפי הזמן
}
