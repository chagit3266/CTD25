#pragma once
#include "graphics.hpp"
#include <filesystem>
#include <memory>
#include <tuple>
#include <map>
#include <string>

//����� ������ ��� ����� ���� ����
// ����� ������ sprite ����� ������, ����� ���� Graphics.

class GraphicsFactory {
public:
    std::shared_ptr<Graphics> load(
        const std::filesystem::path& sprites_dir,
        const std::map<std::string, std::string>& cfg,
        const std::pair<int, int>& cell_size
    );
};
