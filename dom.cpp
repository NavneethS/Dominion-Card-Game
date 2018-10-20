//SMITHY FESTIVAL LABORATORY MARKET CHANCELLOR VILLAGE WOODCUTTER GARDENS THRONEROOM MONEYLENDER REMODEL ADVENTURER MINE CELLAR CHAPEL WORKSHOP FEAST
// MOAT BUREAUCRAT MILITIA SPY WITCH THIEF COUNCILROOM
// LIBRARY
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

#define COPPER 0
#define SILVER 1
#define GOLD 2
#define ESTATE 3
#define DUCHY 4
#define PROVINCE 5
#define CURSE 6
#define GARDENS 7
#define CELLAR 8
#define CHAPEL 9
#define MOAT 10
#define CHANCELLOR 11
#define VILLAGE 12
#define WOODCUTTER 13
#define WORKSHOP 14
#define BUREAUCRAT 15
#define FEAST 16
#define MILITIA 17
#define MONEYLENDER 18
#define REMODEL 19
#define SMITHY 20
#define SPY 21
#define THIEF 22
#define THRONEROOM 23
#define COUNCILROOM 24
#define FESTIVAL 25
#define LABORATORY 26
#define LIBRARY 27
#define MARKET 28
#define MINE 29
#define WITCH 30
#define ADVENTURER 31

char cardname[32][13] =
{"COPPER", "SILVER", "GOLD",
"ESTATE","DUCHY","PROVINCE","CURSE","GARDENS",
"CELLAR","CHAPEL","MOAT",
"CHANCELLOR","VILLAGE","WOODCUTTER","WORKSHOP",
"BUREAUCRAT","FEAST","MILITIA","MONEYLENDER","REMODEL","SMITHY","SPY","THIEF","THRONEROOM",
"COUNCILROOM","FESTIVAL","LABORATORY","LIBRARY","MARKET","MINE","WITCH",
"ADVENTURER"};

int costs[32] = {
0,3,6,
2,5,8,0,4,
2,2,2,
3,3,3,3,
4,4,4,4,4,4,4,4,4,
5,5,5,5,5,5,5,
6};

int supply[32] = {
60,40,30,
24,12,12,30,12,
10,10,10,
10,10,10,10,
10,10,10,10,10,10,10,10,10,
10,10,10,10,10,10,10,
10};

bool kingdom[32];
vector<int> trash;

void showSupply()
{
	cout << endl << "Supply is" << endl;
	for(int i=COPPER; i<=ADVENTURER; i++)
		if(kingdom[i])
			cout << i << "." << cardname[i] << "::" << supply[i] << "\t";
	cout << endl;
}

void initSupply()
{

	kingdom[COPPER] = kingdom[SILVER] = kingdom[GOLD] = true;
	kingdom[ESTATE] = kingdom[DUCHY] = kingdom[PROVINCE] = kingdom[CURSE] = true;

	kingdom[GARDENS] = true;
	kingdom[CELLAR] = kingdom[CHAPEL] = true;
	kingdom[CHANCELLOR] = kingdom[VILLAGE] = kingdom[WOODCUTTER] = kingdom[WORKSHOP] = true;
	kingdom[FEAST] = kingdom[REMODEL] = kingdom[MONEYLENDER] = kingdom[SMITHY] = kingdom[THRONEROOM] =  true;
	kingdom[FESTIVAL] = kingdom[LABORATORY] = kingdom[MARKET] = kingdom[MINE] = true;
	kingdom[ADVENTURER] = true;

	supply[PROVINCE]=3;
}

class Player
{
	private:
		int actions, buys, coins;
		vector<int> deck,hand,played,discard;
	public:
		Player()
		{
			int i;
			for(i=0; i<7; i++)
				deck.push_back(COPPER);
			for(i=7; i<10; i++)
				deck.push_back(ESTATE);
			hand.clear();
			played.clear();
			discard.clear();
		}
		void show();
		void shuffleDeck();
		void initTurn();
		void drawHand(int);
		void actionPhase();
		void playCard(int);
		void buyPhase();
		void cleanPhase();
		int finalScore();
};

