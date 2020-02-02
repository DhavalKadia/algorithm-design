#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

void show();
void init();
void init();
void junction();
void print();

struct panel* replicateIndex(struct panel *);
void trace(short int, short int, struct panel *);
void split(short int, short int, struct panel *);
int getEndpoint(short int, short int, struct panel *);
void freeGateway(struct gateway *);
void freePanel(struct panel *);
void copyPanel(struct panel *, struct panel *);
void s_show(struct panel *);
void dist(struct panel *);
void navigate();
void dir(float, short int, short int);
void select();
int** alloc_m(int, int);

int*** allocLayer(int, int);		//1
void traceLayer(short int, short int, int &, int &, int &);	//1
void analyzeLayer();
int**** allocLinkMap(int, int);
void allocLink(int, int, int);
void exactCenter(int, int, float, float, int &, int &, float);
void fromTo(int, int, int , int );
void assignCenter(short int,short int, int, int, int);
void getBranch(int, int, int &, int &);
void allocateBranch(int, int, int, int, int &);
void analyzeMap();
void startChange();
void adjustMap();
void subTrace(short int m,short int n,struct panel *p);
void getCluster(int preX, int preY, int x, int y, int nextX, int nextY, int, int, int &clusterX, int &clusterY, float &length);
void getBranchC(int, int, int &, int &);
void getBranchC(int x, int y, int x2, int y2, int &branchX, int &branchY);
void getDestinationCluster(int pre2X, int pre2Y, int preX, int preY, int x, int y,int &branchX, int &branchY, int &clusterX, int &clusterY);
void destFinds();
void foundPathTrace(int x, int y);
void getClusterEnd(int preX, int preY, int x, int y, int nextX, int nextY, int, int, int &clusterX, int &clusterY, float &length);
void getBranchCEnd(int, int, int &, int &);
void getBranchCEnd(int x, int y, int x2, int y2, int &branchX, int &branchY);


int alpha;
int i,j,fi=0,**MAP,x_s,y_s,fx,fy,loc,x_d,y_d,v;
int o=0;
int chk;

int ***centerMap, ****linkMap; //1

float branch_end,minimum=2329;

int dBranch[2][2], dJunction[2][2];

int foundJunction = 0;

struct gateway{

    short int pp;
    short int qq;
    struct gateway *down;

}*bottom,*copx,*temp,*bottom_up,*gamma,*gamma2,*beta,*del_gate,*cop_y,*temp_y,*g_y;

struct panel{

    struct gateway *gate;

}*rightest,*fina,*start,*alphaa,*p_y;

int main()
{

    cout<<"\t\t\t\tProgrammed By\n\n\t\t\t\tDhaval Kadia\n\n\t\t\t\t   BE-II\n\n\t\t\t   Computer Sci. & Engr.\n\n       Faculty Of Technology & Engineering - The M.S. University  ( INDIA ) \n\n\t    This was Completed on Mid 2014 , Published on 2015\n";

    init();

    junction();

	analyzeMap();

    print();

    cout<<"\nEnter Your STARTING Coordinates : \n\tX = ";
    cin>>x_s;

    if(x_s>=alpha)
    {
        cout<<"\nEnter below "<<alpha<<" X = ";
        cin>>x_s;
    }

    cout<<"\tY = ";
    cin>>y_s;

    if(y_s>=alpha)
    {
        cout<<"\nEnter below "<<alpha<<" Y = ";
        cin>>y_s;
    }


    if(MAP[x_s][y_s] != 0)	//4
    {
        cout<<"\nEnter Your DESTINATION Coordinates : \n\tX = ";
        cin>>x_d;

        if(x_d>=alpha)
        {
            cout<<"\nEnter below "<<alpha<<" X = ";
            cin>>x_d;
        }

        cout<<"\tY = ";
        cin>>y_d;

        if(y_d>=alpha)
        {
            cout<<"\nEnter below "<<alpha<<" Y = ";
            cin>>y_d;
        }

        if(MAP[x_d][y_d]>0)
        {
	
			destFinds();
			
			start->gate->pp=x_s;
			start->gate->qq=y_s;
			
			if(MAP[x_s][y_s] != -2)
				startChange();
						
			MAP[x_d][y_d]=1;
			   
			
			clock_t t;
			t = clock();//----------------------------------------------------------------------
			cout<<"\nClock started";

			trace(x_s,y_s,start);

			t = clock() - t;//------------------------------------------------------------------
			double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
			printf("\nAlgorithm took %f seconds to find the Shortest Path \n", time_taken);

			freePanel(start);
			
			cout<<"\nDistance : "<<minimum<<" miles to Go On.";

			printf("\nShortest Path from (%d, %d) to (%d, %d) :", x_s, y_s, x_d, y_d);
			s_show(fina);
        }
        else
        {
            cout<<"\n\nSelect Proper Destination Co-Ordinate from Where PATH is 1.\n";
        }
    }
    else
    {
        cout<<"\n\nSelect Proper Current Co-Ordinate from Where PATH is 2.\n";
    }

    cout<<"\n\nFor any type of Suggestions , you can contact me on dhavalkadiamsu@gmail.com\n";
    getch();

    return 1;
}

int** alloc_m(int m,int n)
{
    int ** matrix;
    
	matrix = (  int **) calloc(m, sizeof(  int *));
	
	for(  int i = 0;i < m; i++)
		matrix[i] = (  int *) calloc(n, sizeof(  int));
		
	return matrix;
}

