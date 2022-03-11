#include "BlackJack.h"


// class Cards
//==================================================================================
Cards::Cards(VALUE v, SUIT s, bool cardSt) : cValue(v), suit(s), cardStatus(cardSt) {}
void Cards::flip()
{
	cardStatus = !cardStatus;
}
int Cards::getValue() const
{
	int value = 0;
	if (cardStatus)
	{
		value = cValue;
		if (value > 10)
		{
			value = 10;
		}
	}
	return value;
}


ostream& operator<< (ostream& out, const Cards& aCard)
{
	const string cardVal[] = { "0", "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Qeen", "King" };
	const string cardSuits[] = { "Clubs", "Diamonds", "Hearts", "Spades" };
	if (aCard.cardStatus)
	{
		out << cardVal[aCard.cValue] << " " << cardSuits[aCard.suit];
	}
	else
	{
		out << "XX";
	}
	return out;
}
//==================================================================================

// class Hand
//==================================================================================
Hand::Hand()
{
	cards.reserve(7);
}
Hand::~Hand()
{
	Clear();
}
void Hand::Add(Cards* nCard)
{
	cards.push_back(nCard);
}
void Hand::Clear()
{
	vector<Cards*>::iterator it = cards.begin();
	for (it = cards.begin(); it != cards.end(); ++it)
	{
		delete *it;
		*it = nullptr;
	}
	cards.clear();
}
int Hand::getTotal() const
{
	if (cards.empty())
	{
		return 0;
	}

	if (cards[0]->getValue() == 0)
	{
		return 0;
	}

	int total = 0;

	vector<Cards*>::const_iterator it;
	for (it = cards.begin(); it != cards.end(); ++it)
	{
		total += (*it)->getValue();
	}

	bool isAce = false;
	for (it = cards.begin(); it != cards.end(); ++it)
	{
		if ((*it)->getValue() == Cards::ACE)
		{
			isAce = true;
		}
	}

	if (isAce && total <= 11)
	{
		total += 10;
	}

	return total;
}
//==================================================================================

// class GenericPlayer
//==================================================================================
GenericPlayer::GenericPlayer(const string& n) : m_Name(n) {}
GenericPlayer::~GenericPlayer() {}
bool GenericPlayer::isBusted() const
{
	return (getTotal() > 21);
}
void GenericPlayer::Bust() const
{
	cout << m_Name << " busts" << endl;
}


ostream& operator<< (ostream& out, const GenericPlayer& genPlayer)
{
	out << genPlayer.m_Name << ":\t";
	vector<Cards*>::const_iterator pCard;
	if (!genPlayer.cards.empty())
	{
		for (pCard = genPlayer.cards.begin(); pCard != genPlayer.cards.end(); ++pCard)
		{
			out << *(*pCard) << "\t";
		}

		if (genPlayer.getTotal() != 0)
		{
			cout << "(" << genPlayer.getTotal() << ")";
		}
	}
	else
	{
		out << "<empty>";
	}
	return out;
}
//==================================================================================


// class Player
//==================================================================================
Player::Player(const string& n) : GenericPlayer(n) {}
Player::~Player() {}
bool Player::IsHitting() const
{
	cout << m_Name << ", do you want a hit? (Y/N): ";
	char response;
	cin >> response;
	return (response == 'y' || response == 'Y');

}
void Player::Win() const
{
	cout << "Player " << m_Name << " wins!\n" << endl;
}
void Player::Lose() const
{
	cout << "Player " << m_Name << " loses!\n" << endl;
}
void Player::Push() const
{
	cout << "Player " << m_Name << " pushes!\n" << endl;
}
//==================================================================================


// class House
//==================================================================================
House::House(const string& n) : GenericPlayer(n) {}
House::~House() {}
bool House::IsHitting() const
{
	return (getTotal() <= 16);
}
void House::FlipFirstCard()
{
	if (!(cards.empty()))
	{
		cards[0]->flip();
	}
	else
	{
		cout << "No card to flip!\n";
	}
}
//==================================================================================

// class Deck
//==================================================================================
Deck::Deck()
{
	cards.reserve(52);
	Populate();
}
Deck::~Deck() {}
void Deck::Populate()
{
	for (int s = Cards::CLUBS; s < Cards::SPADES; s++)
	{
		for (int v = Cards::ACE; v < Cards::KING; v++)
		{
			Add(new Cards(static_cast<Cards::VALUE>(v), static_cast<Cards::SUIT>(s)));
		}
	}
}
void Deck::Shuffle()
{
	random_shuffle(cards.begin(), cards.end());
}
void Deck::Deal(Hand& aHand)
{
	if (!cards.empty())
	{
		aHand.Add(cards.back());
		cards.pop_back();
	}
	else
	{
		cout << "Out of cards. Unable to deal.";
	}
}
void Deck::AdditionalCards(GenericPlayer& genPlayer)
{
	cout << endl;
	while (!(genPlayer.isBusted()) && genPlayer.IsHitting())
	{
		Deal(genPlayer);
		cout << genPlayer << endl;

		if (genPlayer.isBusted())
		{
			genPlayer.Bust();
		}
	}
}
//==================================================================================

// class Game
//==================================================================================
Game::Game(const vector<string>& names)
{
	vector<string>::const_iterator pName;
	for (pName = names.begin(); pName != names.end(); ++pName)
	{
		players.push_back(Player(*pName));
	}

	srand(static_cast<unsigned int>(time(0)));
	deck.Populate();
	deck.Shuffle();
}
Game::~Game() {}
void Game::Play()
{
	vector<Player>::iterator pPlayer;
	for (int i = 0; i < 2; i++)
	{
		for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
		{
			deck.Deal(*pPlayer);
		}
		deck.Deal(house);
	}

	house.FlipFirstCard();

	for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
	{
		cout << *pPlayer << endl;
	}
	cout << house << endl;

	for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
	{
		deck.AdditionalCards(*pPlayer);
	}

	house.FlipFirstCard();
	cout << endl << house;

	deck.AdditionalCards(house);

	if (house.isBusted())
	{
		for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
		{
			if (!(pPlayer->isBusted()))
			{
				pPlayer->Win();
			}
		}
	}
	else
	{
		for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
		{
			if (!(pPlayer->isBusted()))
			{
				if (pPlayer->getTotal() > house.getTotal())
				{
					pPlayer->Win();
				}
				else if (pPlayer->getTotal() < house.getTotal())
				{
					pPlayer->Lose();
				}
				else
				{
					pPlayer->Push();
				}
			}
		}
	}

	for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
	{
		pPlayer->Clear();
	}
	house.Clear();
}
//==================================================================================