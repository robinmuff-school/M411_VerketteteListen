#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "conio.h"

#pragma warning(disable:6011)

typedef struct Item {
	int Number;
	char Description[40];
	double Price;
	struct Item* pNext;
	struct Item* pPrev;
} struItem;

//Infom the user that there hasn't been a list created yet.
void NotExistingList()
{
	printf("There's no existing List. Please create one first. \n");
}

//Inform the user that his input was invalid.
void InvalidInput()
{
	printf("Invalid input. Please choose one of the given options!\n");
}

//Clear console.
void Clear()
{
	system("cls");
}

//Create menu and ask for input.
int Menu()
{
	char inputCheck[CHAR_MAX] = "";
	int input = 0;
	//Show the available options to the user.
	printf("|-------------------------|\n"
		"|1: Create list           |\n" 
		"|2: Output list           |\n" 
		"|3: Sort list             |\n" 
		"|4: Delete list           |\n" 
		"|5: Delete element        |\n" 
		"|6: Quit program          |\n" 
		"|-------------------------|\n");
	printf_s("Please choose an option: ");
	//Read user input and save the value in a variable.
	//The reason i save the user input as a string is because if you enter a letter or a symbol then the program is very likely to glitch out and won't respond anymore.
	scanf_s("%s", inputCheck, CHAR_MAX);
	input = atoi(inputCheck);
	Clear();
	return input;
}

// Count all element which are in the list and return the count as an integer value.
int CountElements(struItem* pStart)
{
	struItem* pTemp = pStart;
	int entries = 0;
	do {
		entries++;
		pTemp = pTemp->pNext;
	} while (pTemp != pStart);
	return entries;
}

void OutputSubmenu()
{
	//Show the available options to the user.
	printf("|-------------------------|\n"
		"|1. Next page             |\n"
		"|2. Previous page         |\n"
		"|3. Cancel                |\n"
		"|-------------------------|\n");
}

void OutputMenuStart()
{
	printf("|-------|----------------------------------------|---------|\n");
	printf("|%7s|%-40s|%9s|\n", "Number", "Description", "Price");
	printf("|-------|----------------------------------------|---------|\n");
}

void OutputMenuEnd()
{
	printf("|-------|----------------------------------------|---------|\n");
}

//Output the list in a table view.
//The number and description will be displayed on the left side of the tablle and the price to the right.
//After the table has been created the program will wait on input to continue.
void OutputList(struItem* pStart, char* inputCheck)
{
	struItem* pTemp = pStart;
	int limit = 0;
	int position = 1;
	int input = 1;
	int maxElements = CountElements(pStart);
	do {
		OutputSubmenu();
		//Check if the input from the user is valid.
		switch (input)
		{
		case 1:
		{
			OutputMenuStart();
			if (limit < maxElements)
			{
				if (limit < position)
				{
					limit = limit + 20;
				}
				do
				{
					printf("|%-7i|", pTemp->Number);
					printf("%-40s", pTemp->Description);
					printf("|%9.2f|\n", pTemp->Price);
					pTemp = pTemp->pNext;
					position++;
				} while (pTemp != pStart && position <= limit);
			}
			else
			{
				int temp = maxElements - limit;
				if (temp < 0)
				{
					for (int i = 0; i < 20 + temp; i++)
					{
						pTemp = pTemp->pPrev;
						position--;
					}
					do
					{
						printf("|%-7i|", pTemp->Number);
						printf("%-40s", pTemp->Description);
						printf("|%9.2f|\n", pTemp->Price);
						pTemp = pTemp->pNext;
						position++;
					} while (pTemp != pStart && position <= limit);
				}
				else
				{
					for (int i = 0; i < 20; i++)
					{
						pTemp = pTemp->pPrev;
						position--;
					}
					do
					{
						printf("|%-7i|", pTemp->Number);
						printf("%-40s", pTemp->Description);
						printf("|%9.2f|\n", pTemp->Price);
						pTemp = pTemp->pNext;
						position++;
					} while (pTemp != pStart && position <= limit);
				}
			}
			OutputMenuEnd();
			break;
		}
		case 2:
		{
			OutputMenuStart();
			if (limit - 20 != 0)
			{
				int temp = maxElements - limit;
				if (temp < 0)
				{
					limit = limit - 20;
					for (int i = 0; i < 40 + temp; i++)
					{
						pTemp = pTemp->pPrev;
						position--;
					}
				}
				else
				{
					limit = limit - 20;
					for (int i = 0; i < 40; i++)
					{
						pTemp = pTemp->pPrev;
						position--;
					}
				}
				do
				{
					printf("|%-7i|", pTemp->Number);
					printf("%-40s", pTemp->Description);
					printf("|%9.2f|\n", pTemp->Price);
					pTemp = pTemp->pNext;
					position++;
				} while (pTemp != pStart && position <= limit);
			}
			else
			{
				for (int i = 0; i < 20; i++)
				{
					pTemp = pTemp->pPrev;
					position--;
				}
				do
				{
					printf("|%-7i|", pTemp->Number);
					printf("%-40s", pTemp->Description);
					printf("|%9.2f|\n", pTemp->Price);
					pTemp = pTemp->pNext;
					position++;
				} while (pTemp != pStart && position <= limit);
			}
			OutputMenuEnd();
			break;
		}
		case 3:
		{
			Clear();
			return;
			break;
		}
		default:
			Clear();
			InvalidInput();
			OutputSubmenu();
			break;
		}
	printf_s("Please choose an option: ");
	//Read user input and save the value in variable.
	//The reason i save the user input as a string is because if you enter a letter or a symbol then the program is very likely to glitch out and won't respond anymore.
	scanf_s("%s", inputCheck, CHAR_MAX);
	input = atoi(inputCheck);
	Clear();
	} while (true);
}

