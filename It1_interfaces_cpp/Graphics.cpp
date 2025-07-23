#include "Graphics.hpp"
#include <iostream>

Graphics::Graphics() {}

void Graphics::reset() {
    // איפוס גרפיקה
}

void Graphics::reset(int now_ms) {
    // איפוס גרפיקה לפי זמן
}

void Graphics::draw() {
    // לצורך דוגמה, נדפיס משהו
    std::cout << "Drawing piece...\n";
}
