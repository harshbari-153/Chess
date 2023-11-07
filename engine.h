#include"compute.h"

//id to points
int id_to_points(int id)
{
	if(id == 2 || id == -2)
		return 1;
	
	else if(id == -3 || id == 3 || id == -5 || id == 5)
		return 3;
	
	else if(id == -7 || id == 7)
		return 5;
	
	else if(id == -11 || id == 11)
		return 9;
	
	else
		return 0;
}

int extra_steps(int B[8][8], int i, int j, bool color, game_stack *moves)
{
	int count = 0;
	//pawn
	if(get_mod(B[i][j]) == 2)
	{
		//white
		if(B[i][j] < 0 && color == false)
		{
			if(i == 1 && B[2][j] == 0 && B[3][j] == 0)
				count++;
			if(B[i+1][j] == 0)
				count++;
			if(j >= 1 && B[i+1][j-1] != 0 && !are_same_color(B[i+1][j-1], false))
				count++;
			if(j <= 6 && B[i+1][j+1] != 0 && !are_same_color(B[i+1][j+1], false))
				count++;
		}
		
		//black
		else if(B[i][j] > 0 && color == true)
		{
			if(i == 6 && B[5][j] == 0 && B[4][j] == 0)
				count++;
			if(B[i-1][j] == 0)
				count++;
			if(j >= 1 && B[i-1][j-1] != 0 && !are_same_color(B[i-1][j-1], true))
				count++;
			if(j <= 6 && B[i-1][j+1] != 0 && !are_same_color(B[i-1][j+1], true))
				count++;
		}
		
		else
			cout<<endl<<"An error occured: unknown piece caught: "<<B[i][j]<<color;
	}
	
	//knight
	else if(get_mod(B[i][j]) == 3)
	{
		int move_x[] = {-2, -2, -1, -1, 1, 1, 2, 2};
		int move_y[] = {-1, 1, -2, 2, -2, 2, -1, 1};
		
		for(int k = 0 ; k < 8 ; k++)
		{
			if(i + move_x[k] >= 0 && i + move_x[k] <= 7 && j + move_y[k] >= 0 && j + move_y[k] <= 7 && (B[i + move_x[k]][j + move_y[k]] == 0 || !are_same_color(B[i + move_x[k]][j + move_y[k]], color)))
				count++;
		}
	}
	
	//bishop
	else if(get_mod(B[i][j]) == 5)
	{
		int move_x[] = {-1, 1, -1, 1};
		int move_y[] = {-1, -1, 1, 1};
		
		for(int k = 0 ; k < 4 ; k++)
		{
			for(int z = 1 ; i+move_x[k]*z >= 0 && i+move_x[k]*z <= 7 && j+move_y[k]*z >= 0 && j+move_y[k]*z <= 7 && (B[i+move_x[k]*z][j+move_y[k]*z] == 0 || !are_same_color(B[i+move_x[k]*z][j+move_y[k]*z], color)) ; z++)
			{
				count++;
				if(B[i+move_x[k]*z][j+move_y[k]*z] != 0)
						break;
			}
		}
	}
	
	//rook
	else if(get_mod(B[i][j]) == 7)
	{
		int move_x[] = {-1, 1, 0, 0};
		int move_y[] = {0, 0, -1, 1};
		
		for(int k = 0 ; k < 4 ; k++)
		{
			for(int z = 1 ; i+move_x[k]*z >= 0 && i+move_x[k]*z <= 7 && j+move_y[k]*z >= 0 && j+move_y[k]*z <= 7 && (B[i+move_x[k]*z][j+move_y[k]*z] == 0 || !are_same_color(B[i+move_x[k]*z][j+move_y[k]*z], color)) ; z++)
			{
				count++;
				if(B[i+move_x[k]*z][j+move_y[k]*z] != 0)
						break;
			}
		}
	}
	
	//queen
	else if(get_mod(B[i][j]) == 11)
	{
		//BISHOP
		{
			int move_x[] = {-1, 1, -1, 1};
			int move_y[] = {-1, -1, 1, 1};
			
			for(int k = 0 ; k < 4 ; k++)
			{
				for(int z = 1 ; i+move_x[k]*z >= 0 && i+move_x[k]*z <= 7 && j+move_y[k]*z >= 0 && j+move_y[k]*z <= 7 && (B[i+move_x[k]*z][j+move_y[k]*z] == 0 || !are_same_color(B[i+move_x[k]*z][j+move_y[k]*z], color)) ; z++)
				{
					count++;
					if(B[i+move_x[k]*z][j+move_y[k]*z] != 0)
							break;
				}
			}
		}
		
		//ROOK
		{
			int move_x[] = {-1, 1, 0, 0};
			int move_y[] = {0, 0, -1, 1};
			
			for(int k = 0 ; k < 4 ; k++)
			{
				for(int z = 1 ; i+move_x[k]*z >= 0 && i+move_x[k]*z <= 7 && j+move_y[k]*z >= 0 && j+move_y[k]*z <= 7 && (B[i+move_x[k]*z][j+move_y[k]*z] == 0 || !are_same_color(B[i+move_x[k]*z][j+move_y[k]*z], color)) ; z++)
				{
					count++;
					if(B[i+move_x[k]*z][j+move_y[k]*z] != 0)
							break;
				}
			}
		}
	}
	
	//king
	else if(get_mod(B[i][j]) == 13)
	{
		int move_x[] = {0, 1, 1, 1, 0, -1, -1, -1};
		int move_y[] = {-1, -1, 0, 1, 1, 1, 0, -1};
		
		for(int k = 0 ; k < 8 ; k++)
		{
			if(i + move_x[k] >= 0 && i + move_x[k] <= 7 && j + move_y[k] >= 0 && j + move_y[k] <= 7 && (B[i + move_x[k]][j + move_y[k]] == 0 || !are_same_color(B[i + move_x[k]][j + move_y[k]], color)))
				count++;
		}
		
		//white
		if(B[i][j] < 0 && color == false && i == 0 && j == 4)
		{
			if(B[0][0] == -7 && moves->w_l_c_status())
				count++;
			if(B[0][7] == -7 && moves->w_r_c_status())
				count++;
		}
		
		//black
		if(B[i][j] > 0 && color == true && i == 7 && j == 4)
		{
			if(B[7][0] == 7 && moves->b_l_c_status())
				count++;
			if(B[7][7] == 7 && moves->b_r_c_status())
				count++;
		}
	}
	
	else
		cout<<endl<<"An error occured: unknown piece present at time of board score";
	
	return count;
}

