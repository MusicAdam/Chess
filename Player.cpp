#include "Player.h"
#include "Board.h"

Player* Player::p1ptr	=	NULL;
Player* Player::p2ptr	=	NULL;

Player::Player(int id)
{
	m_id = id;
	m_isValid = false;

	if(m_id == 1){
        m_forward = -1;
	}else{
        m_forward = 1;
	}
}

Player::~Player()
{
	//dtor
}


static Player* Player::One(){
	if(p1ptr == NULL){
		p1ptr = new Player(1);
	}

	return p1ptr;
}

static Player* Player::Two(){
	if(p2ptr == NULL){
		p2ptr = new Player(2);
	}

	return p2ptr;
}

static void Player::clean(){
    p1ptr   =   NULL;
    p2ptr   =   NULL;
}

int Player::forward(){
    return m_forward;
}

int Player::id(){
	return m_id;
}

int Player::controller(){
	return m_controller;
}


bool Player::valid(){
	return m_isValid;
}

void Player::setController(int ctrl){
	m_controller = ctrl;
	m_isValid = true;
}

bool Player::isHuman(){
    if(Player::Active()->controller() == Player::CONTROL_HUMAN){
        return true;
    }

    return false;
}

bool Player::isAI(){
    if(Player::Active()->controller() == Player::CONTROL_AI){
        return true;
    }

    return false;
}

bool Player::ownsPiece(int index){
    GamePiece p = Board::Get()->getGamePiece(index);
   // std::cout << "Owns piece: "
    if(Player::Active()->id() == p.Owner()->id()){

        return true;
    }

    return false;
}

Player* Player::Active()
{
    if(Player::One()->id() == Board::Get()->ActivePlayer()){
        return Player::One();
    }

    return Player::Two();
}

