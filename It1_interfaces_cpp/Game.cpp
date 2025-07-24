#include "Game.hpp"
#include <thread>
#include <chrono>
#include <iostream>

Game::Game(const std::vector<std::shared_ptr<Piece>> &pieces, std::shared_ptr<Board> board)
    : board(std::move(board)), win_flag(true)
{
    start_time = std::chrono::steady_clock::now();
    for (auto &p : pieces)
    {
        pieces_map[p->get_id()] = p;
    }
}

int Game::game_time_ms() const
{
    using namespace std::chrono;
    static auto start_time = steady_clock::now();
    auto now = steady_clock::now();
    return static_cast<int>(duration_cast<milliseconds>(now - start_time).count());
}

void Game::start_user_input_thread()
{
    // לדוגמא: מחכה לקלט קונסולה (אפשר להחליף לאירועי מקלדת מתקדמים)
    std::thread([this]() {
        int command_counter = 0;
        while (!win_flag.load()) {
            // Simulate input every 2 seconds
            std::this_thread::sleep_for(std::chrono::seconds(2)); 

            // Example: Hardcoded commands for demonstration
            // Using the new explicit constructor
            long current_time = game_time_ms();
            
            // Find an alive piece to move
            std::shared_ptr<Piece> piece_to_move = nullptr;
            for (auto &[id, p] : pieces_map) {
                if (p->is_alive()) {
                    piece_to_move = p;
                    break;
                }
            }

            if (piece_to_move) {
                std::string piece_id = piece_to_move->get_id();
                std::string command_type = "Move";
                std::vector<std::string> command_params;

                // Alternate target cells for demonstration
                if (command_counter % 2 == 0) {
                    command_params = {"2", "3"}; // Move to row 2, col 3
                } else {
                    command_params = {"4", "4"}; // Move to row 4, col 4
                }
                
                Command cmd(current_time, piece_id, command_type, command_params);
                user_input_queue.push(cmd);
                
                // Use getters for printing to ensure consistency and demonstrate their use
                std::cout << "Simulating command for " << cmd.get_piece_id() 
                          << " (Type: " << cmd.get_type() << ", Params: [" << cmd.get_params()[0] 
                          << "," << cmd.get_params()[1] << "])" << std::endl;
            } else {
                std::cout << "No alive pieces to simulate commands for." << std::endl;
            }
            command_counter++;
        }
    }).detach();
}
void Game::enqueue_command(const Command &cmd)
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    user_input_queue.push(cmd);
}

void Game::process_input(const Command &cmd)
{
    auto it = pieces_map.find(cmd.piece_id);
    if (it != pieces_map.end())
    {
        it->second->on_command(cmd);
    }
}

void Game::draw()
{
    // TODO: מימוש ציור הלוח והכלים - קורא ל־Board ול־Piece
}

bool Game::show()
{
    // TODO: הצגת המסך, טיפול באירועים - חזרה false אם משתמש סגר חלון
    return true;
}

void Game::resolve_collisions()
{
    // TODO: בדיקת תפיסות בין כלים
}

bool Game::is_win() const
{
    // TODO: בדיקת סיום המשחק
    return false;
}

void Game::announce_win()
{
    std::cout << "Game Over! Winner announced.\n";
}

void Game::run()
{
    start_user_input_thread();

    int start_ms = game_time_ms();

    for (auto &[id, p] : pieces_map)
    {
        p->reset(start_ms);
    }

    while (!is_win())
    {
        int now = game_time_ms();

        // (1) עדכון פיזיקה ואנימציות
        for (auto &[id, p] : pieces_map)
        {
            p->update(now);
        }

        // (2) טיפול בפקודות שהתקבלו

        while (!user_input_queue.empty())
        {
            Command cmd = user_input_queue.front();
            user_input_queue.pop();
            process_input(cmd,now);
        }

        // (3) ציור מצב נוכחי
        draw();

        // (4) הצגת המסך, יציאה אם המשתמש סגר חלון
        if (!show())
            break;

        // (5) פתרון תפיסות
        resolve_collisions();

        // השהיה קלה למניעת שימוש יתר במעבד (אפשר לשפר למדויק)
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    announce_win();
    cv::destroyAllWindows();
}