void Player::playCard(int c)
{
	cout << "Playing " << c << "." << cardname[c] << endl;

	if(c == CELLAR)
	{
		cout << "+1 action" << endl << "Discard any no. of cards, +1 card per card discarded" << endl;
		actions += 1;
		int c,d;
		cout << "Discard how many cards? ";
		cin >> d;
		for(int j=0; j<d; j++)
		{
			cout << "Discard card no.: ";
			cin >> c;
			for(int i=0; i<hand.size(); i++)
			{
				if(c == hand[i])
				{
					discard.push_back(c);
					vector<int>::iterator it = find(hand.begin(),hand.end(), c);
					if (it != hand.end())
						hand.erase(it);
					break;
				}
			}
		}
		cout << "Discarded " << d << " cards, +" << d <<" cards" << endl;
		drawHand(d);
	}

	else if(c == CHAPEL)
	{
		cout << "Trash up to 4 cards from hand" << endl;
		int c,d;
		cout << "Trash how many cards? ";
		cin >> d;
		if(d>4) d=4;
		while(d--)
		{
			cout << "Trash card no.: ";
			cin >> c;
			for(int i=0; i<hand.size(); i++)
			{
				if(c == hand[i])
				{
					trash.push_back(c);
					vector<int>::iterator it = find(hand.begin(),hand.end(), c);
					if (it != hand.end())
						hand.erase(it);
					break;
				}
			}
		}
	}

	else if(c == MOAT)
	{
		drawHand(2);
		//May reveal from hand to be unaffected by Attack
	}

	else if(c == CHANCELLOR)
	{
		cout << "+2 coin" << endl << "May put deck into discard pile" << endl;
		coins += 2;
		char c;
		cout << "Discard deck? y/n: ";
		cin >> c;
		if (c=='y')
		{
			discard.insert(discard.end(), deck.begin(), deck.end());
			deck.clear();
		}
	}

	else if(c == VILLAGE)
	{
		cout << "+1 card" << endl << "+2 actions" << endl;
		drawHand(1);
		actions += 2;
	}

	else if(c == WOODCUTTER)
	{
		cout << "+1 buy" << endl << "+2 coin" << endl;
		buys += 1;
		coins += 2;
	}

	else if(c == WORKSHOP)
	{
		cout << "Gain a card costing upto 4" << endl;
		int c;
		cout << "You can gain:" << endl;
		for(int i=COPPER; i<=ADVENTURER; i++)
		{
			if (kingdom[i] && supply[i] && costs[i]<=4)
				cout << i << "." << cardname[i] << "::" << costs[i] << "\t";
		}
		cout <<  endl << "Gain card no. ";
		cin >> c;
		discard.push_back(c);
		supply[c]--;
	}

	else if(c == BUREAUCRAT)
	{
		deck.push_back(SILVER);
		//Other players reveal a Victory card from hand and put it on deck (or reveal hand with none)
	}

	else if(c == FEAST)
	{
		cout << "Trash this card and gain a card costing upto 5" << endl;
		int c;
		cout << "You can gain:" << endl;
		for(int i=COPPER; i<=ADVENTURER; i++)
		{
			if (kingdom[i] && supply[i] && costs[i] <= 5)
				cout << i << "." << cardname[i] << "::" << costs[i] << "\t";
		}
		cout << endl << "Gain card no. ";
		cin >> c;
		discard.push_back(c);
		supply[c]--;
	}

	else if(c == MILITIA)
	{
		coins += 2;
		//Other players discard down to 3 cards in hand
	}

	else if(c == MONEYLENDER)
	{
		cout << "Trash a copper from hand. If you do, +3 coin" << endl;
		for(int i=0; i<hand.size(); i++)
		{
			if (hand[i] == COPPER)
			{
				trash.push_back(COPPER);
				vector<int>::iterator it = find(hand.begin(),hand.end(), COPPER);
				if (it != hand.end())
					hand.erase(it);
				cout << "Trashed Copper" << endl;
				coins += 3;
				break;
			}
		}
	}

	else if(c == REMODEL)
	{
		cout << "Trash a card from hand. Gain a card costing upto 2 more" << endl;
		int c,d;
		cout << "Trash card no.: ";
		cin >> c;
		for(int i=0; i<hand.size(); i++)
		{
			if (hand[i] == c)
			{
				trash.push_back(c);
				vector<int>::iterator it = find(hand.begin(),hand.end(), c);
				if (it != hand.end())
					hand.erase(it);
				break;
			}
		}

		cout << "You can gain:" << endl;
		for(int i=COPPER; i<=ADVENTURER; i++)
		{
			if (kingdom[i] && supply[i] && costs[i] <= 2+costs[c])
				cout << i << "." << cardname[i] << "::" << costs[i] << "\t";
		}
		cout <<  endl << "Gain card no. ";
		cin >> d;
		discard.push_back(d);
		supply[d]--;
	}

	else if(c == SMITHY)
	{
		drawHand(3);
	}

	else if(c == SPY)
	{
		drawHand(1);
		actions += 1;
		//All players reveal top card of deck and either discards it or puts it back, your choice.
	}

	else if(c == THIEF)
	{
		//Other players reveal the top 2 cards of deck. If any Treasure cards revealed, choose 1 to trash. May 				gain any/all of these trashed cards. Discard the other revealed cards.
	}

	else if(c == THRONEROOM)
	{
		int c;
		bool f=false;
		for(int i=0; i<hand.size(); i++)
		{
			if(hand[i]>=CELLAR && hand[i]<=ADVENTURER)
			{
				cout << hand[i] << "." << cardname[hand[i]] << " ";
				f = true;
			}
		}
		if(!f)
			cout << "No actions to play twice!" << endl;
		else
		{
			cout << "Play card no. twice: ";
			cin >> c;
			if(c==FEAST)
				trash.push_back(c);
			else
				played.push_back(c);

			vector<int>::iterator it = find(hand.begin(),hand.end(), c);
			if (it != hand.end())
				  hand.erase(it);

			playCard(c);
			playCard(c);
		}
	}

	else if(c == COUNCILROOM)
	{
		drawHand(4);
		buys += 1;
		//Other players draw a card
	}

	else if(c == FESTIVAL)
	{
		actions += 2;
		buys += 1;
		coins += 2;
	}

	else if(c == LABORATORY)
	{
		drawHand(2);
		actions += 1;
	}

	else if(c == LIBRARY)
	{
		//Draw until 7 cards in hand. May set aside Action cards drawn, discard this set after drawing
		drawHand(7-hand.size());
	}

	else if(c == MARKET)
	{
		drawHand(1);
		actions += 1;
		buys += 1;
		coins += 1;
	}

	else if(c == MINE)
	{
		cout <<  "Trash a Treasure card from hand. Gain a Treasure card costing upto 3 more into hand" << endl;
		char c;
		int d;
		for(int i=0; i<hand.size(); i++)
		{
			if (hand[i]>=COPPER && hand[i]<=GOLD)
			{
				cout << "Trash " << cardname[hand[i]] << "? y/n: ";
				cin >> c;
				if(c=='y')
				{
					cout << "You can gain to hand:" << endl;
					for(int j=COPPER; j<=GOLD; j++)
					{
						if (supply[j] && costs[j]<=3+costs[hand[i]])
							cout << j << "." << cardname[j] << "::" << costs[j] << "\t";
					}
					cout <<  endl << "Gain card no. ";
					cin >> d;
					trash.push_back(hand[i]);
					hand[i] = d;
					supply[d]--;
					break;
				}
			}
		}
	}

	else if(c == WITCH)
	{
		drawHand(2);
		//Other players gain a Curse
	}

	else if(c == ADVENTURER)
	{
		cout << "Reveal cards from deck until 2 Treasure cards. Put these in hand and discard the others" << endl;
		bool done=false;
		int t=0;
		while(!done)
		{
			if(deck.empty() || t==2)
				done=true;
			else if(deck.back()>=COPPER && deck.back()<=GOLD)
			{
				cout << "Revealed and kept" << cardname[deck.back()] << endl;;
				t++;
				hand.push_back(deck.back());
				deck.pop_back();
			}
			else
			{
				cout << "Revealed and discarded" << cardname[deck.back()] << endl;
				discard.push_back(deck.back());
				deck.pop_back();
			}
		}
	}

	show();
}

