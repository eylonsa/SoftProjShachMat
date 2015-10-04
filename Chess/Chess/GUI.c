#include "GUI.h"


void FreeButtonsBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		free(buttonsBoard[i]);
	}
	free(buttonsBoard);
	buttonsBoard = NULL;
}


int FlipTree(char** error)
{
	if (-1 == DrawTree(tree, error))
	{
		return -1;
	}

	/* We finished drawing*/
	if (SDL_Flip(tree->control->surface) != 0) {
		*error = SDL_GetError();
		return -1;
	}
	return 0;
}

void releaseResouces()
{
	FreeTree(tree);
	tree = NULL;
	FreeEventHandler();
	if (buttonsBoard != NULL){
		FreeButtonsBoard();
	}
	free(curMovesList);
	curMovesList = NULL;
	free(posMovesFromCurPos);
	posMovesFromCurPos = NULL;
	free(chosenMove);
	chosenMove = NULL;
}

void Quit()
{
	releaseResouces();
	guiQuit = 1;
}

void Quit_ButtonClick(control* input)
{
	Quit();
}

// initializtion
void InitGlobalVariable()
{
	window = NULL;
	tree = NULL;

	//GameBoard
	selectedSquare_Control = NULL;
	selectedPiece_Control = NULL;

	board_node = NULL;

	curMovesList = NULL;
	posMovesFromCurPos = NULL;
	chosenMove = NULL;

	gameOver = 0;
	check = 0;
	tie = 0;

	showDepthOptions = 0;

	isUpgrade = 0;

	control*** buttonsBoard = NULL;

	//SaveLoad
	isSaveMode = 0;


	//Settings
	setPieces = 0;

	curSettings = NULL;
}

void SwitchOffHighlightAllMinimaxDepths()
{
	SwitchOffHighlightbyName(BUTTON1NAME);
	SwitchOffHighlightbyName(BUTTON2NAME);
	SwitchOffHighlightbyName(BUTTON3NAME);
	SwitchOffHighlightbyName(BUTTON4NAME);
	SwitchOffHighlightbyName(BUTTONBESTNAME);
}

void SwitchButtonHighlight(control* input)
{
	if (input->ishighlighted == 0){
		input->ishighlighted = 1;
	}
	else
	{
		input->ishighlighted = 0;
	}
}

void SwitchOffHighlightbyName(char* name){
	UINode* node = SearchTreeByName(tree, name);
	if (node != NULL){
		if (node->control->ishighlighted == 1){
			SwitchButtonHighlight(node->control);
		}
	}
}

void SwitchOnHighlightbyName(char* name)
{
	UINode* node = SearchTreeByName(tree, name);
	if (node != NULL){
		if (node->control->ishighlighted == 0){
			SwitchButtonHighlight(node->control);
		}
	}
}

void start_gui()
{
	/* Initialize SDL and make sure it quits*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	atexit(SDL_Quit);
	
	guiQuit = 0;
	error_global = NULL;

	InitGlobalVariable();
	guiQuit = 0;
	SDL_WM_SetCaption("Chess", NULL);

	MainMenu();

	while (guiQuit == 0) {
		HandleEvents();
		SDL_Delay(125);
	}

	releaseResouces();
	if (guiQuit == -1)
	{
		if (NULL != error_global){
			printf(error_global);
			getchar();
		}
	}
}



