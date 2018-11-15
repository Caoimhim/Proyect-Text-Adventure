#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "structs.h"
using namespace std;

//Global Variables
bool bGameRunning; //For game loop

/* getMap
 * Functions reads the map from an external file in the following order:
 * #Rows
 * #Columns
 *  (Enters Loop) Room Description
 *  Possible Routes of movement ( N S E W)
 *  Pickups ( Descriptions)
 *  Interactables ( if examinable or not, and if activable or not)
 *  Inputs: Functions Reads from a file
 *  Outputs: Functiion Writes to an Array containing all the information on the map of the game, as well as it dimensions for further operations with the map
 */
void getMap( oRoom oMatMap[3][10][10], int &iMapFloors, int &iMapRows, int &iMapColumns)
{ 
	ifstream fMap;
	fMap.open( "Test.map");
	string sBuffer;//Needed to use this because reading from a file doesn't play nice when mixing strings and other datatypes
	if ( fMap.is_open())
	{ 
	
		//Get Map Dimensions	

		//REMEMBER: this process for reading a whole line, then converting it to a number
		//and never again mix datatypes when reading from a file this way Respose: XD
		getline( fMap, sBuffer);
		iMapFloors = strtol( sBuffer.c_str(), NULL, 10);
		//cout << iMapFloors << "is floors"<< endl; //just in case
		
		getline( fMap, sBuffer);
		iMapRows = strtol( sBuffer.c_str(), NULL, 10);
		//cout << iMapRows << "is columns" << endl;

		getline( fMap, sBuffer);
		iMapColumns = strtol( sBuffer.c_str(), NULL, 10);
		//cout << iMapColumns << "is columns" << endl;
		
		//Get Map Information
		for ( int iIndexFloors = 0; iIndexFloors < iMapFloors; iIndexFloors++)
		{	
			for ( int iIndexColumns = 0; iIndexColumns < iMapColumns; iIndexColumns++)
			{ 
				for (int iIndexRows = 0; iIndexRows < iMapRows; iIndexRows++)
				{ 
				
				
				getline( fMap, oMatMap[iIndexFloors][iIndexRows][iIndexColumns].sName); //Save Name
				//cout << "room name: " << oMatMap[iIndexFloors][iIndexRows][iIndexColumns].sName << endl;
				getline( fMap, oMatMap[iIndexFloors][iIndexRows][iIndexColumns].sDescription); //Save Description
				//cout << "Description of the room: "<<oMatMap[iIndexFloors][iIndexRows][iIndexColumns].sDescription << endl;
				
				//Where can you go?
				getline( fMap, sBuffer);
				oMatMap[iIndexFloors][iIndexRows][iIndexColumns].bNorth = strtol( sBuffer.c_str(), NULL, 10);
			
				getline( fMap, sBuffer);
				oMatMap[iIndexFloors][iIndexRows][iIndexColumns].bSouth = strtol( sBuffer.c_str(), NULL, 10);

				getline( fMap, sBuffer);
				oMatMap[iIndexFloors][iIndexRows][iIndexColumns].bEast = strtol( sBuffer.c_str(), NULL, 10);

				getline( fMap, sBuffer);
				oMatMap[iIndexFloors][iIndexRows][iIndexColumns].bWest = strtol( sBuffer.c_str(), NULL, 10);
			
				//Stairs
				getline( fMap, sBuffer);
				oMatMap[iIndexFloors][iIndexRows][iIndexColumns].bStairs = strtol( sBuffer.c_str(), NULL, 10);
				if ( oMatMap[iIndexFloors][iIndexRows][iIndexColumns].bStairs == true)
				{ 
					getline( fMap, sBuffer);
					oMatMap[iIndexFloors][iIndexRows][iIndexColumns].oStaircase.bCanGoUp= strtol( sBuffer.c_str(), NULL, 10);
					

					getline( fMap, sBuffer);
					oMatMap[iIndexFloors][iIndexRows][iIndexColumns].oStaircase.bCanGoDown= strtol( sBuffer.c_str(), NULL, 10);
				}
				//Pickups
				//Are there any pickups?
				getline( fMap, sBuffer );
				oMatMap[iIndexFloors][iIndexRows][iIndexColumns].iHowManyPickups = strtol( sBuffer.c_str(), NULL, 10);
				
				if ( oMatMap[iIndexFloors][iIndexRows][iIndexColumns].iHowManyPickups > 0)
				{ 

					//Get Info on items, if there are items
					int iCounterPickups = 0;
					while ( iCounterPickups < oMatMap[iIndexFloors][iIndexRows][iIndexColumns].iHowManyPickups)
					{ 
						//Get Name
						getline( fMap, oMatMap[iIndexFloors][iIndexRows][iIndexColumns].oArrPickups[iCounterPickups].sNameP);
						//cout << "Name of pickup: " << oMatMap[iIndexFloors][iIndexRows][iIndexColumns].oArrPickups[iCounterPickups].sNameP << endl;
						//Get Description
						getline( fMap, oMatMap[iIndexFloors][iIndexRows][iIndexColumns].oArrPickups[iCounterPickups].sDescription);
						iCounterPickups++;
					}
				}
				//End of Pickups stuff

				//Interactables

				//Are there any interactables? How Many?
				getline( fMap, sBuffer );
				oMatMap[iIndexFloors][iIndexRows][iIndexColumns].iHowManyInteractables = strtol( sBuffer.c_str(), NULL, 10);
				
				if ( oMatMap[iIndexFloors][iIndexRows][iIndexColumns].iHowManyInteractables > 0)
				{ 

					//Get Info on items, if there are items
					int iCounterInteractables = 0;
					while ( iCounterInteractables < oMatMap[iIndexFloors][iIndexRows][iIndexColumns].iHowManyInteractables)
					{ 

						//Get Name
						getline( fMap, oMatMap[iIndexFloors][iIndexRows][iIndexColumns].oArrInteractables[iCounterInteractables].sNameI);
						
						//Examinable?
						getline( fMap, sBuffer);
						oMatMap[iIndexFloors][iIndexRows][iIndexColumns].oArrInteractables[iCounterInteractables].bCanExamine = strtol( sBuffer.c_str(), NULL, 10);
						
						if ( oMatMap[iIndexFloors][iIndexRows][iIndexColumns].oArrInteractables[iCounterInteractables].bCanExamine == true )
						{ 
							getline( fMap, oMatMap[iIndexFloors][iIndexRows][iIndexColumns].oArrInteractables[iCounterInteractables].sExamination);
						}
						
						//Activable?
						getline( fMap, sBuffer);
						oMatMap[iIndexFloors][iIndexRows][iIndexColumns].oArrInteractables[iCounterInteractables].bCanActivate = strtol( sBuffer.c_str(), NULL, 10);
						
						if ( oMatMap[iIndexFloors][iIndexRows][iIndexColumns].oArrInteractables[iCounterInteractables].bCanActivate == true )
						{ 
							getline( fMap, oMatMap[iIndexFloors][iIndexRows][iIndexColumns].oArrInteractables[iCounterInteractables].sActivated);
						}
						
						iCounterInteractables++;
					}
				}
				//End of Interactables stuff
			}
		}
	}
	}
	else
	{
		cout << "Error opening map file" << endl;
	}
	fMap.close();
}

