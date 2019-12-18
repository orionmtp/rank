//programme de generation des ordres pour rank 0 et plus (si besoin)
#include <stdio.h>
#include <stdlib.h>

#define RANK 9810
#define DISTANCE 10 //distance entre 2 unités de niveau 0/1. la distance est ensuite calculée en puissance  du rank

//format :
// init :<type>:<rank>:<vitesse max>:<portee>:<position X>:<position Y>
// <type> : 1 : infanterie / autre non défini 
// <rank> : niveau de 0 à ... plus.
// rank 0 : soldat
// rank 1 : chef de groupe (=sergent) (10 soldats max)
// rank 2 : chef de section (=lieutenant) 3 groupes  + 1/2 groupe* (35 unités)
// rank 3 : chef de compagnie (=capitaine) 4 Sections + 1 groupe* (150 unités)
// rank 4 : chef de bataillon (=commandant) 4 compagnies + 1 groupe* (610 unités)
// rank 5 : chef de regiment (=colonel) 4 regiments + 1 groupe* (2450 unités)
// rank 6 : chef de division (= general) 4 brigades + 1 groupe* (9810 unités)
// oui on simplifie le nbre d'elements dans chaque element superieur ...
//<vitesse max>, <portee>, <X>, <Y> => garder une coherence de donnees (cm, km, ...) suivant l'echelle
// contact : 

int rank[7];
int unite;
int rank_max;

void init() // je fais un init du nombre de soldats de chaque niveau
{
if (unite==1)
{
                  rank[6]=0;
                rank[5]=0;
                rank[4]=0;
                rank[3]=0;
                rank[2]=0;
                rank[1]=0;
                rank[0]=1;
  rank_max=0
}
  else
  if (unite<=10)
    {
                      rank[6]=0;
                rank[5]=0;
                rank[4]=0;
                rank[3]=0;
                rank[2]=0;
      rank[1]=1;
      rank[0]=unite-1;
    rank_max=1;
    }
    else
      if (unite<=35)
      {
                              rank[6]=0;
                rank[5]=0;
                rank[4]=0;
                rank[3]=0;
        rank[2]=1;
        rank[1]=4;
        rank[0]=unite-5;
        rank_max=2;
      }
      else
        if (unite<=150)
        {
                                        rank[6]=0;
                rank[5]=0;
                rank[4]=0;
          rank[3]=1;
          rank[2]=4;
          rank[1]=16;
          rank[0]=unite-21;
          rank_max=3;
        }
        else
          if (unite<=610)
          {
                                                    rank[6]=0;
                rank[5]=0;
            rank[4]=1;
            rank[3]=4;
            rank[2]=16;
            rank[1]=64;
            rank[0]=unite-85;
            rank_max=4;
          }
          else
              if (unite<=2450)
              {
                rank[6]=0;
                rank[5]=1;
                rank[4]=4;
                rank[3]=16;
                rank[2]=64;
                rank[1]=256;
                rank[0]=unite-341;
                rank_max=5;
              }
              else
              {
                rank[6]=1;
                rank[5]=4;
                rank[4]=16;
                rank[3]=64;
                rank[2]=256;
                rank[1]=1024;
                rank[0]=unite-1365;
                rank_max=6;
              }
  return 0;
}


int main (int argc, char **argv)
{
  int unite;
  int rank[7];
  int i=0;
  
  rank_max=0;
  if (argc<2)
  {
    printf("usage : $s <nb de soldats>\n max 9810");
    exit 1;
  }
  else
  {

    if (argv[1]>9810)
    {
      printf("usage : $s <nb de soldats>\n max 9810");
      exit 1;
    }
    unite=atoi(argv[1]);
    init();
  }
//  for (i=0;i<unite;i++)
//  {
//    printf("init:1:0:10:25:0:0 ");
//    
//  }
  exit 0;
}