//Delete the list.
//After the list has been deleted the user will be informed.
struItem* DeleteList(struItem* pStart)
{
	struItem* pTemp = pStart->pNext;
	while (pTemp != pStart)
	{
		//Free the memory that is being used for pTemp.
		free(pTemp);
		pTemp = pStart;
		pStart->pNext = pTemp;
		pTemp->pPrev->pNext = pStart;
		pStart->pPrev = pTemp->pPrev;
		pTemp->pPrev = pStart;
	}
	pStart = NULL;
	printf("List has been deleted.\n");
	return pStart;
}

//Create the list dependant on the user's input.
struItem* CreateList(struItem* pStart, char* inputCheck)
{
	int input = 0;
	srand((unsigned int)time(NULL));
	printf("How many Items should be created? ");
	do
	{
		//Read user input and save the value in a variable.
		//The reason i save the user input as a string is because if you enter a letter or a symbol then the program is very likely to glitch out and won't respond anymore.
		scanf_s("%s", inputCheck, CHAR_MAX);
		input = atoi(inputCheck);
		//Check if the input from the user is greater than 0.
		//If not then inform the user, that the input has to be positive.
		if (input > 0)
		{
			break;
		}
		else
		{
			printf("The number you enter has to be positive or is invalid! ");
		}
	} while (!(input > 0));
	for (int i = 0; i < input; i++) {
		//allocate memory for a new struct pNew.
		struItem* pNew = (struItem*)malloc(sizeof(struItem));
		pNew->Number = i + 1;
		char* pChar = pNew->Description;
		//Create a random character.
		*pChar = 'A' + rand() % 26;
		pChar++;
		*pChar = '\0';
		//Create a random price with a double value.
		pNew->Price = rand() * 0.5;
		if (i == 0) {
			pStart = pNew;
			pStart->pNext = pNew;
			pStart->pPrev = pNew;
		}
		else {
			pNew->pNext = pStart;
			pStart->pPrev->pNext = pNew;
			pNew->pPrev = pStart->pPrev;
			pStart->pPrev = pNew;
		}
	}
	OutputList(pStart, inputCheck);
	Clear();
	return pStart;
}

//Swap two elements.
struItem* Swap(struItem* pTemp)
{
	struItem* pSwap = pTemp;
	pTemp = pTemp->pNext;
	pSwap->pNext = pTemp->pNext;
	pTemp->pNext = pSwap;
	pTemp->pPrev = pSwap->pPrev;
	pSwap->pPrev = pTemp;
	pTemp->pPrev->pNext = pTemp;
	pSwap->pNext->pPrev = pSwap;
	return pTemp;
}

