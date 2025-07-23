#include "PieceFactory.hpp"

PieceFactory::PieceFactory(Board& b, const std::filesystem::path& r) : board(b), root(r) {}

std::shared_ptr<Piece> PieceFactory::create_piece(const std::string& p_type, std::pair<int, int> cell) {
    auto state = build_state_machine(root / p_type);
    auto physics = std::make_shared<Physics>();
    auto graphics = std::make_shared<Graphics>();
    return std::make_shared<Piece>(p_type, state, physics, graphics);
}

std::shared_ptr<State> PieceFactory::build_state_machine(const std::filesystem::path& piece_dir) {
    // טעינת JSON, יצירת מצבים ומעברים לפי הקבצים
    // כאן יש מקום לשיתוף פעולה עם Python או קובץ חיצוני
    return std::make_shared<State>(nullptr, nullptr, nullptr);
}