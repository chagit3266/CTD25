#include "physics_factory.hpp"
#include "board.hpp"
#include "physics.hpp"

PhysicsFactory::PhysicsFactory(std::shared_ptr<Board> board)
    : board_(std::move(board)) {
}

std::shared_ptr<Physics> PhysicsFactory::create(std::pair<int, int> start_cell, const std::string& cfg) {
    double speed = 1.0; // ברירת מחדל

    // TODO: ניתוח עתידי של cfg (כעת לא בשימוש)

    return std::make_shared<Physics>(start_cell, board_, speed);
}