void Player::show()
{
	cout << endl << "---------------------------------------------------------------------------" << endl;
	cout << actions << " actions, " << buys << " buys, " << coins << " coins" << endl;
	cout << "Deck:\t\t";
	for(int i=0; i<deck.size(); i++)
		cout << cardname[deck[i]] << " ";
	cout << endl;

	cout << "Hand:\t\t";
	for(int i=0; i<hand.size(); i++)
		cout << cardname[hand[i]] << " ";
	cout << endl;

	cout << "Played:\t\t";
	for(int i=0; i<played.size(); i++)
		cout << cardname[played[i]] << " ";
	cout << endl;

	cout << "Discard:\t";
	for(int i=0; i<discard.size(); i++)
		cout << cardname[discard[i]] << " ";
	cout << endl;

	cout << "Trash:\t\t";
	for(int i=0; i<trash.size(); i++)
		cout << cardname[trash[i]] << " ";
	cout << endl << "---------------------------------------------------------------------------" << endl << endl;
}

void Player::shuffleDeck()
{
	cout << "Shuffled..." << endl;
	random_shuffle(deck.begin(), deck.end());
}

void Player::drawHand(int n)
{
	cout << "Drawing " << n << "..." << endl;
	while(n--)
	{
		if (!deck.empty())
		{
			hand.push_back(deck.back());
			deck.pop_back();
		}
		else if (deck.empty() && !discard.empty())
		{
			deck = discard;
			discard.clear();
			shuffleDeck();
			drawHand(1);
		}
		else if (deck.empty() && discard.empty())
		{
			cout << "Not enough cards!" << endl;
			return;
		}
	}
}