int*** allocLayer(int m,int n)	//1
{
    int *** matrix;
    
	matrix = (int ***) calloc(m, sizeof(int **));
	
	for(int i = 0;i < m; i++)
		matrix[i] = (int **) calloc(n, sizeof(int*));
	
	for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            matrix[i][j] = (int *) calloc(3, sizeof(int));	//4
        }
    }	
	
	return matrix;
}

int**** allocLinkMap(int m,int n)	//1
{
    int **** matrix;
    
	matrix = (int ****) calloc(m, sizeof(int ***));
	
	for(int i = 0;i < m; i++)
		matrix[i] = (int ***) calloc(n, sizeof(int**));
	
	return matrix;
}

void allocLink(int i, int j, int count)
{
    linkMap[i][j] = (int **) calloc(count, sizeof(int*));
	
	for(int k = 0;k < count; k++)    
		linkMap[i][j][k] = (int *) calloc(5, sizeof(int));	//CNRA3
}

void init()
{
    cout<<"\n[ 5<size<26 Recommended ]\n\nEnter Size of MAP you want = ";
    cin>>alpha;

    MAP=alloc_m(alpha,alpha);

    for(i=0;i<alpha;i++)
    {
        for(j=0;j<alpha;j++)
        {
            MAP[i][j]=0;
        }
    }    
    
    centerMap = allocLayer(alpha, alpha);
    
    linkMap = allocLinkMap(alpha, alpha);

    select();

    bottom=(struct gateway*)malloc(sizeof(struct gateway*));
    bottom_up=(struct gateway*)malloc(sizeof(struct gateway*));
    copx=(struct gateway*)malloc(sizeof(struct gateway*));
    temp=(struct gateway*)malloc(sizeof(struct gateway*));

    fina=(struct panel*)malloc(sizeof(struct panel));

    start=(struct panel*)malloc(sizeof(struct panel));

    start->gate=(struct gateway*)malloc(sizeof(struct gateway*));
    bottom=start->gate;
    start->gate->down=NULL;

    gamma=(struct gateway*)malloc(sizeof(struct gateway*));
    gamma2=(struct gateway*)malloc(sizeof(struct gateway*));

    del_gate=(struct gateway*)malloc(sizeof(struct gateway*));

    cop_y=(struct gateway*)malloc(sizeof(struct gateway*));
    temp_y=(struct gateway*)malloc(sizeof(struct gateway*));

    p_y=(struct panel*)malloc(sizeof(struct panel));
    g_y=(struct gateway*)malloc(sizeof(struct gateway*));
}

void print()
{
    cout<<"\n\t\t\t\tMAP :\n\n";

    char l;
    printf("  Y  ");
    for(i=0;i<alpha;i++)
        printf("%d  ",i%10);
    printf("\n X\n");
    for(i=0;i<alpha;i++)
    {
        printf("%2d ",i);
        for(j=0;j<alpha;j++)
        {
            if(MAP[i][j]<0)
            	printf("%3c",'C');
            else if(MAP[i][j] == 0)
            	printf("%3c",'+');
            else if(MAP[i][j] == 1)
            	printf("%3c",'O');
        }

        printf("\n");
    }
}

void copyPanel(struct panel *from,struct panel *to)
{
    cop_y=from->gate;

    to->gate=(struct gateway*)malloc(sizeof(struct gateway*));

    temp_y=to->gate;

    struct gateway *temp_up_y=(struct gateway*)malloc(sizeof(struct gateway*));

    while(cop_y)
    {
        temp_y->pp=cop_y->pp;
        temp_y->qq=cop_y->qq;

        cop_y=cop_y->down;

        temp_y->down=(struct gateway*)malloc(sizeof(struct gateway*));
        temp_up_y=temp_y;
        temp_y=temp_y->down;
    }

    temp_up_y->down=NULL;
}

void subTrace(short int m,short int n,struct panel *p)
{
  if(!getEndpoint(m,n,p))
    if(MAP[m][n]==1)
    {
    	bottom->down=(struct gateway*)malloc(sizeof(struct gateway*));
    	bottom=bottom->down;

        bottom->pp=m;
        bottom->qq=n;
        bottom->down=NULL;
		//cout<<"\n1 and added "<<m<<", "<<n;
        trace(m,n,p);
    }
    else if(MAP[m][n]==-2 && foundJunction == 0)    
        trace(m,n,p);    
}

void trace(short int x,short int y,struct panel *p)
{
    if(x==x_d&&y==y_d)
        dist(p);

        if(minimum>=branch_end)
        {
            minimum=branch_end;
            copyPanel(p,fina);
        }        
    }
    else
    {
        if(MAP[x][y]==-2)
        {
            split(x,y,p);
        }
        else if(MAP[x][y]==1)
        {
            int m,n;
            
            m = x-1; n = y;
            if(m>=0 && m<alpha && n>=0 && n<alpha)
            	subTrace(m, n, p);
            
            m = x+1; n = y;
            if(m>=0 && m<alpha && n>=0 && n<alpha)
            	subTrace(m, n, p);
            	
            m = x; n = y-1;
            if(m>=0 && m<alpha && n>=0 && n<alpha)
            	subTrace(m, n, p);
			
			m = x; n = y+1;
            if(m>=0 && m<alpha && n>=0 && n<alpha)
            	subTrace(m, n, p);
			
			m = x-1; n = y-1;
            if(m>=0 && m<alpha && n>=0 && n<alpha)
            	subTrace(m, n, p);
			
			m = x-1; n = y+1;
            if(m>=0 && m<alpha && n>=0 && n<alpha)
            	subTrace(m, n, p);
			
			m = x+1; n = y-1;
            if(m>=0 && m<alpha && n>=0 && n<alpha)
            	subTrace(m, n, p);
			
			m = x+1; n = y+1;
            if(m>=0 && m<alpha && n>=0 && n<alpha)
            	subTrace(m, n, p);     
        }
    }
}


