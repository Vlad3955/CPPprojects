#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

// class Cards
//==================================================================================
class Cards
{
public:
	enum SUIT
	{
		CLUBS,
		DIAMONDS,
		HEARTS,
		SPADES
	};

	enum VALUE
	{
		ACE = 1,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		JACK,
		QUEEN,
		KING
	};
	Cards(VALUE v = ACE, SUIT s = SPADES, bool cardSt = true);
	void flip();
	int getValue() const;
protected:
	friend ostream& operator<< (ostream& out, const Cards& cards);
	SUIT suit;
	VALUE cValue;
	bool cardStatus;
};
//==================================================================================

// class Hand
//==================================================================================
class Hand
{
public:
	Hand();
	virtual ~Hand();
	void Add(Cards* nCard);
	void Clear();
	int getTotal() const;
protected:
	vector<Cards*> cards;
};
//==================================================================================

// class GenericPlayer
//==================================================================================
class GenericPlayer : public Hand
{
public:
	GenericPlayer(const string& name = "");
	virtual ~GenericPlayer();
	virtual bool IsHitting() const = 0;
	bool isBusted() const;
	void Bust() const;
protected:
	friend ostream& operator<< (ostream& out, const GenericPlayer& genPlayer);
	string m_Name;
};
//==================================================================================

// class Player
//==================================================================================
class Player : public GenericPlayer
{
public:
	Player(const string& name = "");
	virtual ~Player();
	virtual bool IsHitting() const;
	void Win() const;
	void Lose() const;
	void Push() const;
};
//==================================================================================

// class House
//==================================================================================
class House : public GenericPlayer
{
public:
	House(const string& name = "House");
	virtual ~House();
	virtual bool IsHitting() const;
	void FlipFirstCard();
};
//==================================================================================

// class Deck
//==================================================================================
class Deck : public Hand
{
public:
	Deck();
	virtual ~Deck();
	void Populate();
	void Shuffle();
	void Deal(Hand& aHand);
	void AdditionalCards(GenericPlayer& genPlayer);
};
//==================================================================================

// class Game
//==================================================================================
class Game
{
public:
	Game(const vector<string>& names);
	~Game();
	void Play();
private:
	Deck deck;
	House house;
	vector<Player> players;
};
//==================================================================================