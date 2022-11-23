#include <stdio.h>

#include "Team.h"
#include "PointerPlayer.h"
#include "Player.h"
#include "AVL.h"
#include "DoublyLinkedList.h"
int main(){
//    AVL<Player, int> a;
//    Team t = Team(1,0);
//    Player p = Player(1, 0, 0, false, &t);
//    Player p2 = Player(2, 0, 0, false, &t);
//    a.add(p);
//    a.add(p2);
//    Team * t = new Team(1,1);
//    Player* p = new Player(1,0,0, false,t);
//    Player* p2 = new Player(2,0,0, false,t);
//    Player* p3 = new Player(3,0,0, false,t);
//    DoublyLinkedList dl = DoublyLinkedList();
//    dl.addNext(dl.getHead(), PointerPlayer(p));
//    Node* hkhkhkh = dl.addNext(dl.getHead(), PointerPlayer(p2));
//    dl.addPrev(hkhkhkh, PointerPlayer(p3));
    AVL<int> a = AVL<int>();
    a.add(2);
    a.remove(2);

    return 0;
}