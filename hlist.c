#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//question_1:

typedef struct hnode_t hnode_t;		// on définit un noeud tel que ce noeud en a un autre à gauche, un autre à droite, un autre en dessous, et un autre au dessus.
struct hnode_t
{
	hnode_t* next;   
	hnode_t* prev;
	hnode_t* dessus;
	hnode_t* dessous;
	int plus_infini;	//on note si la valeur est +infini, dans ce cas la valeur du noeud est à ignorer, et le noeud à droite aussi.
	int moins_infini;	// analogue
	int valeur;
};


//question_2:

struct hlist_t
{
	hnode_t* head;
	int height;
};

typedef struct hlist_t hlist_t;

//question_3:

hlist_t* hlist_new()
{
	hlist_t* t=malloc(sizeof(hlist_t));     //on alloue de la mémoire
	hnode_t* hd=malloc(sizeof(hnode_t));
	hnode_t* fin=malloc(sizeof(hnode_t));
	t->head=hd;
	t->head->next=fin;
	fin->prev=hd;
	hd->moins_infini=1;			//on marque les valeur + et - l'infini dans la liste
	fin->plus_infini=1;
	t->height=1;				// on initialise la taille à 1
	return t;
}

//qestion_4:

void hlist_free(hlist_t* l)   
{
	hnode_t* c1=l->head;
	hnode_t* c2=l->head;
	int i;
	for(i=0;i<l->height;i++) 			// on parcourt la liste ligne par ligne, c1 retient la positiondu 1er élément d'un étage pendant que c2 prcourt l'étage en supprimant les éléments derniere lui
	{
		while(!c2->plus_infini)
		{
			c2=c2->next;
			free(c2->prev);
		}
		free(c2);
		c1=c1->dessus;				//c1 monte quand c2 a finit de tout éffacer puis c2 le rejoint 
		c2=c1;
		free(c1->dessous); 			// on efface la ces précédente de c1
	}
	free(c1);
	free(c2);
	free(l);					//on libère la mémoire de l
}

//quesion_5:

int hlist_search(hlist_t *l, int v, hnode_t* path[])
{
	hnode_t* compteur=l->head;			//on initialise un compteur au premier élément du premier étage
	for(int i=0; i<l->height-1;i++)			// on monte jusqu'à atteindre le + l'infini du dernier étage
	{
		compteur=compteur->dessus;
	}
	int c=0;					// compte le nombre détage parcouru
	while (c<l->height)				//on parcourt jusqu'à arriver au premier étage
	{
		if ((compteur->valeur)==v && !compteur->moins_infini && !compteur->plus_infini )                // si on trouve la valeur, on finit de remplir path avec les pointeurs vers notre valeur et on renvoi 1
		{
			for(; c<l->height;c++)
			{
				path[c]=compteur;
				compteur=compteur->dessous;
			}
			return 1;
		}
		if (!compteur->plus_infini && (compteur->moins_infini  || compteur->valeur<v) )			// si on trouve une valeur plus petite que v, on se décale à droite
			compteur=compteur->next;
		else					// sinon, on descend et on ajoute le pointeur du dernier élément plus petit à path.
		{
			path[c]=compteur->prev;
			c++;
			compteur=compteur->prev->dessous;
		}
	}
	return 0;
}

