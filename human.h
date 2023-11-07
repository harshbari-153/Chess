#include"engine.h"

bool error_message(int n)
{
	if(n == 0)
		cout<<endl<<"Invalid Input";
	
	else if(n == 1)
		cout<<endl<<"Its the same square";
	
	else if(n == 2)
		cout<<endl<<"That is not your piece";
	
	else if(n == 3)
		cout<<endl<<"You cannot capture your own piece";
		
	else if(n == 4)
		cout<<endl<<"No piece present on that square";
	
	else if(n == 5)
		cout<<endl<<"Invalid Move";
	
	else if(n == -10)
		cout<<endl<<"Testing purpose";

	else
		cout<<"An unknown error occured";
	
	return false;
}

void human_promotion(int B[8][8], bool color, int j)
{
	char choise;
	
	do
	{
		cout<<endl<<endl<<"Pawn Promoted:";
		cout<<endl<<"Press 1 to promote queen";
		cout<<endl<<"Press 2 to promote rook";
		cout<<endl<<"Press 3 to promote bishop";
		cout<<endl<<"Press 4 to promote knight";
		cout<<endl<<"Enter your choise: ";
		cin>>choise;
		
		if(choise == '1' || choise == '2' || choise == '3' || choise == '4')
			break;
		
		else
			cout<<endl<<"Invalid choise";
	}while(true);
	
	//for black
	if(color)
	{
		//queen
		if(choise == '1')
		{
			B[1][j] = 11;
			cout<<endl<<endl<<"Queen promoted sucessfully";
		}
		
		//rook
		else if(choise == '2')
		{
			B[1][j] = 7;
			cout<<endl<<endl<<"Rook promoted sucessfully";
		}
		
		//bishop
		else if(choise == '3')
		{
			B[1][j] = 5;
			cout<<endl<<endl<<"Bishop promoted sucessfully";
		}
		
		//knight
		else
		{
			B[1][j] = 3;
			cout<<endl<<endl<<"Knight promoted sucessfully";
		}
	}
	
	//for white
	else
	{
		//queen
		if(choise == '1')
		{
			B[6][j] = -11;
			cout<<endl<<endl<<"Queen promoted sucessfully";
		}
		
		//rook
		else if(choise == '2')
		{
			B[6][j] = -7;
			cout<<endl<<endl<<"Rook promoted sucessfully";
		}
		
		//bishop
		else if(choise == '3')
		{
			B[6][j] = -5;
			cout<<endl<<endl<<"Bishop promoted sucessfully";
		}
		
		//knight
		else
		{
			B[6][j] = -3;
			cout<<endl<<endl<<"Knight promoted sucessfully";
		}
	}
}

//pawn
bool pawn(int B[8][8], int a, int b, int c, int d, game_stack *moves)
{
	//jump
	if(get_mod(c-a) == 2 && b == d && B[c][d] == 0)
	{
		//white
		if(a == 1 && B[2][b] == 0)
			return make_move(B, a, b, c, d, moves);
		
		//black
		else if(a == 6 && B[5][b] == 0)
			return make_move(B, a, b, c, d, moves);
		
		//none
		else
			return false;
	}
	
	//push
	else if(get_mod(c-a) == 1 && b == d && B[c][d] == 0)
	{
		//white
		if(B[a][b] < 0)
		{
			if(a + 1 == c)
			{	
				//promotion
				if(c == 7)
				{
					human_promotion(B, false, b);
					return make_move(B, -2, B[6][b], b, d, moves);
				}
				
				else
					return make_move(B, a, b, c, d, moves);
			}
			
			else
				return false;
		}
		
		//black
		else
		{
			if(a - 1 == c)
			{
				//promotion
				if(c == 0)
				{
					human_promotion(B, true, b);
					return make_move(B, -2, B[1][b], b, d, moves);
				}
				
				else
					return make_move(B, a, b, c, d, moves);
			}
			
			else
				return false;
		}
	}
	
	//capture
	else if(get_mod(a-c) == 1 && get_mod(b-d) == 1 && B[c][d] != 0)
	{	
		//white
		if(B[a][b] < 0 && B[c][d] > 0)
		{
			if(a + 1 == c)
			{
				//promotion
				if(c == 7)
				{
					human_promotion(B, false, b);
					return make_move(B, -2, B[6][b], b, d, moves);
				}
				
				else
					return make_move(B, a, b, c, d, moves);
			}
			
			else
				return false;
		}
		
		//black
		else if(B[a][b] > 0 && B[c][d] < 0)
		{
			if(a - 1 == c)
			{
				//promotion
				if(c == 0)
				{
					human_promotion(B, true, b);
					return make_move(B, -2, B[1][b], b, d, moves);
				}
				
				else
					return make_move(B, a, b, c, d, moves);
			}
			
			else
				return false;
		}
		
		else
			return false;
	}
		
	//enpass
	else if(get_mod(a-c) == 1 && get_mod(b-d) == 1 && B[c][d] == 0 && moves->can_enpass(B, a, b, c, d))
	{
		//white
		if(B[a][b] < 0 && a == 4 && c == 5 && B[4][d] == 2)
			return make_move(B, -3, 0, b, d, moves);
		
		//black
		else if(B[a][b] > 0 && a == 3 && c == 2 && B[3][d] == -2)
			return make_move(B, -3, 1, b, d, moves);
		
		else
			return false;
	}
	
	//none
	else
		return false;
}

