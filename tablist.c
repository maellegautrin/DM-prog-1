#include <stdlib.h>
#include <stdio.h>

//question_1
struct elem_t
{
  int x;
  int y;
  _Bool is_free; 	// on choisira comme l'énoncé le précise que is_free est vrai ssi le point est dans la liste
  int next;   	 	// next indiquera donc le point suivant dans la liste
  int prev;	 	// et prev le point précédent dans la liste
};

typedef struct elem_t elem_t;

//question_2:
#define MAX_CAP 100

// question_3:

struct tlist_t
{
  elem_t tab[MAX_CAP];
  int size;
  int first;
  int last;
};

typedef struct tlist_t tlist_t;

//question_4:
tlist_t* tlist_new()       // contrairement à ce que l'énoncé demande, on initialisera tous les éléments du tableau avec is_free=false ce qui signifie qu'on ne met aucun éléments dans la liste
{
  tlist_t* t=malloc(sizeof(tlist_t));  	
  for (int i = 0; i < MAX_CAP; ++i)    
    {
      t->tab[i].is_free = 0;
    }
  t->size = 0;
  return t;
}

//question_5:
int tlist_free (tlist_t * l)
{
  int s=l->size;
  free(l);
  return s;
}

//question_6:
int tlist_size (tlist_t * l)
{
  return l->size;
}

//question_7:
int tlist_add (tlist_t * l, int x, int y)
{
  if (l->size == MAX_CAP)  		// si la taille de la liste est déja de MAX_CAP on ne peut plus rien ajouter: on renvoi 0
    {
      return 0;
    }
  for (int i = 0; i < MAX_CAP; i++) 	//on cherche le premier indice de l' élément qui n'est pas dans la liste (ie is_free est faux)
    {
      if (l->tab[i].is_free == 0)	//on ajoute le point (x,y) à cet indice la
	{
	  l->tab[i].x=x;
	  l->tab[i].y=y;
	  l->tab[i].is_free = 1;
	  l->tab[l->last].next = i;
	  l->tab[i].prev = l->last;
	  l->last = i;
	  l->size += 1;
	  return 1;
	}
    }
  return 0;
}


//question_8:
int tlist_remove (tlist_t * l, int x, int y)
{
  for (int i = 0; i < MAX_CAP; ++i)
    {
      if (l->tab[i].x == x && l->tab[i].y == y && l->tab[i].is_free)  //on cherche l'indice du point (x,y) qui est dans la liste
	{
	  l->tab[i].is_free = 0;
	  l->tab[l->tab[i].prev].next = l->tab[i].next;
	  l->tab[l->tab[i].next].prev = l->tab[i].prev;
	  l->size -= 1;
	  return 1;
	}
    }
}

//question_9:
int tlist_pop (tlist_t * l)
{
  if (l->size == 0)			//si la taille est de 0 alors il n'y a rien dan la liste donc on ne peut pas enlever: on retourne 0
    {
      return 0;
    };
  l->tab[l->first].is_free = 0;		//sinon on met le is_free du premier élément de la liste à 0 ce qui le supprime de la liste
  l->first = l->tab[l->first].next;	// on modifie ensuite first
  l->size -= 1;
  return 1;
}

//question_10:
int tlist_top (tlist_t * l, int *x, int *y)
{
  if (l->size == 0)
    {
      return 0;
    };
  *x = l->tab[l->first].x;
  *y = l->tab[l->first].y;
  return 1;
}

//question_11:
int tlist_push (tlist_t * l, int x, int y)
{
  if (l->size == MAX_CAP)
    {
      return 0;
    }
  for (int i = 0; i < MAX_CAP; i++)
    {
      if (l->tab[i].is_free == 0)
	{
	  l->tab[i].is_free = 1;
	  l->tab[l->first].prev = i;
	  l->tab[i].next = l->first;
	  l->first = i;
	  l->size += 1;
	  return 1;
	}

    }
}

//question_12:
int tlist_swap (tlist_t * l, int i, int j)
{
  if (l->tab[i].is_free && l->tab[j].is_free)
    {
      int ex = l->tab[i].x;
      int ey = l->tab[i].y;
      l->tab[i].x = l->tab[j].x;
      l->tab[i].y = l->tab[j].y;
      l->tab[j].x = ex;
      l->tab[j].y = ey;
      return 1;
    }
  return 0;
}

//question_13:

int dist (int i, tlist_t* l)
  {
    int x = l->tab[i].x;
    int y = l->tab[i].y;
    int d = x * x + y * y;
    return d;
  }

int plus_petit(int i,int j,tlist_t* l){
	int c;
	for(c=i;c!=l->last;i=l->tab[i].next){
		if (c==j)
			return 0;
	}
	return 1;
}
 int triRapid (int debut, int fin, tlist_t* l)
  {
    int pivot = debut;
    int i = debut;
    int j = fin;
    _Bool b= true;
    while (b)
      {
    	while (dist(i,l) <= dist(pivot,l) && i!=fin){
	      i = l->tab[i].next;
	      if (b)
		      b=(i!=j);
	}
    	while (dist(j,l) > dist(pivot,l))
	     {
		j = l->tab[j].prev;
		if (b)
			b=(i!=j);
	     }
	    	
	 if (b)
	      tlist_swap (l, i, j);
	tlist_swap (l, pivot, j);
	triRapid (debut, l->tab[j].next, l);
	triRapid (l->tab[j].prev, fin, l);
   }
 }

int tlist_sort (tlist_t * l)
{
    triRapid (l->first, l->last, l);
    return 0;
}

//atoi
// ./test arg1 -> "./test" "arg1" "

int main(int argc, char *argv[])  
{
    if (argc %2==0) {
	    printf("erreur:nombre impair d'entiers");
	    return 1;
    }
    int i;
    int *t = malloc((argc-1)*sizeof(int));
    for (int i=0; i<argc-1; i++) 
	    t[i]=atoi(argv[i+1]);
    tlist_t* l = tlist_new();
    for(i=0; i<argc-1;i+=2)
    { 
	int b= tlist_add(l,t[i],t[i+1]);
	if (b==0) {
		printf("erreur: capacité dépassée");
		return 1;
	}
    }
    tlist_sort(l);
    printf ("{");
    for(i=l->first;i!=l->last;i=l->tab[i].next)
    {
       int lx=l->tab[i].x;
       int ly=l->tab[i].y;
       printf ("{%d,%d},",lx,ly);
    }
    int lx=l->tab[l->last].x;
    int ly=l->tab[l->last].y;
    printf ("{%d,%d}}\n",lx,ly);
  return 0;
}
