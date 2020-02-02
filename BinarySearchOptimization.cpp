//  DHAVAL KADIA dhaval.dev

/*
    FEATURES ADDED :

    # BASED ON ALMOST LINKED LIST ( USES LESS MEMMORY )
    # EACH BUCKET CONTAINS B-TREE
    # SHOWING TREE OF BUCKET IN INNFIX VIEW ( POSTFIX VIEW IS ADDED )
    # BALANCING OF B-TREE IS PERFORMED ON ADDING ELEMENT TO EACH B-TREE
    # ( STILL BALANCING IMPROVEMENTS USING AVL CONCEPT IS YET TO BE DONE )
    # ELIMINATION OF EMPTY BUCKET IS THERE
    # MERGING OF BUCKETS HAVING LESS ELEMENT IS THERE
    # ( SPLITING OF HIGHLY DENSE BUCKET IS YET TO BE DONE )
    # SEARCHING BY BINARY SEARCH
*/

#include<iostream>
#include<stdlib.h>
using namespace std;

int *in,minn,maxn,dens,range;
int count_n=0,flag=0,find_n,flag_index=0;
int i,j,tmpn,least[10],balance[10];

void disp();
void calc();
int get_index(int n);
void update(int,int);
void init();
void count_least();
void alloc(struct binary *,int,struct binary *);
void auto_post(struct binary *);
int get_L(struct binary *,struct binary *,struct binary *);
int get_R(struct binary *,struct binary *,struct binary *);
void shift_R(struct binary *);
void shift_L(struct binary *);
void tree_init();
void tree_gen();
void locate(int,int,struct binary *);
void base_gen();
void eliminate_tree(struct panel *);//
void count_density();
void get_density(struct binary *tmp);
int find_defragment();
void defragment();
void merge_tree(struct panel *tmp);
int find_fragment();
void fragment();
void split_tree(struct panel *tmp);
void count_max();
void get_max(struct binary *tmp);
void BUCKET_SEARCH(int,struct binary *tmp);

struct div
{
    int x;
    struct div *next;
}*first[10],*last[10],*tmp;

struct binary
{
    int n;
    struct binary *left;
    struct binary *right;
}*L,*L_up,*R,*R_up,*root[10],*neww,*add_bin;

struct panel
{
    int grt;
    int total;
    struct binary *gateway;
    struct panel *down;
}*base[10],*pan,*pan_tmp,*add_pan,*pan_x;


int main()
{
    cout<<"Enter Array Size : ";
    cin>>range;
    in=new int[range];

    for(int i=0;i<range;i++)
        in[i]=abs((rand()%1000));

    init();
    calc();
    count_least();
    tree_init();
    base_gen();

    disp();
    eliminate_tree(base[0]);
    cout<<"\n\nafter elimiating";
    disp();

    count_density();

    defragment();
    cout<<"\n\n\nafter defragement";
    disp();

    //fragment();
    //cout<<"\n\n\nafter splitting";
    //disp();
    cout<<"\n\n(BUG IS OCCUERED DURING SPLITTING , IT WILL BE FIXED SOON./nIF YOU ARE GETTING ERROR , ENTER BIGGER SIZE.)\n";

    count_max();

    cout<<"\n\nEnter Number to Find = ";
    cin>>find_n;

    pan_x=base[0];
    while((pan_x!=NULL)&(find_n>pan_x->grt))
    {
        pan_x=pan_x->down;
        flag_index++;
    }

BUCKET_SEARCH(find_n,pan_x->gateway);

    if(flag==0)
        cout<<"\n\nNumber "<<find_n<<" is NOT found...\n\n";

    return 1;
}

void disp()
{
    int bckt=1;
    cout<<"\n\nDISPLAY:";
    pan_x=base[0];
    while(pan_x)
    {
        cout<<"\n\nBUCKET "<<bckt<<" : ";
        auto_post(pan_x->gateway);
        pan_x=pan_x->down;
        bckt++;
    }
}