/* printInit
 * prints the first line of the story, WHICH WON'T BE REPEATED
 * Input: a string from a file
 * Output: NONE
 */
void printInit( )
{ 
	ifstream fDescription;
	fDescription.open( "game_info.txt");
	string sLaunch;
	if ( fDescription.is_open())
	{ 
		cout << "game launched" << endl;
		int iCounter = 0;
		while ( iCounter < 10) // Will print up to 10 lines
		{

			getline( fDescription, sLaunch); 
			cout <<  sLaunch << endl;
			iCounter++;
		}
	}
	else
	{ 
		cout << "No game description found, skipping" << endl;
	}
	//General Instructions for the engine
	cout << "You can input up to 4 words. Any words after the 4th will be ignored" << endl;

}

/* printStatus
 * prints out all the current valid descriptions
 * Inputs: The player's information stored in a struct, the map;
 * Outputs: NONE
 */
void printStatus( oGamer oPlayer, oRoom oMatMap[3][10][10])
{ 
	//First print general room information
	cout << "Floor: " << oPlayer.iLocation[0] << " (" << oPlayer.iLocation[1] << ", " << oPlayer.iLocation[2] << ")" << endl <<oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].sDescription << endl;

	//Then print information on visible interactables
	if ( oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].iHowManyInteractables > 0)
	{ 
		for ( int iCounter = 0; iCounter < oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].iHowManyInteractables; iCounter++ )
		{ 
				cout << oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].oArrInteractables[iCounter].sNameI << endl;
		}
	}
	//Lastly print out Pickups information
	if ( oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].iHowManyPickups > 0)
	{ 
		for ( int iCounter = 0; iCounter < oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].iHowManyPickups; iCounter++ )
		{ 
			if ( oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].oArrPickups[iCounter].bHidden == false)
			{ 
				cout << oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].oArrPickups[iCounter].sDescription << endl;
			}
		}
	}
}

/* getUserInput
 * gets input from the user, and splits it in up to four seperate strings
 * Inputs: NONE
 * Outpuits: Input from the user is returned
 */
string getUserInput()
{ 
	string sInput;
	cout << "→ ";
	getline( cin, sInput);
	return sInput;
}

/* parse
 * Receives a string, and splits it in up to 4 substrings, and then interprets the user input
 * Input: Input gotten from the user
 * Output: Writes changes into the map
 */