void traceLayer(short int x,short int y, int &sumX, int &sumY, int &count)	//1
{
	MAP[x][y] = -2;
	
	sumX += x + 1;
	sumY += y + 1;
	count++;
	
	int m,n;
	for(m=x-1;m<=x+1;m++)
	{
		if(m>=0&&m<alpha)
		{
			for(n=y-1;n<=y+1;n++)
			{
				if(n>=0&&n<alpha)
				{
					if(m!=x||n!=y)
					{
						if(MAP[m][n]==2)
						{   
							traceLayer(m,n, sumX, sumY, count);
						}
					}
				}
			}
		}
	}
}

void exactCenter(int x,int y, float accuX, float accuY, int &nearestX, int &nearestY, float leastD)	//1
{
	MAP[x][y] = -4;
	
	float distance = ((float)x-accuX)*((float)x-accuX) + (y-accuY)*(y-accuY);
	
	if( distance < leastD)
	{
		nearestX = x;
		nearestY = y;
		
		leastD = distance;
	}
	
	int m,n;
	for(m=x-1;m<=x+1;m++)
	{
		if(m>=0&&m<alpha)
		{
			for(n=y-1;n<=y+1;n++)
			{
				if(n>=0&&n<alpha)
				{
					if(m!=x||n!=y)
					{
						if(MAP[m][n]==-2)
						{   
							exactCenter(m, n, accuX, accuY, nearestX, nearestY, leastD);
						}
					}
				}
			}
		}
	}
}

void assignCenter(short int x,short int y, int centerX, int centerY, int count)	//4
{
	MAP[x][y]=-5;
	
	centerMap[x][y][0] = centerX;
	centerMap[x][y][1] = centerY;
	centerMap[x][y][2] = count;
	
	int m,n;
	for(m=x-1;m<=x+1;m++)
	{
		if(m>=0&&m<alpha)
		{
			for(n=y-1;n<=y+1;n++)
			{
				if(n>=0&&n<alpha)
				{
					if(m!=x||n!=y)
					{
						if(MAP[m][n]==-2)
						{   
							assignCenter(m,n, centerX, centerY, count);
						}
					}
				}
			}
		}
	}
}

void fromTo(int x,int y, int from, int to)	//1
{
	MAP[x][y] = to;
	
	int m,n;
	for(m=x-1;m<=x+1;m++)
	{
		if(m>=0&&m<alpha)
		{
			for(n=y-1;n<=y+1;n++)
			{
				if(n>=0&&n<alpha)
				{
					if(m!=x||n!=y)
					{
						if(MAP[m][n]== from)
						{   
							fromTo(m,n, from, to);
						}
					}
				}
			}
		}
	}
}

void getBranch(int x, int y, int &branchX, int &branchY)
{
	int m,n;
	for(m=x-1;m<=x+1;m++)
	{
		if(m>=0&&m<alpha)
		{
			for(n=y-1;n<=y+1;n++)
			{
				if(n>=0&&n<alpha)
				{
					if(m!=x||n!=y)
					{
						if(MAP[m][n]== 1)
						{   
							branchX = m;
							branchY = n;
							
							return;
						}
					}
				}
			}
		}
	}
}

void getBranchC(int x, int y, int &branchX, int &branchY)
{
	int m,n;
	for(m=x-1;m<=x+1;m++)
	{
		if(m>=0&&m<alpha)
		{
			for(n=y-1;n<=y+1;n++)
			{
				if(n>=0&&n<alpha)
				{
					if(m!=x||n!=y)
					{
						if(MAP[m][n]== 1)
						{   
							branchX = m;
							branchY = n;
							
							return;
						}
					}
				}
			}
		}
	}
	
	branchX = branchY = -55;
}

void getBranchC(int x, int y, int x2, int y2, int &branchX, int &branchY)
{
	int m,n;
	for(m=x2-1;m<=x2+1;m++)
	{
		if(m>=0&&m<alpha)
		{
			for(n=y2-1;n<=y2+1;n++)
			{
				if(n>=0&&n<alpha)
				{
					if((m!=x||n!=y) && (m!=x2||n!=y2))
					{
						if(MAP[m][n]== 1)
						{   
							branchX = m;
							branchY = n;
							
							return;
						}
					}
				}
			}
		}
	}
	
	branchX = branchY = -66;
}

void allocateBranch(int x,int y, int centerX, int centerY, int &count)	//1
{
	MAP[x][y] = -6;
	
	int branchX = -1, branchY = -1;
	
	getBranch(x, y, branchX, branchY);
	
	linkMap[centerX][centerY][count][0] = branchX;
	linkMap[centerX][centerY][count][1] = branchY;
	
	linkMap[centerX][centerY][count][2] = -777;
	linkMap[centerX][centerY][count][3] = -777;
	linkMap[centerX][centerY][count][4] = -777;
	
	count++;
	
	int m,n;
	for(m=x-1;m<=x+1;m++)
	{
		if(m>=0&&m<alpha)
		{
			for(n=y-1;n<=y+1;n++)
			{
				if(n>=0&&n<alpha)
				{
					if(m!=x||n!=y)
					{
						if(MAP[m][n]== -2)
						{   
							allocateBranch(m,n, centerX, centerY, count);
						}
					}
				}
			}
		}
	}
}

