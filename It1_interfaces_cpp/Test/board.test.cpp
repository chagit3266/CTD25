#include "../board.hpp"
#include "../mock_img.cpp"
#include <gtest/gtest.h>

TEST(SimpleTest, BasicAssertion) {
    EXPECT_EQ(1, 1);  // טסט תמיד עובר
}

TEST(BoardTest,CellToPixelConversion){
    MockImg mock_img;
    Board board(64, 64, 8, 8, mock_img);

    
}


TEST(BoardTest,CloneIndependent){
    Img mock_img;
    Board original(64, 64, 8, 8, mock_img);
    Board copy=original.clone();

    //שינוי בעותק לא אמור להשפיע על המקור
    copy.img=Img();
    EXPECT_FALSE(original.img.empty());//בודק שהמקור לא נשאר ריק

}