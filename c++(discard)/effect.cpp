#include <effect.hpp>
Self2TargetEffect::Self2TargetEffect(
    std::function<Self2TargetInfo(Self2TargetInfo)> _f, int _round_counter) {
    this->f = _f;
    this->round_counter = _round_counter;
}

Self2TargetInfo Self2TargetEffect::activate(Self2TargetInfo _info) {
    if (this->round_counter <= 0)
        return _info;
    return this->f(_info);
}

void Self2TargetEffect::new_round() {
    if (this->round_counter != 0)
        this->round_counter--;
}

bool Self2TargetEffect::still_activate() {
    return this->round_counter > 0;
}