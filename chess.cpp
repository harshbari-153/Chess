#include"human.h"

void instructions()
{
	cout<<endl<<endl<<"          Instructions";
	cout<<endl<<"1) About Moves";
	cout<<endl<<"To make a move piece, write the coordinates from the source square to destination square";
	cout<<endl<<"The coordinates starts from character followed by number";
	cout<<endl<<"In between a colen and then the destination square";
	cout<<endl<<"For example: B2:C3";
	cout<<endl<<"This means a piece taken from square B2 and kept on square C3";
	cout<<endl<<endl<<"2) About Pieces";
	cout<<endl<<"2 represents pawn";
	cout<<endl<<"3 represents knight";
	cout<<endl<<"5 represents bishop";
	cout<<endl<<"7 represents rook";
	cout<<endl<<"11 represents queen";
	cout<<endl<<"13 represents king";
	cout<<endl<<"negative sign is for white pieces";
	cout<<endl<<"positive sign is for black pieces";
	cout<<endl<<"rest are all empty squares";
	cout<<endl<<endl<<"3) Rules Included";
	cout<<endl<<"It has castle, enpass, pawn promotion as same as standard moves accordingly";
	cout<<endl<<"It also have 3 step repetetion as draw";
}

void display_result(int result, int n)
{
	n = (n / 2) + (n % 2);

	if(result != 0)
	cout<<endl<<endl<<"CHECKMATE";
	
	//declare result
	if(result == 0)
		cout<<endl<<"It is a draw in "<<n<<" moves";
	
	//black wins
	else if(result == 1)
		cout<<endl<<"You won against computer in "<<n<<" moves";
	
	//white wins
	else
		cout<<endl<<"Computer won in "<<n<<" moves";
			
}

int pieces_to_depth(int B[8][8])
{
	int points = 0, count = 0;
	bool major_piece = false;
	
	for(int i = 0 ; i < 8 ; i++)
		for(int j = 0 ; j < 8 ; j++)
			if(B[i][j] != 0)
			{
				count = count + 1;
				points = points + id_to_points(B[i][j]);
				if(get_mod(B[i][j]) == 7 || get_mod(B[i][j]) == 11)
					major_piece = true;
			}
	
	if(count <= 4 && points <= 7 && major_piece == false)
		return 7;
	else if(count <= 8 && points <= 19)
		return 6;
	else if(count <= 16 && points <= 39)
		return 5;
	else if(count <= 32 && points <= 78)
		return 4;
	else
		return 3;
	
}

//new game starts
void game_begins(bool color)
{
	int result, status, temp;
	
	int B[8][8] = {
				{-7, -3, -5, -11, -13, -5, -3, -7},
				{-2, -2, -2, -2, -2, -2, -2, -2},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{2, 2, 2, 2, 2, 2, 2, 2},
				{7, 3, 5, 11, 13, 5, 3, 7}};
	
	//create game stack
	game_stack *moves = new game_stack();
	
	if(!color)
		human_play(color, B, moves);
	
	//game begins
	while(true)
	{
		//computer play
		temp = computer_play(!color, B, moves, 0, pieces_to_depth(B), -9998, 9998);
		status = game_status(B, color, moves);
		if(status != -1)
		{
			if(status == 0)
				result = 0;
			else
				result = -1;
			break;
		}
		
		//human play
		human_play(color, B, moves);
		status = game_status(B, !color, moves);
		if(status != -1)
		{
			if(status == 0)
				result = 0;
			else
				result = 1;
			break;
		}
		
		
	}
	display(B, color);
	display_result(result, moves->get_total_moves());
}

int main()
{
	char choise;
	
	cout<<"Welcome To Chess Game";
	
	while(true)
	{
		cout<<endl<<endl<<"Press 1 to play as white";
		cout<<endl<<"Press 2 to play as black";
		cout<<endl<<"Press 3 to read instructions";
		cout<<endl<<"Press 0 to exit";
		cout<<endl<<"Enter your choise: ";
		cin>>choise;
		
		if(choise == '1')
			game_begins(false);
		
		else if(choise == '2')
			game_begins(true);
		
		else if(choise == '3')
			instructions();
		
		else if(choise == '0')
		{
			cout<<endl<<"Program Terminated";
			return 0;
		}
		
		else
			cout<<"Invalid choise";
	}
}