void eliminate_tree(struct panel *pan_in)
{
    if(pan_in->down)
    {
        pan_tmp=pan_in;

        pan=pan_in->down;

        while((pan->gateway->n!=-1)&&pan->down!=NULL)
        {
            pan_tmp=pan_tmp->down;
            pan=pan->down;
        }

        if(pan->down)
            if(pan->down->gateway->n==-1)
                while(pan->down->gateway->n==-1)
                    pan=pan->down;
        if(pan->down)
            pan_tmp->down=pan->down;

        if(pan->down)
            eliminate_tree(pan->down);
    }
}

void auto_post(struct binary *tmp)
{
    /*if(tmp->left)
        auto_post(tmp->left);

    if(tmp->right)
        auto_post(tmp->right);

    cout<<tmp->n<<"  ";*/

    // INVERT COMMENT IF YOU WANT TO CHECK POSTFIX VIEW OF TREE LOCATED AT EACH BUCKET

    if(tmp->left)
        auto_post(tmp->left);

    cout<<tmp->n<<"  ";

    if(tmp->right)
        auto_post(tmp->right);
}

int get_L(struct binary * home,struct binary *pre,struct binary *cur)
{
    if(cur->right)
        get_L(home,cur,cur->right);
    else
    {
        L=cur;
        L_up=pre;
    }

    if(home==L_up)
        return 0;
    else
        return 1;
}

int get_R(struct binary * home,struct binary *pre,struct binary *cur)
{
    if(cur->left)
        get_R(home,cur,cur->left);
    else
    {
        R=cur;
        R_up=pre;
    }

    if(home==R_up)
        return 0;
    else
        return 1;
}

void shift_R(struct binary * target)
{
    get_R(target,target,target->right);
    get_L(target,target,target->left);

    if(get_L(target,target,target->left)==0)
    {
        tmpn=target->n;
        target->n=target->left->n;
           target->left=target->left->left;
        L->n=tmpn;
        L->left=NULL;
        L->right=NULL;
        R->left=L;
    }
    else
    {
        tmpn=target->n;
        target->n=L->n;
        L_up->right=L->left;
            L->n=tmpn;
        L->left=NULL;
        L->right=NULL;
        R->left=L;
    }
}

void shift_L(struct binary * target)
{
    get_R(target,target,target->right);
    get_L(target,target,target->left);

    if(get_R(target,target,target->right)==0)
    {
        tmpn=target->n;
        target->n=target->right->n;
            target->right=target->right->right;
        R->n=tmpn;
        R->left=NULL;
        R->right=NULL;
        L->right=R;
    }
    else
    {
        tmpn=target->n;
        target->n=R->n;
        R_up->left=R->right;
            R->n=tmpn;
        R->left=NULL;
        R->right=NULL;
        L->right=R;
    }
}

