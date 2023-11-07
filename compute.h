#include<iostream>
using namespace std;

//display board
void display(int B[8][8], bool color)
{
	char A = 'A';
	cout<<endl<<endl;
	
	//white
	if(!color)
	{
		for(int i = 7 ; i >= 0 ; i--)
		{
			cout<<endl<<i+1<<":";
			for(int j = 0 ; j < 8 ; j++)
			{
				if(B[i][j] > -1)
					cout<<" ";
				if(B[i][j] > -10 && B[i][j] < 10)
					cout<<" ";
				if(B[i][j] == 0)
					cout<<" -";
				else
					cout<<" "<<B[i][j];
			}
		}
		cout<<endl<<"**********************************"<<endl<<"  ";
		for(int i = 0 ; i < 8 ; i++)
			cout<<"   "<<char(A+i);
	}
	
	else
	{
		for(int i = 0 ; i < 8 ; i++)
		{
			cout<<endl<<i+1<<":";
			for(int j = 7 ; j >= 0 ; j--)
			{
				if(B[i][j] > -1)
					cout<<" ";
				if(B[i][j] > -10 && B[i][j] < 10)
					cout<<" ";
				if(B[i][j] == 0)
					cout<<" -";
				else
					cout<<" "<<B[i][j];
			}
		}
		cout<<endl<<"**********************************"<<endl<<"  ";
		for(int i = 0 ; i < 8 ; i++)
			cout<<"   "<<char(A+8-i-1);
	}
	cout<<endl;
}

//get positive value
int get_mod(int n)
{
	if(n > 0)
		return n;
	return n*(-1);
}

//game stack
class game_stack
{
	private:
	int x_1[20], y_1[20], x_2[20], y_2[20], captured[20];
	int top, undo_moves;
	int w_l_c, w_r_c, b_l_c, b_r_c;
	
	public:
	game_stack()
	{
		top = 0;
		undo_moves = 0;
		
		w_l_c = -1;
		w_r_c = -1;
		b_l_c = -1;
		b_r_c = -1;
	}
	
	//get total moves
	int get_total_moves()
	{
		return top;
	}
	
	//steps repeat
	bool steps_repeat()
	{
		if(top < 12)
			return false;
		
		else
		{
			if(x_1[(top+19)%20] == x_1[(top+15)%20] && x_1[(top+19)%20] == x_1[(top+11)%20] && y_1[(top+19)%20] == y_1[(top+15)%20] && y_1[(top+19)%20] == y_1[(top+11)%20] && x_2[(top+19)%20] == x_2[(top+15)%20] && x_2[(top+19)%20] == x_2[(top+11)%20] && y_2[(top+19)%20] == y_2[(top+15)%20] && y_2[(top+19)%20] == y_2[(top+11)%20])
			{
				if(x_1[(top+18)%20] == x_1[(top+14)%20] && x_1[(top+18)%20] == x_1[(top+10)%20] && y_1[(top+18)%20] == y_1[(top+14)%20] && y_1[(top+18)%20] == y_1[(top+10)%20] && x_2[(top+18)%20] == x_2[(top+14)%20] && x_2[(top+18)%20] == x_2[(top+10)%20] && y_2[(top+18)%20] == y_2[(top+14)%20] && y_2[(top+18)%20] == y_2[(top+10)%20])
				{
					if(x_1[(top+17)%20] == x_1[(top+13)%20] && x_1[(top+17)%20] == x_1[(top+9)%20] && y_1[(top+17)%20] == y_1[(top+13)%20] && y_1[(top+17)%20] == y_1[(top+9)%20] && x_2[(top+17)%20] == x_2[(top+13)%20] && x_2[(top+17)%20] == x_2[(top+9)%20] && y_2[(top+17)%20] == y_2[(top+13)%20] && y_2[(top+17)%20] == y_2[(top+9)%20])
					{
						if(x_1[(top+16)%20] == x_1[(top+12)%20] && x_1[(top+16)%20] == x_1[(top+8)%20] && y_1[(top+16)%20] == y_1[(top+12)%20] && y_1[(top+16)%20] == y_1[(top+8)%20] && x_2[(top+16)%20] == x_2[(top+12)%20] && x_2[(top+16)%20] == x_2[(top+8)%20] && y_2[(top+16)%20] == y_2[(top+12)%20] && y_2[(top+16)%20] == y_2[(top+8)%20])
						{
							return true;
						}
					}
				}
			}
		}
			
		return false;
	}
	
