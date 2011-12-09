#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
class Piece;
class Player
{
	public:
		enum {
			CONTROL_HUMAN,	//Human control
			CONTROL_AI //Computer control
		};

		virtual ~Player();

		static Player* One();
		static Player* Two();

        //Resets players to initial state
		static void clean();

		//Gets active player
		static Player* Active();


        //Private member access
		int id();
		int controller();
		int forward();

		//State identifiers
		bool isHuman();
		bool isAI();
		bool OwnsPiece(int index);
		bool OwnsPiece(Piece* piece);

        /* DELETE? */
		bool valid();
		/*    **    */

		void setController(int ctrl);
	protected:
		Player(int id);
	private:
		static Player* p1ptr;
		static Player* p2ptr;



		int m_id;
		int m_controller;
		int m_forward;

		bool m_isValid; //True when all the player data has been set, hence we have a valid player structure
};

#endif // PLAYER_H
