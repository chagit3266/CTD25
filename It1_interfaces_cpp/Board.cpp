#include "board.hpp"

Board::Board(int chp, int cwp, int chm, int cwm, int wc, int hc, std::shared_ptr<Img> img)
    : cell_H_pix(chp), cell_W_pix(cwp), cell_H_m(chm), cell_W_m(cwm),
    W_cells(wc), H_cells(hc), img(img) {
}

std::shared_ptr<Board> Board::clone() const {
    return std::make_shared<Board>(cell_H_pix, cell_W_pix,
        cell_H_m, cell_W_m,
        W_cells, H_cells,
        img->clone());
}
