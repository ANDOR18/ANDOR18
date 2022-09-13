#include <string>
#include <iostream>
#include "Player.h"

using namespace std;

Player::Player()
{
	name = "No Name";
}

void Player::SetName(const string& temp)
{
	if (temp!="_")
		name = temp;
}

string Player::GetName() const
{
	return name;
}

void Player::Display() const;
{
	cout<<name<<flush;
}

