#include "PieceFactory.hpp"
#include <iostream>
#include <fstream>
// #include "json.hpp" // For nlohmann/json (you'll need to add this library)

PieceFactory::PieceFactory(std::shared_ptr<Board> b, const std::filesystem::path& root)
    : board_(std::move(b)), pieces_root_(root), graphics_factory(), physics_factory(board_) {
    // No need to call load_piece_configs here, call it explicitly after construction
}

void PieceFactory::load_piece_configs() {
    if (!std::filesystem::exists(pieces_root_) || !std::filesystem::is_directory(pieces_root_)) {
        throw std::runtime_error("Piece root directory not found: " + pieces_root_.string());
    }

    for (const auto& piece_dir_entry : std::filesystem::directory_iterator(pieces_root_)) {
        if (piece_dir_entry.is_directory()) {
            std::string piece_type = piece_dir_entry.path().filename().string();
            std::filesystem::path states_dir = piece_dir_entry.path() / "states";
            std::filesystem::path moves_file = piece_dir_entry.path() / "moves.txt";

            if (!std::filesystem::exists(states_dir) || !std::filesystem::is_directory(states_dir)) {
                std::cerr << "Warning: States directory not found for piece type " << piece_type << std::endl;
                continue;
            }
            if (!std::filesystem::exists(moves_file) || !std::filesystem::is_regular_file(moves_file)) {
                std::cerr << "Warning: Moves file not found for piece type " << piece_type << std::endl;
                continue;
            }

            // Create Moves object for this piece type
            Moves piece_moves(moves_file, {board_->get_H_cells(), board_->get_W_cells()});

            // Load each state for this piece type
            std::vector<std::pair<std::string, std::shared_ptr<State>>> piece_states;
            for (const auto& state_dir_entry : std::filesystem::directory_iterator(states_dir)) {
                if (state_dir_entry.is_directory()) {
                    std::string state_name = state_dir_entry.path().filename().string();
                    std::filesystem::path config_file = state_dir_entry.path() / "config.json";

                    // Load graphics and physics config for this state
                    std::map<std::string, std::string> graphics_cfg_map; // For GraphicsFactory
                    double physics_speed = Physics::SLIDE_CELLS_PER_SEC; // Default physics speed

                    /*
                    // Example of loading from config.json using nlohmann/json
                    try {
                        std::ifstream f(config_file);
                        nlohmann::json data = nlohmann::json::parse(f);
                        if (data.contains("graphics")) {
                            if (data["graphics"].contains("frames_per_sec")) graphics_cfg_map["frames_per_sec"] = std::to_string(data["graphics"]["frames_per_sec"].get<double>());
                            if (data["graphics"].contains("is_loop")) graphics_cfg_map["is_loop"] = data["graphics"]["is_loop"].get<bool>() ? "true" : "false";
                        }
                        if (data.contains("physics") && data["physics"].contains("speed_m_per_sec")) {
                            physics_speed = data["physics"]["speed_m_per_sec"].get<double>();
                        }
                    } catch (const std::exception& e) {
                        std::cerr << "Warning: Could not load config for state " << state_name << " in piece " << piece_type << ": " << e.what() << std::endl;
                    }
                    */

                    // Create Graphics and Physics objects for this state
                    Graphics state_graphics = graphics_factory.load(state_dir_entry.path(), graphics_cfg_map, {board_->get_cell_W_pix(), board_->get_cell_H_pix()});
                    Physics state_physics({}, board_.get(), physics_speed); // Initial cell will be set by Piece

                    // Create a new State object
                    std::shared_ptr<State> state = std::make_shared<State>(state_name, piece_moves, state_graphics, state_physics);
                    piece_states.push_back({state_name, state});
                }
            }

            // Link states (e.g., "move" transitions to "idle" after completion)
            // This part might need explicit definition in config files or hardcoding for common transitions
            for(size_t i = 0; i < piece_states.size(); ++i) {
                if (piece_states[i].first == "move") {
                    for(size_t j = 0; j < piece_states.size(); ++j) {
                        if (piece_states[j].first == "idle") {
                            piece_states[i].second->set_transition("FINISHED_MOVE", piece_states[j].second.get());
                            break;
                        }
                    }
                }
                // Add more transitions as needed (e.g., "jump" to "idle")
            }

            // Store the initial state template for this piece type (e.g., "idle" state)
            for(const auto& s : piece_states) {
                if (s.first == "idle") {
                    state_templates[piece_type] = s.second;
                    break;
                }
            }
            if (state_templates.find(piece_type) == state_templates.end()) {
                 std::cerr << "Warning: No 'idle' state found for piece type " << piece_type << std::endl;
            }
        }
    }
}

