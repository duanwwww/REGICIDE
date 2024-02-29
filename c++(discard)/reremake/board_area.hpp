#pragma once
#include <vector>
#include <iostream>
class Character;
class StartRoundEffect;
class SkillEffect;
class SelectNextEffect;
class Group{
public:
    std::vector<Character*> characters;
    int current_character;
    Group(std::vector<Character*> _characters);
    void add_character(Character* _character);
    void add_character(Character* _character, int index);
    void set_next_character();
    void switch_to_next_character();
};

enum State{
    StartRound = 0,
    DefenceBuffUpdate,
    UseSkill,
    PlayCard,
    SelectTarget,
    DealEffect,
    DealDamage,
    JudgeKill,
    JudgeWin,
    AttackBuffUpdate,
    SkillCounterUpdate,
    SwitchToNext,
};

class BoardArea{
public:
    std::vector<Group*> groups;
    int current_group;
    int current_state;
    StartRoundEffect* default_start_round_effect;
    std::vector<StartRoundEffect*> start_round_effects;
    std::vector<std::string> forbidden_effect;
    SkillEffect* skill_effect;
    SelectNextEffect* select_next_effect, *default_select_next_effect;
};