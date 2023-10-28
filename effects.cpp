#include <effects.hpp>
Effect::Effect(std::function<void(BoardInfo &)> _f) {
    this->f = _f;
}

void Effect::activate(BoardInfo &_board_info) {
    this->f(_board_info);
}