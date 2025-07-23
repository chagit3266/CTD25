#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <queue>
#include <vector>
#include <mutex>
#include "Command.hpp"
#include "Piece.hpp"
#include "Board.hpp"

//לולאת משחק מלאה עם ניהול פקודות, עדכונים, ציור, ותזמון.
class Game {
public:
    Game(const std::vector<std::shared_ptr<Piece>>& pieces, std::shared_ptr<Board> board);

    void run();

    void enqueue_command(const Command& cmd);

private:
    std::unordered_map<std::string, std::shared_ptr<Piece>> pieces_map;
    std::shared_ptr<Board> board;

    std::queue<Command> user_input_queue;
    std::mutex queue_mutex;

    bool running;

    int game_time_ms() const;

    void start_user_input_thread();

    void process_input(const Command& cmd);
    void draw();
    bool show();
    void resolve_collisions();
    bool is_win() const;
    void announce_win();

};
