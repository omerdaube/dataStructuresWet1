//
// Created by mayan on 23-Nov-22.
//

#ifndef MIVNY1_GOALSTREEPLAYER_H
#define MIVNY1_GOALSTREEPLAYER_H
class Player;

class PointerPlayer {
private:
    Player* playerP;
public:
    PointerPlayer();
    explicit PointerPlayer(Player* playerP);
    const Player* getPlayerP() const;
    bool operator<(int iden) const;
    bool operator==(int iden) const;
    friend bool operator<(const PointerPlayer& pointerP1, const PointerPlayer& pointerP2);
    friend bool operator==(const PointerPlayer& pointerP1, const PointerPlayer& pointerP2);
    //bool operator>(const Player&) const;
};

#endif //MIVNY1_GOALSTREEPLAYER_H
