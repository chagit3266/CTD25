#include "Game.hpp"
#include "Command.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>

TEST(GameTest, EnqueueAndProcessCommand) {
    // ����� ����� �����
    auto mock_piece = std::make_shared<Piece>("p1");

    // ����� ��� �����
    auto board = std::make_shared<Board>();

    // ����� ���� �� ������
    Game game({mock_piece}, board);

    // ����� �����
    Command cmd(0, "p1", "move", {"1", "2"});
    game.enqueue_command(cmd);

    // ����� ���� �� ���� (��� ������ run)
    game.process_input(cmd);

    // ����� �� ������ ����� �� ������
    EXPECT_TRUE(mock_piece->was_called);
    EXPECT_EQ(mock_piece->last_cmd.type, "move");
    EXPECT_EQ(mock_piece->last_cmd.params[0], "1");
    EXPECT_EQ(mock_piece->last_cmd.params[1], "2");
}
