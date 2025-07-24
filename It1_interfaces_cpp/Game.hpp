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

//����� ���� ���� �� ����� ������, �������, ����, ������.
class Game {
public:
    Game(const std::vector<std::shared_ptr<Piece>>& pieces, std::shared_ptr<Board> board);

    void run();

    // void enqueue_command(const Command& cmd);

private:

    std::unordered_map<std::string, std::shared_ptr<Piece>> pieces_map;
    std::shared_ptr<Board> board;
    std::chrono::steady_clock::time_point start_time; /**< The time the game started. */
    std::queue<Command> user_input_queue;
    std::mutex queue_mutex;
    std::atomic<bool> win_flag; /**< Flag to indicate if the game is won. */

    int game_time_ms() const;

    void start_user_input_thread();

    void draw();
    
    bool show();

    void process_input(const Command& cmd);
    
    void resolve_collisions();

    bool is_win() const;
    
    void announce_win();

};
