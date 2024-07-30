#include<stdio.h>
#include"game.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include <opencv2/ximgproc.hpp>
#include <opencv2/opencv.hpp>
#include <wiringSerial.h>
#include <wiringPi.h>
#include <string>
#include <unistd.h>
#include "capture.h"
#include "rectget.h"
#include "move.h"
#include <pthread.h>
#include <time.h>

void transfer(int chessmap[9],char board[ROW][COL])
{
	for(int i=0;i<9;i++)
	{
		if(chessmap[i]==1)
			board[i%3][i/3]='#';
		else if(chessmap[i]==2)
			board[i%3][i/3]='*';
		else if(chessmap[i]==0)
			board[i%3][i/3]=' ';
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
			if (board[2][a] != ' ')
			{
				goto x1;
			}
			else if (board[2][a] == ' ')
			{
				p = 1;
				goto doit;
			}
		}
	x1:
		if ((board[0][a] == '#') && (board[2][a] == '#'))
		{
			if (board[1][a] != ' ')
			{
				goto x2;
			}
			else if (board[1][a] == ' ')
			{
				p = 2;
				goto doit;
			}
		}
	x2:
		if ((board[1][a] == '#') && (board[2][a] == '#'))
		{
			if (board[0][a] != ' ')
			{
				goto x3;
			}
			else if (board[0][a] == ' ')
			{
				p = 3;
				goto doit;
			}
		}
	x3:
		if ((board[a][0] == '#') && (board[a][1] == '#'))
		{
			if (board[a][2] != ' ')
			{
				goto x4;
			}
			else if (board[a][2] == ' ')
			{
				p = 4;
				goto doit;
			}
		}
	x4:
		if ((board[a][0] == '#') && (board[a][2] == '#'))
		{
			if (board[a][1] != ' ')
			{
				goto x5;
			}
			else if (board[a][1] == ' ')
			{
				p = 5;
				goto doit;
			}
		}
	x5:
		if ((board[a][1] == '#') && (board[a][2] == '#'))
		{
			if (board[a][0] != ' ')
			{
				goto x6;
			}
			else if (board[a][0] == ' ')
			{
				p = 6;
				goto doit;
			}
		}
	x6:
		if ((board[0][0] == '#') && (board[1][1] == '#'))
		{
			if (board[2][2] != ' ')
			{
				goto x7;
			}
			else if (board[2][2] == ' ')
			{
				p = 7;
				goto doit;
			}
		}
	x7:
		if ((board[0][0] == '#') && (board[2][2] == '#'))
		{
			if (board[1][1] != ' ')
			{
				goto x8;
			}
			else if (board[1][1] == ' ')
			{
				p = 8;
				goto doit;
			}
		}
	x8:
		if ((board[2][2] == '#') && (board[1][1] == '#'))
		{
			if (board[0][0] != ' ')
			{
				goto x9;
			}
			else if (board[0][0] == ' ')
			{
				p = 9;
				goto doit;
			}
		}
	x9:
		if ((board[2][0] == '#') && (board[1][1] == '#'))
		{
			if (board[0][2] != ' ')
			{
				goto x10;
			}
			else if (board[0][2] == ' ')
			{
				p = 10;
				goto doit;
			}
		}
	x10:
		if ((board[2][0] == '#') && (board[0][2] == '#'))
		{
			if (board[1][1] != ' ')
			{
				goto x11;
			}
			else if (board[1][1] == ' ')
			{
				p = 11;
				goto doit;
			}
		}
	x11:
		if ((board[0][2] == '#') && (board[1][1] == '#'))
		{
			if (board[2][0] != ' ')
			{
				p = 0;
			}
			else if (board[2][0] == ' ')
			{
				p = 12;
				goto doit;
			}
		}
	}
	for (a = 0; a < 3; a++)
	{
		if ((board[0][a] == '*') && (board[1][a] == '*'))
		{
			if (board[2][a] != ' ')
			{
				goto x13;
			}
			else if (board[2][a] == ' ')
			{
				p = 1;
				goto doit;
			}
		}
	x13:
		if ((board[0][a] == '*') && (board[2][a] == '*'))
		{
			if (board[1][a] != ' ')
			{
				goto x14;
			}
			else if (board[1][a] == ' ')
			{
				p = 2;
				goto doit;
			}
		}
	x14:
		if ((board[1][a] == '*') && (board[2][a] == '*'))
		{
			if (board[0][a] != ' ')
			{
				goto x15;
			}
			else if (board[0][a] == ' ')
			{
				p = 3;
				goto doit;
			}
		}
	x15:
		if ((board[a][0] == '*') && (board[a][1] == '*'))
		{
			if (board[a][2] != ' ')
			{
				goto x16;
			}
			else if (board[a][2] == ' ')
			{
				p = 4;
				goto doit;
			}
		}
	x16:
		if ((board[a][0] == '*') && (board[a][2] == '*'))
		{
			if (board[a][1] != ' ')
			{
				goto x17;
			}
			else if (board[a][1] == ' ')
			{
				p = 5;
				goto doit;
			}
		}
	x17:
		if ((board[a][1] == '*') && (board[a][2] == '*'))
		{
			if (board[a][0] != ' ')
			{
				goto x18;
			}
			else if (board[a][0] == ' ')
			{
				p = 6;
				goto doit;
			}
		}
	x18:
		if ((board[0][0] == '*') && (board[1][1] == '*'))
		{
			if (board[2][2] != ' ')
			{
				goto x19;
			}
			else if (board[2][2] == ' ')
			{
				p = 7;
				goto doit;
			}
		}
	x19:
		if ((board[0][0] == '*') && (board[2][2] == '*'))
		{
			if (board[1][1] != ' ')
			{
				goto x20;
			}
			else if (board[1][1] == ' ')
			{
				p = 8;
				goto doit;
			}
		}
	x20:
		if ((board[2][2] == '*') && (board[1][1] == '*'))
		{
			if (board[0][0] != ' ')
			{
				goto x21;
			}
			else if (board[0][0] == ' ')
			{
				p = 9;
				goto doit;
			}
		}
	x21:
		if ((board[2][0] == '*') && (board[1][1] == '*'))
		{
			if (board[0][2] != ' ')
			{
				goto x22;
			}
			else if (board[0][2] == ' ')
			{
				p = 10;
				goto doit;
			}
		}
	x22:
		if ((board[2][0] == '*') && (board[0][2] == '*'))
		{
			if (board[1][1] != ' ')
			{
				goto x23;
			}
			else if (board[1][1] == ' ')
			{
				p = 11;
				goto doit;
			}
		}
	x23:
		if ((board[0][2] == '*') && (board[1][1] == '*'))
		{
			if (board[2][0] != ' ')
			{
				p = 0;
			}
			else if (board[2][0] == ' ')
			{
				p = 12;
				goto doit;
			}
		}
	}
	doit:
	switch (p)
	{
	case 1:
	{
		board[2][a] = '#';
		calx=2;caly=a;
		break;
	}
	case 2:
	{
		board[1][a] = '#';
		calx=1;caly=a;
		break;
	}
	case 3:
	{
		board[0][a] = '#';
		calx=1;caly=a;
		break;
	}
	case 4:
	{
		board[a][2] = '#';
		calx=a;caly=2;
		break;
	}
	case 5:
	{
		board[a][1] = '#';
		calx=a;caly=1;
		break;
	}
	case 6:
	{
		board[a][0] = '#';
		calx=a;caly=0;
		break;
	}
	case 7:
	{
		board[2][2] = '#';
		calx=2;caly=2;
		break;
	}
	case 8:
	{
		board[1][1] = '#';
		calx=1;caly=1;
		break;
	}
	case 9:
	{
		board[0][0] = '#';
		calx=0;caly=0;
		break;
	}
	case 10:
	{
		board[0][2] = '#';
		calx=0;caly=2;
		break;
	}
	case 11:
	{
		board[1][1] = '#';
		calx=1;caly=1;
		break;
	}
	case 12:
	{
		board[2][0] = '#';
		calx=2;caly=0;
		break;
	}
	//�߼�����
	default:
	{
		//����ռ����λ
		if (board[1][1] == ' ')
		{
			board[1][1] = '#';
			calx=1;caly=1;
			break;
		}
		//���������
		//��ס�Է�������
		else if (board[1][1] == '*')
		{
			//�ݻ�������1
			if (board[0][0] == '*')
			{
				if (board[0][1] == ' ' && board[0][2] == ' ' && board[2][1] == ' ')
				{
					board[0][1] = '#';
					calx=0;caly=1;
					break;
				}
				else if (board[1][0] == ' ' && board[2][0] == ' ' && board[1][2] == ' ')
				{
					board[1][0] = '#';
					calx=1;caly=0;
					break;
				}
			}
			else if (board[0][2] == '*')
			{
				if (board[0][1] == ' ' && board[0][0] == ' ' && board[2][1] == ' ')
				{
					board[0][1] = '#';
					calx=0;caly=1;
					break;
				}
				else if (board[1][2] == ' ' && board[1][0] == ' ' && board[2][2] == ' ')
				{
					board[1][2] = '#';
					calx=1;caly=2;
					break;
				}
			}
			else if (board[2][0] == '*')
			{
				if (board[1][0] == ' ' && board[0][0] == ' ' && board[1][2] == ' ')
				{
					board[1][0] = '#';
					calx=1;caly=0;
					break;
				}
				else if (board[2][1] == ' ' && board[2][2] == ' ' && board[0][1] == ' ')
				{
					board[2][1] = '#';
					calx=2;caly=1;
					break;
				}
			}
			else if (board[2][2] == '*')
			{
				if (board[2][1] == ' ' && board[0][1] == ' ' && board[2][0] == ' ')
				{
					board[2][1] = '#';
					calx=2;caly=1;
					break;
				}
				else if (board[1][0] == ' ' && board[0][2] == ' ' && board[1][2] == ' ')
				{
					board[1][2] = '#';
					calx=1;caly=2;
					break;
				}
			}
			//�ݻ�������2
			if (board[0][1] == '*')
			{
				if (board[0][0] == ' ' && board[0][2] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					break;
				}
				else if (board[0][2] == ' ' && board[2][0] == ' ' && board[0][0] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					break;
				}
			}
			else if (board[1][0] == '*')
			{
				if (board[0][0] == ' ' && board[2][0] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					break;
				}
				else if (board[2][0] == ' ' && board[0][0] == ' ' && board[0][2] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					break;
				}
			}
			else if (board[1][2] == '*')
			{
				if (board[0][2] == ' ' && board[2][0] == ' ' && board[2][2] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					break;
				}
				else if (board[2][2] == ' ' && board[0][2] == ' ' && board[0][0] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					break;
				}
			}
			else if (board[2][1] == '*')
			{
				if (board[2][0] == ' ' && board[0][2] == ' ' && board[2][2] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					break;
				}
				else if (board[2][2] == ' ' && board[2][0] == ' ' && board[0][0] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					break;
				}
			}
			//�ݻ�������3
			if (board[0][0] == '*')
			{
				if (board[0][1] == ' ' && board[0][2] == ' ' && board[2][0] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					break;
				}
				else if (board[1][0] == ' ' && board[2][0] == ' ' && board[0][2] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					break;
				}
			}
			else if (board[0][2] == '*')
			{
				if (board[0][1] == ' ' && board[0][0] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					break;
				}
				else if (board[1][2] == ' ' && board[0][0] == ' ' && board[2][2] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					break;
				}
			}
			else if (board[2][0] == '*')
			{
				if (board[1][0] == ' ' && board[0][0] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					break;
				}
				else if (board[2][1] == ' ' && board[2][2] == ' ' && board[0][0] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					break;
				}
			}
			else if (board[2][2] == '*')
			{
				if (board[2][1] == ' ' && board[0][2] == ' ' && board[2][0] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					break;
				}
				else if (board[2][0] == ' ' && board[0][2] == ' ' && board[1][2] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					break;
				}
			}
			if (board[0][0] == ' ' || board[2][2] == ' ' || board[0][2] == ' ' || board[2][0] == ' ')
			{
				if (board[0][0] == ' ' && board[0][1] == ' ' && board[1][0] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					break;
				}
				else if (board[0][2] == ' ' && board[0][1] == ' ' && board[1][2] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					break;
				}
				else if (board[2][0] == ' ' && board[2][1] == ' ' && board[1][0] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					break;
				}
				else if (board[2][2] == ' ' && board[2][1] == ' ' && board[1][2] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					break;
				}
			}
		}
		else if (board[1][1] == '#')
		{
			//���������1
			if (board[0][0] == '#')
			{
				if (board[0][1] == ' ' && board[0][2] == ' ' && board[2][1] == ' ')
				{
					board[0][1] = '#';
					calx=0;caly=1;
					break;
				}
				else if (board[1][0] == ' ' && board[2][0] == ' ' && board[1][2] == ' ')
				{
					board[1][0] = '#';
					calx=1;caly=0;
					break;
				}
			}
			else if (board[0][2] == '#')
			{
				if (board[0][1] == ' ' && board[0][0] == ' ' && board[2][1] == ' ')
				{
					board[0][1] = '#';
					calx=0;caly=1;
					break;
				}
				else if (board[1][2] == ' ' && board[1][0] == ' ' && board[2][2] == ' ')
				{
					board[1][2] = '#';
					calx=1;caly=2;
					break;
				}
			}
			else if (board[2][0] == '#')
			{
				if (board[1][0] == ' ' && board[0][0] == ' ' && board[1][2] == ' ')
				{
					board[1][0] = '#';
					calx=1;caly=0;
					break;
				}
				else if (board[2][1] == ' ' && board[2][2] == ' ' && board[0][1] == ' ')
				{
					board[2][1] = '#';
					calx=2;caly=1;
					break;
				}
			}
			else if (board[2][2] == '#')
			{
				if (board[2][1] == ' ' && board[0][1] == ' ' && board[2][0] == ' ')
				{
					board[2][1] = '#';
					calx=2;caly=1;
					break;
				}
				else if (board[1][0] == ' ' && board[0][2] == ' ' && board[1][2] == ' ')
				{
					board[1][2] = '#';
					calx=1;caly=2;
					break;
				}
			}
			//����������2
			if (board[0][1] == '#')
			{
				if (board[0][0] == ' ' && board[0][2] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					break;
				}
				else if (board[0][2] == ' ' && board[2][0] == ' ' && board[0][0] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					break;
				}
			}
			else if (board[1][0] == '#')
			{
				if (board[0][0] == ' ' && board[2][0] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					break;
				}
				else if (board[2][0] == ' ' && board[0][0] == ' ' && board[0][2] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					break;
				}
			}
			else if (board[1][2] == '#')
			{
				if (board[0][2] == ' ' && board[2][0] == ' ' && board[2][2] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					break;
				}
				else if (board[2][2] == ' ' && board[0][2] == ' ' && board[0][0] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					break;
				}
			}
			else if (board[2][1] == '#')
			{
				if (board[2][0] == ' ' && board[0][2] == ' ' && board[2][2] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					break;
				}
				else if (board[2][2] == ' ' && board[2][0] == ' ' && board[0][0] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					break;
				}
			}
			//���������3
			if (board[0][0] == '#')
			{
				if (board[0][1] == ' ' && board[0][2] == ' ' && board[2][0] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					break;
				}
				else if (board[1][0] == ' ' && board[2][0] == ' ' && board[0][2] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					break;
				}
			}
			else if (board[0][2] == '#')
			{
				if (board[0][1] == ' ' && board[0][0] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					break;
				}
				else if (board[1][2] == ' ' && board[0][0] == ' ' && board[2][2] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					break;
				}
			}
			else if (board[2][0] == '#')
			{
				if (board[1][0] == ' ' && board[0][0] == ' ' && board[2][2] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					break;
				}
				else if (board[2][1] == ' ' && board[2][2] == ' ' && board[0][0] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					break;
				}
			}
			else if (board[2][2] == '#')
			{
				if (board[2][1] == ' ' && board[0][2] == ' ' && board[2][0] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					break;
				}
				else if (board[2][0] == ' ' && board[0][2] == ' ' && board[1][2] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					break;
				}
			}
			//����ռ��
			if (board[0][0] == ' ' || board[2][2] == ' ' || board[0][2] == ' ' || board[2][0] == ' ')
			{
				if (board[0][0] == ' ' && board[0][1] == ' ' && board[1][0] == ' ')
				{
					board[0][0] = '#';
					calx=0;caly=0;
					break;
				}
				else if (board[0][2] == ' ' && board[0][1] == ' ' && board[1][2] == ' ')
				{
					board[0][2] = '#';
					calx=0;caly=2;
					break;
				}
				else if (board[2][0] == ' ' && board[2][1] == ' ' && board[1][0] == ' ')
				{
					board[2][0] = '#';
					calx=2;caly=0;
					break;
				}
				else if (board[2][2] == ' ' && board[2][1] == ' ' && board[1][2] == ' ')
				{
					board[2][2] = '#';
					calx=2;caly=2;
					break;
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
				break;
			}
		}
	}
	}
}