void analyzeLayer(int x, int y)
{
	int sumX = 0, sumY = 0, count = 0, centerX, centerY, cc = 0;
	float accuCX, accuCY;
	
	traceLayer(x, y, sumX, sumY, count);
	
	accuCX = (float)sumX / (float)count - 1;
	accuCY = (float)sumY / (float)count - 1;
	
	centerX = accuCX;
	centerY = accuCY;
	
	if(accuCX - (int)accuCX > 0.5)
		centerX += 1;
	
	if(accuCY - (int)accuCY > 0.5)
		centerY += 1;
	
	if(MAP[centerX][centerY] != -2)
	{
		float nearestX = accuCX, nearestY = accuCY, leastD = 99999;
	
		exactCenter(x, y, nearestX, nearestY, centerX, centerY, leastD);	
	
		fromTo(x, y, -4, -2);
	}
	
	assignCenter(x, y, centerX, centerY, count);
	fromTo(x, y, -5, -2);
	
	allocLink(centerX, centerY,count);
	allocateBranch(x, y, centerX, centerY, cc);
	fromTo(x, y, -6, -2);
}

void getCluster(int pre2X, int pre2Y, int preX, int preY, int x, int y, int orgClusterX, int orgClusterY, int &clusterX, int &clusterY, float &length)
{
	int m,n;
	for(m=x-1;m<=x+1;m++)
	{
		if(m>=0&&m<alpha)
		{
			for(n=y-1;n<=y+1;n++)
			{
				if(n>=0&&n<alpha)
				{
					if((m!=x||n!=y) && (m!=preX||n!=preY) && (m!=pre2X||n!=pre2Y))
					{
						if(MAP[m][n]== 1)
						{   
							length++;

							if((x-m)&&(y-n))
							{
							   length=length+0.41;
							}
							
							getCluster(preX, preY, x, y, m, n, orgClusterX, orgClusterY, clusterX, clusterY, length);
						}
						else if(MAP[m][n]== -2 && (centerMap[m][n][0] != orgClusterX || centerMap[m][n][1] != orgClusterY))
						{
							clusterX = centerMap[m][n][0];
							clusterY = centerMap[m][n][1];
							
							return;
						}
					}
				}
			}
		}
	}
}

void getDestinationCluster(int pre2X, int pre2Y, int preX, int preY, int x, int y,int &branchX, int &branchY, int &clusterX, int &clusterY)
{
	int m,n;
	for(m=x-1;m<=x+1;m++)
	{
		if(m>=0&&m<alpha)
		{
			for(n=y-1;n<=y+1;n++)
			{
				if(n>=0&&n<alpha)
				{
					if((m!=x||n!=y) && (m!=preX||n!=preY) && (m!=pre2X||n!=pre2Y))
					{
						if(MAP[m][n]== 1)
						{          							    
							getDestinationCluster(preX, preY, x, y, m, n, branchX, branchY, clusterX, clusterY);
						}
						else if(MAP[m][n]== -2)
						{
							branchX = x;
							branchY = y;
							
							clusterX = centerMap[m][n][0];
							clusterY = centerMap[m][n][1];
							
							return;
						}
					}
				}
			}
		}
	}
}

void destFinds()
{
	int nextX, nextY, next2X, next2Y, clusterX, clusterY, branchX, branchY;
	
	int m,n, cnt = 0;
		
		for(m=x_d-1;m<=x_d+1;m++)
		{
			if(m>=0&&m<alpha)
			{
				for(n=y_d-1;n<=y_d+1;n++)
				{
					if(n>=0&&n<alpha)
					{
						if((m!=x_d||n!=y_d))
						{
							if(MAP[m][n]== 1)
							{   
								getBranchC(x_d, y_d, m, n, nextX, nextY);
								
								getDestinationCluster(x_d, y_d, m, n, nextX, nextY, branchX, branchY, clusterX, clusterY);	            					
								
								dBranch[cnt][0] = branchX;
								dBranch[cnt][1] = branchY;
								
								dJunction[cnt][0] = clusterX;
								dJunction[cnt][1] = clusterY;
								
								linkMap[clusterX][clusterY][0][4] = -555;
								
								cnt++;
							}
						}
					}
				}
			}
		}
}