//Let the user decide if he wants to sort ascending or descending.
int SortSubmenu(char* inputCheck)
{
	int subInput = 0;
	while (subInput < 1 || subInput > 3)
	{
		//Show the available options to the user.
		printf("|-------------------------|\n"
			"|1. Sort Ascending        |\n"
			"|2. Sort Descending       |\n"
			"|3. Cancel                |\n"
			"|-------------------------|\n");
		printf_s("Please choose an option: ");
		//Read user input and save the value in variable.
		//The reason i save the user input as a string is because if you enter a letter or a symbol then the program is very likely to glitch out and won't respond anymore.
		scanf_s("%s", inputCheck, CHAR_MAX);
		subInput = atoi(inputCheck);
		Clear();
		//Check if the input from the user is valid.
		if (subInput < 1 || subInput > 3)
		{
			InvalidInput();
		}
		else
		{
			break;
		}
	}
	return subInput;
}

//Sort the list
struItem* SortList(struItem* pStart, char* inputCheck)
{
	struItem* pTemp = pStart;
	int input = 0;
	int subInput = 0;
	int elements = CountElements(pStart);
	while (input < 1 || input > 4)
	{
		//Show the available options to the user.
		printf("|-------------------------|\n"
			"|1. Sort by Number        |\n"
			"|2. Sort by Description   |\n"
			"|3. Sort by Price         |\n"
			"|4. Cancel                |\n"
			"|-------------------------|\n");
		printf_s("Please choose an option: ");
		//Read user input and save the value in variable.
		//The reason i save the user input as a string is because if you enter a letter or a symbol then the program is very likely to glitch out and won't respond anymore
		scanf_s("%s", inputCheck, CHAR_MAX);
		input = atoi(inputCheck);
		Clear();
		if (input < 1 || input > 4)
		{
			InvalidInput();
		}
		else
		{
			break;
		}
	}
	switch (input)
	{
	//Case 1 = sorting by number.
	case 1:
	{
		subInput = SortSubmenu(inputCheck);
		clock_t start = clock();
		for (int cycle = 0; cycle < elements; cycle++)
		{
			pTemp = pStart;
			while (pTemp->pNext != pStart)
			{
				if (subInput == 1)
				{
					if (pTemp == pStart && pStart->Number > pStart->pNext->Number)
					{
						pTemp = Swap(pTemp);
						pStart = pTemp;
					}
					else if (pTemp->Number > pTemp->pNext->Number)
					{
						pTemp = Swap(pTemp);
					}
					pTemp = pTemp->pNext;
				}
				else if (subInput == 2)
				{
					if (pTemp == pStart && pStart->Number < pStart->pNext->Number)
					{
						pTemp = Swap(pTemp);
						pStart = pTemp;
					}
					else if (pTemp->Number < pTemp->pNext->Number)
					{
						pTemp = Swap(pTemp);
					}
					pTemp = pTemp->pNext;
				}
				else
				{
					break;
				}
			}
		}
		clock_t end = clock();
		double time = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("Time: %lf\n", time);
		break;
	}
	//Case 2 = sorting by description.
	case 2:
	{
		subInput = SortSubmenu(inputCheck);
		clock_t start = clock();
		for (int cycle = 0; cycle < elements; cycle++)
		{
			pTemp = pStart;
			while (pTemp->pNext != pStart)
			{
				if (subInput == 1)
				{
					if (pTemp == pStart && strcmp(pTemp->Description, pTemp->pNext->Description) > 0)
					{
						pTemp = Swap(pTemp);
						pStart = pTemp;
					}
					else if (strcmp(pTemp->Description, pTemp->pNext->Description) > 0)
					{
						pTemp = Swap(pTemp);
					}
					pTemp = pTemp->pNext;
				}
				else if (subInput == 2)
				{
					if (pTemp == pStart && strcmp(pTemp->Description, pTemp->pNext->Description) < 0)
					{
						pTemp = Swap(pTemp);
						pStart = pTemp;
					}
					else if (strcmp(pTemp->Description, pTemp->pNext->Description) < 0)
					{
						pTemp = Swap(pTemp);
					}
					pTemp = pTemp->pNext;
				}
				else
				{
					break;
				}
			}
		}
		clock_t end = clock();
		double time = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("Time: %lf\n", time);
		break;
	}
	//Case 3 = sorting by price.
	case 3:
	{
		subInput = SortSubmenu(inputCheck);
		clock_t start = clock();
		for (int cycle = 0; cycle < elements; cycle++)
		{
			pTemp = pStart;
			while (pTemp->pNext != pStart)
			{
				if (subInput == 1)
				{
					if (pTemp == pStart && pStart->Price > pStart->pNext->Price)
					{
						pTemp = Swap(pTemp);
						pStart = pTemp;
					}
					else if (pTemp->Price > pTemp->pNext->Price)
					{
						pTemp = Swap(pTemp);
					}
					pTemp = pTemp->pNext;
				}
				else if (subInput == 2)
				{
					if (pTemp == pStart && pStart->Price < pStart->pNext->Price)
					{
						pTemp = Swap(pTemp);
						pStart = pTemp;
					}
					else if (pTemp->Price < pTemp->pNext->Price)
					{
						pTemp = Swap(pTemp);
					}
					pTemp = pTemp->pNext;
				}
				else
				{
					break;
				}
			}
		}
		clock_t end = clock();
		double time = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("Time: %lf\n", time);
		break;
	}
	//Case 4 = Cancel sorting and return back to menu.
	case 4:
	{
		return pStart;
		break;
	}
	default:
	{
		Clear();
		InvalidInput();
		break;
	}
	}
	//If the selection in the sortsubmenu isn't cancel then output the list.
	//Else go back to sortlist method.
	if (subInput != 3)
	{
		OutputList(pStart, inputCheck);
	}
	else
	{
		SortList(pStart, inputCheck);
	}
	return pStart;
}

