#include <deck.hpp>
#include <effect.hpp>
#include <vector>
class Character {
private:
    Deck *deck;
    std::vector<Self2TargetEffect *> effects;

protected:
    Character(Deck *, std::vector<Self2TargetEffect *>);

public:
    std::vector<Self2TargetEffect *> get_effect();
    DrawPile *set_up_deck();
    virtual BoardCharacter *create_board_character(int, int) = 0;
};

class BoardCharacter {
private:
    CharacterInfo info;
    DrawPile *draw_deck;
    std::vector<Card *> cards_in_hand;
    std::vector<Self2TargetEffect *> effects;
    std::vector<int> selected;
    std::vector<Self2TargetEffect *> ATK_effects_stack;
    std::vector<Self2TargetEffect *> DEF_effects_stack;

protected:
    BoardCharacter(Character *, int, int,
                   DrawPile *); // HP, max_cards_in_hand, deck;
public:
    Pile *activate;
    const int max_cards_in_hand;
    void set_draw_deck(DrawPile* );
    bool draw_card();
    int num_deck();
    int num_hand();
    int left_HP();
    CharacterInfo get_info();
    void set_info(CharacterInfo);
    bool select_cards(bool, int,
                      int); // need to be legal or not, minimum sum, minimum
                            // num. return false only if select none
    void add_cards_to_deck(std::list<Card *>);
    std::vector<Self2TargetEffect *> get_ATK_effects_stack();
    std::vector<Self2TargetEffect *> get_DEF_effects_stack();
    SettlePile *play_selected_cards(); // YOU SHOULD CHECK NULLPTR
    Pile *be_damaged(int);             // YOU SHOULD CHECK NULLPTR
    void new_round();
    virtual void update_ATK_effect() = 0;
    virtual void update_DEF_effect() = 0;
    virtual void update_counter(std::vector<int>) = 0;
};