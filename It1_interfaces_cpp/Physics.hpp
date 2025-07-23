#pragma once
#include <optional>
#include "Command.hpp"

//����� ������, ������, �����.
class Physics {
public:
    Physics();

    void reset();


    // ����� ����� ���� ����� ��� ����� ��� �� �����
    std::optional<Command> reset(int now_ms);

    void update_position(int now_ms);

    // TODO: ����� �����, ������, ���������
};
