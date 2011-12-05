#ifndef AI_H
#define AI_H

#include <iostream>
#include <vector>
#include <map >

using std::vector;
using std::multimap;

class MoveData;

class AI
{
    public:
        virtual ~AI();

        //Assess the board and makes a move
        static void GetMove();
        //Resets the AI to intial state
        static void clean();

        static AI* Get();

        bool dontMove;

        vector<vector<MoveData> > FriendlyMoves;
        vector<vector<MoveData> > EnemyMoves;
    protected:
        AI();
    private:
        static AI* aiPtr;
        vector<vector<MoveData> >::iterator Move_it;

        /****************************
            DEBUG FUNCTIONS
        ****************************/
        void dbg_wait();



};

#endif // AI_H