//knight
bool knight(int B[8][8], int a, int b, int c, int d, game_stack *moves)
{
	if(!l_shape(B, a, b, c, d))
		return false;
	
	return make_move(B, a, b, c, d, moves);
}

//bishop
bool bishop(int B[8][8], int a, int b, int c, int d, game_stack *moves)
{
	//principal diagonal
	if(a+b == c+d)
	{
		if(b < d && principal_diagonal(B, a, b, c, d))
			return make_move(B, a, b, c, d, moves);
		
		else if(d < b && principal_diagonal(B, c, d, a, b))
			return make_move(B, a, b, c, d, moves);
		
		else
			return false;
	}

	//non principal diagonal
	else if(b+c == d+a)
	{
		if(b < d && non_principal_diagonal(B, a, b, c, d))
			return make_move(B, a, b, c, d, moves);
	
		else if(d < b && non_principal_diagonal(B, c, d, a, b))
			return make_move(B, a, b, c, d, moves);
		
		else
			return false;
	}
	
	//none
	else
		return false;
}

//rook
bool rook(int B[8][8], int a, int b, int c, int d, game_stack *moves)
{
	//verticle
	if(b == d)
	{
		if(a < c && vertical(B, a, b, c, d))
			return make_move(B, a, b, c, d, moves);
		
		else if(c < a && vertical(B, c, d, a, b))
			return make_move(B, a, b, c, d, moves);
		
		else
			return false;
	}

	//horizontal
	else if(a == c)
	{
		if(b < d && horizontal(B, a, b, c, d))
			return make_move(B, a, b, c, d, moves);
	
		else if(d < b && horizontal(B, c, d, a, b))
			return make_move(B, a, b, c, d, moves);
		
		else
			return false;
	}
	
	//none
	else
		return false;
}

//queen
bool queen(int B[8][8], int a, int b, int c, int d, game_stack *moves)
{
	if(rook(B, a, b, c, d, moves) || bishop(B, a, b, c, d, moves))
		return true;
	
	return false;
}

