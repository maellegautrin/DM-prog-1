//question_1
struct elem_t                                
{
    int x;
    int y;
    _Bool is_free;
    int next;
    int prev;
};

typedef struct elem_t elem_t;

//question_2:
int MAX_CAP = 100;                        

// question_3:
typedef elem_t tabl[100];

struct tlist_t
{
    tabl tab;
    int size;
    int first;
    int last;
};

typedef struct tlist_t tlist_t;    
         
//question_4:
tlist_t* tlist_news()                        
{
    tlist_t* t;
    for(int i=0; i<MAX_CAP;++i){
        t->tab[i].is_free=1;
    }
    t->size=0;
    return t;
}

//question_5:
int tlist_free(tlist_t* l)               
{
    int s=l->size;
    l->first=0;
    l->last=0;
    l->size=0;
    return s;
}

//question_6:
int tlist_size(tlist_t* l)
{
    return l->size;
}

//question_7:
int tlist_add(tlist_t* l,int x, int y)
{
    if (l->size==MAX_CAP){return 0;}
    for(int i=0; i<MAX_CAP; i++){
        if(l->tab[i].is_free==0)
        {
            l->tab[i].is_free=1;
            l->tab[l->last].next=i;
            l->tab[i].prev=l->last;
            l->last=i;
            l->size +=1;
            return 1;
        }
    }
    return 0;
}


//question_8:
int tlist_remove(tlist_t* l, int x, int y){
    for(int i= 0;i<MAX_CAP;i++){
        if(l->tab[i].x==x && l->tab[i].y==y && l->tab[i].is_free){
            l->tab[i].is_free=0;
            l->tab[l->tab[i].prev].next=l->tab[i].next;
            l->tab[l->tab[i].next].prev=l->tab[i].prev;
            l->size -=1;
        }
    }
}

//question_9:
int tlist_pop(tlist_t* l){
    if(l->size==0){return 0;};
    l->tab[l->first].is_free=0;
    l->first=l->tab[l->first].next;
    l->size -=1;
    return 1;
}

//question_10:
int tlist_top(tlist_t* l, int *x, int *y){
    if(l->size==0){return 0;};
    *x=l->tab[l->first].x;
    *y=l->tab[l->first].y;
    return 1;
}

//question_11:
int tlist_push(tlist_t* l, int x, int y){
    
}



int main(void)
{
    return 0;
}