void analyzeMap()
{
	for(int i=0;i<alpha;i++)
	{
	    for(int j=0;j<alpha;j++)
        {
            if(MAP[i][j] == 2)
            {
            	analyzeLayer(i, j);
			}
        }
	}
	 
	int nextX, nextY, next2X, next2Y, centerX, centerY, clusterX, clusterY;
	float length = 0;
	 
	for(int x=0;x<alpha;x++)
	{
	    for(int y=0;y<alpha;y++)
        {
            if(MAP[x][y] == -2)
            { 	
            	centerX = centerMap[x][y][0];
            	centerY = centerMap[x][y][1];
            	
            	if(linkMap[centerX][centerY][0][4] == -777)	//0 as a representative
            	{
            		for(int i = 0; i < centerMap[x][y][2]; i++)
            		{
            			if(linkMap[centerX][centerY][i][0] != -1)
            			{
            				length = 0;
            				getBranchC(linkMap[centerX][centerY][i][0], linkMap[centerX][centerY][i][1], nextX, nextY);
            				
            				if(nextX != -55)
            				{
            					length++;
            					if((linkMap[centerX][centerY][i][0]-nextX)&&(linkMap[centerX][centerY][i][1]-nextY))
         							length += 0.41;
            					
            					getBranchC(linkMap[centerX][centerY][i][0], linkMap[centerX][centerY][i][1], nextX, nextY, next2X, next2Y);
            					
            					if(next2X != -66)
            					{
            						length++;
            						if((next2X-nextX)&&(next2Y-nextY))
         								length += 0.41;
         						
            						getCluster(linkMap[centerX][centerY][i][0], linkMap[centerX][centerY][i][1], nextX, nextY, next2X, next2Y, centerX, centerY, clusterX, clusterY, length);
								}
								else if(next2X == -66)
									getCluster(linkMap[centerX][centerY][i][0], linkMap[centerX][centerY][i][1], nextX, nextY, nextX, nextY, centerX, centerY, clusterX, clusterY, length);
            					
							}
							else if(nextX == -55)
								getCluster(linkMap[centerX][centerY][i][0], linkMap[centerX][centerY][i][1], linkMap[centerX][centerY][i][0], linkMap[centerX][centerY][i][1], linkMap[centerX][centerY][i][0], linkMap[centerX][centerY][i][1], centerX, centerY, clusterX, clusterY, length);
            				
	            			linkMap[centerX][centerY][i][2] = clusterX;
	            			linkMap[centerX][centerY][i][3] = clusterY;
	            			linkMap[centerX][centerY][i][4] = length;	            	
            			}
					}
					
					if(linkMap[centerX][centerY][0][4] == -777)
						linkMap[centerX][centerY][0][4] = -666;
				}
			}
        }
	}

}

void startChange()
{
	MAP[x_s][y_s] = -2;
	
	centerMap[x_s][y_s][0] = x_s;
	centerMap[x_s][y_s][1] = y_s;
	centerMap[x_s][y_s][2] = 2;
	
	int m,n, x = x_s, y = y_s, counter = 0;
	
	allocLink(x_s, y_s, 2);
	
            for(m=x-1;m<=x+1;m++)
            {
                if(m>=0&&m<alpha)
                {
                    for(n=y-1;n<=y+1;n++)
                    {
                        if(n>=0&&n<alpha)
                        {
                            if(m!=x||n!=y)
                            {
                                if(MAP[m][n]== 1 && counter < 2)
                                {   
                                	linkMap[x_s][y_s][counter][0] = m;
                                	linkMap[x_s][y_s][counter][1] = n;
                                	
                                	counter++;
                                }
                            }
                        }
                    }
                }
            }
}

void split(short int x,short int y,struct panel *p)
{
	int centerX, centerY, count, m, n;
        	
    centerX = centerMap[x][y][0];
    centerY = centerMap[x][y][1];
    count = centerMap[x][y][2];
        	
    if(!getEndpoint(centerX,centerY,p))
    {
        bottom->down=(struct gateway*)malloc(sizeof(struct gateway*));
        bottom=bottom->down;

        bottom->pp=centerX;
        bottom->qq=centerY;

        bottom->down=NULL;
    }
        
		if(x == x_s && y == y_s)
		{
			for(int i = 0; i < count; i++)
        	{        		
        		m = linkMap[centerX][centerY][i][0];
        		n = linkMap[centerX][centerY][i][1];
        		        		        		
        			if(!getEndpoint(m,n,p))
                    {
                                struct panel *temp_pan=(struct panel*)malloc(sizeof(struct panel));

                                temp_pan=replicateIndex(p);

                                if(!getEndpoint(m,n,temp_pan))
                                {
                                    bottom->down=(struct gateway*)malloc(sizeof(struct gateway*));
                                    bottom=bottom->down;

                                    bottom->pp=m;
                                    bottom->qq=n;
                                    bottom->down=NULL;
                                }
                                trace(m,n,temp_pan);

                                freePanel(temp_pan);
                    }
			}
		}
		else if(linkMap[centerX][centerY][0][4] != -555)		
		{
        	for(int i = 0; i < count; i++)
        	{        		
        		m = linkMap[centerX][centerY][i][2];
        		n = linkMap[centerX][centerY][i][3];
        		
        		if(m != -777)	
        		{	        		
        			if(!getEndpoint(m,n,p))
                    {
                                struct panel *temp_pan=(struct panel*)malloc(sizeof(struct panel));

                                temp_pan=replicateIndex(p);

                                if(!getEndpoint(m,n,temp_pan))
                                {
                                    bottom->down=(struct gateway*)malloc(sizeof(struct gateway*));
                                    bottom=bottom->down;

                                    bottom->pp=m;
                                    bottom->qq=n;

                                    bottom->down=NULL;
                                }
                                trace(m,n,temp_pan);

                                freePanel(temp_pan);
                    }
           		}
			}
		}
		else
		{
			if(centerX == dJunction[0][0] && centerY == dJunction[0][1])
			{
				foundJunction = 1;
				
				getEndpoint(dBranch[0][0],dBranch[0][1],p);

                                    bottom->down=(struct gateway*)malloc(sizeof(struct gateway*));
                                    bottom=bottom->down;

                                    bottom->pp=dBranch[0][0];
                                    bottom->qq=dBranch[0][1];

                                    bottom->down=NULL;
                                    
				trace(dBranch[0][0], dBranch[0][1], p);
			}
			else if(centerX == dJunction[1][0] && centerY == dJunction[1][1])
			{
				
				foundJunction = 1;
				
				getEndpoint(dBranch[1][0],dBranch[1][1],p);

                                    bottom->down=(struct gateway*)malloc(sizeof(struct gateway*));
                                    bottom=bottom->down;

                                    bottom->pp=dBranch[1][0];
                                    bottom->qq=dBranch[1][1];

                                    bottom->down=NULL;
				
				trace(dBranch[1][0], dBranch[1][1], p);
			}
			else
				cout<<"\nERROR";
				
			foundJunction = 0;
		}
}