	//add move to stack
	void add(int B[8][8], int a, int b, int c, int d)
	{
		//left white rook
		if(a == 0 && b == 0 && w_l_c == -1 && B[a][b] == -7)
			w_l_c = top;
		
		//right white rook
		if(a == 0 && b == 7 && w_r_c == -1 && B[a][b] == -7)
			w_r_c = top;
		
		//left black rook
		if(a == 7 && b == 0 && b_l_c == -1 && B[a][b] == 7)
			b_l_c = top;
		
		//right black rook
		if(a == 7 && b == 7 && b_r_c == -1 && B[a][b] == 7)
			b_r_c = top;
		
		//white king
		if(a == 0 && b == 4 && B[a][b] == -13)
		{
			if(w_l_c == -1)
				w_l_c = top;
			if(w_r_c == -1)
				w_r_c = top;
		}
		
		//black king
		if(a == 7 && b == 4 && B[a][b] == 13)
		{
			if(b_l_c == -1)
				b_l_c = top;
			if(b_r_c == -1)
				b_r_c = top;
		}
		
		//normal moves
		if(a >= 0)
		{
			captured[top%20] = B[c][d];
			B[c][d] = B[a][b];
			B[a][b] = 0;
		}
		
		//for castle
		else if(a == -1)
		{
			captured[top%20] = 0;
			//for white
			if(b == 0)
			{
				//left castle
				if(c == 0)
				{
					B[0][2] = B[0][4];
					B[0][4] = 0;
					B[0][3] = B[0][0];
					B[0][0] = 0;
				}
				
				//right castle
				else
				{
					B[0][6] = B[0][4];
					B[0][4] = 0;
					B[0][5] = B[0][7];
					B[0][7] = 0;
				}
			}
			
			//for black
			else
			{
				//left castle
				if(c == 0)
				{
					B[7][2] = B[7][4];
					B[7][4] = 0;
					B[7][3] = B[7][0];
					B[7][0] = 0;
				}
				
				//right castle
				else
				{
					B[7][6] = B[7][4];
					B[7][4] = 0;
					B[7][5] = B[7][7];
					B[7][7] = 0;
				}
			}
		}
		
		//for promotion
		else if(a == -2)
		{
			//for white
			if(b < 0)
			{
				captured[top%20] = B[7][d];
				B[7][d] = b;
				B[6][c] = 0;
			}
			
			//for black
			else
			{
				captured[top%20] = B[0][d];
				B[0][d] = b;
				B[1][c] = 0;
			}
		}
		
		//for enpass
		else if(a == -3)
		{
			//white
			if(b == 0)
			{
				B[4][c] = 0;
				B[5][d] = -2;
				B[4][d] = 0;
				captured[top%20] = 2;
			}
			
			//black
			else
			{
				B[3][c] = 0;
				B[2][d] = 2;
				B[3][d] = 0;
				captured[top%20] = -2;
			}
		}
		
		//any error
		else
			cout<<endl<<endl<<"An Error Occured: Unknown move found";
		
		//note down moves
		x_1[top%20] = a;
		y_1[top%20] = b;
		x_2[top%20] = c;
		y_2[top%20] = d;
		top = top + 1;
		
		if(undo_moves < 20)
			undo_moves++;
	}
	
