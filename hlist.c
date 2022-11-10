
//question_1:
struct hnode_t 			// on définit un noeud tel que ce noeud en a un autre à gauche, un autre à droite, un autre en dessous, et un autre au dessus.
{
	hnode_t* next;   
	hnode_t* prev;
	hnode_t* dessus;
	hnode_t* dessous;
	int valeur;
	int plus_infini;	//on note si la valeur est +infini, dans ce cas la valeur du noeud est à ignorer, et le noeud à droite aussi.
	int moins_infini;	// analogue
};

typedef struct hnode_t hnode_t;

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
	hlist_t* h=malloc(sizeof(hlist_t));     //on alloue de la mémoire
	t->head.moins_infini=1;			//on marque les valeur + et - l'infini dans la liste
	t->head.next.plus_infini=1;
	t->height=1;				// on initialise la taille à 1
}

//qestion_4:

void hlist_free(hlist_t* l)
{
	free(l);
}

//quesion_5:

int hlist_search(hlist_t *l, int v, hnode_t* path[])
{
	hnode_t* compteur=l->head;			//on initialise un compteur au premier élément du premier étage
	for(int i=0; i<l->height;i++)			// on monte jusqu'à atteindre le + l'infini du dernier étage
	{
		compteur=compteur->dessus;		
	}
	int c=0;
	while (c<l->height)				//on parcourt jusqu'à arriver au dernier étage
	{
		if (compteur->valeur==v)                // si on trouve la valeur, on finit de remplir path avec les pointeurs vers notre valeur et on renvoi 1
		{
			for(c; c<l->height;c++)
				path[c]=valeur;
				compteur=compteur.dessous;
			return 1;
		}
		if (compteur->valeur<v)			// si on trouve une valeur plus petite que v, on se décale à droite
			compteur=compteur.next;
		else					// sinon, on descend et on ajoute le pointeur du dernier élément plus petit à path.
		{
			path[c]=compteur.prev;
			c++;
			compteur=compteur.prev.dessous; 
		}
	}
	return 0;
}

//question_6:

int hlist_add(hlist_remove(hlist_t *l, int v)
{
	hnode_t* path[]=malloc(sizeof(l->height));
	if (hlist_search(l,v,path))
		return 0;

	hnode_t* newnode=malloc(sizeof(hnode_t));
	newnode->valeur=v;
	newnode->prev=path[l->height];
	newnode->next=path[l->height].next;
	path[l->height].next=newnode;
	newnode->next.prev=newnode;
	srand(time(NULL));
	int b= rand() % 2;
	int c=1;
	while (b)
	{
		hnode_t* newnode=malloc(sizeof(hnode_t));
		newnode->valeur=v;
		newnode->prev=path[l->height-c];
		newnode->next=path[l->height-c].next;
		path[l->height-c].next=newnode;
		newnode->next.prev=newnode;
		b= rand() % 2;
		c++;
	}
}




