struct panel* replicateIndex(struct panel *vect)
{
    copx=vect->gate;
    rightest=(struct panel*)malloc(sizeof(struct panel));
    rightest->gate=(struct gateway*)malloc(sizeof(struct gateway*));

    temp=rightest->gate;

    struct gateway *temp_up=(struct gateway*)malloc(sizeof(struct gateway*));

    while(copx)
    {
        temp->pp=copx->pp;
        temp->qq=copx->qq;

        copx=copx->down;

        temp->down=(struct gateway*)malloc(sizeof(struct gateway*));
        temp_up=temp;
        temp=temp->down;
    }

    temp_up->down=NULL;

    return rightest;
}

int getEndpoint(short int a,short int b,struct panel *pan)
{
 bottom=pan->gate;

 while(bottom)
    {
        if((bottom->pp==a)&&(bottom->qq==b))
            {
                return 1;
            }
        bottom_up=bottom;
        bottom=bottom->down;
    }
    bottom=bottom_up;

    return 0;
}

void navigate()
{
    short int d_x,d_y,c_x,c_y;
    int step;
    float dis;

    bottom=fina->gate;

    d_x=bottom->down->pp-bottom->pp;
    d_y=bottom->down->qq-bottom->qq;

    if(d_x&&d_y)
        dis=1.41;
    else
        dis=1;

    step=1;

    bottom=bottom->down;

    while(bottom->down)
    {
        c_x=bottom->down->pp-bottom->pp;
        c_y=bottom->down->qq-bottom->qq;

        if(c_x==d_x&&c_y==d_y)
        {
            step++;

            if(c_x&&c_y)
                dis=dis+1.41;
            else
                dis=dis+1;
        }
        else
        {
            dir(step,d_x,d_y);

            step=1;

            d_x=bottom->down->pp-bottom->pp;
            d_y=bottom->down->qq-bottom->qq;

            if(d_x&&d_y)
                dis=1.41;
            else
                dis=1;
        }

        bottom=bottom->down;
    }

    dir(step,c_x,c_y);
}

void dir(float s,short int a,short int b)
{
    if(a==1&&b==0)
        printf("\n %.2f mile SOUTH      [ %d step x 1    mile ]",s,(int)s);
    else if(a==-1&&b==0)
        printf("\n %.2f mile NORTH      [ %d step x 1    mile ]",s,(int)s);
    else if(a==0&&b==1)
        printf("\n %.2f mile EAST       [ %d step x 1    mile ]",s,(int)s);
    else if(a==0&&b==-1)
        printf("\n %.2f mile WEST       [ %d step x 1    mile ]",s,(int)s);
    else if(a==1&&b==1)
        printf("\n %.2f mile SOUTH-EAST [ %d step x 1.41 mile ]",s*1.41,(int)s);
    else if(a==-1&&b==-1)
        printf("\n %.2f mile NORTH-WEST [ %d step x 1.41 mile ]",s*1.41,(int)s);
    else if(a==1&&b==-1)
        printf("\n %.2f mile SOUTH-WEST [ %d step x 1.41 mile ]",s*1.41,(int)s);
    else if(a==-1&&b==1)
        printf("\n %.2f mile NORTH-EAST [ %d step x 1.41 mile ]",s*1.41,(int)s);
}

void dist(struct panel *pan)
{
    branch_end=0;

    bottom=pan->gate;

    while(bottom->down)
    {
    	if(MAP[bottom->pp][bottom->qq] == -2)
    	{
    		for(int i = 0; i< centerMap[bottom->pp][bottom->qq][2]; i++)
    		{
    			if(linkMap[bottom->pp][bottom->qq][i][2] == bottom->down->pp && linkMap[bottom->pp][bottom->qq][i][3] == bottom->down->qq)
    				branch_end += linkMap[bottom->pp][bottom->qq][i][4];
			}    		
		}
		else
		{
			branch_end++;

        	if((bottom->pp-bottom->down->pp)&&(bottom->qq-bottom->down->qq))
        	{
            	branch_end=branch_end+0.41;
        	}
		}

        bottom=bottom->down;
    }
}

void junction()
{
    int m,n,branch;
    for(i=0;i<alpha;i++)
    {
        for(j=0;j<alpha;j++)
        {
            branch=0;
            for(m=i-1;m<=i+1;m++)
            {
                if(MAP[i][j]>0)
                {
                    if(m>=0&&m<alpha)
                    {
                        for(n=j-1;n<=j+1;n++)
                        {
                            if(n>=0&&n<alpha)
                            {
                                if(MAP[m][n]>0&&(m!=i||n!=j))// && (m!=0||n!=0)&&(m!=0||n!=alpha-1)&&(m!=alpha-1||n!=0)&&(m!=alpha-1||n!=alpha-1))	//5
                                	branch++;
                            }
                        }
                    }
                }
            }

        if(branch>2)
            MAP[i][j]=2;
        }
    }
    
    adjustMap();
}

