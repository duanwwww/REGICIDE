#include <deck.hpp>
#include <effect.hpp>
#include <vector>
class Character {
private:
    Deck *deck;
    Self2TargetEffect *effect;

protected:
    Character(Deck *, Self2TargetEffect *);

public:
    Self2TargetEffect *get_effect();
    DrawPile *set_up_deck();
    virtual BoardCharacter *create_board_character(int, int) = 0;
};

class BoardCharacter {
private:
    CharacterInfo info;
    DrawPile *draw_deck;
    std::vector<Card *> cards_in_hand;
    Self2TargetEffect *effect;
    std::vector<int> selected;

protected:
    BoardCharacter(Character *, int, int,
                   DrawPile *); // HP, max_cards_in_hand, deck;
public:
    Pile *activate;
    const int max_cards_in_hand;
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
    SettlePile *play_selected_cards(); // YOU SHOULD CHECK NULLPTR
    Pile *be_damaged(int);             // YOU SHOULD CHECK NULLPTR
    virtual Self2TargetEffect *get_effect() = 0;
    virtual void update_counter(std::vector<int>) = 0;
};