	//undo a move
	void undo(int B[8][8])
	{
		int a, b, c, d, e;
		if(undo_moves <= 0)
			cout<<endl<<"Can't undo more moves";
		
		else
		{
			top = top - 1;
			undo_moves--;
			
			a = x_1[top%20];
			b = y_1[top%20];
			c = x_2[top%20];
			d = y_2[top%20];
			e = captured[top%20];
			
			if(w_l_c == top)
				w_l_c = -1;
			
			if(w_r_c == top)
				w_r_c = -1;
			
			if(b_l_c == top)
				b_l_c = -1;
			
			if(b_r_c == top)
				b_r_c = -1;
			
			//normal moves
			if(a >= 0)
			{
				B[a][b] = B[c][d];
				B[c][d] = e;
			}
		
			//for castle
			else if(a == -1)
			{
				//for white
				if(b == 0)
				{
					//left castle
					if(c == 0)
					{
						B[0][4] = B[0][2];
						B[0][2] = 0;
						B[0][0] = B[0][3];
						B[0][3] = 0;
					}
				
					//right castle
					else
					{
						B[0][4] = B[0][6];
						B[0][6] = 0;
						B[0][7] = B[0][5];
						B[0][5] = 0;
					}
				}
			
				//for black
				else
				{
					//left castle
					if(c == 0)
					{
						B[7][4] = B[7][2];
						B[7][2] = 0;
						B[7][0] = B[7][3];
						B[7][3] = 0;
					}
				
					//right castle
					else
					{
						B[7][4] = B[7][6];
						B[7][6] = 0;
						B[7][7] = B[7][5];
						B[7][5] = 0;
					}
				}
			}
		
			//for promotion
			else if(a == -2)
			{
				//for white
				if(b < 0)
				{
					B[7][d] = e;
					B[6][c] = -2;
				}
			
				//for black
				else
				{
					B[0][d] = e;
					B[1][c] = 2;
				}
			}
		
			//for enpass
			else if(a == -3)
			{
				//white
				if(b == 0)
				{
					B[4][c] = -2;
					B[5][d] = 0;
					B[4][d] = 2;
				}
				
				//black
				else
				{
					B[3][c] = 2;
					B[2][d] = 0;
					B[3][d] = -2;
				}
			}
		
			//any error
			else
				cout<<endl<<endl<<"An Error Occured: Unknown move found";
		}
	}
	
	//enpass status
	bool can_enpass(int B[8][8], int a, int b, int c, int d)
	{
		if(y_1[(top+19)%20] != y_2[(top+19)%20] || y_1[(top+19)%20] != d || get_mod(x_2[(top+19)%20]-x_1[(top+19)%20]) != 2)
			return false;
		
		//white
		if(B[a][b] < 0 && x_2[(top+19)%20] == 4)
		{
			if(c == 5 && B[4][d] == 2 && a == 4)
				return true;
		}
		
		//black
		else if(B[a][b] > 0 && x_2[(top+19)%20] == 3)
		{
			if(c == 2 && B[3][d] == -2 && a == 3)
				return true;
		}
		
		else
			return false;
		
		return false;
	}
	
	//castle status
	bool w_l_c_status()
	{
		if(w_l_c == -1)
			return true;
		return false;
	}
	
	bool w_r_c_status()
	{
		if(w_r_c == -1)
			return true;
		return false;
	}
	
	bool b_l_c_status()
	{
		if(b_l_c == -1)
			return true;
		return false;
	}
	
	bool b_r_c_status()
	{
		if(b_r_c == -1)
			return true;
		return false;
	}
};

bool non_principal_diagonal(int B[8][8], int a, int b, int c, int d)
{
	if(b + c != d + a)
		return false;
	
	for(int k = 1 ; k < d - b ; k++)
		if(B[a+k][b+k] != 0)
			return false;
	
	return true;
}

bool principal_diagonal(int B[8][8], int a, int b, int c, int d)
{
	if(b + a != d + c)
		return false;
	
	for(int k = 1 ; k < d - b ; k++)
		if(B[a-k][b+k] != 0)
			return false;
	
	return true;
}

bool vertical(int B[8][8], int a, int b, int c, int d)
{
	if(b != d)
		return false;
	
	for(int k = a + 1 ; k < c ; k++)
		if(B[k][b] != 0)
			return false;
	
	return true;
}

bool horizontal(int B[8][8], int a, int b, int c, int d)
{
	if(a != c)
		return false;
	
	for(int k = b + 1 ; k < d ; k++)
		if(B[a][k] != 0)
			return false;
	
	return true;
}

bool l_shape(int B[8][8], int a, int b, int c, int d)
{
	if((get_mod(c-a) == 2 && get_mod(d-b) == 1) || (get_mod(c-a) == 1 && get_mod(d-b) == 2))
		return true;

	return false;
}

bool are_same_color(int n, bool color)
{
	if(n < 0 && color == false)
		return true;
	
	if(n > 0 && color == true)
		return true;
	
	return false;
}

//get the square on which king is standing
int get_king_square(int B[8][8], bool color)
{
	int id;
	
	//black
	if(color)
		id = 13;
	
	//white
	else
		id = -13;
	
	for(int i = 0 ; i < 8 ; i++)
		for(int j = 0 ; j < 8 ; j++)
			if(B[i][j] == id)
				return (i*8 + j);

	display(B, color);
	cout<<endl<<"An error occured: No king found on board";
		return -1;
}

