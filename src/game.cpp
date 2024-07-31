
#include"game.h"


void transfer(int chessmap[9],char board[ROW][COL])
{
	for(int i=0;i<9;i++)
	{
		if(chessmap[i]==1)
			board[i/3][i%3]='#';
		else if(chessmap[i]==2)
			board[i/3][i%3]='*';
		else if(chessmap[i]==0)
			board[i/3][i%3]=' ';
	}
}

void transfer5(int chessmap[9],char board[ROW][COL])
{
	for(int i=0;i<9;i++)
	{
		if(chessmap[i]==1)
			board[i/3][i%3]='*';
		else if(chessmap[i]==2)
			board[i/3][i%3]='#';
		else if(chessmap[i]==0)
			board[i/3][i%3]=' ';
	}
}
void InitBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void Computer_move(char board[ROW][COL], int row, int col)
{
	int x = 0;
	int y = 0;
	int p = 0;
	int a = 0;
	for (a = 0; a < 3; a++)
	{
		if ((board[0][a] == '#') && (board[1][a] == '#'))
		{
			if (board[2][a] == ' ')
			{
				board[2][a]='#';
				calx=2;caly=a;
				return;
			}
		}
		if ((board[0][a] == '#') && (board[2][a] == '#'))
		{
			if (board[1][a] == ' ')
			{
				board[1][a]='#';
				calx=1;caly=a;
				return;
			}
		}
		if ((board[1][a] == '#') && (board[2][a] == '#'))
		{
			if (board[0][a] == ' ')
			{
				board[0][a]='#';
				calx=0;caly=a;
				return;
			}
		}
		if ((board[a][0] == '#') && (board[a][1] == '#'))
		{
			if (board[a][2] == ' ')
			{
				board[a][2]='#';
				calx=a;caly=2;
				return;
			}
		}
		if ((board[a][0] == '#') && (board[a][2] == '#'))
		{
			if (board[a][1] == ' ')
			{
				board[a][1]='#';
				calx=a;caly=1;
				return;
			}
		}
		if ((board[a][1] == '#') && (board[a][2] == '#'))
		{
			if (board[a][0] == ' ')
			{
				board[a][0]='#';
				calx=a;caly=0;
				return;
			}
		}
		if ((board[0][0] == '#') && (board[1][1] == '#'))
		{
			if (board[2][2] == ' ')
			{
				board[2][2]='#';
				calx=2;caly=2;
				return;
			}
		}
		if ((board[0][0] == '#') && (board[2][2] == '#'))
		{
			if (board[1][1] == ' ')
			{
				board[1][1]='#';
				calx=1;caly=1;
				return;
			}
		}
		if ((board[2][2] == '#') && (board[1][1] == '#'))
		{if (board[0][0] == ' ')
			{
				board[0][0]='#';
				calx=0;caly=0;
				return;
			}
		}
		if ((board[2][0] == '#') && (board[1][1] == '#'))
		{if (board[0][2] == ' ')
			{
				board[0][2]='#';
				calx=0;caly=2;
				return;
			}
		}
		if ((board[2][0] == '#') && (board[0][2] == '#'))
		{if (board[1][1] == ' ')
			{
				board[1][1]='#';
				calx=1;caly=1;
				return;
			}
		}
		if ((board[0][2] == '#') && (board[1][1] == '#'))
		{if (board[2][0] == ' ')
			{
				board[2][0]='#';
				calx=2;caly=0;
				return;
			}
		}
	}

	for (a = 0; a < 3; a++)
	{
		if ((board[0][a] == '*') && (board[1][a] == '*'))
		{if (board[2][a] == ' ')
			{
				board[2][a]='#';
				calx=2;caly=a;
				return;
			}
		}
		if ((board[0][a] == '*') && (board[2][a] == '*'))
		{if (board[1][a] == ' ')
			{
				board[1][a]='#';
				calx=1;caly=a;
				return;
			}
		}
		if ((board[1][a] == '*') && (board[2][a] == '*'))
		{if (board[0][a] == ' ')
			{
				board[0][a]='#';
				calx=0;caly=a;
				return;
			}
		}
		if ((board[a][0] == '*') && (board[a][1] == '*'))
		{if (board[a][2] == ' ')
			{
				board[a][2]='#';
				calx=a;caly=2;
				return;
			}
		}
		if ((board[a][0] == '*') && (board[a][2] == '*'))
		{if (board[a][1] == ' ')
			{
				board[a][1]='#';
				calx=a;caly=1;
				return;
			}
		}
		if ((board[a][1] == '*') && (board[a][2] == '*'))
		{if (board[a][0] == ' ')
			{
				board[a][0]='#';
				calx=a;caly=0;
				return;
			}
		}
		if ((board[0][0] == '*') && (board[1][1] == '*'))
		{if (board[2][2] == ' ')
			{
				board[2][2]='#';
				calx=2;caly=2;
				return;
			}
		}
		if ((board[0][0] == '*') && (board[2][2] == '*'))
		{if (board[1][1] == ' ')
			{
				board[1][1]='#';
				calx=1;caly=1;
				return;
			}
		}
		if ((board[2][2] == '*') && (board[1][1] == '*'))
		{if (board[0][0] == ' ')
			{
				board[0][0]='#';
				calx=0;caly=0;
				return;
			}
		}
		if ((board[2][0] == '*') && (board[1][1] == '*'))
		{if (board[0][2] == ' ')
			{
				board[0][2]='#';
				calx=0;caly=2;
				return;
			}
		}
		if ((board[2][0] == '*') && (board[0][2] == '*'))
		{if (board[1][1] == ' ')
			{
				board[1][1]='#';
				calx=1;caly=1;
				return;
			}
		}
		if ((board[0][2] == '*') && (board[1][1] == '*'))
		{if (board[2][0] == ' ')
			{
				board[2][0]='#';
				calx=2;caly=0;
				return;
			}
		}
	}

if(board[0][0]==' '&&(((board[0][1]=='#'&&board[0][2]==' ')||(board[0][1]==' '&&board[0][2]=='#'))&&((board[1][0]=='#'&&board[2][0]==' ')||(board[1][0]==' '&&board[2][0]=='#'))
					||((board[0][1]=='#'&&board[0][2]==' ')||(board[0][1]==' '&&board[0][2]=='#'))&&((board[1][1]=='#'&&board[2][2]==' ')||(board[1][1]==' '&&board[2][2]=='#'))
					||((board[1][1]=='#'&&board[2][2]==' ')||(board[1][1]==' '&&board[2][2]=='#'))&&((board[1][0]=='#'&&board[2][0]==' ')||(board[1][0]==' '&&board[2][0]=='#'))))
	{
		board[0][0]='#';
		calx=0;caly=0;
		return;
	}
	else if(board[0][2]==' '&&(((board[0][1]=='#'&&board[0][0]==' ')||(board[0][1]==' '&&board[0][0]=='#'))&&((board[1][2]=='#'&&board[2][2]==' ')||(board[1][2]==' '&&board[2][2]=='#'))
							||((board[1][1]=='#'&&board[2][0]==' ')||(board[1][1]==' '&&board[2][0]=='#'))&&((board[1][2]=='#'&&board[2][2]==' ')||(board[1][2]==' '&&board[2][2]=='#'))
							||((board[0][1]=='#'&&board[0][0]==' ')||(board[0][1]==' '&&board[0][0]=='#'))&&((board[1][1]=='#'&&board[2][0]==' ')||(board[1][1]==' '&&board[2][0]=='#'))))
	{
		board[0][2]='#';
		calx=0;caly=2;
		return;
	}
	else if(board[2][0]==' '&&(((board[2][1]=='#'&&board[2][2]==' ')||(board[2][1]==' '&&board[2][2]=='#'))&&((board[1][0]=='#'&&board[0][0]==' ')||(board[1][0]==' '&&board[0][0]=='#'))
							||((board[1][1]=='#'&&board[0][2]==' ')||(board[1][1]==' '&&board[0][2]=='#'))&&((board[1][0]=='#'&&board[0][0]==' ')||(board[1][0]==' '&&board[0][0]=='#'))
							||((board[2][1]=='#'&&board[2][2]==' ')||(board[2][1]==' '&&board[2][2]=='#'))&&((board[1][1]=='#'&&board[0][2]==' ')||(board[1][1]==' '&&board[0][2]=='#'))))
	{
		board[2][0]='#';
		calx=2;caly=0;
		return;
	}
	else if(board[2][2]==' '&&(((board[1][2]=='#'&&board[0][2]==' ')||(board[1][2]==' '&&board[0][2]=='#'))&&((board[2][1]=='#'&&board[2][0]==' ')||(board[2][1]==' '&&board[2][0]=='#'))
							||((board[1][1]=='#'&&board[0][0]==' ')||(board[1][1]==' '&&board[0][0]=='#'))&&((board[2][1]=='#'&&board[2][0]==' ')||(board[2][1]==' '&&board[2][0]=='#'))
							||((board[1][2]=='#'&&board[0][2]==' ')||(board[1][2]==' '&&board[0][2]=='#'))&&((board[1][1]=='#'&&board[0][0]==' ')||(board[1][1]==' '&&board[0][0]=='#'))))
	{
		board[2][2]='#';
		calx=2;caly=2;
		return;
	}


	
		if(board[0][0]==' '&&((board[0][1]=='*'&&board[0][2]==' ')||(board[0][1]==' '&&board[0][2]=='*'))&&((board[1][0]=='*'&&board[2][0]==' ')||(board[1][0]==' '&&board[2][0]=='*')))
	{
		if(board[0][2]=='*'&&board[2][0]=='*'&&board[1][1]=='#')
		{
			if(board[0][1]==' ')
				{
					board[0][1]='#';
				calx=0;caly=1;
				return;
				}
				else if(board[1][0]==' ')
				{
					board[1][0]='#';
					calx=1;caly=0;
					return;
				}
				else if(board[2][1]==' ')
				{
					board[2][1]='#';
				calx=2;caly=1;
				return;
				}
				else if(board[1][2]==' ')
				{
					board[1][2]='#';
					calx=1;caly=2;
					return;
				}
		}
		else if(board[0][2]=='*'&&board[2][0]=='*'&&board[1][1]==' ')
		{
			board[1][1]='#';
			calx=1;caly=1;
			return;
		}
		board[0][0]='#';
		calx=0;caly=0;
		return;
	}
	else if(board[0][2]==' '&&((board[0][1]=='*'&&board[0][0]==' ')||(board[0][1]==' '&&board[0][0]=='*'))&&((board[1][2]=='*'&&board[2][2]==' ')||(board[1][2]==' '&&board[2][2]=='*')))
	{
		if(board[0][0]=='*'&&board[2][2]=='*'&&board[1][1]=='#')
		{
			if(board[0][1]==' ')
				{
					board[0][1]='#';
				calx=0;caly=1;
				return;
				}
				else if(board[1][0]==' ')
				{
					board[1][0]='#';
					calx=1;caly=0;
					return;
				}
				else if(board[2][1]==' ')
				{
					board[2][1]='#';
				calx=2;caly=1;
				return;
				}
				else if(board[1][2]==' ')
				{
					board[1][2]='#';
					calx=1;caly=2;
					return;
				}
		}
		else if(board[0][0]=='*'&&board[2][2]=='*'&&board[1][1]==' ')
		{
			board[1][1]='#';
			calx=1;caly=1;
			return;
		}
		board[0][2]='#';
		calx=0;caly=2;
		return;
	}
	else if(board[2][0]==' '&&((board[2][1]=='*'&&board[2][2]==' ')||(board[2][1]==' '&&board[2][2]=='*'))&&((board[1][0]=='*'&&board[0][0]==' ')||(board[1][0]==' '&&board[0][0]=='*')))
	{
		if(board[0][0]=='*'&&board[2][2]=='*'&&board[1][1]=='#')
		{
			if(board[0][1]==' ')
				{
					board[0][1]='#';
				calx=0;caly=1;
				return;
				}
				else if(board[1][0]==' ')
				{
					board[1][0]='#';
					calx=1;caly=0;
					return;
				}
				else if(board[2][1]==' ')
				{
					board[2][1]='#';
				calx=2;caly=1;
				return;
				}
				else if(board[1][2]==' ')
				{
					board[1][2]='#';
					calx=1;caly=2;
					return;
				}
		}
		else if(board[0][0]=='*'&&board[2][2]=='*'&&board[1][1]==' ')
		{
			board[1][1]='#';
			calx=1;caly=1;
			return;
		}
		board[2][0]='#';
		calx=2;caly=0;
		return;
	}
	else if(board[2][2]==' '&&((board[1][2]=='*'&&board[0][2]==' ')||(board[1][2]==' '&&board[0][2]=='*'))&&((board[2][1]=='*'&&board[2][0]==' ')||(board[2][1]==' '&&board[2][0]=='*')))
	{
		if(board[0][2]=='*'&&board[2][0]=='*'&&board[1][1]=='#')
		{
			if(board[0][1]==' ')
				{
					board[0][1]='#';
				calx=0;caly=1;
				return;
				}
				else if(board[1][0]==' ')
				{
					board[1][0]='#';
					calx=1;caly=0;
					return;
				}
				else if(board[2][1]==' ')
				{
					board[2][1]='#';
				calx=2;caly=1;
				return;
				}
				else if(board[1][2]==' ')
				{
					board[1][2]='#';
					calx=1;caly=2;
					return;
				}
		}
		else if(board[0][2]=='*'&&board[2][0]=='*'&&board[1][1]==' ')
		{
			board[1][1]='#';
			calx=1;caly=1;
			return;
		}
		board[2][2]='#';
		calx=2;caly=2;
		return;
	}
	
		//����ռ����λ
		if (board[1][1] == ' ')
		{
			// if((board[0][0]==' '&&board[0][1]=='#'&&board[0][2]==' '&&board[1][0]=='*'&&board[2][1]==' '&&board[2][0]==' ')||
			// 	(board[0][0]==' '&&board[0][1]=='#'&&board[0][2]==' '&&board[1][2]=='*'&&board[2][1]==' '&&board[2][2]==' ')||
			// 	(board[2][0]==' '&&board[1][0]=='#'&&board[0][0]==' '&&board[2][1]=='*'&&board[1][2]==' '&&board[2][2]==' ')||
			// 	(board[2][0]==' '&&board[1][0]=='#'&&board[0][0]==' '&&board[0][1]=='*'&&board[1][2]==' '&&board[0][2]==' ')||
			// 	(board[0][0]==' '&&board[0][1]=='#'&&board[0][2]==' '&&board[1][0]=='*'&&board[2][1]==' '&&board[2][0]==' ')||
			// 	(board[0][0]==' '&&board[0][1]=='#'&&board[0][2]==' '&&board[1][0]=='*'&&board[2][1]==' '&&board[2][0]==' ')||
			// 	(board[0][0]==' '&&board[0][1]=='#'&&board[0][2]==' '&&board[1][0]=='*'&&board[2][1]==' '&&board[2][0]==' ')||
			// 	(board[0][0]==' '&&board[0][1]=='#'&&board[0][2]==' '&&board[1][0]=='*'&&board[2][1]==' '&&board[2][0]==' '))
			// {
			// 	board[1][1]='#';
			// 	calx=1;caly=1;
			// 	return;
			// }
			
			if((board[0][0]=='#'&&board[0][2]==' '&&board[2][0]==' '&&board[0][1]==' '&&board[1][0]==' ')||
				(board[0][2]=='#'&&board[0][0]==' '&&board[2][2]==' '&&board[0][1]== ' '&&board[1][2]==' ')||
				(board[2][2]==' '&&board[0][0]==' '&&board[2][0]=='#'&&board[2][1]==' '&&board[1][0]==' ')||
				(board[2][1]==' '&&board[1][2]==' '&&board[0][2]==' '&&board[2][0]==' '&&board[2][2]=='#'))
			{	
				board[1][1] = '#';
				calx=1;caly=1;
				return;
			}
			if((board[0][0]=='*'&&board[0][1]==' '&&board[0][2]==' '&&board[1][0]==' '&&board[1][1]==' '&&board[1][2]==' '&&board[2][0]==' '&&board[2][1]==' '&&board[2][2]==' ')||
			(board[0][0]==' '&&board[0][1]==' '&&board[0][2]=='*'&&board[1][0]==' '&&board[1][1]==' '&&board[1][2]==' '&&board[2][0]==' '&&board[2][1]==' '&&board[2][2]==' ')||
			(board[0][0]==' '&&board[0][1]==' '&&board[0][2]==' '&&board[1][0]==' '&&board[1][1]==' '&&board[1][2]==' '&&board[2][0]=='*'&&board[2][1]==' '&&board[2][2]==' ')||
			(board[0][0]==' '&&board[0][1]==' '&&board[0][2]==' '&&board[1][0]==' '&&board[1][1]==' '&&board[1][2]==' '&&board[2][0]==' '&&board[2][1]==' '&&board[2][2]=='*'))
			{
				board[1][1] = '#';
				calx=1;caly=1;
				return;
			}
			if(board[0][0]=='*'&&board[0][2]==' '&&board[2][0]==' '&&board[0][1]==' '&&board[1][0]==' ')
			{
				board[0][2]=='#';
				calx=0;caly=2;
				return;
			}
			else if(board[0][2]=='*'&&board[0][0]==' '&&board[2][2]==' '&&board[0][1]== ' '&&board[1][2]==' ')
			{
				board[0][0]=='#';
				calx=0;caly=0;
				return;
			}
			else if(board[2][2]==' '&&board[0][0]==' '&&board[2][0]=='*'&&board[2][1]==' '&&board[1][0]==' ')
			{
				board[2][2]=='#';
				calx=2;caly=2;
				return;
			}
			else if(board[2][1]==' '&&board[1][2]==' '&&board[0][2]==' '&&board[2][0]==' '&&board[2][2]=='*')
			{
				board[2][0]=='#';
				calx=2;caly=0;
				return;
			}
			board[1][1] = '#';
				calx=1;caly=1;
				return;
		}
		
		//���������?
		//��ס�Է�������
		else if (board[1][1] == '*')
		{
			//�ݻ�������1
			if (board[0][0] == '#')
			{
				if(board[2][2]==' '&&board[0][2]==' '&&board[1][2]==' '&&board[0][1]==' ')
				{
					board[2][2]='#';
					calx=2,caly=2;
					return;
				}
				else if(board[2][2]==' '&&board[2][1]==' '&&board[2][0]==' '&&board[1][0]==' ')
				{
					board[2][2]='#';
					calx=2,caly=2;
					return;
				}
				if(board[2][2]=='#'&&board[0][2]==' ')
				{
					board[0][2]='#';
					calx=0,caly=2;
					return;
				}
				else if(board[2][2]=='#'&&board[2][0]==' ')
				{
					board[2][0]='#';
					calx=2,caly=0;
					return;
				}
				else if (board[0][1] == ' ' && board[0][2] == ' ' && board[2][1] == ' ')
				{
					board[0][1] = '#';
					calx=0;caly=1;
					return;
				}
				else if (board[1][0] == ' ' && board[2][0] == ' ' && board[1][2] == ' ')
				{
					board[1][0] = '#';
					calx=1;caly=0;
					return;
				}
			}
			else if (board[0][2] == '#')
			{
				if(board[2][0]==' '&&board[0][0]==' '&&board[1][0]==' '&&board[0][1]==' ')
				{
					board[2][0]='#';
					calx=2,caly=0;
					return;
				}
				else if(board[2][2]==' '&&board[2][1]==' '&&board[2][0]==' '&&board[1][2]==' ')
				{
					board[2][0]='#';
					calx=2,caly=0;
					return;
				}
				if(board[2][0]=='#'&&board[0][0]==' ')
				{
					board[0][0]='#';
					calx=0,caly=0;
					return;
				}
				else if(board[2][0]=='#'&&board[2][2]==' ')
				{
					board[2][2]='#';
					calx=2,caly=2;
					return;
				}
				else if (board[0][1] == ' ' && board[0][0] == ' ' && board[2][1] == ' ')
				{
					board[0][1] = '#';
					calx=0;caly=1;
					return;
				}
				else if (board[1][2] == ' ' && board[1][0] == ' ' && board[2][2] == ' ')
				{
					board[1][2] = '#';
					calx=1;caly=2;
					return;
				}
			}
			else if (board[2][0] == '#')
			{
				if(board[0][0]==' '&&board[0][2]==' '&&board[1][0]==' '&&board[0][1]==' ')
				{
					board[0][2]='#';
					calx=0,caly=2;
					return;
				}
				else if(board[2][2]==' '&&board[2][1]==' '&&board[0][2]==' '&&board[1][2]==' ')
				{
					board[0][2]='#';
					calx=0,caly=2;
					return;
				}
				if(board[0][2]=='#'&&board[0][0]==' ')
				{
					board[0][0]='#';
					calx=0,caly=0;
					return;
				}
				else if(board[0][2]=='#'&&board[2][2]==' ')
				{
					board[2][2]='#';
					calx=2,caly=2;
					return;
				}
				else if (board[1][0] == ' ' && board[0][0] == ' ' && board[1][2] == ' ')
				{
					board[1][0] = '#';
					calx=1;caly=0;
					return;
				}
				else if (board[2][1] == ' ' && board[2][2] == ' ' && board[0][1] == ' ')
				{
					board[2][1] = '#';
					calx=2;caly=1;
					return;
				}
			}
			else if (board[2][2] == '#')
			{
				if(board[0][0]==' '&&board[0][2]==' '&&board[1][2]==' '&&board[0][1]==' ')
				{
					board[0][0]='#';
					calx=0,caly=0;
					return;
				}
				else if(board[0][0]==' '&&board[2][1]==' '&&board[2][0]==' '&&board[1][0]==' ')
				{
					board[0][0]='#';
					calx=0,caly=0;
					return;
				}
				if(board[0][0]=='#'&&board[0][2]==' ')
				{
					board[0][2]='#';
					calx=0,caly=2;
					return;
				}
				else if(board[0][0]=='#'&&board[2][0]==' ')
				{
					board[2][0]='#';
					calx=2,caly=0;
					return;
				}
				else if (board[2][1] == ' ' && board[0][1] == ' ' && board[2][0] == ' ')
				{
					board[2][1] = '#';
					calx=2;caly=1;
					return;
				}
				else if (board[1][0] == ' ' && board[0][2] == ' ' && board[1][2] == ' ')
				{
					board[1][2] = '#';
					calx=1;caly=2;
					return;
				}
			}
			//�ݻ�������2
			if (board[0][1] == '*')
			{
				if (board[0][0] == ' ' && board[0][2] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					return;
				}
				else if (board[0][2] == ' ' && board[2][0] == ' ' && board[0][0] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					return;
				}
			}
			else if (board[1][0] == '*')
			{
				if (board[0][0] == ' ' && board[2][0] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					return;
				}
				else if (board[2][0] == ' ' && board[0][0] == ' ' && board[0][2] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					return;
				}
			}
			else if (board[1][2] == '*')
			{
				if (board[0][2] == ' ' && board[2][0] == ' ' && board[2][2] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					return;
				}
				else if (board[2][2] == ' ' && board[0][2] == ' ' && board[0][0] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					return;
				}
			}
			else if (board[2][1] == '*')
			{
				if (board[2][0] == ' ' && board[0][2] == ' ' && board[2][2] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					return;
				}
				else if (board[2][2] == ' ' && board[2][0] == ' ' && board[0][0] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					return;
				}
			}
			//�ݻ�������3
			if (board[0][0] == '*')
			{
				if (board[0][1] == ' ' && board[0][2] == ' ' && board[2][0] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					return;
				}
				else if (board[1][0] == ' ' && board[2][0] == ' ' && board[0][2] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					return;
				}
			}
			else if (board[0][2] == '*')
			{
				if (board[0][1] == ' ' && board[0][0] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					return;
				}
				else if (board[1][2] == ' ' && board[0][0] == ' ' && board[2][2] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					return;
				}
			}
			else if (board[2][0] == '*')
			{
				if (board[1][0] == ' ' && board[0][0] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					return;
				}
				else if (board[2][1] == ' ' && board[2][2] == ' ' && board[0][0] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					return;
				}
			}
			else if (board[2][2] == '*')
			{
				if (board[2][1] == ' ' && board[0][2] == ' ' && board[2][0] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					return;
				}
				else if (board[2][0] == ' ' && board[0][2] == ' ' && board[1][2] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					return;
				}
			}
			if (board[0][0] == ' ' || board[2][2] == ' ' || board[0][2] == ' ' || board[2][0] == ' ')
			{
				if (board[0][0] == ' ' && board[0][1] == ' ' && board[1][0] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					return;
				}
				else if (board[0][2] == ' ' && board[0][1] == ' ' && board[1][2] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					return;
				}
				else if (board[2][0] == ' ' && board[2][1] == ' ' && board[1][0] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					return;
				}
				else if (board[2][2] == ' ' && board[2][1] == ' ' && board[1][2] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					return;
				}
			}
		}
		else if (board[1][1] == '#')
		{
			//���������?1
			if((board[0][0]=='*'&&board[2][2]=='*')||(board[2][0]=='*'&&board[0][2]=='*'))
			{
				if(board[0][1]==' ')
				{
					board[0][1]='#';
				calx=0;caly=1;
				return;
				}
				else if(board[1][0]==' ')
				{
					board[1][0]='#';
					calx=1;caly=0;
					return;
				}
				else if(board[2][1]==' ')
				{
					board[2][1]='#';
				calx=2;caly=1;
				return;
				}
				else if(board[1][2]==' ')
				{
					board[1][2]='#';
					calx=1;caly=2;
					return;
				}
			}
			if (board[0][0] == '#')
			{
				if (board[0][1] == ' ' && board[0][2] == ' ' && board[2][1] == ' ')
				{
					board[0][1] = '#';
					calx=0;caly=1;
					return;
				}
				else if (board[1][0] == ' ' && board[2][0] == ' ' && board[1][2] == ' ')
				{
					board[1][0] = '#';
					calx=1;caly=0;
					return;
				}
			}
			else if (board[0][2] == '#')
			{
				if (board[0][1] == ' ' && board[0][0] == ' ' && board[2][1] == ' ')
				{
					board[0][1] = '#';
					calx=0;caly=1;
					return;
				}
				else if (board[1][2] == ' ' && board[1][0] == ' ' && board[2][2] == ' ')
				{
					board[1][2] = '#';
					calx=1;caly=2;
					return;
				}
			}
			else if (board[2][0] == '#')
			{
				if (board[1][0] == ' ' && board[0][0] == ' ' && board[1][2] == ' ')
				{
					board[1][0] = '#';
					calx=1;caly=0;
					return;
				}
				else if (board[2][1] == ' ' && board[2][2] == ' ' && board[0][1] == ' ')
				{
					board[2][1] = '#';
					calx=2;caly=1;
					return;
				}
			}
			else if (board[2][2] == '#')
			{
				if (board[2][1] == ' ' && board[0][1] == ' ' && board[2][0] == ' ')
				{
					board[2][1] = '#';
					calx=2;caly=1;
					return;
				}
				else if (board[1][0] == ' ' && board[0][2] == ' ' && board[1][2] == ' ')
				{
					board[1][2] = '#';
					calx=1;caly=2;
					return;
				}
			}
			//����������2
			if (board[0][1] == '#')
			{
				if (board[0][0] == ' ' && board[0][2] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					return;
				}
				else if (board[0][2] == ' ' && board[2][0] == ' ' && board[0][0] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					return;
				}
			}
			else if (board[1][0] == '#')
			{
				if (board[0][0] == ' ' && board[2][0] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					return;
				}
				else if (board[2][0] == ' ' && board[0][0] == ' ' && board[0][2] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					return;
				}
			}
			else if (board[1][2] == '#')
			{
				if (board[0][2] == ' ' && board[2][0] == ' ' && board[2][2] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					return;
				}
				else if (board[2][2] == ' ' && board[0][2] == ' ' && board[0][0] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					return;
				}
			}
			else if (board[2][1] == '#')
			{
				if (board[2][0] == ' ' && board[0][2] == ' ' && board[2][2] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					return;
				}
				else if (board[2][2] == ' ' && board[2][0] == ' ' && board[0][0] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					return;
				}
			}
			//���������?3
			if (board[0][0] == '#')
			{
				if (board[0][1] == ' ' && board[0][2] == ' ' && board[2][0] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					return;
				}
				else if (board[1][0] == ' ' && board[2][0] == ' ' && board[0][2] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					return;
				}
			}
			else if (board[0][2] == '#')
			{
				if (board[0][1] == ' ' && board[0][0] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					return;
				}
				else if (board[1][2] == ' ' && board[0][0] == ' ' && board[2][2] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					return;
				}
			}
			else if (board[2][0] == '#')
			{
				if (board[1][0] == ' ' && board[0][0] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					return;
				}
				else if (board[2][1] == ' ' && board[2][2] == ' ' && board[0][0] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					return;
				}
			}
			else if (board[2][2] == '#')
			{
				if (board[2][1] == ' ' && board[0][2] == ' ' && board[2][0] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					return;
				}
				else if (board[2][0] == ' ' && board[0][2] == ' ' && board[1][2] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					return;
				}
			}
			//����ռ��
			if (board[0][0] == ' ' || board[2][2] == ' ' || board[0][2] == ' ' || board[2][0] == ' ')
			{
				if (board[0][0] == ' ' && board[0][1] == ' ' && board[1][0] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					return;
				}
				else if (board[0][2] == ' ' && board[0][1] == ' ' && board[1][2] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					return;
				}
				else if (board[2][0] == ' ' && board[2][1] == ' ' && board[1][0] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					return;
				}
				else if (board[2][2] == ' ' && board[2][1] == ' ' && board[1][2] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					return;
				}
			}
		}
		while (1)
		{
			x = getTickCount() % row;
			y = getTickCount() % col;
			if (board[x][y] == ' ')
			{
				board[x][y] = '#';
				calx=x;caly=y;
				return;
			}
		}
	}