int board_score(int B[8][8], bool color, game_stack *moves)
{
	int sum = 0, temp = 0;
	int bk, wk;
	
	//for black
	if(color)
	{
		for(int i = 0 ; i < 8 ; i++)
			for(int j = 0 ; j < 8 ; j++)
				if(B[i][j] != 0)
				{
					if(B[i][j] > 0)
						sum = sum + id_to_points(B[i][j])*15 + extra_steps(B, i, j, true, moves);
					else
						sum = sum - id_to_points(B[i][j])*15 - extra_steps(B, i, j, false, moves);
				}
	}
	
	//for white
	else
	{
		for(int i = 0 ; i < 8 ; i++)
			for(int j = 0 ; j < 8 ; j++)
				if(B[i][j] != 0)
				{
					if(B[i][j] > 0)
						sum = sum - id_to_points(B[i][j])*15 - extra_steps(B, i, j, true, moves);
					else
						sum = sum + id_to_points(B[i][j])*15 + extra_steps(B, i, j, false, moves);
				}
	}
	
	//count for parser pawn
	//white
	if(color == false)
	{
		for(int i = 0 ; i < 3 ; i++)
			for(int j = 0 ; j < 8 ; j++)
				if(B[4+i][j] == -2)
					sum = sum + (i+1)*5;
		for(int i = 0 ; i < 2 ; i++)
			for(int j = 0 ; j < 8 ; j++)
				if(B[2+i][j] == -2)
					sum = sum + (i+1)*2;
		
		for(int i = 0 ; i < 3 ; i++)
			for(int j = 0 ; j < 8 ; j++)
				if(B[3-i][j] == 2)
					sum = sum - (i+1)*5;
		for(int i = 0 ; i < 2 ; i++)
			for(int j = 0 ; j < 8 ; j++)
				if(B[5-i][j] == 2)
					sum = sum - (i+1)*2;
	}
	
	//black
	else
	{
		for(int i = 0 ; i < 3 ; i++)
			for(int j = 0 ; j < 8 ; j++)
				if(B[4+i][j] == -2)
					sum = sum - (i+1)*5;
		for(int i = 0 ; i < 2 ; i++)
			for(int j = 0 ; j < 8 ; j++)
				if(B[2+i][j] == -2)
					sum = sum - (i+1)*2;
		
		for(int i = 0 ; i < 3 ; i++)
			for(int j = 0 ; j < 8 ; j++)
				if(B[3-i][j] == 2)
					sum = sum + (i+1)*5;
		for(int i = 0 ; i < 2 ; i++)
			for(int j = 0 ; j < 8 ; j++)
				if(B[5-i][j] == 2)
					sum = sum + (i+1)*2;
	}
	
	//count for distance between 2 kings
	bk = get_king_square(B, true);
	wk = get_king_square(B, false);
	sum = sum - ((get_mod((bk/8) - (wk/8)) + get_mod((bk%8) - (wk%8)))/2 + ((get_mod((bk/8) - (wk/8)) + get_mod((bk%8) - (wk%8)))%2));
	
	//push king on corners
	if(color == true)
	{
		if((wk/8) <= 3)
			sum = sum + 3 - (wk/8);
		else 
			sum = sum + (wk/8) - 4;
		
		if((wk%8) <= 3)
			sum = sum + 3 - (wk%8);
		else 
			sum = sum + (wk%8) - 4;
		
	}
	
	else
	{
		if((bk/8) <= 3)
			sum = sum + 3 - (bk/8);
		else 
			sum = sum + (bk/8) - 4;
		
		if((bk%8) <= 3)
			sum = sum + 3 - (bk%8);
		else 
			sum = sum + (bk%8) - 4;
	}
	
	return sum;
}

