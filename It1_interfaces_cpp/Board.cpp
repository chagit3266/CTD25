#include "board.hpp"

Board Board::clone() const {
    // Create a new copy of the Board, including a copy of the image
    Img img_copy = img.clone();
    return Board(cell_H_pix, cell_W_pix, W_cells, H_cells, img_copy);
}
