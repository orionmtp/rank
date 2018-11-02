#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define ennemymax 256

// TODO 
// gestion des ordres rank 1+ 
// remontée rank 1 vers superieurs (contacts, objectifs)

char phrase[256];
char reponse[256];
struct Info {
	int nom;
	int rank;
	int posx;
	int posy;
	int type;
	int vitesse;
	int vitessemax;
	int portee;
	int status;
} perso, contact[ennemymax],subord[ennemymax];

struct Order {
	int order;
	int posx;
	int posy;
	int cibx;
	int ciby;
} ordre;

int nbcontact=0;
int nbsubord=0;
int nbreport=0;

int f_min(int a, int b)
{
	if (a<b)
		return a;
	else
		return b;
}

int f_max(int a, int b)
{
	if (a>b)
		return a;
	else
		return b;
}

int initie()
{
	strtok(phrase,":");
	perso.type=atoi(strtok(NULL,":"));
	perso.rank=atoi(strtok(NULL,":"));
	perso.vitessemax=atoi(strtok(NULL,":"));
	perso.portee=atoi(strtok(NULL,":"));
	perso.posx=atoi(strtok(NULL,":"));
	perso.posy=atoi(strtok(NULL,":"));
	perso.vitesse=0;
	printf("register:%i:%i:%i:%i:%i:%i\n",perso.type,perso.rank,perso.posx,perso.posy,perso.portee,perso.vitessemax);
	perso.nom=-1;
	return 1;
}

int envois()
{
	int i;

	printf("report:%i:info:%i:%i:%i\n",perso.nom,perso.posx,perso.posy,perso.status);
	if (perso.status!=0)
	{
		for (i=0;i<nbcontact;i++)
		{
			printf("report:%i:contact:%i:%i:%i\n",perso.nom,contact[i].type,contact[i].posx,contact[i].posy);
		}
	}
	printf("report:%i:end\n",perso.nom);

		
	return 1;
}

int moulinette()
{
	int i,a,b,c;
	a=0;
	b=0;
	c=0;
	for (i=0;i<nbsubord;i++)
	{
		if (subord[i].status==1)
		{
			a=a+subord[i].posx;
			b=b+subord[i].posy;
			c++;
		}
	}
	perso.posx=a/c;
	perso.posy=b/c;
	switch (ordre.order)
	{
		case 6 : // rank 1 et plus : defendre le point indiqué (= se deplacer rapidement sur le point puis cibler le plus proche ennemi)
		{
			for (i=0;i<nbsubord;i++)
			{
				if (subord[i].status==0)
					break;
				
			}
			break;
		}
		case 7 : // rank 1 et plus : capturer le point indiqué (= se deplacer rapidement si aucune cible, sinon lentement et tirer ves l'ennemi le plus proche de la cible et à portée)
		{
			for (i=0;i<nbsubord;i++)
			{
				if (subord[i].status==0)
					break;
				
			}
			break;
		}
		case 9 : // rank 1 et plus : soutenir (= cibler les ennemis les plus proches du point indiqué)
		{
			for (i=0;i<nbsubord;i++)
			{
				if (subord[i].status==0)
					break;
				
			}
			break;
		}
	}
	return 1;
}

int execute()
{
	double angle;
	if (perso.rank==0)
	{
		if ((ordre.posx!=perso.posx)||(ordre.posy!=perso.posy))
		{
			if (ordre.order==4)
				perso.vitesse=perso.vitessemax;
			else
				perso.vitesse=perso.vitessemax*2;
			angle=atan2((double) ordre.posx-perso.posx,(double) ordre.posy-perso.posy);
			perso.posx=perso.posx+(int) (perso.vitesse*cos(angle));
			perso.posy=perso.posy+(int) (perso.vitesse*sin(angle));
		}
		if ((ordre.order==2)||(ordre.order==3))
		{
			angle=atan2((double) ordre.cibx-perso.posx,(double) ordre.ciby-perso.posy);
			if (((int) (ordre.cibx-perso.posx)/cos(angle))<=perso.portee)
				printf("tir sur cible position %i:%i\n",ordre.cibx,ordre.ciby);
			else
				printf("cible hors de portee\n");
		}
	}
	else
		moulinette();
	envois();
	return 1;
}