int max(int a, int b)
{
	if(a > b)
		return a;
	return b;
}

int min(int a, int b)
{
	if(a < b)
		return a;
	return b;
}

void id_to_piece(int n)
{
	if(n == 3 || n == -3)
		cout<<"Knight";
	
	else if(n == 5 || n == -5)
		cout<<"Bishop";
	
	else if(n == 7 || n == -7)
		cout<<"Rook";
	
	else if(n == 11 || n == -11)
		cout<<"Queen";
	
	else
		cout<<"Unknown:"<<n;
}

void print_computer_move(int B[8][8], int a, int b, int c, int d)
{
	//normal move
	if(a >= 0)
		cout<<endl<<"Computer Move: "<<char(b+'A')<<a+1<<":"<<char(d+'A')<<c+1;
	
	//castle
	else if(a == -1)
		if(c == 0)
			cout<<endl<<"Computer Move: Big Castle";
		else
			cout<<endl<<"Computer Move: Small Castle";
		
	//promotion
	else if(a == -2)
	{
		//white
		if(b < 0)
		{
			cout<<endl<<"Computer Move: "<<char(c+'A')<<"7:"<<char(d+'A')<<"8 Promotion: ";
			id_to_piece(B[7][d]);
		}
		//black
		else
		{
			cout<<endl<<"Computer Move: "<<char(c+'A')<<"2:"<<char(d+'A')<<"1 Promotion: ";
			id_to_piece(B[0][d]);
		}
		
	}
	
	//enpass
	else if(a == -3)
		//white
		if(b == 0)
			cout<<endl<<"Computer Move: "<<char(c+'A')<<"4:"<<char(d+'A')<<"5";
		//black
		else
			cout<<endl<<"Computer Move: "<<char(c+'A')<<"3:"<<char(d+'A')<<"2";
		
	//error
	else
		cout<<endl<<"Computer Move: Error occured";
}

bool alpha_beta_pruning(int *min_max_point, int *index, int *alpha, int *beta, int level, int points, int n)
{
	if(level % 2 == 0)
	{
		if(*min_max_point < points)
		{
			*index = n;
			*min_max_point = points;
		}
		*alpha = max(*alpha, *min_max_point);
	}
	else
	{
		if(*min_max_point > points)
		{
			*index = n;
			*min_max_point = points;
		}
		*beta = min(*beta, *min_max_point);
	}
	
	if(beta <= alpha)
		return false;
	return true;
}

