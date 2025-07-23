#pragma once
#include "img.hpp"
#include <memory>

//שומר את מידות התא, מספר התאים, ואת התמונה (Img). כולל יכולת לשכפל את הלוח.
class Board {
private:
    int cell_H_pix;
    int cell_W_pix;
    int W_cells;
    int H_cells;
    Img img;

public:
    Board(int ch = 0, int cw = 0, int w = 0, int h = 0, const Img& i = Img())
        : cell_H_pix(ch), cell_W_pix(cw), W_cells(w), H_cells(h), img(i) {
    }

    // Getters
    int get_cell_H_pix() const { return cell_H_pix; }
    int get_cell_W_pix() const { return cell_W_pix; }
    int get_W_cells() const { return W_cells; }
    int get_H_cells() const { return H_cells; }
    const Img& get_img() const { return img; }  // עבור const Board
    Img& get_img() { return img; }              // עבור non-const Board
    // Setters
    void set_cell_H_pix(int v) { cell_H_pix = v; }
    void set_cell_W_pix(int v) { cell_W_pix = v; }
    void set_W_cells(int v) { W_cells = v; }
    void set_H_cells(int v) { H_cells = v; }
    void set_img(const Img& i) { img = i; }

    // Create a copy of the board, including a copy of the image (clone)
    Board clone() const;
};