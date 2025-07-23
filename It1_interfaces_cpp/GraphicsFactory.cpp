#include "graphicsfactory.hpp"
#include "graphics.hpp"

std::shared_ptr<Graphics> GraphicsFactory::load(
    const std::filesystem::path& sprites_dir,
    const std::map<std::string, std::string>& cfg,
    const std::pair<int, int>& cell_size
) {
    // Placeholder: בפועל ייטען גרפיקה מהתיקייה והגדרות
    return std::make_shared<Graphics>(sprites_dir, cfg, cell_size);
}