//actual game engine
int computer_play(bool color, int B[8][8], game_stack *moves, int level, int depth, int alpha, int beta)
{
	int index;
	int min_max_point;
	bool control = true;
	int x_1[265], y_1[265], x_2[265], y_2[265], points, n = 0;
	
	//leaf node
	if(level == depth)
	{
		if(level % 2 == 0)
			return board_score(B, color, moves);
		else
			return board_score(B, !color, moves);
	}
	
	//recursive
	else
	{
		if(moves->steps_repeat())
			return 0;
		
		//for max player
		if(level % 2 == 0)
			min_max_point = -9998;
		else
			min_max_point = 9998;
		
		//traverse whole board
		for(int i = 0 ; i < 8 ; i++)
			for(int j = 0 ; j < 8 ; j++)
				if(B[i][j] != 0 && are_same_color(B[i][j], color))
				{
					//pawn
					if(get_mod(B[i][j]) == 2)
					{
						//white
						if(B[i][j] < 0 && color == false)
						{
							//jump
							if(control && i == 1 && B[2][j] == 0 && B[3][j] == 0 && make_move(B, i, j, i+2, j, moves))
							{
								x_1[n] = i;
								y_1[n] = j;
								x_2[n] = i+2;
								y_2[n] = j;
								points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
								moves->undo(B);
								n++;
								control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
							}
							
							//push
							if(B[i+1][j] == 0 && control)
							{
								//promotion
								if(i == 6)
								{
									int promote[] = {-11, -7, -5, -3};
									for(int k = 0 ; (k < 4 && control); k++)
									{
										B[i][j] = promote[k];
										if(make_move(B, -2, B[i][j], j, j, moves) && control)
										{
											x_1[n] = -2;
											y_1[n] = B[i+1][j];
											x_2[n] = j;
											y_2[n] = j;
											points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
											moves->undo(B);
											n++;
											control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
										}
									}
								}
								
								//normal move
								else
								{
									if(control && make_move(B, i, j, i+1, j, moves))
									{
										x_1[n] = i;
										y_1[n] = j;
										x_2[n] = i+1;
										y_2[n] = j;
										points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
										moves->undo(B);
										n++;
										control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
									}
								}
							}
							
							//enpass left
							if(control && j >= 1 && i == 4 && B[5][j-1] == 0 && B[4][j-1] == 2 && moves->can_enpass(B, i, j, i+1, j-1) && make_move(B, -3, 0, j, j-1, moves))
							{
								x_1[n] = -3;
								y_1[n] = 0;
								x_2[n] = j;
								y_2[n] = j-1;
								points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
								moves->undo(B);
								n++;
								control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
							}
							
							//enpass right
							if(control && j <= 6 && i == 4 && B[5][j+1] == 0 && B[4][j+1] == 2 && moves->can_enpass(B, i, j, i+1, j+1) && make_move(B, -3, 0, j, j+1, moves))
							{
								x_1[n] = -3;
								y_1[n] = 0;
								x_2[n] = j;
								y_2[n] = j+1;
								points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
								moves->undo(B);
								n++;
								control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
							}
							
							//capture left
							if(j >= 1 && B[i+1][j-1] > 0)
							{
								//promotion
								if(i == 6)
								{
									int promote[] = {-11, -7, -5, -3};
									for(int k = 0 ; (k < 4 && control) ; k++)
									{
										B[i][j] = promote[k];
										
										if(make_move(B, -2, B[i][j], j, j-1, moves) && control)
										{
											x_1[n] = -2;
											y_1[n] = B[i+1][j-1];
											x_2[n] = j;
											y_2[n] = j-1;
											points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
											moves->undo(B);
											n++;
											control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
										}
									}
								}
								
								//normal move
								else
								{
									if(control && make_move(B, i, j, i+1, j-1, moves))
									{
										x_1[n] = i;
										y_1[n] = j;
										x_2[n] = i+1;
										y_2[n] = j-1;
										points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
										moves->undo(B);
										n++;
										control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
									}
								}	
							}
							
							//capture right
							if(j <= 6 && B[i+1][j+1] > 0)
							{
								//promotion
								if(i == 6)
								{
									int promote[] = {-11, -7, -5, -3};
									for(int k = 0 ; (k < 4 && control) ; k++)
									{
										B[i][j] = promote[k];
										
										if(make_move(B, -2, B[i][j], j, j+1, moves) && control)
										{
											x_1[n] = -2;
											y_1[n] = B[i+1][j+1];
											x_2[n] = j;
											y_2[n] = j+1;
											points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
											moves->undo(B);
											n++;
											control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
										}
									}
								}
								
								//normal move
								else
								{
									if(control && make_move(B, i, j, i+1, j+1, moves))
									{
										x_1[n] = i;
										y_1[n] = j;
										x_2[n] = i+1;
										y_2[n] = j+1;
										points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
										moves->undo(B);
										n++;
										control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
									}
								}	
							}
						}
						
						//black
						if(B[i][j] > 0 && color == true)
						{
							//jump
							if(control && i == 6 && B[5][j] == 0 && B[4][j] == 0 && make_move(B, i, j, i-2, j, moves))
							{
								x_1[n] = i;
								y_1[n] = j;
								x_2[n] = i-2;
								y_2[n] = j;
								points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
								moves->undo(B);
								n++;
								control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
							}
							
							//push
							if(B[i-1][j] == 0)
							{
								//promotion
								if(i == 1)
								{
									int promote[] = {11, 7, 5, 3};
								
									for(int k = 0 ; (k < 4 && control) ; k++)
									{
										B[i][j] = promote[k];
										
										if(make_move(B, -2, B[i][j], j, j, moves) && control)
										{
											x_1[n] = -2;
											y_1[n] = B[i-1][j];
											x_2[n] = j;
											y_2[n] = j;
											points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
											moves->undo(B);
											n++;
											control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
										}
									}
								}
								
								//normal move
								else
								{
									if(control && make_move(B, i, j, i-1, j, moves))
									{
										x_1[n] = i;
										y_1[n] = j;
										x_2[n] = i-1;
										y_2[n] = j;
										points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
										moves->undo(B);
										n++;
										control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
									}
								}
							}
							
							//enpass left
							if(control && j >= 1 && i == 3 && B[2][j-1] == 0 && B[3][j-1] == -2 && moves->can_enpass(B, i, j, i-1, j-1) && make_move(B, -3, 1, j, j-1, moves))
							{
								x_1[n] = -3;
								y_1[n] = 1;
								x_2[n] = j;
								y_2[n] = j-1;
								points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
								moves->undo(B);
								n++;
								control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
							}
							
							//enpass right
							if(control && j <= 6 && i == 3 && B[2][j+1] == 0 && B[3][j+1] == -2 && moves->can_enpass(B, i, j, i-1, j+1) && make_move(B, -3, 1, j, j+1, moves))
							{
								x_1[n] = -3;
								y_1[n] = 1;
								x_2[n] = j;
								y_2[n] = j+1;
								points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
								moves->undo(B);
								n++;
								control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
							}
							
							//capture left
							if(j >= 1 && B[i-1][j-1] < 0)
							{
								//promotion
								if(i == 1)
								{
									int promote[] = {11, 7, 5, 3};
								
									for(int k = 0 ; (k < 4 && control) ; k++)
									{
										B[i][j] = promote[k];
										
										if(make_move(B, -2, B[i][j], j, j-1, moves) && control)
										{
											x_1[n] = -2;
											y_1[n] = B[i-1][j-1];
											x_2[n] = j;
											y_2[n] = j-1;
											points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
											moves->undo(B);
											n++;
											control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
										}
									}
								}
								
								//normal move
								else
								{
									if(control && make_move(B, i, j, i-1, j-1, moves))
									{
										x_1[n] = i;
										y_1[n] = j;
										x_2[n] = i-1;
										y_2[n] = j-1;
										points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
										moves->undo(B);
										n++;
										control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
									}
								}
							}
							
							//capture right
							if(j <= 6 && B[i-1][j+1] < 0)
							{
								//promotion
								if(i == 1)
								{
									int promote[] = {11, 7, 5, 3};
								
									for(int k = 0 ; (k < 4 && control) ; k++)
									{
										B[i][j] = promote[k];
										
										if(make_move(B, -2, B[i][j], j, j+1, moves) && control)
										{
											x_1[n] = -2;
											y_1[n] = B[i-1][j+1];
											x_2[n] = j;
											y_2[n] = j+1;
											points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
											moves->undo(B);
											n++;
											control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
										}
									}
								}
								
								//normal move
								else
								{
									if(control && make_move(B, i, j, i-1, j+1, moves))
									{
										x_1[n] = i;
										y_1[n] = j;
										x_2[n] = i-1;
										y_2[n] = j+1;
										points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
										moves->undo(B);
										n++;
										control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
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
						
						for(int k = 0 ; (k < 8 && control) ; k++)
						{
							if(j+move_y[k] >= 0 && j+move_y[k] <= 7 && i+move_x[k] <= 7 && i+move_x[k] >= 0 && l_shape(B, i, j, i+move_x[k], j+move_y[k]))
							{
								if((B[i+move_x[k]][j+move_y[k]] == 0 || !are_same_color(B[i+move_x[k]][j+move_y[k]], color)) && make_move(B, i, j, i+move_x[k], j+move_y[k], moves))
								{
									x_1[n] = i;
									y_1[n] = j;
									x_2[n] = i+move_x[k];
									y_2[n] = j+move_y[k];
									points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
									moves->undo(B);
									n++;
									control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
								}
							}
						}
					}
					
					//bishop
					else if(get_mod(B[i][j]) == 5)
					{
						int move_x[] = {-1, 1, -1, 1};
						int move_y[] = {1, -1, -1, 1};
						
						for(int z = 0 ; z < 4 ; z++)
						{
							for(int k = 1 ; control && i+move_x[z]*k >= 0 && i+move_x[z]*k <= 7 && j+move_y[z]*k >= 0 && j+move_y[z]*k <= 7 && (B[i+move_x[z]*k][j+move_y[z]*k] == 0 || !are_same_color(B[i+move_x[z]*k][j+move_y[z]*k], color)); k++)
							{	
								if(make_move(B, i, j, i+move_x[z]*k, j+move_y[z]*k, moves))
								{
									x_1[n] = i;
									y_1[n] = j;
									x_2[n] = i+move_x[z]*k;
									y_2[n] = j+move_y[z]*k;
									points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
									moves->undo(B);
									n++;
									control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
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
							for(int k = 1 ; control && i+move_x[z]*k >= 0 && i+move_x[z]*k <= 7 && j+move_y[z]*k >= 0 && j+move_y[z]*k <= 7 && (B[i+move_x[z]*k][j+move_y[z]*k] == 0 || !are_same_color(B[i+move_x[z]*k][j+move_y[z]*k], color)); k++)
							{	
								if(make_move(B, i, j, i+move_x[z]*k, j+move_y[z]*k, moves))
								{
									x_1[n] = i;
									y_1[n] = j;
									x_2[n] = i+move_x[z]*k;
									y_2[n] = j+move_y[z]*k;
									points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
									moves->undo(B);
									n++;
									control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
								}
								if(B[i+move_x[z]*k][j+move_y[z]*k] != 0)
									break;
							}
						}
					}
					
					//queen
					else if(get_mod(B[i][j]) == 11)
					{
						//bishop
						{
							int move_x[] = {-1, 1, -1, 1};
							int move_y[] = {1, -1, -1, 1};
							
							for(int z = 0 ; z < 4 ; z++)
							{
								for(int k = 1 ; control && i+move_x[z]*k >= 0 && i+move_x[z]*k <= 7 && j+move_y[z]*k >= 0 && j+move_y[z]*k <= 7 && (B[i+move_x[z]*k][j+move_y[z]*k] == 0 || !are_same_color(B[i+move_x[z]*k][j+move_y[z]*k], color)); k++)
								{	
									if(make_move(B, i, j, i+move_x[z]*k, j+move_y[z]*k, moves))
									{
										x_1[n] = i;
										y_1[n] = j;
										x_2[n] = i+move_x[z]*k;
										y_2[n] = j+move_y[z]*k;
										points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
										moves->undo(B);
										n++;
										control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
									}
									if(B[i+move_x[z]*k][j+move_y[z]*k] != 0)
										break;
								}
							}
						}
						
						//rook
						{
							int move_x[] = {-1, 1, 0, 0};
							int move_y[] = {0, 0, -1, 1};
							
							for(int z = 0 ; z < 4 ; z++)
							{
								for(int k = 1 ; control && i+move_x[z]*k >= 0 && i+move_x[z]*k <= 7 && j+move_y[z]*k >= 0 && j+move_y[z]*k <= 7 && (B[i+move_x[z]*k][j+move_y[z]*k] == 0 || !are_same_color(B[i+move_x[z]*k][j+move_y[z]*k], color)); k++)
								{	
									if(make_move(B, i, j, i+move_x[z]*k, j+move_y[z]*k, moves))
									{
										x_1[n] = i;
										y_1[n] = j;
										x_2[n] = i+move_x[z]*k;
										y_2[n] = j+move_y[z]*k;
										points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
										moves->undo(B);
										n++;
										control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
									}
									if(B[i+move_x[z]*k][j+move_y[z]*k] != 0)
										break;
								}
							}
						}
					}
					
					//king
					else if(get_mod(B[i][j]) == 13)
					{
						int move_x[] = {0, 1, 1, 1, 0, -1, -1, -1};
						int move_y[] = {-1, -1, 0, 1, 1, 1, 0, -1};
						
						//castles
						if(j == 4)
						{
							//black castles
							if(B[i][j] > 0)
							{
								if(i == 7)
								{
									//left castle
									if(control && B[7][0] == 7 && B[7][1] == 0 && B[7][2] == 0 && B[7][3] == 0 && moves->b_l_c_status())
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
												x_1[n] = -1;
												y_1[n] = 1;
												x_2[n] = 0;
												y_2[n] = 9;
												points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
												moves->undo(B);
												n++;
												control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
											}
										}
									}
									
									//right castle
									if(control && B[7][7] == 7 && B[7][5] == 0 && B[7][6] == 0 && moves->b_r_c_status())
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
												x_1[n] = -1;
												y_1[n] = 1;
												x_2[n] = 1;
												y_2[n] = 9;
												points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
												moves->undo(B);
												n++;
												control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
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
									if(control && B[0][0] == -7 && B[0][1] == 0 && B[0][2] == 0 && B[0][3] == 0 && moves->w_l_c_status())
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
												x_1[n] = -1;
												y_1[n] = 0;
												x_2[n] = 0;
												y_2[n] = 9;
												points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
												moves->undo(B);
												n++;
												control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
											}
										}
									}
									
									//right castle
									if(control && B[0][7] == -7 && B[0][5] == 0 && B[0][6] == 0 && moves->w_r_c_status())
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
												x_1[n] = -1;
												y_1[n] = 0;
												x_2[n] = 1;
												y_2[n] = 9;
												points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
												moves->undo(B);
												n++;
												control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
											}
										}
									}
								}
							}
						}
						
						for(int z = 0 ; (z < 8 && control) ; z++)
						{
							if(i+move_x[z] >= 0 && i+move_x[z] <= 7 && j+move_y[z] >= 0 && j+move_y[z] <= 7 && (B[i+move_x[z]][j+move_y[z]] == 0 || !are_same_color(B[i+move_x[z]][j+move_y[z]], color)))
							{
								if(make_move(B, i, j, i+move_x[z], j+move_y[z], moves))
								{
									x_1[n] = i;
									y_1[n] = j;
									x_2[n] = i+move_x[z];
									y_2[n] = j+move_y[z];
									points = computer_play(!color, B, moves, level+1, depth, alpha, beta);
									moves->undo(B);
									n++;
									control = alpha_beta_pruning(&min_max_point, &index, &alpha, &beta, level, points, n-1);
								}
							}
						}
					}
					
					//error
					else
						cout<<endl<<"An error occured: known piece found on board at game engine";
				}
		//board traversal completed
		
		//for checkmate or stalemate
		if(n == 0)
		{
			if(is_check(B, color))
			{
				if(level % 2 == 1)
				{
					return 9999;
				}
				else
				{
					return -9999;
				}
			}
				
			else
				return 0;
		}
		
		//first level
		if(level == 0)
		{
			make_move(B, x_1[index], y_1[index], x_2[index], y_2[index], moves);
			print_computer_move(B, x_1[index], y_1[index], x_2[index], y_2[index]);
			return index;
		}
		else
		{
			return min_max_point;
		}
	}
}