
//question_1:
struct hnode_t
{
	hnode_t* next;
	hnode_t* prev;
	hnode_t* dessus;
	hnode_t* dessous;
	int valeur;
	int plus_infini;
	int moins_infini;
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
	hlist_t* h=malloc(sizeof(hlist_t));
	t->head.moins_infini=1;
	t->head.next.plus_infini=1;
	t->height=1;
}

//qestion_4:

void hlist_free(hlist_t* l)
{
	free(l);
}

//quesion_5:

int hlist_search(hlist_t *l, int v, hnode_t* path[])
{
	hnode_t* compteur=l->height;
	for(int i=0; i<l->height;i++)
	{
		compteur=compteur->dessus;
	}
	int c=0;
	while (c<l->height)
	{
		if (compteur->valeur==v)
			return 1;
		if (compteur->valeur<v)
			compteur=compteur.next;
		else
		{
			path[c]=compteur.prev;
			c++;
			compteur=compteur.prev.dessous;
		}
	}
	return 0;
}
















