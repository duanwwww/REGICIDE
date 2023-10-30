#include <card.hpp>
#include <functional>
struct CharacterInfo {
    int HP, ATK_buff, DEF_buff, ATK_debuff, DEF_debuff, ATK_coefficient,
        DEF_coefficient;
};

struct Self2TargetInfo {
    CharacterInfo self, target;
    SuitList available;
};

class Self2TargetEffect {
private:
    std::function<Self2TargetInfo(Self2TargetInfo)> f;
    int round_counter;

public:
    Self2TargetEffect(std::function<Self2TargetInfo(Self2TargetInfo)>, int);
    Self2TargetInfo activate(Self2TargetInfo);
    void new_round();
    bool still_activate();
};