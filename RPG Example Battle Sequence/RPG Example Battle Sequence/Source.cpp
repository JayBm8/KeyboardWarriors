#include <time.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
ExampleStart:

	srand (time(NULL));   //initialises the randomizer for later use

	int input;            //this variable SHOULD be fine for all of the inputs the player will ever type into this game. Don't quote me on that
	cout << "This is an example build of how a battle phase will play out in this\ntext-based RPG. Please type any character and enter to continue.\n";
	cin >> input;


	int playerBaseHP = 250;             //stores all the information for the characters base stats,
	int playerBaseStrength = 50;        //stat boosts from gear and their total stats, which will be
	int playerBaseDefence = 50;         //used in damage calculation

	int playerGearHP = 0;
	int playerGearStrength = 0;
	int playerGearDefence = 0;

	int playerTotalHP = playerBaseHP + playerGearHP;
	int playerTotalStrength = playerBaseStrength + playerGearStrength;
	int playerTotalDefence = playerBaseDefence + playerGearDefence;

	int playerCurrentHP = playerTotalHP;                        //these are the values that are likely to change during battle, we need these so that
	int playerCurrentStrength = playerTotalStrength;            //we can have the 'total' values as a ceiling, preventing players from healing above their
	int playerCurrentDefence = playerTotalDefence;              //total HP

	int monsterHP = 0;                    //monsters of the same type will all have the same stat values,
	int monsterStrength = 0;              //but I thought it would be easier to have this as a general group of 
	int monsterDefence = 0;               //monster stats and changing them according to the monster encountered, within the battle phase

    string monsterName [4] = {"Bat", "Rat", "Wolf", "Behemoth"};         //this is a string array including 3 names of the different monsters that can be encountered
	                                                         //on this floor (held as {0}, {1} and {2} as opposed to 1, 2 and 3
BattleStart:
	int randomMonsterSelection = rand() % 4;                 //this is the random number generator (generates numbers from 0 to 2)

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
		else if (randomMonsterName == "Behemoth")
		{
			monsterHP = 3000;
			monsterStrength = 40;
			monsterDefence = 2;
		}
		else
		{
			cout << "The monsters name was not any of the available options, something REALLY screwed up";
		}

		do                 //do while loop. while the player and the monster are both healthy, the battle phase will continue until one of them dies
		{
			int monsterDamage = monsterStrength - 0.1 * playerCurrentDefence;        //battle damage is calculated by the attackers total strength stat minus 10% of 
            int playerDamage = playerCurrentStrength - 0.1 * monsterDefence;         //the defenders defence. we can change this at any time which will no doubt happen
			int battleInput;

			cout << "Your health is " << playerCurrentHP << ". The " << randomMonsterName << "s health is " << monsterHP << ".\nHow do you wish to proceed?\n";
			cout << "1. Attack  2. Heal  3. Run\n";
			cin >> battleInput;
			switch (battleInput)
			{
	        case 1:                                                       //right now your only options are basic attacks, healing and running away.
				monsterHP = monsterHP - playerDamage;                     //later on we will add health pots for healing so that you can't endlessly
				if (monsterHP <= 0)                                       //heal yourself back to full 
				{
					cout << "You deal the killing blow to the " << randomMonsterName << " with " << playerDamage << " damage.\n"; //if you deal the final blow to the 
					break;                                                                                                        //monster, you won't take damage on 
				}                                                                                                                 //the final turn 
				else
				{
				playerCurrentHP = playerCurrentHP - monsterDamage;        
				cout << "You deal " << playerDamage << " damage to the " << randomMonsterName << ". The " << randomMonsterName << " deals " << monsterDamage << " to you.\n";
				break;
				}
	        case 2:
				if ((playerCurrentHP + 60) <= playerTotalHP)                            //the code here is just to ensure that players cant boost themselves
				{                                                                       //over their HP limit by healing
				playerCurrentHP = playerCurrentHP + 60;
				playerCurrentHP = playerCurrentHP - monsterDamage;
				cout << "You heal 60 damage." "The " << randomMonsterName << " deals " << monsterDamage << " to you.\n";
				break;
				}
				else if (playerCurrentHP + 60 > playerTotalHP)
				{
				playerCurrentHP = playerTotalHP;
				playerCurrentHP = playerCurrentHP - monsterDamage;
				cout << "You are now completely healthy!" "The " << randomMonsterName << " deals " << monsterDamage << " to you.\n";
				break;
				}
				else if (playerCurrentHP >= playerTotalHP)
				{
				cout << "Your health cannot go any higher!";
				break;
				}
	        case 3:
				cout << "You have run away from the " << randomMonsterName << " successfully.\n";         //you'll be able to run from battle at any time but 
				goto BattleStart;                                                                         //running from battle may be punished by possible exit damage
			default:
				cout << "The input you have entered is invalid, please choose 1, 2 or 3 and press enter.";
				break;
			}
		}

		while (playerCurrentHP > 0 && monsterHP > 0);           //when either the player or the monster dies, this if statement will find out which one
		                                                 //is dead and give the appropriate dialog. this is also where any loot will be awarded
			if (monsterHP <= 0)
			{
				cout << "Congratulations, you have slain the " << randomMonsterName << "!\n";
				cin >> input;
				break;
			}
			
			else if (playerCurrentHP <= 0)
			{
				cout << "You have died. Game Over.\n Would you like to start again?\n1. Yes  2.No\n";
				cin >> input;
				switch (input)
				{
				case 1:
					goto ExampleStart;
				case 2: 
					return 0;
				}

			}

        cin >> input;

		//if the user decides to run, they will run and be called a pussy. I figured that in a later build, running may not be 100% garunteed
		//and that if they are successful in running, they may get a quick stab from the monster on their way out of the fight
	case 2:
		cout << "You have run away from the " << randomMonsterName << " successfully. Pussy.\n";
		cin >> input;
		goto BattleStart;

		//this is just to make sure that they select either 1 or 2, anything else will send them back to the battle start phase
	default:
		{
			cout << "The option you have entered is unavailable at this time or\ndoes not exist, please select again.\n";
			goto BattleStart;
		}

	}

	cin >> input;

}