int analyse()
{
	time_t t;
	int nom,ok,i,a,b,c;
	
	if (strstr(phrase,"init"))
	{
		initie();
		strcpy(phrase,"");
	}
	if (strstr(phrase,"registered"))
	{
		strtok(phrase,":");
		perso.nom=atoi(strtok(NULL,":"));
		strcpy(phrase," ");
	}
	if (strstr(phrase,"register"))
	{
		srand((unsigned) time(&t));
		strtok(phrase,":");
		subord[nbsubord].type=atoi(strtok(NULL,":"));
		subord[nbsubord].rank=atoi(strtok(NULL,":"));
		perso.rank=f_max(perso.rank,subord[nbsubord].rank+1);
		subord[nbsubord].posx=atoi(strtok(NULL,":"));
		subord[nbsubord].posy=atoi(strtok(NULL,":"));
		subord[nbsubord].portee=atoi(strtok(NULL,":"));
		subord[nbsubord].vitessemax=atoi(strtok(NULL,":"));
		subord[nbsubord].status=1;
		subord[nbsubord].nom=nbsubord;
		printf("registered:%i\n",subord[nbsubord].nom);
		nbsubord++;
		strcpy(phrase," ");
	}
	if (strstr(phrase,"report"))
	{
		strtok(phrase,":");
		if (strstr(phrase,"info"))
		{
			nom=atoi(strtok(NULL,":"));
			if (nom<nbsubord)
			{
				strtok(NULL,":");
				subord[nom].posx=atoi(strtok(NULL,":"));
				subord[nom].posy=atoi(strtok(NULL,":"));
				subord[nom].status=atoi(strtok(NULL,":"));
			}
		}
		if (strstr(phrase,"contact"))
		{
			nom=atoi(strtok(NULL,":"));
			if (nom<nbsubord)
			{
				strtok(NULL,":");
				a=atoi(strtok(NULL,":"));
				b=atoi(strtok(NULL,":"));
				c=atoi(strtok(NULL,":"));
				ok=0;
				for (i=0;i<nbcontact;i++)
				{
					if ((contact[i].posx!=b)&&(contact[i].posy!=c)&&(contact[i].type!=a))
						ok=1;
					else
						break;
				}
				if (ok==1)
				{
					contact[nbcontact].type=a;
					contact[nbcontact].posx=b;
					contact[nbcontact].posy=c;
					nbcontact++;
				}
				
			}
		}
		if (strstr(phrase,"end"))
		{
			nom=atoi(strtok(NULL,":"));
			if (nom<nbsubord)
				nbreport++;
		}
		strcpy(phrase," ");
		ok=0;
		for (i=0;i<nbsubord;i++)
			if (subord[i].status==1)
				ok++;
		if (nbreport==ok)
		{
			execute();
			nbcontact=0;
			nbreport=0;
		}
	}
	if (strstr(phrase,"order"))
	{
		strtok(phrase,":");
		ordre.order=atoi(strtok(NULL,":"));
		switch(ordre.order)
		{
			case 1: //rank 0 et plus: ordre vide
			{
				ordre.posx=perso.posx;
				ordre.posy=perso.posy;
				ordre.cibx=0;
				ordre.ciby=0;
				break;
			}
			case 2 : // rank 0 only: tirer sur une cible specifique sans bouger
			{
				ordre.posx=perso.posx;
				ordre.posy=perso.posy;
				ordre.cibx=atoi(strtok(NULL,":"));
				ordre.ciby=atoi(strtok(NULL,":"));
				break;
			}
			case 3: // rank 0 only: bouger et tirer
			{
				ordre.posx=atoi(strtok(NULL,":"));
				ordre.posy=atoi(strtok(NULL,":"));
				ordre.cibx=atoi(strtok(NULL,":"));
				ordre.ciby=atoi(strtok(NULL,":"));
				break;
			}
			case 4 : // rank 0 only : bouger vite sans tirer
			{
				ordre.posx=atoi(strtok(NULL,":"));
				ordre.posy=atoi(strtok(NULL,":"));
				ordre.cibx=0;
				ordre.ciby=0;
				break;
			}
			case 5 : // a determiner
			{
				break;
			}
			case 6 : // rank 1 et plus : defendre le point indiqué (= se deplacer rapidement sur le point puis cibler le plus proche ennemi)
			{
				ordre.posx=atoi(strtok(NULL,":"));
				ordre.posy=atoi(strtok(NULL,":"));
				break;
			}
			case 7 : // rank 1 et plus : capturer le point indiqué (= se deplacer rapidement si aucune cible, sinon lentement et tirer ves l'ennemi le plus proche de la cible et à portée)
			{
				ordre.posx=atoi(strtok(NULL,":"));
				ordre.posy=atoi(strtok(NULL,":"));
				break;
			}
			case 8 : // rank 1 et plus : soutenir (= cibler les ennemis les plus proches du point indiqué)
			{
				ordre.posx=atoi(strtok(NULL,":"));
				ordre.posy=atoi(strtok(NULL,":"));
				break;
			}
		}
		strcpy(phrase," ");

	}
	if (strstr(phrase,"contact"))
	{
		strtok(phrase,":");
		contact[nbcontact].type=atoi(strtok(NULL,":"));
		contact[nbcontact].posx=atoi(strtok(NULL,":"));
		contact[nbcontact].posy=atoi(strtok(NULL,":"));
		nbcontact++;
		strcpy(phrase,"");
	}
	if (strstr(phrase,"dead"))
	{
		perso.status=0;
		envois();
	}
	return 1;
}

int collecte()
{
	if (strstr(phrase,"end")==NULL)
	{
		analyse();
	}
	else
	{
		execute();
		nbcontact=0;
		nbreport=0;
	}
	return 1;
}

int main ()
{
	printf ("> ");
	printf("init:1:0:10:25:0:0 ");
	fgets(phrase,256,stdin);
//	strcpy(phrase,"init:0:1:10:25:0:0");
	nbcontact=0;
	perso.status=1;
	while (strstr(phrase,"quit")==NULL&&(perso.status!=0))
	{
		collecte();
		printf("> ");
		fgets(phrase,256,stdin);
	}
	printf("au revoir\n");
	return(0);
}