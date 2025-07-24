#pragma once

//אחראית על התצוגה בפועל
// משתנה בזמן ריצה
//מציגה את הכלי עם אנימציות ותמונות.
class Graphics {
public:
    Graphics(const std::filesystem::path& folder, const std::pair<int, int>& cell_size, bool loop = true, double fps = 6.0);
    Graphics(const Graphics& other);

    void reset(const Command& cmd);
    void update(int now_ms);       
    const Img& get_img() const;     
    bool is_finished() const;
};
