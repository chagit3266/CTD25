#pragma once

#include <memory>
#include <string>
#include <utility> // for std::pair

class Board;
class Physics;

class PhysicsFactory {
public:
    explicit PhysicsFactory(std::shared_ptr<Board> board);

    std::shared_ptr<Physics> create(std::pair<int, int> start_cell, const std::string& cfg);

private:
    std::shared_ptr<Board> board_;
};