bool is_check(int B[8][8], bool color)
{
	int N = get_king_square(B, color);
	int x = N / 8;
	int y = N % 8;
	
	//pawn
	//white
	if(!color)
	{
		if(x <= 5 && ((y >= 1 && B[x+1][y-1] == 2) || (y <= 6 && B[x+1][y+1] == 2)))
			return true;
	}
	
	//black
	else
	{
		if(x >= 2 && ((y >= 1 && B[x-1][y-1] == -2) || (y <= 6 && B[x-1][y+1] == -2)))
			return true;
	}
	
	//knight
	{
		int move_x[] = {-1, -1, -2, -2, 1, 1, 2, 2};
		int move_y[] = {-2, 2, -1, 1, -2, 2, -1, 1};
		
		for(int k = 0 ; k < 8 ; k++)
			if(x+move_x[k] >= 0 && x+move_x[k] <= 7 && y+move_y[k] >= 0 && y+move_y[k] <= 7 && get_mod(B[x+move_x[k]][y+move_y[k]]) == 3 && !are_same_color(B[x+move_x[k]][y+move_y[k]], color))
				return true;
	}
	
	//rook and queen
	{
		int move_x[] = {-1, 1, 0, 0};
		int move_y[] = {0, 0, -1, 1};
		
		for(int k = 0 ; k < 4 ; k++)
		{
			for(int z = 1 ; x+move_x[k]*z >= 0 && x+move_x[k]*z <= 7 && y+move_y[k]*z >= 0 && y+move_y[k]*z <= 7 && (B[x+move_x[k]*z][y+move_y[k]*z] == 0 || !are_same_color(B[x+move_x[k]*z][y+move_y[k]*z], color)) ; z++)
			{
				if(B[x+move_x[k]*z][y+move_y[k]*z] != 0)
				{
					if(get_mod(B[x+move_x[k]*z][y+move_y[k]*z]) == 7 || get_mod(B[x+move_x[k]*z][y+move_y[k]*z]) == 11)
						return true;
					else
						break;
				}
			}
		}
	}
	
	//bishop and queen
	{
		int move_x[] = {-1, 1, 1, -1};
		int move_y[] = {1, 1, -1, -1};
		
		for(int k = 0 ; k < 4 ; k++)
		{
			for(int z = 1 ; x+move_x[k]*z >= 0 && x+move_x[k]*z <= 7 && y+move_y[k]*z >= 0 && y+move_y[k]*z <= 7 && (B[x+move_x[k]*z][y+move_y[k]*z] == 0 || !are_same_color(B[x+move_x[k]*z][y+move_y[k]*z], color)) ; z++)
			{
				if(B[x+move_x[k]*z][y+move_y[k]*z] != 0)
				{
					if(get_mod(B[x+move_x[k]*z][y+move_y[k]*z]) == 5 || get_mod(B[x+move_x[k]*z][y+move_y[k]*z]) == 11)
						return true;
					else
						break;
				}
			}
		}
	}
	
	//king
	if((x<=6 && y<=6 && get_mod(B[x+1][y+1])==13) || (x<=6 && get_mod(B[x+1][y])==13) || (x<=6 && y>=1 && get_mod(B[x+1][y-1])==13) || (y>=1 && get_mod(B[x][y-1])==13) || (x>=1 && y>=1 && get_mod(B[x-1][y-1])==13) || (x>=1 && get_mod(B[x-1][y])==13) || (x>=1 && y<=6 && get_mod(B[x-1][y+1])==13) || (y<=6 && get_mod(B[x][y+1])==13))
		return true;
	
	return false;
}

//validate check
bool check_verification(int B[8][8], bool color, game_stack *moves)
{
	//if it is a check, then return false by undoing the move
	if(is_check(B, color))
	{
		moves->undo(B);
		return false;
	}
	
	return true;
}

//make a move and check for any attack on king
bool make_move(int B[8][8], int a, int b, int c, int d, game_stack *moves)
{
	bool col;
	
	//assign color
	//normal moves
	if(a >= 0)
	{
		if(B[a][b] > 0)
			col = true;
		else
			col = false;
	}
	
	//special moves
	else if(a == -2)
	{
		if(b > 0)
			col = true;
		else
			col = false;
	}
	
	else
	{
		if(b == 1)
			col = true;
		else
			col = false;
	}
	
	moves->add(B, a, b, c, d);

	//verify any attack on king
		return check_verification(B, col, moves);
}

