#pragma once
#include <string>
#include <vector>

//����� ����� ������
class Command {
public:
    int timestamp;               // ��� ���������� ��� ����� �����
    std::string piece_id;        // ���� ����
    std::string type;            // ��� ������: "Move", "Jump" ���'
    std::vector<std::string> params; // ������� ������ (���� �����)

    Command() = default;
    Command(int ts, const std::string& id, const std::string& t, const std::vector<std::string>& p)
        : timestamp(ts), piece_id(id), type(t), params(p) {
    }
};