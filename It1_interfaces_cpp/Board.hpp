#pragma once
#include "img.hpp"
#include <memory>

//שומר את מידות התא, מספר התאים, ואת התמונה (Img). כולל יכולת לשכפל את הלוח.
class Board {
public:
    int cell_H_pix;
    int cell_W_pix;
    int cell_H_m;
    int cell_W_m;
    int W_cells;
    int H_cells;
    std::shared_ptr<Img> img;

    Board(int chp, int cwp, int chm, int cwm, int wc, int hc, std::shared_ptr<Img> img);

    std::shared_ptr<Board> clone() const;
};
