#include "../graphics.hpp"
#include <gtest/gtest.h>

TEST(GraphicsTest, ResetDoesNotCrash) {
    Graphics g;
    g.reset();
    g.reset(1000); // �� ����
    SUCCEED(); // �� �� ���, ���
}

TEST(GraphicsTest, DrawDoesNotCrash) {
    Graphics g;
    g.draw();
    SUCCEED(); // �� �� ���, ���
}