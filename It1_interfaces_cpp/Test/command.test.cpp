#include "../It1_interfaces_cpp/Command.hpp"
#include <gtest/gtest.h>

TEST(CommandTest, DefaultConstructor) {
    //בדיקת בנאי הברירת מחדל
    Command cmd;
    EXPECT_EQ(cmd.timestamp, 0);//שתאריך מאותחל ב0
    EXPECT_TRUE(cmd.piece_id.empty());//שכל המחרוזות ריקות
    EXPECT_TRUE(cmd.type.empty());
    EXPECT_TRUE(cmd.params.empty());//שהוקטור של הפרמטרים ריקים
}

//בדיקת בנאי עם פרמטרים
TEST(CommandTest, ParameterizedConstructor) {
    std::vector<std::string> params = { "e2", "e4" };
    Command cmd(1000, "pawn1", "Move", params);

    EXPECT_EQ(cmd.timestamp, 1000);
    EXPECT_EQ(cmd.piece_id, "pawn1");
    EXPECT_EQ(cmd.type, "Move");
    ASSERT_EQ(cmd.params.size(), 2);
    EXPECT_EQ(cmd.params[0], "e2");
    EXPECT_EQ(cmd.params[1], "e4");
}

//TEST(CommandTest, CopyConstructor) {
//    Command original(500, "rook1", "Capture", { "a1", "a8" });
//    Command copy = original;
//
//    EXPECT_EQ(copy.timestamp, original.timestamp);
//    EXPECT_EQ(copy.piece_id, original.piece_id);
//    EXPECT_EQ(copy.type, original.type);
//    ASSERT_EQ(copy.params.size(), original.params.size());
//    EXPECT_EQ(copy.params[0], original.params[0]);
//}
//
//TEST(CommandTest, MoveSemantics) {
//    Command original(200, "knight1", "LShape", { "b1", "c3" });
//    Command moved = std::move(original);
//
//    EXPECT_EQ(moved.timestamp, 200);
//    EXPECT_EQ(moved.piece_id, "knight1");
//    EXPECT_EQ(moved.type, "LShape");
//    ASSERT_EQ(moved.params.size(), 2);
//    EXPECT_EQ(moved.params[1], "c3");
//}