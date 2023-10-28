#include <functional>
class BoardInfo;
class Effect {
private:
    std::function<void(BoardInfo &)> f;

public:
    Effect(std::function<void(BoardInfo &)>);
    void activate(BoardInfo &);
    /* e.g.
    Effect* e;
    e->activate(info);
    */
};