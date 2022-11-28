#include <stdio.h>

#include "Team.h"
//#include "PointerPlayer.h"
#include "Player.h"
#include "AVL.h"
#include "worldcup23a1.h"
//#include "DoublyLinkedList.h"
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
    world_cup_t wc;
    wc.add_team(1, 0);
    wc.add_team(5, 0);
    wc.add_player(1,1,5,100,2, false);
    wc.add_player(2,1,9,1,2, false);
    wc.add_player(3,5,9,1,2, false);
    //wc.unite_teams(1,5,1);
    //int r = 0;
//    wc.wc.add_team((2, 0);
//    wc.wc.add_team((3, 0);
//    wc.wc.add_team((4, 0);
//    wc.wc.add_team((15, 0);
//    wc.wc.add_team((233, 0);
//    wc.wc.add_team((444, 0);
//    wc.remove_team(2);
//    wc.remove_team(3);
//    wc.remove_team(4);




//    wc.add_player(3,5,5,50,2, false);
//    wc.add_player(4,5,5,1,2, false);
//    wc.add_player(5,5,5,1,2, true);
//    wc.add_player(6,5,5,1,2, false);
//    wc.add_player(7,5,5,1,2, false);
//    wc.add_player(8,5,5,1,2, false);
//    wc.add_player(9,5,5,1,2, false);
//    wc.add_player(10,5,5,1,2, false);
//    wc.add_player(11,5,5,1,2, false);
//    wc.add_player(21,1,5,2,2, false);
//    wc.add_player(22,1,5,2,2, false);
//    wc.add_player(23,1,5,2,2, true);
//    wc.add_player(23,1,5,2,2, false);
//    wc.add_player(25,1,5,2,2, false);
//    wc.add_player(24,1,5,2,2, false);
//    wc.add_player(26,1,5,800,4, false);
//    wc.add_player(27,1,5,800,4, false);
//    wc.add_player(28,1,5,2,2, false);
//    wc.add_player(29,1,5,2,2, false);
//    wc.add_player(41,1,5,2,2, false);
//    wc.add_player(42,1,5,2,2, false);
//    wc.add_player(34,1,5,2,2, false);
//    wc.add_player(54,1,5,2,2, false);
//    wc.add_player(64,1,5,2,2, false);
//    wc.play_match(1,5);
//    int r = wc.get_top_scorer(1).ans();
//    printf("%d", r);
//    int y = wc.get_num_played_games(54).ans();



//    wc.add_player((3,5,5,9,2, false);
//    wc.wc.add_player((4,5,5,8,2, false);
//    wc.wc.add_player((5,5,5,7,2, false);
//    wc.wc.add_player((6,5,5,6,2, false);
//    wc.wc.add_player((7,5,5,5,2, false);
//    wc.wc.add_player((8,5,5,4,2, false);
//    wc.wc.add_player((9,5,5,3,2, false);
//    wc.wc.add_player((10,5,5,2,2, false);
//    wc.wc.add_player((11,5,5,1,2, false);
    //wc.remove_player(11);
    //AVL<int> a = AVL<int>();
    //a.add(2);
    //a.remove(2);

    int a = 3;
    int b = 4;
    int c = 5;
    DoublyLinkedList<int>* lp = new DoublyLinkedList<int>();
    lp->addToEnd(a);
    lp->addToBeginning(b);
    lp->addAfter(c);
    lp->removeFromBeginning();
    lp->removeFromEnd();
    lp->removeFromBeginning();
    lp->addAfter(2);


//    wc.add_team( 1, 10000);
//    wc.add_team( 2, 20000);
//    wc.add_team( 3, 30000);
//    wc.add_team( 4, 40000);
//    wc.add_player( 1001, 1 ,10, 0 ,0, false);
//    wc.add_player( 1002, 1, 10 ,0 ,0, false);
//    wc.add_player( 1003 ,1 ,10 ,0 ,0, false);
//    wc.add_player( 1004 ,1 ,10 ,0 ,2, false);
//    wc.add_player( 1005 ,1 ,10, 0, 0 ,false);
//    wc.add_player( 1006, 1, 10 ,4 ,3,false);
//    wc.add_player( 1007 ,1 ,10, 0 ,0 ,false);
//    wc.add_player( 1008 ,1, 10, 0 ,0 ,true);
//    wc.add_player( 1009 ,1, 10, 0, 0, false);
//    wc.add_player( 1010 ,1 ,10, 0, 0 ,false);
//    wc.add_player( 1011 ,1 ,10 ,0, 0 ,false);
//    wc.add_player( 1012, 1 ,10 ,0 ,0, false);
//    wc.add_player( 2001 ,2 ,20 ,0 ,0 ,false);
//    wc.add_player( 2002 ,2 ,20 ,0, 0 ,false);
//    wc.add_player( 2003 ,2 ,20 ,0 ,0 ,false);
//    wc.add_player( 2004 ,2 ,20, 0, 0, false);
//    wc.add_player( 2005 ,2 ,20 ,0, 0, false);
//    wc.add_player( 2006 ,2, 20 ,0, 0 ,false);
//    wc.add_player( 2007 ,2 ,20 ,0 ,0 ,false);
//    wc.add_player( 2008 ,2 ,20 ,6 ,4 ,true);
//    wc.add_player( 2009 ,2 ,20 ,0 ,0 ,false);
//    wc.add_player( 2010 ,2, 0 ,0, 0, false);
//    wc.add_player( 2011,2 ,20 ,0 ,0 ,false);
//    wc.add_player( 3001 ,3 ,30 ,0, 0, false);
//    wc.add_player( 3002 ,3 ,30 ,0 ,0 ,false);
//    wc.add_player( 3003 ,3 ,30 ,0, 0 ,false);
//    wc.add_player( 3004 ,3 ,30, 0, 0 ,false);
//    wc.add_player( 3005, 3, 30 ,2 ,0 ,false);
//    wc.add_player( 3006, 3 ,30 ,0 ,0, false);
//    wc.add_player( 3007 ,3 ,30 ,0 ,0, false);
//    wc.add_player( 3008, 3 ,30 ,0 ,0 ,false);
//    wc.add_player( 3009, 3, 30 ,0 ,2 ,false);
//    wc.add_player( 3010 ,3 ,30 ,0 ,0 ,true);
//    wc.add_player( 3011 ,3 ,30, 0, 0, true);
//    wc.add_player( 4001, 4 ,2 ,1 ,2 ,false);
//    wc.add_player( 4002 ,4 ,2 ,2 ,2, false);
//    int x1 = wc.get_top_scorer(2).ans();
//    int x2 = wc.get_top_scorer(-1).ans();
//    int x3 = wc.get_top_scorer(5).ans();
//    int z1 = wc.get_all_players_count(5).ans();
//    int z2 = wc.get_all_players_count(-2).ans();
//    int* arr;
//    arr = new int[50];
//    wc.get_all_players(-1, arr);
//    for(int i = 0; i<wc.get_all_players_count(-1).ans();i++)
//        printf("%d,", arr[i]);
//    delete arr;
    return 0;
}