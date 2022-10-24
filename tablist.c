struct elem_t
{
    int x;
    int y;
    _Bool is_free;
    int next;
    int prev;
};

typedef struct elem_t elem_t;
int MAX_CAP = 100;


typedef elem_t tabl[100];

struct tlist_t
{
    tabl tab;
    int size;
    int first;
    int last;
};

typedef struct tlist_t tlist_t;

tlist_t* tlist_news(void)
{
    tlist_t t;
    for(int i=0;i<MAX_CAP;++i){
        t.tab[i].is_free=1;
    }
    t.size=0;
    return t;
}


int tlist_free(tlist_t* l)
{
    int s=l.size;
    l.first=0;
    l.last=0;
    l.size=0;
    return s;
}

int tlist_size(tlist_t* l)
{
    return l.size;
}

tlist_t main(void)
{
    return tlist_news(void);
}