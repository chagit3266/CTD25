#pragma once
#include "img.hpp"
#include <vector>
#include <string>
#include <utility>
#include <opencv2/opencv.hpp>

class MockImg : public Img {
public:
    static std::vector<std::pair<int,int>> traj; // draw_on positions
    static std::vector<std::pair<std::pair<int,int>, std::string>> txt_traj;

    MockImg() = default;

    Img& read(const std::string& path,
              const std::pair<int, int>& size = {},
              bool keep_aspect = false,
              int interpolation = cv::INTER_AREA) override
    {
        // לא נטען באמת, רק מדמה קריאה
        return *this;
    }

    void draw_on(Img& other_img, int x, int y) override {
        traj.emplace_back(x, y);
    }

    void put_text(const std::string& txt, int x, int y, double font_size,
                  const cv::Scalar& color = cv::Scalar(255, 255, 255, 255),
                  int thickness = 1) override
    {
        txt_traj.emplace_back(std::make_pair(x, y), txt);
    }

    void show() override {
        // אין צורך להציג כלום ב־mock
    }

    static void reset() {
        traj.clear();
        txt_traj.clear();
    }
};
