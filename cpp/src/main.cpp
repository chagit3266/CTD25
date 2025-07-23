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
        Img board_img;
        // כאן תוכלי לקרוא תמונה אם יש צורך, למשל:
        board_img.read("../../board.png", {640,480}, true);

        // 2. יצירת לוח עם הפרמטרים הנדרשים
        // יש לעדכן את הערכים בהתאם למשחק שלך
        int board_width_cells = 8;
        int board_height_cells = 8;
        int cell_width_pix = board_img.get_mat().cols / board_width_cells;
        int cell_height_pix = board_img.get_mat().rows / board_height_cells;

        std::shared_ptr<Board> game_board = std::make_shared<Board>(
            cell_height_pix, cell_width_pix, board_width_cells, board_height_cells, board_img
        );


        // 3. יצירת פקטוריז (בהתאם למחלקות שלך)
        PhysicsFactory physicsFactory(game_board);
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