#pragma once

//אחראית על התצוגה בפועל
// משתנה בזמן ריצה
//מציגה את הכלי עם אנימציות ותמונות.
class Graphics {
public:
    Graphics();

    void reset();
    void reset(int now_ms);

    void draw();
    // TODO: תמונות, אנימציות
};