void parse(oGamer &oPlayer, oRoom oMatMap[3][10][10], string sUserInput )
{ 
	string sArrInput[4];
	int iPosition;
	//iPlayer.iLocation[0] = z
	//iPlater.iLocation[1] = x
	//iPlayer.iLocation[3] = y

	for ( int iCounter = 0; iCounter < 4; iCounter++)
	{ 
		iPosition = sUserInput.find(" ");
		sArrInput[iCounter] = sUserInput.substr(0, iPosition);
		//cout << sArrInput[iCounter] << " we parsed this" << endl;
		if ( iPosition < 0)
		{ 
			//cout << "stop parsing" << endl;
			break;
		}
		sUserInput = sUserInput.substr(iPosition + 1);
		//cout << sUserInput << " This is what is remaining" << endl;

	}
	
	//MOVEMENT
		if ( sArrInput[0] == "north" || sArrInput[0] == "North" || sArrInput[0] == "N")
		{ 
			if ( oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].bNorth == 0)
			{ 
				cout << "You can't go North." << endl;

			}
			else
			{ 
				oPlayer.iLocation[2] -= 1;
			}
		}

		else if ( sArrInput[0] == "south" || sArrInput[0] == "South" || sArrInput[0] == "S")
		{ 
			if ( oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].bSouth == 0)
			{ 
				cout << "You can't go South." << endl;

			}
			else
			{ 
				oPlayer.iLocation[2] += 1;
			}
		}

		else if ( sArrInput[0] == "east" || sArrInput[0] == "East" || sArrInput[0] == "E")
		{ 
			if ( oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].bEast == 0)
			{ 
				cout << "You can't go East." << endl;

			}
			else
			{ 
				oPlayer.iLocation[1] += 1;
//				cout << "You moved in X to " << oPlayer.iLocation[0] << endl;
			}
		}
		
		else if ( sArrInput[0] == "west" || sArrInput[0] == "West" || sArrInput[0] == "W")
		{ 
			if ( oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].bWest == 0)
			{ 
				cout << "You can't go West." << endl;

			}
			else
			{ 
				oPlayer.iLocation[1] -= 1;
			}

		}

		//Stairs
		else if ( sArrInput[0] == "go")
		{ 
			if ( sArrInput[1] == "up" || sArrInput[1] == "upstairs")
			{ 
				if (oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].bStairs == true)
				{ 
					if (oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].oStaircase.bCanGoUp == true)
					{ 
						cout << "You climbed the stairs" << endl;
						oPlayer.iLocation[0] += 1;
					}
					else
					{ 
						cout << "It seems you can't go up these stairs"  << endl;
					}
				}
				else 
				{ 
					cout << "There are no stairs here" << endl;
				}
				
			}
			else if  ( sArrInput[1] == "down" || sArrInput[1] == "downstairs")
			{ 
				
				if (oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].bStairs == true)
				{ 
					if (oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].oStaircase.bCanGoDown == true)
					{ 
						cout << "You climbed down the stairs" << endl;
						oPlayer.iLocation[0] -= 1;
					}
					else
					{ 
						cout << "It seems you can't go down these stairs" << endl;
					}
				}
			}
		}
		else if ( sArrInput[0] == "up")
		{ 
				
			if (oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].bStairs == true)
			{ 
				if (oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].oStaircase.bCanGoUp == true)
				{ 
					cout << "You climbed the stairs" << endl;
					oPlayer.iLocation[0] += 1;
				}
				else
				{ 
					cout << "It seems you can't go up these stairs" << endl;
				}
			}
			else 
			{ 
				cout << "There are no stairs here" << endl;
			}
		}
		else if ( sArrInput[0] == "down")
		{ 
				
			if (oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].bStairs == true)
			{ 
				if (oMatMap[oPlayer.iLocation[0]][oPlayer.iLocation[1]][oPlayer.iLocation[2]].oStaircase.bCanGoDown == true)
				{ 
					cout << "You climbed down the stairs" << endl;
					oPlayer.iLocation[0] -= 1;
				}
				else
				{ 
					cout << "It seems you can't go down these stairs" << endl;
				}
			}
			else 
			{ 
				cout << "There are no stairs here" << endl;
			}
		}


		else
		{ 
			cout << "Sorry, I don't understand: " << sArrInput[0]	<< " " << sArrInput[1] << " " << sArrInput[2] << " " << sArrInput[3] << endl;
		}
		cout << endl;
	//cout << sArrInput[3] << endl;
	//Here we need to split this string in 4
	//Most complex sentence would be VERB + IO + PREPOSITION + DO
	//Example: Hit monster with sword
	//Simple sentences should also be legal like
	//take key
	//or simply:
	//North
}

/* main
 * calls all other functions. Contains the game loop
 * Inputs: NONE
 * Outputs: VOID
 */
int main ()
{ 
	//Variables
	oRoom oMatMap[3][10][10];
	int iMapFloors, iMapRows, iMapColumns;
	oGamer oPlayer;

	printInit();
	getMap(oMatMap, iMapFloors, iMapRows, iMapColumns); //Get the map from external file

	bGameRunning = 1;
	oPlayer.iLocation[0] = 0;
	oPlayer.iLocation[1] = 0;
	oPlayer.iLocation[2] = 0;
	while ( bGameRunning == 1) // Game loop start
	{
		//Print current status
		printStatus(oPlayer, oMatMap);

		//Get and parse user input
		string sInput;
		//Input Function
		sInput = getUserInput();
		//Processing
		parse( oPlayer, oMatMap, sInput);
	}
	
	return 0;
}
