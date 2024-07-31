#include "picture.h"


void paintchess(int chess[9],int serial)
{
    for(int i = 0;i<9;i++)
    {
        if(chess[i]==1)
        {
            serialPrintf(serial, "t%1d.bco=0",i);
            serialPutchar(serial,0xff);
            serialPutchar(serial,0xff);
            serialPutchar(serial,0xff);
        }
        else if(chess[i]==2)
        {
            serialPrintf(serial, "t%1d.bco=65535",i);
            serialPutchar(serial,0xff);
            serialPutchar(serial,0xff);
            serialPutchar(serial,0xff);
        }
        else if(chess[i]==0)
        {
            serialPrintf(serial, "t%1d.bco=65520",i);
            serialPutchar(serial,0xff);
            serialPutchar(serial,0xff);
            serialPutchar(serial,0xff);
        }
    }
}
