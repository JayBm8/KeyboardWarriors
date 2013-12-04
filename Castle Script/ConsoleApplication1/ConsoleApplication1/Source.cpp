#include <ctime>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main()
{
ExampleStart:

	srand (time(NULL));   //initialises the randomizer for later use

	int input;            //this variable SHOULD be fine for all of the inputs the player will ever type into this game. Don't quote me on that
	cout << "This is an example build of how a battle phase will play out in this\ntext-based RPG. Please type any character and enter to continue.\n";
	cin >> input;


	int playerBaseHP = 200;             //stores all the information for the characters base stats,
	int playerBaseStrength = 50;        //stat boosts from gear and their total stats, which will be
	int playerBaseDefence = 50;         //used in damage calculation

	int playerGearHP = 0;
	int playerGearStrength = 0;
	int playerGearDefence = 0;

	int playerHP = playerBaseHP + playerGearHP;
	int playerStrength = playerBaseStrength + playerGearStrength;
	int playerDefence = playerBaseDefence + playerGearDefence;

	int monsterHP = 0;                    //monsters of the same type will all have the same stat values,
	int monsterStrength = 0;              //but I thought it would be easier to have this as a general group of 
	int monsterDefence = 0;               //monster stats and changing them according to the monster encountered, within the battle phase

    string monsterName [3] = {"Bat", "Rat", "Wolf"};         //this is a string array including 3 names of the different monsters that can be encountered
	                                                         //on this floor (held as {0}, {1} and {2} as opposed to 1, 2 and 3

	int randomMonsterSelection = rand() % 3;                 //this is the random number generator (generates numbers from 0 to 2)

	string randomMonsterName = monsterName[randomMonsterSelection];     //just a string to hold the outcome of the random number generator

MonsterEncounter:

	cout << "You have encountered a " << randomMonsterName << ", how do you wish to proceed?\n";    //the monster has been chosen and the player is prompted
	cout << "1. Attack  2. Run\n";
	cin >> input;

	switch(input)              //begins a switch selection for the user to choose
	{
	case 1:                                //if the user selects to fight, this if statement will find which monster they are fighting
		if (randomMonsterName == "Bat")    //and will set that monsters stats accordingly
		{
			monsterHP = 150;
			monsterStrength = 50;
			monsterDefence = 30;
		}
		else if (randomMonsterName == "Rat")
		{
			monsterHP = 100;
			monsterStrength = 50;
			monsterDefence = 30;
		}
		else if (randomMonsterName == "Wolf")
		{
			monsterHP = 150;
			monsterStrength = 60;
			monsterDefence = 10;
		}
		else
		{
			cout << "The monsters name was not any of the available options, something REALLY screwed up";
		}

BattleStart:
		do
		{
			int monsterDamage = monsterStrength - 0.1 * playerDefence;        //dattle damage is calculated by the attackers total strength stat minus 10% of 
            int playerDamage = playerStrength - 0.1 * monsterDefence;         //the defenders defence. we can change this at any time which will no doubt happen

			cout << "Your health is " << playerHP << ". The " << randomMonsterName << "'s health is " << monsterHP << ".\nHow do you wish to proceed?\n";
			cout << "1. Attack  2. Heal  3. Run\n";
			cin >> input;
			if (input = 1)
			{
				monsterHP = monsterHP - playerDamage;
				playerHP = playerHP - monsterDamage;
				goto BattleStart;
				break;
			}
			else if (input = 2)
			{
				playerHP = playerHP + 50;
				playerHP = playerHP - monsterDamage;
				goto BattleStart;
				break;
			}
			else if (input = 3)
			{
				cout << "You have run away from the " << randomMonsterName << " successfully. Pussy.\n";
				break;
			}

		}

		while (playerHP >= 0 || monsterHP >=0);
		{
			if (playerHP <= 0)
			{
				cout << "You have died. Game Over.\n Would you like to start again?\n1. Yes  2.No\n";
				cin >> input;
				switch (input)
				{
				case 1:
					goto ExampleStart;
				case 2: return 0;
				}

			}
			else if (monsterHP <= 0)
			{
				cout << "Congratulations, you have slain the " << randomMonsterName;
				cin >> input;
				break;
			}

		}

		{

		cin >> input;

		//if the user decides to run, they will run and be called a pussy. I figured that in a later build, running may not be 100% garunteed
		//and that if they are successful in running, they may get a quick stab from the monster on their way out of the fight
	case 2:
		cout << "You have run away from the " << randomMonsterName << " successfully. Pussy.\n";
		cin >> input;
		break;

		//this is just to make sure that they select either 1 or 2, anything else will send them back to the battle start phase
	default:
		{
			cout << "The option you have entered is unavailable at this time or\ndoes not exist, please select again.\n";
			goto MonsterEncounter;
		}

	}

	cin >> input;

}