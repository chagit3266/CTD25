#include "graphicsfactory.hpp"
#include "graphics.hpp"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <nlohmann/json.hpp> // JSON ספריה
#include <iostream>

using json = nlohmann::json;

std::shared_ptr<Graphics> GraphicsFactory::load(
    const std::filesystem::path& sprites_dir,//ניתוב לתיקית התמונות
    const std::map<std::string, std::string>& cfg,//מפת מחרוזות עם הגדרות עבור סוגי אנימציות
    const std::pair<int, int>& cell_size //גודל התא שעל הלוח
) {
    auto graphics = std::make_shared<Graphics>();

    for (const auto& [state_name, folder_name] : cfg) {
        std::filesystem::path state_path = sprites_dir / folder_name;
        std::filesystem::path config_path = state_path / "config.json";
        std::filesystem::path sprites_path = state_path / "sprites";

        // קריאת config.json
        std::ifstream config_file(config_path);
        if (!config_file) {
            std::cerr << "Cannot open config: " << config_path << "\n";
            continue;
        }

        json config_json;
        config_file >> config_json;

        // פרטי גרפיקה
        int fps = config_json["graphics"]["frames_per_sec"];
        bool is_loop = config_json["graphics"]["is_loop"];

        // קריאת התמונות
        std::vector<cv::Mat> frames;
        for (const auto& entry : std::filesystem::directory_iterator(sprites_path)) {
            if (entry.path().extension() == ".png") {
                cv::Mat img = cv::imread(entry.path().string(), cv::IMREAD_UNCHANGED);
                if (!img.empty()) {
                    cv::resize(img, img, cv::Size(cell_size.second, cell_size.first)); // התאמת לגודל תא
                    frames.push_back(img);
                }
            }
        }

        // מיון לפי שם קובץ כדי שהפריימים יהיו לפי סדר
        std::sort(frames.begin(), frames.end(), [](const cv::Mat& a, const cv::Mat& b) {
            return a.rows < b.rows; // לפי צורך, עדיף לפי שם קובץ אם שומרים שמות
            });

        GraphicsState state{ frames, fps, is_loop };
        graphics->add_state(state_name, state);
    }

    return graphics;
}