void adjustMap()	//6
{
	int m,n;
	
    for(i=0;i<alpha;i++)
    {
        for(j=0;j<alpha;j++)
        {
           if(MAP[i][j] == 1)
           {
           		if(i < alpha - 1 && j < alpha - 1)           		
           			if(MAP[i][j+1] == 2 && MAP[i+1][j] == 2)           			
						MAP[i][j+1] = MAP[i+1][j] = 1;
						
				if(i < alpha - 1 && j > 0)
           			if(MAP[i][j-1] == 2 && MAP[i+1][j] == 2)
						MAP[i][j-1] = MAP[i+1][j] = 1;
						
				if(i > 0 && j > 0)
           			if(MAP[i-1][j] == 2 && MAP[i][j-1] == 2)
					   	MAP[i-1][j] = MAP[i][j-1] = 1;
           			
				if(i > 0 && j < alpha - 1)
					if(MAP[i][j+1] == 2 && MAP[i-1][j] == 2)
           				MAP[i][j+1] = MAP[i-1][j] = 1;
           				
				if(i > 0 && j > 0 && j < alpha - 1)
					if(MAP[i-1][j-1] == 2 && MAP[i-1][j+1] == 2)
           				MAP[i-1][j-1] = MAP[i-1][j+1] = 1;
           				
				if(i > 0 && i < alpha - 1 && j < alpha - 1)
					if(MAP[i-1][j+1] == 2 && MAP[i+1][j+1] == 2)
           				MAP[i-1][j+1] = MAP[i+1][j+1] = 1;
           				
				if(i < alpha - 1 && j > 0 && j < alpha - 1)
					if(MAP[i+1][j+1] == 2 && MAP[i+1][j-1] == 2)
           				MAP[i+1][j+1] = MAP[i+1][j-1] = 1;
           				
				if(i > 0 && i < alpha - 1 && j > 0)
					if(MAP[i+1][j-1] == 2 && MAP[i-1][j-1] == 2)
           				MAP[i+1][j-1] = MAP[i-1][j-1] = 1;           				
		   }        
        }
    }
}

void foundPathTrace(int x, int y)
{
	printf("-> [%d , %d] ",x, y);
	
            int m,n;
            for(m=x-1;m<=x+1;m++)
            {
                if(m>=0&&m<alpha)
                {
                    for(n=y-1;n<=y+1;n++)
                    {
                        if(n>=0&&n<alpha)
                        {
                            if(m!=x||n!=y)
                            {
                                if(MAP[m][n]== 1)
                                {   
                                    foundPathTrace(m, n);
                                }
                            }
                        }
                    }
                }
            }
}


void getBranchCEnd(int x, int y, int &branchX, int &branchY)
{
	printf("-> [%d , %d] ",x, y);
	
            int m,n;
            for(m=x-1;m<=x+1;m++)
            {
                if(m>=0&&m<alpha)
                {
                    for(n=y-1;n<=y+1;n++)
                    {
                        if(n>=0&&n<alpha)
                        {
                            if(m!=x||n!=y)
                            {
                                if(MAP[m][n]== 1)
                                {   
                                    branchX = m;
                                    branchY = n;
                                    
                                    return;
                                }
                            }
                        }
                    }
                }
            }
            
            branchX = branchY = -55;
}

void getBranchCEnd(int x, int y, int x2, int y2, int &branchX, int &branchY)
{
	printf("-> [%d , %d] ",x2, y2);
	
            int m,n;
            for(m=x2-1;m<=x2+1;m++)
            {
                if(m>=0&&m<alpha)
                {
                    for(n=y2-1;n<=y2+1;n++)
                    {
                        if(n>=0&&n<alpha)
                        {
                            if((m!=x||n!=y) && (m!=x2||n!=y2))
                            {
                                if(MAP[m][n]== 1)
                                {   
                                    branchX = m;
                                    branchY = n;
                                    
                                    return;
                                }
                            }
                        }
                    }
                }
            }
            
            branchX = branchY = -66;
}

void getClusterEnd(int pre2X, int pre2Y, int preX, int preY, int x, int y, int orgClusterX, int orgClusterY, int &clusterX, int &clusterY, float &length)
{
	printf("-> [%d , %d] ",x, y);
	
            int m,n;
            for(m=x-1;m<=x+1;m++)
            {
                if(m>=0&&m<alpha)
                {
                    for(n=y-1;n<=y+1;n++)
                    {
                        if(n>=0&&n<alpha)
                        {
                            if((m!=x||n!=y) && (m!=preX||n!=preY) && (m!=pre2X||n!=pre2Y))
                            {
                                if(MAP[m][n]== 1)
                                { 
       							    getClusterEnd(preX, preY, x, y, m, n, orgClusterX, orgClusterY, clusterX, clusterY, length);
                                }
                                else if(MAP[m][n]== -2 && (centerMap[m][n][0] != orgClusterX || centerMap[m][n][1] != orgClusterY))
                                {
                                	return;
								}
                            }
                        }
                    }
                }
            }
}