//Remove an element.
struItem* RemoveElement(struItem* pStart, struItem* pTemp)
{
	//Reconnect the connections.
	//The pNext from the previous element will now point towards the pNext element from the element, that gets deleted.
	pTemp->pPrev->pNext = pTemp->pNext;
	//The pPrev from the next element will now point towards the previous element from the element, that gets deleted.
	pTemp->pNext->pPrev = pTemp->pPrev;
	pStart = pTemp->pNext;
	free(pTemp);
	//Attention the return value mustn't always be the value of the actual pStart.
	//It will be determed in the DeleteElement method, which calls this method, what pStart actually is.
	return pStart;
}

//Delete an element from user input.
struItem* DeleteElement(struItem* pStart, char* inputCheck)
{
	struItem* pTemp = pStart;
	int input = 0;
	int deletedElements = 0;
	int cycle = 0;
	do
	{
		//Show the available options to the user.
		printf("|-------------------------|\n"
			"|1. Delete by Number      |\n"
			"|2. Delete by Description |\n"
			"|3. Delete by Price       |\n"
			"|4. Cancel                |\n"
			"|-------------------------|\n");
		printf_s("Please choose an option: ");
		//Read user input and save the value in a variable.
		//The reason i save the user input as a string is because if you enter a letter or a symbol then the program is very likely to glitch out and won't respond anymore
		scanf_s("%s", inputCheck, CHAR_MAX);
		Clear();
		input = atoi(inputCheck);
	} while (input < 1 || input > 4);
	switch (input)
	{
	//Case 1 = delete an element by its number.
	case 1:
	{
		int iNumber = 0;
		do
		{
			printf("Which element would you like to delete? Please enter its number: ");
			scanf_s("%s", inputCheck, CHAR_MAX);
			iNumber = atoi(inputCheck);
			do
			{
				if (iNumber == pTemp->Number)
				{
					if (pTemp == pStart)
					{
						pStart = RemoveElement(pStart, pTemp);
						pTemp = pStart;
					}
					else
					{
						pTemp = RemoveElement(pStart, pTemp);
					}
					deletedElements++;
				}
				pTemp = pTemp->pNext;
			} while (pTemp != pStart);
			if (deletedElements == 0)
			{
				Clear();
				printf("No element with the number %i could be found! Please enter an existing item number.\n", iNumber);
			}
			else
			{
				Clear();
				printf("Removed %i element(s).\n", deletedElements);
			}
		} while (deletedElements == 0);
		break;
	}
	//Case 2 = delete an element by its description.
	case 2:
	{
		char iDescription[40] = "";
		do
		{
			printf("Which element would you like to delete? Please enter its description: ");
			//Read user input and save the value in a variable.
			scanf_s("%s", iDescription, 40);
			do
			{
				if (strcmp(iDescription, pTemp->Description) == 0)
				{
					if (pTemp == pStart)
					{
						pStart = RemoveElement(pStart, pTemp);
						pTemp = pStart;
					}
					else
					{
						pTemp = RemoveElement(pStart, pTemp);
					}
					deletedElements++;
				}
				pTemp = pTemp->pNext;
			} while (pTemp != pStart);
			if (deletedElements == 0)
			{
				Clear();
				printf("No element with the description %s could be found! Please enter an existing item description.\n", iDescription);
			}
			else
			{
				Clear();
				printf("Removed %i element(s).\n", deletedElements);
			}
		} while (deletedElements == 0);
		break;
	}
	//Case 3 = delete an element by its price.
	case 3:
	{
		double iPrice = 0;
		do
		{
			printf("Which element would you like to delete? Please enter its Price: ");
			//Read user input and save the value in a variable.
			scanf_s("%s", inputCheck, CHAR_MAX);
			iPrice = atof(inputCheck);
			do
			{
				if (iPrice == pTemp->Price)
				{
					if (pTemp == pStart)
					{
						pStart = RemoveElement(pStart, pTemp);
						pTemp = pStart;
					}
					else
					{
						pTemp = RemoveElement(pStart, pTemp);
					}
					deletedElements++;
				}
				pTemp = pTemp->pNext;
			} while (pTemp != pStart);
			if (deletedElements == 0)
			{
				Clear();
				printf("No element with the price %lf could be found! Please enter an existing item price.\n", iPrice);
			}
			else
			{
				Clear();
				printf("Removed %i element(s).\n", deletedElements);
			}
		} while (deletedElements == 0);
		break;
	}
	//Case 4 = Cancel deleting an element and return back to menu.
	case 4:
	{
		Clear();
		return pStart;
		break;
	}
	default:
	{
		break;
	}
	}
	OutputList(pStart, inputCheck);
	Clear();
	return pStart;
}