void tree_init()
{
    for(i=0;i<10;i++)
        {
            root[i]=(struct binary*)malloc(sizeof(struct binary));
            root[i]->left=NULL;
            root[i]->right=NULL;
        }

    for(i=0;i<10;i++)
    {
        if(least[i]==0)
        {
            root[i]->n=-1;
            root[i]->left=NULL;
            root[i]->right=NULL;
        }
        if(least[i]==1)
        {
            root[i]->n=first[i]->x;
            root[i]->left=NULL;
            root[i]->right=NULL;
        }
        else if(least[i]==2)
        {
            root[i]->n=first[i]->x;

            if((first[i]->next->x)>(root[i]->n))
            {
                root[i]->right=(struct binary*)malloc(sizeof(struct binary));
                root[i]->right->n=first[i]->next->x;
                root[i]->right->left=NULL;
                root[i]->right->right=NULL;
                root[i]->left=NULL;
            }
            else
            {
                root[i]->left=(struct binary*)malloc(sizeof(struct binary));
                root[i]->left->n=first[i]->next->x;
                root[i]->left->left=NULL;
                root[i]->left->right=NULL;
                root[i]->right=NULL;
            }
        }
        else if(least[i]>=3)
        {
            int a,b,c,mn,md,mx;
            a=first[i]->x;
            b=first[i]->next->x;
            c=first[i]->next->next->x;

            last[i]=first[i]->next->next->next;

            mx=(a>b)?((a>c)?a:c):((b>c)?b:c);

            if(mx==a)
                if(b>c)
                    {md=b;   mn=c;}
                else
                    {md=c;   mn=b;}
            else if(mx==b)
                if(a>c)
                    {md=a;   mn=c;}
                else
                    {md=c;   mn=a;}
            else if(mx==c)
                if(b>a)
                    {md=b;   mn=a;}
                else
                    {md=a;   mn=b;}

            root[i]->n=md;
            root[i]->right=(struct binary*)malloc(sizeof(struct binary));
            root[i]->left=(struct binary*)malloc(sizeof(struct binary));
            root[i]->right->n=mx;
            root[i]->left->n=mn;

            root[i]->right->left=NULL;
            root[i]->right->right=NULL;
            root[i]->left->left=NULL;
            root[i]->left->right=NULL;

            if(least[i]>3)
            {
                balance[i]=0;

                while(last[i]->next)
                {
                    if(last[i]->x<=root[i]->n)
                        balance[i]--;
                    else
                        balance[i]++;

                    locate(i,last[i]->x,root[i]);
                    last[i]=last[i]->next;
                }
            }
        }
    }
}

void locate(int index,int m,struct binary *cur)
{
    if(m<=cur->n)
        {
            if(cur->left)
                locate(index,m,cur->left);
            else
            {
                cur->left=(struct binary*)malloc(sizeof(struct binary));
                cur->left->n=m;

                cur->left->left=NULL;
                cur->left->right=NULL;
            }
            if(balance[index]<-1)
            {
                shift_R(root[index]);
                balance[index]++;
            }
        }
    else
        {
            if(cur->right)
                locate(index,m,cur->right);
            else
            {
                cur->right=(struct binary*)malloc(sizeof(struct binary));
                cur->right->n=m;

                cur->right->left=NULL;
                cur->right->right=NULL;
            }
            if(balance[index]>1)
            {
                shift_L(root[index]);
                balance[index]--;
            }
        }
}

int get_index(int n)
{
    int m=0;
    while(n>(minn+m*dens))
        m++;

    if(n==maxn)
        return 9;
    else if(n==minn)
        return 0;
    else
        return (m-1);
}

void calc()
{
    minn=maxn=in[0];

    for(int i=1;i<range;i++)
    {
        if(maxn<in[i])
            maxn=in[i];

        if(minn>in[i])
            minn=in[i];
    }
    dens=(maxn-minn)/10;

    for(i=0;i<range;i++)
      update(in[i],get_index(in[i]));
}


void update(int n,int i)
{
    {
        last[i]->x=n;
        last[i]->next=(struct div*)malloc(sizeof(struct div));
        last[i]=last[i]->next;
        last[i]->x=-1;
        last[i]->next=NULL;
    }
}

void init()
{

    neww=(struct binary*)malloc(sizeof(struct binary));
    L=(struct binary*)malloc(sizeof(struct binary));
    L_up=(struct binary*)malloc(sizeof(struct binary));
    R=(struct binary*)malloc(sizeof(struct binary));
    R_up=(struct binary*)malloc(sizeof(struct binary));
    add_bin=(struct binary*)malloc(sizeof(struct binary));

    for(i=0;i<10;i++)
    {
        first[i]=last[i]=(struct div*)malloc(sizeof(struct div));
        first[i]->x=-1;
    }

    for(i=0;i<10;i++)
       first[i]->next=NULL;

    for(i=0;i<10;i++)
        balance[i]=0;
}