bool insufficient_pieces(int B[8][8])
{
	bool b_count = false;
	bool w_count = false;
	
	for(int i = 0 ; i < 8 ; i++)
		for(int j = 0 ; j < 8 ; j++)
			if(B[i][j] != 0 && B[i][j] != -13 && B[i][j] != 13)
			{
				//return if pawns are present
				if(B[i][j] == 2 || B[i][j] == -2 || B[i][j] == 7 || B[i][j] == -7 || B[i][j] == 11 || B[i][j] == -11)
					return false;
				
				//count for black
				else if(B[i][j] > 0)
				{
					if(b_count == true)
						return false;
					b_count = true;
				}
				
				//count for white
				else
				{
					if(w_count == true)
						return false;
					w_count = true;
				}
			}
			
	return true;
}

int game_status(int B[8][8], bool color, game_stack *moves)
{
	if(moves->steps_repeat())
	{
		cout<<endl<<"3 steps repeated";
		return 0;
	}
		
	if(insufficient_pieces(B))
	{
		cout<<endl<<"No sufficient pieces for checkmate";
		return 0;
	}
	
	for(int i = 0 ; i < 8 ; i++)
		for(int j = 0 ; j < 8 ; j++)
			if(B[i][j] != 0 && are_same_color(B[i][j], color))
			{
				//pawn
				if(get_mod(B[i][j]) == 2)
				{
					//white
					if(B[i][j] < 0)
					{
						//jump
						if(i == 1 && B[2][j] == 0 && B[3][j] == 0 && make_move(B, i, j, i+2, j, moves))
						{
							moves->undo(B);
							return -1;
						}
						
						//push
						if(B[i+1][j] == 0)
						{
							//promotion
							if(i == 6)
							{
								if(make_move(B, -2, -11, j, j, moves))
								{
									moves->undo(B);
									return -1;
								}
							}
							
							//normal move
							else
							{
								if(make_move(B, i, j, i+1, j, moves))
								{
									moves->undo(B);
									return -1;
								}
							}
						}
						
						//enpass left
						if(j >= 1 && i == 4 && B[5][j-1] == 0 && moves->can_enpass(B, i, j, i+1, j-1) && make_move(B, -3, 0, j, j-1, moves))
						{
							moves->undo(B);
							return -1;
						}
						
						//enpass right
						if(j <= 6 && i == 4 && B[5][j+1] == 0 && moves->can_enpass(B, i, j, i+1, j+1) && make_move(B, -3, 0, j, j+1, moves))
						{
							moves->undo(B);
							return -1;
						}
						
						//capture left
						if(j >= 1 && B[i+1][j-1] > 0)
						{
							//promotion
							if(i == 6)
							{
								if(make_move(B, -2, -11, j, j-1, moves))
								{
									moves->undo(B);
									return -1;
								}
								
							}
							
							//normal move
							else
							{
								if(make_move(B, i, j, i+1, j-1, moves))
								{
									moves->undo(B);
									return -1;
								}
							}	
						}
						
						//capture right
						if(j <= 6 && B[i+1][j+1] > 0)
						{
							//promotion
							if(i == 6)
							{
								if(make_move(B, -2, -11, j, j+1, moves))
								{
									moves->undo(B);
									return -1;
								}
							}
							
							//normal move
							else
							{
								if(make_move(B, i, j, i+1, j+1, moves))
								{
									moves->undo(B);
									return -1;
								}
							}	
						}
					}
					
					//black
					else
					{
						//jump
						if(i == 6 && B[5][j] == 0 && B[4][j] == 0 && make_move(B, i, j, i-2, j, moves))
						{
							moves->undo(B);
							return -1;
						}
						
						//push
						if(B[i-1][j] == 0)
						{
							//promotion
							if(i == 1)
							{
								if(make_move(B, -2, 11, j, j, moves))
								{
									moves->undo(B);
									return -1;
								}
							}
							
							//normal move
							else
							{
								if(make_move(B, i, j, i-1, j, moves))
								{
									moves->undo(B);
									return -1;
								}
							}
						}
						
						//enpass left
						if(j >= 1 && i == 3 && B[2][j-1] == 0 && moves->can_enpass(B, i, j, i-1, j-1) && make_move(B, -3, 1, j, j-1, moves))
						{
							moves->undo(B);
							return -1;
						}
						
						//enpass right
						if(j <= 6 && i == 3 && B[2][j+1] == 0 && moves->can_enpass(B, i, j, i-1, j+1) && make_move(B, -3, 1, j, j+1, moves))
						{
							moves->undo(B);
							return -1;
						}
						
						//capture left
						if(j >= 1 && B[i-1][j-1] < 0)
						{
							//promotion
							if(i == 1)
							{
								if(make_move(B, -2, 11, j, j-1, moves))
								{
									moves->undo(B);
									return -1;
								}
							}
							
							//normal move
							else
							{
								if(make_move(B, i, j, i-1, j-1, moves))
								{
									moves->undo(B);
									return -1;
								}
							}
						}
						
						//capture right
						if(j <= 6 && B[i-1][j+1] < 0)
						{
							//promotion
							if(i == 1)
							{
								if(make_move(B, -2, 11, j, j+1, moves))
								{
									moves->undo(B);
									return -1;
								}
							}
							
							//normal move
							else
							{
								if(make_move(B, i, j, i-1, j+1, moves))
								{
									moves->undo(B);
									return -1;
								}
							}
						}
					}
				}
				
				//knight
				else if(get_mod(B[i][j]) == 3)
				{
					int move_x[] = {-2, -2, -1, -1, 1, 1, 2, 2};
					int move_y[] = {-1, 1, -2, 2, -2, 2, -1, 1};
					
					for(int k = 0 ; k < 8 ; k++)
					{
						if(j+move_y[k] >= 0 && j+move_y[k] <= 7 && i+move_x[k] <= 7 && i+move_x[k] >= 0 && l_shape(B, i, j, i+move_x[k], j+move_y[k]))
						{
							if((B[i+move_x[k]][j+move_y[k]] == 0 || !are_same_color(B[i+move_x[k]][j+move_y[k]], color)) && make_move(B, i, j, i+move_x[k], j+move_y[k], moves))
							{
								moves->undo(B);
								return -1;
							}
						}
					}
				}
				
				//bishop
				else if(get_mod(B[i][j]) == 5)
				{
					int move_x[] = {-1, 1, -1, 1};
					int move_y[] = {-1, -1, 1, 1};
					
					for(int z = 0 ; z < 4 ; z++)
					{
						for(int k = 1 ; i+move_x[z]*k >= 0 && i+move_x[z]*k <= 7 && j+move_y[z]*k >= 0 && j+move_y[z]*k <= 7 && (B[i+move_x[z]*k][j+move_y[z]*k] == 0 || !are_same_color(B[i+move_x[z]*k][j+move_y[z]*k], color)); k++)
						{
							if(make_move(B, i, j, i+move_x[z]*k, j+move_y[z]*k, moves))
							{
								moves->undo(B);
								return -1;
							}
							if(B[i+move_x[z]*k][j+move_y[z]*k] != 0)
								break;
						}
					}
				}
				
				//rook
				else if(get_mod(B[i][j]) == 7)
				{
					int move_x[] = {-1, 1, 0, 0};
					int move_y[] = {0, 0, -1, 1};
					
					for(int z = 0 ; z < 4 ; z++)
					{
						for(int k = 1 ; i+move_x[z]*k >= 0 && i+move_x[z]*k <= 7 && j+move_y[z]*k >= 0 && j+move_y[z]*k <= 7 && (B[i+move_x[z]*k][j+move_y[z]*k] == 0 || !are_same_color(B[i+move_x[z]*k][j+move_y[z]*k], color)); k++)
						{
							if(make_move(B, i, j, i+move_x[z]*k, j+move_y[z]*k, moves))
							{
								moves->undo(B);
								return -1;
							}
							if(B[i+move_x[z]*k][j+move_y[z]*k] != 0)
								break;
						}
					}
				}
				
				//queen
				else if(get_mod(B[i][j]) == 11)
				{
					//ROOK
					{
						int move_x[] = {-1, 1, 0, 0};
						int move_y[] = {0, 0, -1, 1};
						
						for(int z = 0 ; z < 4 ; z++)
						{
							for(int k = 1 ; i+move_x[z]*k >= 0 && i+move_x[z]*k <= 7 && j+move_y[z]*k >= 0 && j+move_y[z]*k <= 7 && (B[i+move_x[z]*k][j+move_y[z]*k] == 0 || !are_same_color(B[i+move_x[z]*k][j+move_y[z]*k], color)); k++)
							{
								if(make_move(B, i, j, i+move_x[z]*k, j+move_y[z]*k, moves))
								{
									moves->undo(B);
									return -1;
								}
								if(B[i+move_x[z]*k][j+move_y[z]*k] != 0)
									break;
							}
						}
					}
					
					//BISHOP
					{
						int move_x[] = {-1, 1, -1, 1};
						int move_y[] = {-1, -1, 1, 1};
						
						for(int z = 0 ; z < 4 ; z++)
						{
							for(int k = 1 ; i+move_x[z]*k >= 0 && i+move_x[z]*k <= 7 && j+move_y[z]*k >= 0 && j+move_y[z]*k <= 7 && (B[i+move_x[z]*k][j+move_y[z]*k] == 0 || !are_same_color(B[i+move_x[z]*k][j+move_y[z]*k], color)); k++)
							{
								if(make_move(B, i, j, i+move_x[z]*k, j+move_y[z]*k, moves))
								{
									moves->undo(B);
									return -1;
								}
								if(B[i+move_x[z]*k][j+move_y[z]*k] != 0)
									break;
							}
						}
					}
				}
				
				//king
				else
				{
					int move_x[] = {0, 1, 1, 1, 0, -1, -1, -1};
					int move_y[] = {-1, -1, 0, 1, 1, 1, 0, -1};
					
					for(int z = 0 ; z < 8 ; z++)
					{
						if(i+move_x[z] >= 0 && i+move_x[z] <= 7 && j+move_y[z] >= 0 && j+move_y[z] <= 7 && (B[i+move_x[z]][j+move_y[z]] == 0 || !are_same_color(B[i+move_x[z]][j+move_y[z]], color)))
						{
							if(make_move(B, i, j, i+move_x[z], j+move_y[z], moves))
							{
								moves->undo(B);
								return -1;
							}
						}
					}
					
					//castles
					if(j == 4)
					{
						//black castles
						if(color)
						{
							if(i == 7)
							{
								//left castle
								if(B[7][0] == 7 && B[7][1] == 0 && B[7][2] == 0 && B[7][3] == 0 && moves->b_l_c_status())
								{
									B[7][3] = B[7][4];
									B[7][4] = 0;
			
									if(is_check(B, true))
									{
										B[7][4] = B[7][3];
										B[7][3] = 0;
									}
									else
									{
										B[7][4] = B[7][3];
										B[7][3] = 0;
			
										if(make_move(B, -1, 1, 0, 9, moves))
										{
											moves->undo(B);
											return -1;
										}
									}
								}
								
								//right castle
								if(B[7][7] == 7 && B[7][5] == 0 && B[7][6] == 0 && moves->b_r_c_status())
								{
									B[7][5] = B[7][4];
									B[7][4] = 0;
			
									if(is_check(B, true))
									{
										B[7][4] = B[7][5];
										B[7][5] = 0;
									}
									else
									{
										B[7][4] = B[7][5];
										B[7][5] = 0;
			
										if(make_move(B, -1, 1, 1, 9, moves))
										{
											moves->undo(B);
											return -1;
										}
									}
								}
							}
						}
					
						//white castles
						else
						{
							if(i == 0)
							{
								//left castle
								if(B[0][0] == -7 && B[0][1] == 0 && B[0][2] == 0 && B[0][3] == 0 && moves->w_l_c_status())
								{
									B[0][3] = B[0][4];
									B[0][4] = 0;
			
									if(is_check(B, false))
									{
										B[0][4] = B[0][3];
										B[0][3] = 0;
									}
									else
									{
										B[0][4] = B[0][3];
										B[0][3] = 0;
			
										if(make_move(B, -1, 0, 0, 9, moves))
										{
											moves->undo(B);
											return -1;
										}
									}
								}
								
								//right castle
								if(B[0][7] == -7 && B[0][5] == 0 && B[0][6] == 0 && moves->w_r_c_status())
								{
									B[0][5] = B[0][4];
									B[0][4] = 0;
			
									if(is_check(B, false))
									{
										B[0][4] = B[0][5];
										B[0][5] = 0;
									}
									else
									{
										B[0][4] = B[0][5];
										B[0][5] = 0;
			
										if(make_move(B, -1, 0, 1, 9, moves))
										{
											moves->undo(B);
											return -1;
										}
									}
								}
							}
						}
					}
				}
			}
			
	if(is_check(B, color))
		return 1;
	return 0;
}