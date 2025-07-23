#include "img.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include "../../It1_interfaces_cpp/Game.hpp"
#include "../../It1_interfaces_cpp/PhysicsFactory.hpp"
#include "../../It1_interfaces_cpp/GraphicsFactory.hpp"
#include "../../It1_interfaces_cpp/Piece.hpp"
#include "../../It1_interfaces_cpp/State.hpp"
#include "../../It1_interfaces_cpp/Physics.hpp"
#include "../../It1_interfaces_cpp/Graphics.hpp"

int main() {
    try {
        // 1. יצירת תמונה ללוח (אפשר להוסיף קריאה לקובץ אם יש)
        auto img = std::make_shared<Img>();
        // כאן תוכלי לקרוא תמונה אם יש צורך, למשל:
        // img->read("board.png", {640,480}, true);

        // 2. יצירת לוח עם הפרמטרים הנדרשים
        // יש לעדכן את הערכים בהתאם למשחק שלך
        int cell_H_pix = 64;
        int cell_W_pix = 64;
        int cell_H_m = 1;
        int cell_W_m = 1;
        int W_cells = 8;
        int H_cells = 8;

        std::shared_ptr<Board> board = std::make_shared<Board>(
            cell_H_pix, cell_W_pix,
            cell_H_m, cell_W_m,
            W_cells, H_cells,
            img
        );

        // 3. יצירת פקטוריז (בהתאם למחלקות שלך)
        PhysicsFactory physicsFactory(board);
        GraphicsFactory graphicsFactory;

        // 4. יצירת שחקנים (Pieces) עם כל הרכיבים הדרושים
        std::vector<std::shared_ptr<Piece>> pieces;

        // יצירת State, Physics ו-Graphics עבור כל כלי
        auto state1 = std::make_shared<State>();

        auto piece1 = std::make_shared<Piece>("QW", state1);

        pieces.push_back(piece1);

        auto state2 = std::make_shared<State>();

        auto piece2 = std::make_shared<Piece>("RW", state2);

        pieces.push_back(piece2);

        // 5. יצירת המשחק
        Game game(pieces, board);

        // 6. לולאת המשחק
        game.run();

    }
    catch (const std::exception& ex) {
        std::cerr << "שגיאה: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}