#pragma once
#include "img.hpp"
#include "board.hpp"
#include "Piece.hpp"
#include "PieceFactory.hpp"
#include "Game.hpp" // The Game class
#include <iostream>
#include <vector>
#include <memory> // For shared_ptr

int main() {
    try {
        std::cout << "Starting KongfuChess Game..." << std::endl;

        // 1. Initialize Board
        Img board_img;
        // Make sure board.png is in CTD25/ directory
        board_img.read(R"(../../board.png)", {640, 480}, true); // Adjust path as needed
        
        // Define board cell dimensions (e.g., 8x8 board, total 640x480 pixels)
        // For a chess-like board, usually 8x8. Adjust cell_H/W_pix accordingly.
        int board_width_cells = 8;
        int board_height_cells = 8;
        int cell_width_pix = board_img.get_mat().cols / board_width_cells;
        int cell_height_pix = board_img.get_mat().rows / board_height_cells;

        std::shared_ptr<Board> game_board = std::make_shared<Board>(
            cell_height_pix, cell_width_pix, board_width_cells, board_height_cells, board_img
        );

        // 2. Initialize PieceFactory
        // Assume PIECES directory is ../PIECES relative to SRC/main.cpp
        std::filesystem::path pieces_root_dir = R"(../pieces)";
        PieceFactory piece_factory(game_board, pieces_root_dir);
        piece_factory.load_piece_configs(); // Load all piece types and their states

        // 3. Create Pieces for the game
        std::vector<std::shared_ptr<Piece>> game_pieces;
        
        try {
            game_pieces.push_back(piece_factory.create_piece("RW", {7,0}));
            game_pieces.push_back(piece_factory.create_piece("NW", {7,1}));
            game_pieces.push_back(piece_factory.create_piece("BW", {7,2}));
            game_pieces.push_back(piece_factory.create_piece("QW", {7,3}));
            game_pieces.push_back(piece_factory.create_piece("KW", {7,4}));
            game_pieces.push_back(piece_factory.create_piece("BW", {7,5}));
            game_pieces.push_back(piece_factory.create_piece("NW", {7,6}));
            game_pieces.push_back(piece_factory.create_piece("RW", {7,7}));
            game_pieces.push_back(piece_factory.create_piece("RB", {0,0}));
            game_pieces.push_back(piece_factory.create_piece("NB", {0,1}));
            game_pieces.push_back(piece_factory.create_piece("BB", {0,2}));
            game_pieces.push_back(piece_factory.create_piece("QB", {0,3}));
            game_pieces.push_back(piece_factory.create_piece("KB", {0,4}));
            game_pieces.push_back(piece_factory.create_piece("BB", {0,5}));
            game_pieces.push_back(piece_factory.create_piece("NB", {0,6}));
            game_pieces.push_back(piece_factory.create_piece("RB", {0,7}));
            for(int i=0;i<8;i++){
                game_pieces.push_back(piece_factory.create_piece("PW", {6,i}));
                game_pieces.push_back(piece_factory.create_piece("PB", {1,i}));
            }

        } catch (const std::exception& e) {
            std::cerr << "Error creating piece: " << e.what() << std::endl;
            return 1;
        }

        // 4. Initialize and Run the Game
        Game kongfu_game(game_pieces, game_board);
        kongfu_game.run();

        std::cout << "KongfuChess Game finished successfully!" << std::endl;
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Game Error: " << e.what() << std::endl;
        return 1;
    }
}