void count_least()
{
    for(i=0;i<10;i++)
        least[i]=0;
    for(i=0;i<10;i++)
    {
        if(first[i]->next!=NULL)
            if(first[i]->next->next!=NULL)
                if(first[i]->next->next->next!=NULL)
                    if(first[i]->next->next->next->next!=NULL)
                        least[i]=4;
                    else
                        least[i]=3;
                else
                    least[i]=2;
            else
                least[i]=1;
    }
}

void base_gen()
{
    for(i=0;i<10;i++)
        {
            base[i]=(struct panel*)malloc(sizeof(struct panel));
            base[i]->gateway=root[i];
        }

    for(i=0;i<9;i++)
        base[i]->down=base[i+1];

    pan_tmp=(struct panel*)malloc(sizeof(struct panel));
    add_pan=(struct panel*)malloc(sizeof(struct panel));
    pan_x=(struct panel*)malloc(sizeof(struct panel));
    base[9]->down=NULL;
}

void get_density(struct binary *tmp)
{
    if(tmp->left)
        get_density(tmp->left);

    if(tmp->right)
        get_density(tmp->right);

    count_n++;
}

void count_density()
{
    pan_x=base[0];
    while(pan_x)
    {
        count_n=0;
        get_density(pan_x->gateway);
        pan_x->total=count_n;
        pan_x=pan_x->down;
    }
}

void merge_tree(struct panel *tmp)
{
    if(!tmp->gateway->left)
    {
        tmp->gateway->left=(struct binary*)malloc(sizeof(struct binary));
        tmp->gateway->left->n=0;
    }

    neww=tmp->gateway;

    while(neww->right)
        neww=neww->right;

    neww->right=tmp->down->gateway;
    int k=tmp->down->total;
    tmp->down=tmp->down->down;

    for(int z=0;z<k/2;z++)
        shift_L(tmp->gateway);

}

int find_defragment()
{
    count_density();
    pan=base[0];
    while(pan)
    {
       if(pan->total<(range/10))
            return 1;
       pan=pan->down;
    }

    return 0;
}

void defragment()
{
    while(find_defragment()==1)
    {
        pan=base[0];
        while(pan->down->total>(range/10))
            pan=pan->down;
        merge_tree(pan);

    }
}

int find_fragment()
{
    count_density();
    pan=base[0];
    while(pan)
    {
       if(pan->total>(range*0.2))
        if(pan->gateway->right->right)
          if(pan->gateway->right->right->left)
            if(pan->gateway->right->right->right)
                return 1;

       pan=pan->down;
    }
    return 0;
}

void split_tree(struct panel *tmp)
{
    neww=tmp->gateway;
    add_bin=neww->right->right;
    add_pan->gateway=add_bin;
    add_pan->down=tmp->down;

    tmp->down=add_pan;
}

void fragment()
{
    count_density();
    pan=base[0];
    while(pan)
    {
       if(pan->total>(range*0.1))
        if(pan->gateway->right)
          if(pan->gateway->right->right)
            if(pan->gateway->right->right->left)
              if(pan->gateway->right->right->right)
                split_tree(pan);

       pan=pan->down;
    }
}

void get_max(struct binary *tmp)
{
    if(tmp->left)
        get_max(tmp->left);

    if(tmp->right)
        get_max(tmp->right);

    if(tmp->n>count_n)
        count_n=tmp->n;
}

void count_max()
{
    pan_x=base[0];
    while(pan_x)
    {
        count_n=0;
        get_max(pan_x->gateway);
        pan_x->grt=count_n;
        pan_x=pan_x->down;
    }
}

void BUCKET_SEARCH(int b,struct binary *tmp)
{
    if(b==tmp->n)
        {
            cout<<"\n\nNumber "<<b<<" found at BUCKET NO : "<<++flag_index<<"\n\n";
            flag=1;
        }
    else
    {
        if(b<=tmp->n)
        {
            if(tmp->left)
                BUCKET_SEARCH(b,tmp->left);
        }
        else
        {
            if(tmp->right)
                BUCKET_SEARCH(b,tmp->right);
        }
    }
}
