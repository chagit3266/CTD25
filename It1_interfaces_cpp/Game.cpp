#include "Game.hpp"
#include <thread>
#include <chrono>
#include <iostream>

Game::Game(const std::vector<std::shared_ptr<Piece>>& pieces, std::shared_ptr<Board> board)
    : board(std::move(board)), running(true)
{
    for (auto& p : pieces) {
        pieces_map[p->get_id()] = p;
    }
}

int Game::game_time_ms() const {
    using namespace std::chrono;
    static auto start_time = steady_clock::now();
    auto now = steady_clock::now();
    return static_cast<int>(duration_cast<milliseconds>(now - start_time).count());
}

void Game::start_user_input_thread() {
    // לדוגמא: מחכה לקלט קונסולה (אפשר להחליף לאירועי מקלדת מתקדמים)
    std::thread input_thread([this]() {
        while (running) {
            std::string line;
            std::getline(std::cin, line);
            if (line == "exit") {
                running = false;
                break;
            }
            // כאן מניתח שורת קלט לפקודה - למימוש ספציפי
            // לדוגמה: piece_id type param1 param2 ...
            std::istringstream iss(line);
            std::string piece_id, type;
            iss >> piece_id >> type;
            std::vector<std::string> params;
            std::string param;
            while (iss >> param) {
                params.push_back(param);
            }

            Command cmd(game_time_ms(), piece_id, type, params);

            {
                std::lock_guard<std::mutex> lock(queue_mutex);
                user_input_queue.push(cmd);
            }
        }
        });
    input_thread.detach();
}

void Game::enqueue_command(const Command& cmd) {
    std::lock_guard<std::mutex> lock(queue_mutex);
    user_input_queue.push(cmd);
}

void Game::process_input(const Command& cmd) {
    auto it = pieces_map.find(cmd.piece_id);
    if (it != pieces_map.end()) {
        it->second->on_command(cmd);
    }
}

void Game::draw() {
    // TODO: מימוש ציור הלוח והכלים - קורא ל־Board ול־Piece
}

bool Game::show() {
    // TODO: הצגת המסך, טיפול באירועים - חזרה false אם משתמש סגר חלון
    return true;
}

void Game::resolve_collisions() {
    // TODO: בדיקת תפיסות בין כלים
}

bool Game::is_win() const {
    // TODO: בדיקת סיום המשחק
    return false;
}

void Game::announce_win() {
    std::cout << "Game Over! Winner announced.\n";
}

void Game::run() {
    start_user_input_thread();

    int start_ms = game_time_ms();
    for (auto& [id, p] : pieces_map) {
        p->reset(start_ms);
    }

    while (running) {
        int now = game_time_ms();

        // (1) עדכון פיזיקה ואנימציות
        for (auto& [id, p] : pieces_map) {
            p->update(now);
        }

        // (2) טיפול בפקודות שהתקבלו
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            while (!user_input_queue.empty()) {
                Command cmd = user_input_queue.front();
                user_input_queue.pop();
                process_input(cmd);
            }
        }

        // (3) ציור מצב נוכחי
        draw();

        // (4) הצגת המסך, יציאה אם המשתמש סגר חלון
        if (!show())
            break;

        // (5) פתרון תפיסות
        resolve_collisions();

        // (6) בדיקת ניצחון וסיום
        if (is_win()) {
            announce_win();
            break;
        }

        // השהיה קלה למניעת שימוש יתר במעבד (אפשר לשפר למדויק)
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