void s_show(struct panel *px)
{
    int nextX, nextY, next2X, next2Y, centerX, centerY, clusterX, clusterY, m, n, count;
	float length = 0;
	  
    p_y=px;

    g_y=p_y->gate;

    while(g_y)
    {        
        if(MAP[g_y->pp][g_y->qq] == -2)
        {
        	printf("\nFrom Cluster: [%d , %d] ",g_y->pp,g_y->qq);
        	
        	centerX = centerMap[g_y->pp][g_y->qq][0];
    		centerY = centerMap[g_y->pp][g_y->qq][1];
    		count = centerMap[g_y->pp][g_y->qq][2];
    		
    		printf("To Path: ");
    		for(int i = 0; i < count; i++)
        	{        		
        		if(linkMap[centerX][centerY][i][2] == g_y->down->pp && linkMap[centerX][centerY][i][3] == g_y->down->qq)
        		   {
        		   		
        		   		length = 0;
						getBranchCEnd(linkMap[centerX][centerY][i][0], linkMap[centerX][centerY][i][1], nextX, nextY);
						
						if(nextX != -55)
						{
							length++;
							if((linkMap[centerX][centerY][i][0]-nextX)&&(linkMap[centerX][centerY][i][1]-nextY))
								length += 0.41;
							
							getBranchCEnd(linkMap[centerX][centerY][i][0], linkMap[centerX][centerY][i][1], nextX, nextY, next2X, next2Y);
							
							if(next2X != -66)
							{
								length++;
								if((next2X-nextX)&&(next2Y-nextY))
									length += 0.41;
							
								getClusterEnd(linkMap[centerX][centerY][i][0], linkMap[centerX][centerY][i][1], nextX, nextY, next2X, next2Y, centerX, centerY, clusterX, clusterY, length);
							}
							else if(next2X == -66)
							{									
								getClusterEnd(linkMap[centerX][centerY][i][0], linkMap[centerX][centerY][i][1], nextX, nextY, nextX, nextY, centerX, centerY, clusterX, clusterY, length);
							}
							
						}
						else if(nextX == -55)
						{
							getClusterEnd(linkMap[centerX][centerY][i][0], linkMap[centerX][centerY][i][1], linkMap[centerX][centerY][i][0], linkMap[centerX][centerY][i][1], linkMap[centerX][centerY][i][0], linkMap[centerX][centerY][i][1], centerX, centerY, clusterX, clusterY, length);
						}
				   }
			}
		}
		else
		{
			printf("-> [%d , %d] ",g_y->pp,g_y->qq);
		}
        
        g_y=g_y->down;
    }
}

void freePanel(struct panel *vect)
{
    del_gate=vect->gate;

    freeGateway(del_gate);

    free(vect);
}

void freeGateway(struct gateway *gat)
{
    if(gat==NULL)
        return;
    else
    {
        freeGateway(gat->down);

        free(gat);
    }
}

void select()
{
    cout<<"\n\nSelect Pattern of MAP from below Choices :";
    cout<<"\n1. X inside Square.\n2. + inside Square.\n3. Mercedes Symbol inside Square.\n4. Diamond Shaped.\n5. Make Your Customized MAP.";
    cout<<"\n\nEnter Choice = ";
    cin>>v;

    if(v==1)
    {
        for(int z=0;z<alpha;z++)
            MAP[0][z]=1;
        for(int z=0;z<alpha;z++)
            MAP[z][0]=1;
        for(int z=1;z<alpha;z++)
            MAP[z][z]=1;
        for(int z=0;z<alpha;z++)
            MAP[(alpha-1)][z]=1;
        for(int z=0;z<alpha;z++)
            MAP[z][(alpha-1)]=1;
        for(int z=0;z<alpha;z++)
            MAP[z][(alpha-1)-z]=1;
	
		for(int z=0;z<alpha;z++)	//7
			MAP[z][6] = 1;
		for(int z=0;z<alpha;z++)	//7
			MAP[z][16] = 1;
			
		for(int z=0;z<alpha;z++)	//7
			MAP[z][44] = 1;
		for(int z=0;z<alpha;z++)	//7
			MAP[z][34] = 1;
    }
    else if(v==2)
    {
        for(int z=0;z<alpha;z++)
            MAP[0][z]=1;
        for(int z=0;z<alpha;z++)
            MAP[z][0]=1;
        for(int z=0;z<alpha;z++)
            MAP[(alpha-1)][z]=1;
        for(int z=0;z<alpha;z++)
            MAP[z][(alpha-1)]=1;
        for(int z=0;z<alpha;z++)
            MAP[z][alpha/2]=1;
        for(int z=0;z<alpha;z++)
            MAP[alpha/2][z]=1;
    }
    else if(v==3)
    {
        for(int z=0;z<alpha;z++)
            MAP[0][z]=1;
        for(int z=0;z<alpha;z++)
            MAP[z][0]=1;
        for(int z=0;z<alpha;z++)
            MAP[(alpha-1)][z]=1;
        for(int z=0;z<alpha;z++)
            MAP[z][(alpha-1)]=1;
        for(int z=0;z<(alpha/2);z++)
            MAP[z][alpha/2]=1;
        for(int z=(alpha/2);z<alpha;z++)
            MAP[z][z]=1;
        for(int z=(alpha/2);z<alpha;z++)
            MAP[z][(alpha-1)-z]=1;
    }
    else if(v==4)
    {
        for(int z=(alpha/2);z<alpha;z++)
            MAP[0][z]=1;
        for(int z=(alpha/2);z<alpha;z++)
            MAP[z][0]=1;
        for(int z=0;z<(alpha/2);z++)
            MAP[(alpha-1)][z]=1;
        for(int z=0;z<(alpha/2);z++)
            MAP[z][(alpha-1)]=1;
        for(int z=0;z<alpha;z++)
            MAP[z][alpha/2]=1;
        for(int z=0;z<alpha;z++)
            MAP[alpha/2][z]=1;
    }
    else if(v==5)
    {
    cout<<"\n\nEnter 1 Where you want to add PATH and Enter 0 Where remain it BLANK.\n\n";
    for(i=0;i<alpha;i++)
	 {
	     for(j=0;j<alpha;j++)
         {
            cout<<"MAP ["<<i<<"]["<<j<<"] = ";
            cin>>MAP[i][j];
         }
         cout<<"\n";
	 }
    }
    else
        cout<<"\n\nEnter Choice From 1 to 5.";
}