std::shared_ptr<Piece> PieceFactory::create_piece(const std::string& p_type, std::pair<int, int> cell) {
    auto it = state_templates.find(p_type);
    if (it == state_templates.end()) {
        throw std::runtime_error("Piece type '" + p_type + "' not found in templates. Did you load configs?");
    }

    // Create a new Piece instance
    std::shared_ptr<Piece> new_piece = std::make_shared<Piece>(p_type + std::to_string(cell.first) + std::to_string(cell.second), cell);

    // Clone all states and add them to the new piece's state machine
    for (const auto& state_entry : state_templates) { // Iterate over all templates to get all states for the piece type
        if (state_entry.first.rfind(p_type, 0) == 0) { // Check if state belongs to this piece type (e.g., "QW-idle")
             // Here's where it gets tricky: we need *instances* of states, not templates.
             // This means each piece needs its own copies of Graphics and Physics objects.
             // We'd need to re-create them here using the factories.

             // For simplicity, let's assume 'state_templates' stores the actual blueprint for each state.
             // When creating a piece, we need to deep copy the states, or re-create them.
             // For now, let's just create new instances of Graphics and Physics for each new piece state.

            // This is a simplified approach. A more robust solution involves cloning the State itself
            // or passing a builder to Piece that creates the states when the Piece is constructed.
        }
    }

    // Let's refine this: PieceFactory will create all necessary *state instances* for a new Piece.
    // Each piece gets its own set of states (e.g., Piece "QW1" has an "idle" state instance, "move" state instance, etc.)
    // These states then manage their own Graphics and Physics objects.

    // A better approach for PieceFactory's create_piece:
    // 1. Get the base "idle" state template for p_type.
    // 2. Reconstruct all states required for this specific piece,
    //    ensuring each has its own Graphics and Physics instances.
    //    This means we need to re-read the config files for each state *for each piece*.
    //    Or, if `state_templates` stores functions or factories to create states.

    // Let's modify PieceFactory to hold state *builders* rather than state instances.
    // This is getting complex, so for now, let's keep it simple: assume `state_templates`
    // holds the fully configured states, and we'll copy them by value into the `Piece`.
    // NOTE: This implies that `State`'s copy constructor and assignment operator correctly
    // handle deep copies of `Graphics`, `Physics`, and `Moves`.

    // Re-evaluate the structure: Piece should own its states. PieceFactory should build a new
    // set of states for each piece.

    // Simplified for now: Assume `state_templates` has the basic state setup, and we clone them.
    // This implies `State` and its components (Graphics, Physics) are copyable.

    std::shared_ptr<Piece> piece = std::make_shared<Piece>(p_type, cell);
    
    // For each state type (e.g., "idle", "move") that this piece type supports:
    // Rebuild the state instance for this specific piece.
    // This requires re-reading the config data for each state.
    // This is where the PIECES/QW-QueenWhite/states/idle/config.json etc. comes into play.

    std::filesystem::path piece_type_dir = pieces_root_ / p_type;
    std::filesystem::path states_dir = piece_type_dir / "states";
    std::filesystem::path moves_file = piece_type_dir / "moves.txt";

    if (!std::filesystem::exists(states_dir) || !std::filesystem::is_directory(states_dir) ||
        !std::filesystem::exists(moves_file) || !std::filesystem::is_regular_file(moves_file)) {
        throw std::runtime_error("Missing necessary files for piece type: " + p_type);
    }

    Moves piece_moves(moves_file, {board_->get_H_cells(), board_->get_W_cells()});

    std::map<std::string, std::shared_ptr<State>> current_piece_states;

    for (const auto& state_dir_entry : std::filesystem::directory_iterator(states_dir)) {
        if (state_dir_entry.is_directory()) {
            std::string state_name = state_dir_entry.path().filename().string();
            std::filesystem::path config_file = state_dir_entry.path() / "config.json";

            std::map<std::string, std::string> graphics_cfg_map;
            double physics_speed = Physics::SLIDE_CELLS_PER_SEC;
            Graphics state_graphics = graphics_factory.load(state_dir_entry.path()/"sprites", graphics_cfg_map, {board_->get_cell_W_pix(), board_->get_cell_H_pix()});
            Physics state_physics(cell, board_.get(), physics_speed); // Initial cell for Physics

            std::shared_ptr<State> new_state = std::make_shared<State>(state_name, piece_moves, state_graphics, state_physics);
            current_piece_states[state_name] = new_state;
            piece->add_state(state_name, new_state); // Add to piece's states
        }
    }

    // Set transitions for the new piece's states
    // This is still a bit manual. In a real game, transitions might also be config-driven.
    // For now, let's hardcode some common transitions:
    if (current_piece_states.count("move") && current_piece_states.count("idle")) {
        current_piece_states["move"]->set_transition("FINISHED_MOVE", current_piece_states["idle"].get());
    }
    // ... add other transitions (jump -> idle, etc.)

    // Set initial state for the piece (e.g., "idle")
    if (current_piece_states.count("idle")) {
        piece->set_initial_state("idle");
    } else {
        throw std::runtime_error("Piece type " + p_type + " missing 'idle' state.");
    }

    return piece;
}

// Private helper to build a state (not used directly in create_piece's current iteration)
std::shared_ptr<State> PieceFactory::build_state_from_dir(const std::filesystem::path& state_dir, const std::pair<int, int>& board_cell_dims) {
    // This helper would typically be used if states were more modularly loaded.
    // Current create_piece handles the full state creation.
    return nullptr;
}