//king
bool king(int B[8][8], int a, int b, int c, int d, game_stack *moves)
{
	//castle
	if(b == 4 && a == c && get_mod(b-d) == 2)
	{
		//for white
		if(a == 0)
		{
			//left castle
			if(d == 2)
			{
				if(!moves->w_l_c_status() || B[0][0] != -7 || is_check(B, false) || B[0][1] != 0 || B[0][2] != 0 || B[0][3] != 0)
					return false;
				
				B[0][3] = B[0][4];
				B[0][4] = 0;
				
				if(is_check(B, false))
				{
					B[0][4] = B[0][3];
					B[0][3] = 0;
					return false;
				}
				
				B[0][4] = B[0][3];
				B[0][3] = 0;
				
				return make_move(B, -1, 0, 0, 9, moves);
			}
			
			//right castle
			else
			{
				if(!moves->w_r_c_status() || B[0][7] != -7 || is_check(B, false) || B[0][5] != 0 || B[0][6] != 0)
					return false;
				
				B[0][5] = B[0][4];
				B[0][4] = 0;
				
				if(is_check(B, false))
				{
					B[0][4] = B[0][5];
					B[0][5] = 0;
					return false;
				}
				
				B[0][4] = B[0][5];
				B[0][5] = 0;
				
				return make_move(B, -1, 0, 1, 9, moves);
			}
		}
		
		//for black
		else if(a == 7)
		{
			//left castle
			if(d == 2)
			{
				if(!moves->b_l_c_status() || B[7][0] != 7 || is_check(B, true) || B[7][1] != 0 || B[7][2] != 0 || B[7][3] != 0)
					return false;
				
				B[7][3] = B[7][4];
				B[7][4] = 0;
				
				if(is_check(B, true))
				{
					B[7][4] = B[7][3];
					B[7][3] = 0;
					return false;
				}
				
				B[7][4] = B[7][3];
				B[7][3] = 0;
				
				return make_move(B, -1, 1, 0, 9, moves);
			}
			
			//right castle
			else
			{
				if(!moves->b_r_c_status() || B[7][7] != 7 || is_check(B, true) || B[7][5] != 0 || B[7][6] != 0)
					return false;
				
				B[7][5] = B[7][4];
				B[7][4] = 0;
				
				if(is_check(B, true))
				{
					B[7][4] = B[7][5];
					B[7][5] = 0;
					return false;
				}
				
				B[7][4] = B[7][5];
				B[7][5] = 0;
				
				return make_move(B, -1, 1, 1, 9, moves);
			}
		}
		
		//none
		else
			return false;
	}
	
	//normal move
	else
	{
		if(get_mod(c-a) > 1 || get_mod(d-b) > 1)
			return false;
		
		return make_move(B, a, b, c, d, moves);
	}
	
	//on success
	return true;
}

bool play_move(int B[8][8], int a, int b, int c, int d, bool color, game_stack *moves)
{
	int piece = get_mod(B[a][b]);
	
	//pawn
	if(piece == 2)
	{
		if(pawn(B, a, b, c, d, moves))
			return true;
	}
	
	//knight
	else if(piece == 3)
	{
		if(knight(B, a, b, c, d, moves))
			return true;
	}
	
	//bishop
	else if(piece == 5)
	{
		if(bishop(B, a, b, c, d, moves))
			return true;
	}
	
	//rook
	else if(piece == 7)
	{
		if(rook(B, a, b, c, d, moves))
			return true;
	}
	
	//queen
	else if(piece == 11)
	{
		if(queen(B, a, b, c, d, moves))
		return true;
	}
	
	//king
	else if(piece == 13)
	{
		if(king(B, a, b, c, d, moves))
			return true;
	}
	
	else
		return error_message(-1);	
	
	return error_message(5);
}

bool validate_move(int B[8][8], int a, int b, int c, int d, bool color, game_stack *moves)
{
	//on same square
	if(a == c && b == d)
		return error_message(1);
	
	//empty square
	if(B[a][b] == 0)
		return error_message(4);
	
	//not your piece and capture own piece
	//black color
	if(color)
	{
		if(B[a][b] < 0)
			return error_message(2);
		
		if(B[c][d] > 0)
			return error_message(3);
	}
	
	//white color
	else
	{
		if(B[a][b] > 0)
			return error_message(2);
		
		if(B[c][d] < 0)
			return error_message(3);
	}
	
	return play_move(B, a, b, c, d, color, moves);
}

bool validate_input(int B[8][8], char a, char b, char c, char d, bool color, game_stack *moves)
{
	if(a < 'A' || a > 'H' || b < '1' || b > '8')
		return error_message(0);
	
	if(c < 'A' || c > 'H' || d < '1' || d > '8')
		return error_message(0);
	
	return validate_move(B, b-'1', a-'A', d-'1', c-'A', color, moves);
}

void human_play(bool color, int B[8][8], game_stack *moves)
{
	char a, b, temp, c, d;
	
	//take user input as move and validate move

	do
	{
		display(B, color);
		cout<<endl<<"Enter your move: ";
		cin>>a>>b>>temp>>c>>d;
		if(a == 'u' && b == 'n' && temp == 'd' && c == 'o')
		{
			if(moves->get_total_moves() >= 2)
			{
				moves->undo(B);
				moves->undo(B);
				cout<<endl<<"Undo Completed";
			}
			else
				cout<<endl<<"No sufficient moves for undo";
		}
	}while((a == 'u' && b == 'n' && temp == 'd' && c == 'o') || validate_input(B, a, b, c, d, color, moves) == false);
}