//Main method of the program.
//It is mainly based on one "switch" which is based on the user's input from the menu and one "do while" which is always set to true and can only be stopped if the user ends the program (option 6).
int main() 
{
	struItem* pStart = NULL;
	char inputCheck[CHAR_MAX] = "";
	do
	{
		int input = Menu();
		switch (input)
		{
		//Case 1 = create the list.
		case 1:
		{
			char subInput[CHAR_MAX];
			if (pStart == NULL)
			{
				pStart = CreateList(pStart, inputCheck);
														//double t = ((double)end - start) / CLOCKS_PER_SEC;
			}
			else
			{
				//If there's already an existing list ask the user if he wants to replace it and delete the old one.
				printf("There is already an existing list, do you want to replace it (y/n)?");
				//Read user input and save the value in a variable.
				scanf_s("%s", subInput, CHAR_MAX);
				//If the user enters 'y' the old list gets deleted and he can create a new one.
				//The reason i used a char array is because if it's just a char and the user enters more than one letter the program glitches out and wont respond anymore, this way it just takes the first letter that was entered.
				if (subInput[0] == 'y')
				{
					pStart = DeleteList(pStart);
					pStart = CreateList(pStart, inputCheck);
				}
				Clear();
			}
			break;
		}
		//Case 2 = if a list exists, output it.
		//Else inform the user that there's no existing list.
		case 2:
		{
			if (pStart != NULL)
			{
				OutputList(pStart, inputCheck);
			}
			else
			{
				NotExistingList();
			}
			break;
		}
		//Case 3 = if a list exists, sort it by the following option.
		//Else inform the user that there's no existing list.
		case 3:
		{
			if (pStart != NULL)
			{
				pStart = SortList(pStart, inputCheck);
			}
			else
			{
				NotExistingList();
			}
			break;
		}
		//Case 4 = if a list exists, delete it.
		//Else inform the user that there's no existing list.
		case 4:
		{
			if (pStart != NULL)
			{
				pStart = DeleteList(pStart);
			}
			else
			{
				NotExistingList();
			}
			break;
		}
		//Case 5 = if a list exists, let the user decide which element he wants to delete.
		//Else inform the user that there's no existing list.
		case 5:
		{
			if (pStart != NULL)
			{
				pStart = DeleteElement(pStart, inputCheck);
				break;
			}
			else
			{
				NotExistingList();
			}
			break;
		}
		//Case 6 = before quitting the program, check if there's an existing list, if yes, then delete it.
		case 6:
		{
			if (pStart != NULL)
			{
				pStart = DeleteList(pStart);
			}
			printf("Quitting program.\n");
			return 0;
			break;
		}
		default:
		{
			InvalidInput();
			break;
		}
		}
	} while (true);
}