void Player::initTurn()
{
	actions = buys = 1;
	coins=0;
}

void Player::actionPhase()
{
	int c;
	cout << "Action Phase:- " << actions << " actions" << endl;
	while(actions)
	{
		cout << "You can play:" << endl;
		bool f=false;
		for(int i=0; i<hand.size(); i++)
		{
			if(hand[i]>=CELLAR && hand[i]<=ADVENTURER)
			{
				cout << hand[i] << "." << cardname[hand[i]] << " ";
				f = true;
			}
		}
		if(!f)
		{
			cout << "Nothing!" << endl;
			return;
		}
		else
		{
			cout << endl << "Play card no. ";
			cin >> c;
			if(c==FEAST)
				trash.push_back(c);
			else
				played.push_back(c);

			vector<int>::iterator it = find(hand.begin(),hand.end(), c);
			if (it != hand.end())
				  hand.erase(it);

			actions--;
			playCard(c);
		}
	}
}

void Player::buyPhase()
{
	int c,tmp;
	for(int i=0; i<hand.size(); i++)
	{
		tmp = hand[i];
		if (tmp>=COPPER && tmp<=GOLD)
		{
			played.push_back(tmp);
			coins += tmp+1;
		}
	}

	hand.erase(remove(hand.begin(), hand.end(), COPPER), hand.end());
	hand.erase(remove(hand.begin(), hand.end(), SILVER), hand.end());
	hand.erase(remove(hand.begin(), hand.end(), GOLD), hand.end());

	cout << "Buy Phase:- " << buys << " buys, " << coins << "coins" << endl;
	while(buys)
	{
		cout << "You can buy:" << endl;
		bool f=false;
		for(int i=COPPER; i<=ADVENTURER; i++)
		{
			if (kingdom[i] && supply[i] && costs[i] <= coins)
			{
				cout << i << "." << cardname[i] << "::" << costs[i] << "\t";
				f=true;
			}
		}
		if(!f)
		{
			cout << "Nothing!" << endl;
			return;
		}
		else
		{
			cout << endl << "Buy card no. ";
			cin >> c;
			discard.push_back(c);
			coins -= costs[c];
			supply[c]--;
			buys--;
		}
	}
}

void Player::cleanPhase()
{
	cout << "CleanUp Phase:- ";
	discard.insert(discard.end(), played.begin(), played.end());
	played.clear();
	discard.insert(discard.end(), hand.begin(), hand.end());
	hand.clear();
	drawHand(5);
	initTurn();
}

int Player::finalScore()
{
	int s=0;
	deck.insert(deck.end(), hand.begin(), hand.end());
	hand.clear();
	deck.insert(deck.end(), played.begin(), played.end());
	played.clear();
	deck.insert(deck.end(), discard.begin(), discard.end());
	discard.clear();
	show();
	for(int i=0; i<deck.size(); i++)
	{
		if (deck[i] == CURSE)
			s -= 1;
		else if (deck[i] == ESTATE)
			s += 1;
		else if (deck[i] == DUCHY)
			s += 3;
		else if (deck[i] == PROVINCE)
			s += 6;
		else if (deck[i] == GARDENS)
			s += deck.size()/10;
	}
	return s;
}

bool isEnd()
{
	int p=0;
	if(supply[PROVINCE]==0)
		return true;
	for(int i=COPPER; i<=ADVENTURER; i++)
	{
		if(kingdom[i] && supply[i]==0)
			p++;
		if(p==3)
			return true;
	}
	return false;
}

int main()
{
	int i=0;
	srand(time(NULL));
	Player player1, player2;
	trash.clear();
	initSupply();

	player1.shuffleDeck();
	player1.drawHand(5);
	player1.initTurn();
	player1.show();

	while(1)
	{
		cout << endl << "Player1 : Turn Number " << i++ << endl;
		player1.actionPhase();
		player1.show();
		player1.buyPhase();
		player1.show();
		player1.cleanPhase();
		player1.show();
		showSupply();

		if(isEnd())
			break;
	}
	cout << "Final score: " << player1.finalScore() << endl;
	return 0;
}

