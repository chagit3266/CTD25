#include "Graphics.hpp"
#include <iostream>

Graphics::Graphics(const std::filesystem::path& folder, const std::pair<int, int>& cs, bool lp, double fps_)
    : sprites_folder(folder), cell_size(cs), loop(lp), fps(fps_), current_frame(0), last_update_ms(0)
{
    frames.clear();
    if (!std::filesystem::exists(sprites_folder))
    {
        throw std::runtime_error("Sprites folder does not exist: " + sprites_folder.string());
    }

    // Load images, sort them to ensure correct animation order (e.g., "frame_01.png", "frame_02.png")
    std::vector<std::filesystem::path> image_paths;
    for (const auto& p : std::filesystem::directory_iterator(sprites_folder))
    {
        if (p.is_regular_file())
        {
            // Check for common image extensions
            std::string ext = p.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".bmp")
            {
                image_paths.push_back(p.path());
            }
        }
    }
    std::sort(image_paths.begin(), image_paths.end()); // Sort by filename

    for (const auto& path : image_paths)
    {
        Img img_frame;
        img_frame.read(path.string(), cell_size, true); // Keep aspect ratio
        frames.push_back(img_frame);
    }

    if (frames.empty())
    {
        std::cerr << "Warning: No image frames loaded from " << sprites_folder.string() << std::endl;
    }
}

Graphics::Graphics(const Graphics& other)
    : sprites_folder(other.sprites_folder), cell_size(other.cell_size), loop(other.loop),
    fps(other.fps), frames(other.frames), current_frame(other.current_frame),
    last_update_ms(other.last_update_ms), current_command(other.current_command) {
}

void Graphics::reset(const Command& cmd)
{
    current_command = cmd;
    current_frame = 0;
    last_update_ms = 0; // Reset timer for new animation sequence
}


void Graphics::update(int now_ms)
{
    if (frames.empty())
        return;

    if (last_update_ms == 0)
    {
        last_update_ms = now_ms;
        return; // First update call, just set time
    }

    int delta_ms = now_ms - last_update_ms;
    int frame_duration_ms = static_cast<int>(1000.0 / fps);

    if (frame_duration_ms <= 0)
        frame_duration_ms = 1; // Prevent division by zero

    while (delta_ms >= frame_duration_ms)
    {
        current_frame++;
        if (current_frame >= static_cast<int>(frames.size()))
        {
            if (loop)
            {
                current_frame = 0; // Loop back
            }
            else
            {
                current_frame = static_cast<int>(frames.size()) - 1; // Stay on last frame
                // Consider adding a flag to indicate animation is finished here
            }
        }
        delta_ms -= frame_duration_ms;
        last_update_ms = now_ms - delta_ms; // Adjust last_update_ms to account for remaining delta_ms
    }
}

const Img& Graphics::get_img() const
{
    if (frames.empty())
    {
        throw std::runtime_error("No frames loaded for graphics.");
    }
    return frames[current_frame];
}

bool Graphics::is_finished() const
{
    if (loop || frames.empty())
        return false;
    return current_frame == static_cast<int>(frames.size()) - 1;
}