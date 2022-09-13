#ifndef PLAYER_H
#define PLAYER_H
#include <string>

using namespace std;

class Player
{
	public:
		Player();
		void SetName(const string&);
		string GetName() const;
		void Display() const;
		
	private:
		string name;
};

class BasketballPlayer : public Player
{
	public:
		void Shots(const int);
		void Shotsmade(const int);
	
	private:
		int shotpct;
};




#endif