//question_6:
int hlist_add(hlist_t *l, int v)
{
	hnode_t **path=malloc((l->height+1)*sizeof(hnode_t *)); 	//on alloue de la mémoire pour path
	if (hlist_search(l,v,path))					//si l'élément n'est présent on ne l'ajoute pas
		return 0;
	else
	{
		srand(time(NULL));					//on initialise srand 
		int b= 1;						// on initialise b à vrai car dans tous les cas il faut rajouter la valeur au premir étage
		int c=1;						//c compte le nombre d'étage auquel on se trouve
		hnode_t* haut_infini=path[0];				//haut_infini mémorise l'adresse du -infini de l'étage le plus haut
		while (b)
		{
			hnode_t* newnode=malloc(sizeof(hnode_t));	//on crée un nouveau noeud pour l'insertion
			newnode->valeur=v;				//on affecte la valeur
			newnode->prev=path[l->height-c];		//on rajoute comme précedent et comme suivant puis on met à jour le suivant et le prcédent du nouveau
			newnode->next=path[l->height-c]->next;
			path[l->height-c]->next=newnode;
			if (c!=1)					// si on est pas à l'étage le plus bas on relie au noeud du dessous
			{
				newnode->dessous=path[l->height-c+1]->next;
				path[l->height-c+1]->next->dessus=newnode;
			}
			newnode->next->prev=newnode;
			newnode->plus_infini=0;				//on marque le fait qu'on ne veut pas coder -infini ou +infini
			newnode->moins_infini=0;
			if (c==l->height)				//si on arrive à l'étage le plus haut, il faut recréer un étage
			{
				hnode_t* node_moins_infini=malloc(sizeof(hnode_t));		//on créer un noeud +infini et un -infini
				hnode_t* node_plus_infini=malloc(sizeof(hnode_t));
				node_moins_infini->next=node_plus_infini;
				node_plus_infini->prev=node_moins_infini;
				node_moins_infini->moins_infini=1;			//on met à jour leurs valeurs en mettant les booléens à vrai ou faux
				node_moins_infini->plus_infini=0;
				node_plus_infini->plus_infini=1;
				node_plus_infini->moins_infini=0;
				hnode_t* dessous_haut=haut_infini;
				while(!dessous_haut->plus_infini)			//on cherche le noeud +infini de l'avant dernier étage
					dessous_haut=dessous_haut->next;
				haut_infini->dessus=node_moins_infini;			//on "relie" cet étage aux autres
				haut_infini->next->dessus=node_plus_infini;
				node_plus_infini->dessous=dessous_haut;
				node_moins_infini->dessous=haut_infini;
				(l->height)++;						//on augmente la hauteur de 1
				
				path[1]=path[0]; 					//on sauvegarde l'adresse de l'avant dernier -infini
				path[0]=node_moins_infini;				// on met le nouveau noeud le plus hut dans path[0]
				haut_infini=node_moins_infini;				//on met à jour le nouveau haut_infini
			}
			b= rand() % 2;							//on refait le tirage pour savoir si on va recopier la valeur à l'étage du dessus
		c++;
		}
		return 1;
	}
} 


//question_7:
	    
int hlist_remove(hlist_t *l, int v)
{
	hnode_t **path=malloc(l->height*sizeof(hnode_t *));
	if (hlist_search(l,v,path))				//si l'élément est présent, on peut le supprimer sinon on retourne 0
	{
		int c=l->height-1;				
		while (path[c]->valeur==v && !path[c]->moins_infini && !path[c]->plus_infini)		//on se place àu noeud le plus haut contenant l valeur (on connait grace à path)	
		{
			if (c==l->height-1 && path[c]->prev->moins_infini && path[c]->next->plus_infini) 	//si v était la seule valeur de l'avant dernier étage alors il faut supprimer un étage
			{
				free(path[c]->prev);								//on libère la mémoire
				free(path[c]->next);
				free(path[c]);
				l->height--;									//la taille décroit
				
			}
			else											//sinon on rebranche juste son précédent avec son suivant puis on libère l'espace
			{
				path[c]->next->prev=path[c]->prev;
				path[c]->prev->next=path[c]->next;
				free(path[c]);
			}	
			c--;											//on décrémente c car on est descendu 
			
		}
		
		return 1;
	}
	return 0;
}
	     
//question_8:
	      
int main(int argi, char* argv[])
{
	hlist_t* l= hlist_new();			//on crée une liste vide
	for(int i=1;i<argi;i++)
		hlist_add(l,atoi(argv[i]));		//on ajoute tous les éléments demandés
	hnode_t* c=l->head->next;			//on initialie pour l'affichage
	printf("-∞  ");
	while(!c->plus_infini)				//on aiiche la partie contenant les valeurs
	{
		int val=c->valeur;
		printf("%d  ",val);
	 	c=c->next;
	}
	printf("+∞\n");
	hlist_free(l);
	return 0;
}
	
	      
	      
	      
	      
	      
	      
	

