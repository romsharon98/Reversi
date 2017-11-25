/*aviv shisman 206558157
 */

#include <iostream>
#include "GameFlow.h"
/*
 * the constructor
 * screen - we will use the methods show and size
 * manger- will be used to get the arr of cells and set new value for cells
 * players - a pointer arr to the players
 * current signifies who is the current player
 * numOf pieces looks for the ending of the game
 */
GameFlow::GameFlow(GameShower* s, CellManger* c, Rule *r, Player**p) {
    screen=s;
    manger=c;
    rule=r;
    players=p;
    current=0;
    numOfPieces=4;
}
/*
 * play method uses to start the game
 */
void GameFlow::play() {
    do {
        screen->show();

        Point **points = new Point *[screen->getSize() * screen->getSize()];

        //going trough all the cells in the array and checking who is valid place to set piece
        int i = 0, j = 0, k = 0;
        for (i = 1; i <= screen->getSize(); i++) {
            for (j = 1; j <= screen->getSize(); j++) {
                if (rule->check(manger->getArr(), i, j, players[current]->getSymbol())) {
                    points[k] = new Point(i, j);
                    k++;
                }
            }
        }
        if (k == 0) {
            cout<<"No possible move for:"<<players[current]->getSymbol()<<endl;
            current++;
            if(current==2){current =0; }
            for (int i = 0; i < k; i++) {
                delete (points[i]);
            }
            delete (points);
            continue;
        }
        Point *a = players[current]->oneMove(points, k);
        if (players[current]->getSymbol() == 'x') {
            manger->setBlack(a->getX(), a->getY());
        } else {
            manger->setWhite(a->getX(), a->getY());
        }
        numOfPieces++;
        //applying the rule: flipping the appropriate pieces
        rule->apply(manger->getArr(),a->getX(),a->getY(),players[current]->getSymbol());
        current++;

        if (current == 2) {
            current = 0;
        }

        delete (a);
        for (int i = 0; i < k; i++) {
            delete (points[i]);
        }
        delete (points);
    }while(numOfPieces<screen->getSize()*screen->getSize());

    cout<<"game is over count who has the most pieces"<<endl;
}