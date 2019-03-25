//
// Created by stefstef on 31/3/2017.
//

#include <cstdlib>
#include "StupidPlayer.h"
#include <fstream>
/*int StupidPlayer::getMove(const char **ViewAround) {
    std::ofstream he("inner.txt");
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            he<<ViewAround[i][j];
        }
        he<<'\n';
    }
    return STAND;

}*/


/*std::string StupidPlayer::getName() {
	return std::string("StupidPlayer");
}

std::string StupidPlayer::getId() {
	return std::string("cs161119");
}*/


StupidPlayer::StupidPlayer()
{
	x=0;
	y=0;
	d1=0;
	d2=0;
	tc=0;
	mv=-1;
	sc=0;
}


void StupidPlayer::init(int width, int height, int pos1, int pos2) {
	
	int i,j;
	d1=width;
	d2=height;
	x=pos1;
	y=pos2;

}



/*void StupidPlayer::init(int size1,int size2,int pos1,int pos2)
{
	int i,j;
	d1=size1;
	d2=size2;
	x=pos1;
	y=pos2;
}*/

int StupidPlayer::getMove(const char **arr)
{
	
	// mv move pairnei thn prohgoumenh kinhsh
	// sc posa kena exw guro mou
    // x,y arxikes sinthikes 
    
   sc = 0; //Áñ÷éêïðïéþ ôéò åëåýèåñåò èÝóåéò êÜèå öïñÜ ìå 0 ãéáôß ìå âÜóç ôçí èÝóç ðïõ âñßóêïìáé êÜèå öïñÜ áðïöáóßæù
   
   //ÁÍ Å×Ù ÔÏ ÔÑÏÐÁÉÏ ÓÅ ÌÉÁ ÁÐÏ ÔÉÓ 4 ÊÁÔÅÕÈÕÍÓÅÉÓ ÌÏÕ..
   //ÔÑÏÐÁÉÏ ÁÑÉÓÔÅÑÁ..
   if(arr[2][1]=='W')
   return 3;
   //ÔÑÏÐÁÉÏ ÊÁÔÙ..
   if(arr[3][2]=='W')
   return 1;
   //ÔÑÏÐÁÉÏ ÄÅÎÉÁ..
   if(arr[2][3]=='W')
   return 2;
   //ÔÑÏÐÁÉÏ ÐÁÍÙ..
   if(arr[1][2]=='W')
   return 0;
   
   
   if(arr[2][1]==' ')
   sc++;
   if(arr[1][2]==' ')
   sc++;
   if(arr[2][3]==' ')
   sc++;
   if(arr[3][2]==' ')
   sc++;
   

   
   if(sc==0) //ÁÌÁ ÄÅÍ ÕÐÁÑ×ÅÉ ÊÁÍÅÍÁÓ ÄÉÁÄÑÏÌÏÓ ÓÔÉÓ 4 ÊÁÔÅÕÈÕÍÓÅÉÓ...            
   {        //ÔÏÔÅ ÁÍ Å×Ù ÔÏ ÄÉÊÁÉÙÌÁ ÊÁÍÙ ÔÇËÅÌÅÔÁÖÏÑÁ ÁËËÉÙò ÐÁÑÁÌÅÍÙ ÓÔÇÍ ÈÅÓÇ ÌÏÕ !!
   if(tc<=2)
   {
   	tc++; 
   	return 6; //kanw thlemetafora kai ayksanw to sunolo ton metaforwn
   }
   else 
    return 5; //alliws menw sthn thesi mou
   }
   else if(sc==1) //ÅÄÙ ÄÉÁËÅÃÙ ÔÇÍ ÌÉÁ ÄÉÁÈÅÓÉÌÇ ÊÁÔÅÕÈÕÍÓÇ..!! 
   {
   if(arr[2][1]==' ')
   {
   	x--;
   	mv=3;
   	return 3;
   }
   if(arr[3][2]==' ')
   {
   	y++;
   	mv=1;
   	return 1;
   }
   if(arr[2][3]==' ')
   {
   	x++;
   	mv=2;
   	return 2;
   }
   if(arr[1][2]==' ')
   {
   	y--;
   	mv=0;
   	return 0;
   }
   }
   else if(sc==2) //ÅÄÙ ÄÉÁËÅÃÙ ÁÐÏ ÔÉÓ 2 ÄÉÁÈÅÓÉÌÅÓ ÁÕÔÇÍ ÐÑÏÓ ÓÔÇÍ ÏÐÏÉÁ ÄÅÍ Å×Ù ÊÉÍÇÈÅÉ ÐÑÏÇÃÏÕÌÅÍÙÓ!! 
   {
   	if(arr[2][1]==' ' && arr[3][2]==' ')
   	{
   	   if(mv==2)
   	   {
   	   	y++;
   	   	mv=1;
   	   	return 1;
	   }
	   else if(mv==0)
	   {
	   	x--;
	   	mv=3;
	   	return 3;
	   }
	   else if(mv==1)
	   {
	   	x--;
	   	mv=3;
	   	return 3;
	   }
	   else if(mv==3)
	   {
	   	y++;
   	   	mv=1;
   	   	return 1;
	   }
	   else if(mv==-1)
	   {
	   	y++;
   	   	mv=1;
   	   	return 1;
	   }
	   
	}
	else if(arr[2][1]==' ' && arr[2][3]==' ')
   	{
   		if(mv==2)
   		{
   			x++;
   			mv=2;
   			return 2;
		}
		else if(mv==3)
		{
			x--;
			mv=3;
			return 3;
		}
		else if(mv==1)
		{
		  	x++;
   			mv=2;
   			return 2;
		}
		else if(mv==0)
		{
			x--;
			mv=3;
			return 3;
		}
		else if(mv==-1)
		{
			x++;
   			mv=2;
   			return 2;
		}
	}
	else if(arr[2][1]==' ' && arr[1][2]==' ')
	{
		if(mv==2)
		{
			y--;
			mv=0;
		   return 0;
		}
		else if(mv==1)
		{
		    x--;
		    mv=3;
		    return 3;
		}
		else if(mv==0)
		{
			y--;
			mv=0;
		   return 0;
		}
		else if(mv==3)
		{
			x--;
		    mv=3;
		    return 3;
		}
		else if(mv==-1)
		{
			x--;
		    mv=3;
		    return 3;
		}
	}
   	else if(arr[3][2]==' ' && arr[2][3]==' ')
   	{
   		if(mv==0)
   		{
   		  x++;
   		  mv=2;
   		  return 2;
		}
		else if(mv==3)
		{
		  y++;
		  mv=1;
		  return 1;
		}
		else if(mv==1)
		{
		  x++;
   		  mv=2;
   		  return 2;
		}
		else if(mv==2)
		{
		  y++;
		  mv=1;
		  return 1;	
		}
		else if(mv==-1)
		{
		  y++;
		  mv=1;
		  return 1;
		}
	}
   	else if(arr[3][2]==' ' && arr[1][2]==' ')
   	{
   		if(mv==0)
   		{
   			y--;
   			mv=0;
   			return 0;
		}
		else if(mv==1)
		{
			y++;
			mv=1;
			return 1;
		}
		else if(mv==2)
		{
			y++;
			mv=1;
			return 1;
		}
		else if(mv==3)
		{
			y--;
   			mv=0;
   			return 0;
		}
		else if(mv==-1)
		{
			y--;
   			mv=0;
   			return 0;
		}
	}
   	else if(arr[2][3]==' ' && arr[1][2]==' ')
   	{
   		if(mv==3)
   		{
   		 y--;
   		 mv=0;
   		 return 0;
		}
		else if(mv==1)
		{
		  x++;
		  mv=2;
		  return 2;
		}
		else if(mv==2)
		{
		 y--;
   		 mv=0;
   		 return 0;	
		}
		else if(mv==0)
		{
		  x++;
		  mv=2;
		  return 2;	
		}
		else if(mv==-1)
		{
		 y--;
   		 mv=0;
   		 return 0;	
		}
    }
   }
   else if(sc==3) //ÅÄÙ ÄÉÁËÅÃÙ ÁÐÏ ÔÉÓ 3 ÄÉÁÈÅÓÉÌÅÓ ÁÕÔÇÍ ÐÑÏÓ ÓÔÇÍ ÏÐÏÉÁ ÄÅÍ Å×Ù ÊÉÍÇÈÅÉ ÐÑÏÇÃÏÕÌÅÍÙÓ!! 
   {
   	if(arr[2][1]==' ' && arr[3][2]==' ' && arr[2][3]==' ')
   	{
	   if(mv==2)
	   {
	   	x++;
   		mv=2;
   		return 2;
	   }
	   else if(mv==0)
	   {
	   	 x--;
	   	 mv=3;
	   	 return 3;
	   }
	   else if(mv==3)
	   {
	   	  y++;
	   	  mv=1;
	   	  return 1;
	   }
	   else if(mv==1)
	   {
	   	 x--;
	   	 mv=3;
	   	 return 3;
	   }
	   else if(mv==-1)
	   	{
	   	x++;
   		mv=2;
   		return 2;
		}
	}
   	else if(arr[2][1]==' ' && arr[3][2]==' ' && arr[1][2]==' ')
   	{
   		if(mv==2)
   		{
   		  y++;
   		  mv=1;
   		  return 1;
		}
		else if(mv==0)
		{
			x--;
			mv=3;
			return 3;
		}
		else if(mv==1)
		{
			y++;
			mv=1;
			return 1;
		}
		else if(mv==3)
		{
			y++;
   		    mv=1;
   		    return 1;
		}
		else if(mv==-1)
		{
		  	x--;
			mv=3;
			return 3;
		}
	}
   	else if(arr[2][1]==' ' && arr[2][3]==' ' && arr[1][2]==' ')
   	{
   		if(mv==2)
   		{
   		  x++;
   		  mv=2;
   		  return 2;
		}
		else if(mv==3)
		{
			y--;
			mv=0;
			return 0;
		}
		else if(mv==1)
		{
			x--;
			mv=3;
			return 3;
		}
		else if(mv==0)
		{
			y--;
			mv=0;
			return 0;
		}
		else if(mv==-1)
		{
			x--;
			mv=3;
			return 3;
		}
	}
	else if( arr[2][3]==' ' && arr[3][2]==' ' && arr[1][2]==' ')
	{
		if(mv==3)
		{
			y++;
			mv=1;
			return 1;
		}
		else if(mv==0)
		{
			y--;
			mv=0;
			return 0;
		}
		else if(mv==1)
		{
			x++;
			mv=2;
			return 2;
		}
		else if(mv==2)
		{
			y++;
			mv=1;
			return 1;
		}
		else if(mv==-1)
		{
			y++;
			mv=1;
			return 1;
		}
	}
   }
   else //ÅÄÙ ÄÉÁËÅÃÙ ÁÐÏ ÔÉÓ 4 ÄÉÁÈÅÓÉÌÅÓ ÁÕÔÇÍ ÐÑÏÓ ÓÔÇÍ ÏÐÏÉÁ ÄÅÍ Å×Ù ÊÉÍÇÈÅÉ ÐÑÏÇÃÏÕÌÅÍÙÓ!! 
   {
   	 if(mv==1)
   	 {
   	 	y++;
   	 	mv=1;
   	 	return 1;
	 }
	 else if(mv==0)
	 {
	 	y--;
	 	mv=0;
	 	return 0;
	 }
	 else if(mv==3)
	 {
	 	x--;
	 	mv=3;
	 	return 3;
	 }
	 else if(mv==2)
	 {
	 	x++;
	 	mv=2;
	 	return 2;
	 }
	 else if(mv==-1)
	 {
	 	x++;
	 	mv=2;
	 	return 2;
	 }
   }
}



string StupidPlayer::getName()
{
	return "Panos Kalamaras";
}

string StupidPlayer::getId()
{
	return "cs161040";
}

