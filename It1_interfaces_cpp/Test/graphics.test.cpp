#include "../graphics.hpp"
#include <gtest/gtest.h>

TEST(GraphicsTest, ResetDoesNotCrash) {
    Graphics g;
    g.reset();
    g.reset(1000); // כל מספר
    SUCCEED(); // אם לא נפל, עבר
}

TEST(GraphicsTest, DrawDoesNotCrash) {
    Graphics g;
    g.draw();
    SUCCEED(); // אם לא נפל, עבר
}