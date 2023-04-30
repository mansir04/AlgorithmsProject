
// GITHUB LINK : https://github.com/mrdv54/AlgorithmsProject

// Project is entirely made in C++ to demonstrate the use of classes and understand object oriented programming. 

/*---------------------------A L G O R I T H M S___A N D___P R O B L E M___S O L V I N G___P R O J E C T-------------------------------*/

/*---------------------------A L G O R I T H M S___A N D___P R O B L E M___S O L V I N G___P R O J E C T-------------------------------*/

/*---------------------------A L G O R I T H M S___A N D___P R O B L E M___S O L V I N G___P R O J E C T-------------------------------*/


//LIBRARIES
#include<bits/stdc++.h>
#include <vector>
#include <queue>
#include <limits>
#include <map>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include <windows.h>
#include <iomanip>
#include <string>
#include <vector>


using namespace std;


/*------------------------------------------------D I J K S T R A----------------------------------------------------------
--------------------------------------------------D I J K S T R A----------------------------------------------------------
--------------------------------------------------D I J K S T R A----------------------------------------------------------*/


const int INF = numeric_limits<int>::max(); // maximum value of an int
int fuel=10000; // global variable to store the remaining fuel

struct Edge {
    int v, w, fuel, time; // v = destination vertex, w = edge weight, fuel = fuel required, time = time required
};
int n = 20, m = 38, s,t;

int infinite=INT_MAX;
int mini=infinite;
int chk=0;
int visited[N]={0};
int initReductionCost=0;//r cap
int reductionCost1=0;//r1 cap
int reductionCost2=0;//r2 cap
int parentCost=0;//previous parent cost
int parentCost1=0;//comp1 costing
int parentCost2=0;//comp2 costing
int totalCost=0;//final cost
string path;//path
int comp1Cost,comp2Cost;

int city[N][N] = {
    {infinite, 5, 2, 7},
    {5, infinite, 4, 8},
    {2, 4, infinite, 3},
    {7, 8, 3, infinite},
  
    };
int comp1[N][N],comp2[N][N];

map<int, string> cityNames {
    {0, "Kedarnath"},
    {1, "Badrinath"},
    {2, "Mathura"},
    {3, "Vrindavan"},
    {4, "Dwarka"},
    {5, "Shirdi"},
    {6, "Rameshvaram"},
    {7, "Banaras"},
    {8, "Kolkata"},
    {9, "Panchkula"},
    {10, "Shazanpur"},
    {11, "Bhopal"},
    {12, "Noida"},
    {13, "Delhi"},
    {14, "Ahemdabad"},
    {15, "trivendram"},
    {16, "Pondicherry"},
    {17, "Bangalore"},
    {18, "Kanpur"},
    {19, "Mumbai"}
};

vector<int> dist, parent;

void dijkstra(int s, vector<vector<Edge>>& adjList, vector<int>& dist, vector<int>& parent) {
    int n = adjList.size();
    dist.assign(n, INF);
    parent.assign(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, s);
    dist[s] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;/* node*/
        int d = pq.top().first;//distance
        pq.pop();
        if (d > dist[u]) continue;
        for (auto& e : adjList[u]) {
            int v = e.v, w = e.w, f = e.fuel, t = e.time;
            if (f <= fuel && dist[u] + t < dist[v]) {
                dist[v] = dist[u] + t;
                parent[v] = u;
                fuel -= f; // update remaining fuel based on fuel required
                pq.emplace(dist[v], v);
            }
        }
    }
}

void printPath(int u, const vector<int>& parent,map<int, string> cityNames) {
    if (parent[u] == -1) {
        cout << cityNames[u];
        return;
    }
    printPath(parent[u], parent, cityNames);
    cout << " -> " << cityNames[u];
}


/*------------------------------------------------S Y S T E M S E T U P----------------------------------------------------------
--------------------------------------------------S Y S T E M S E T U P----------------------------------------------------------
--------------------------------------------------S Y S T E M S E T U P----------------------------------------------------------*/



void printChar(char ch,int n)        //function to print patterns
{
    while(n--)
    {
        putchar(ch);
    }
}
void title()
{
    system("cls");                   //setting the console for program
    system("COLOR 11");
    cout<<"\n\n\t";
    printChar('=',30);
    cout<<" E N R O U T E ";
    printChar('=',30);
    cout<<"\n";
}

void gotoxy(int x,int y)
{
	COORD CRD;                      //setting cursor position
    CRD.X = x;
    CRD.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),CRD);
}

//  Reduction matrix method...............

void display(int matrix[N][N])
{
    cout<<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(matrix[i][j]!=infinite)
            cout<<matrix[i][j]<<"\t";
            else
            cout<<"X\t";
        }
        cout<<endl<<endl;
    }
}
void findInitCost()//For initial reduction
{
    for(int i=0;i<N;i++)
    {
        mini=infinite;
        for(int j=0;j<N;j++)    //FINDING MINIMUM ELEMENT
        {
            if(city[i][j]<mini)
            {
                mini=city[i][j];
            }
        }
        for(int j=0;j<N;j++)    //reduced matrix
        {
            if(city[i][j]!=infinite)
            city[i][j]=city[i][j]-mini;
        }
        initReductionCost=initReductionCost+mini;  //reduction cost
    }
    for(int i=0;i<N;i++)
    {
        mini=infinite;
        for(int j=0;j<N;j++)
        {
            if(city[j][i]<mini)
            {
                mini=city[j][i];
            }
        }
        for(int j=0;j<N;j++)
        {
            if(city[j][i]!=infinite)
            city[j][i]=city[j][i]-mini;
        }
        initReductionCost=initReductionCost+mini;
    }
    cout<<endl;
    display(city);
    cout<<endl;
    totalCost=parentCost=initReductionCost;
}
int ReductionMatrix1()
{
    reductionCost1=0;
    for (int i=0;i<N;i++)
    {
        mini=infinite;
        for(int j=0;j<N;j++)
        {
            if(comp1[i][j]<mini)
            {
                mini=comp1[i][j];
            }
        }
        if(mini!=infinite)
        {
            for (int j = 0; j < N; j++)
            {
                if (comp1[i][j] != infinite)
                {
                    comp1[i][j] = comp1[i][j] - mini;
                }
            }
        }
        if(mini==infinite)
        {
            mini=0;
        }
        reductionCost1=reductionCost1+mini;
    }
    for (int i=0;i<N;i++)
    {
        mini=infinite;
        for(int j=0;j<N;j++)
        {
            if(comp1[j][i]<mini)
            {
                mini=comp1[j][i];
            }
        }
        if(mini!=infinite)
        {
            for (int j = 0; j < N; j++)
            {
                if (comp1[j][i] != infinite)
                {
                    comp1[j][i] = comp1[j][i] - mini;
                }
            }
        }
        if (mini==infinite)
        {
            mini=0;
        }
        reductionCost1=reductionCost1+mini;
    }
    parentCost1=parentCost+reductionCost1;
    return parentCost1;
}
int ReductionMatrix2()  //called inside copy2
{
    reductionCost2=0;
    for (int i=0;i<N;i++)
    {
        mini=infinite;
        for(int j=0;j<N;j++)
        {
            if(comp2[i][j]<mini)
            {
                mini=comp2[i][j];
            }
        }
        if(mini!=infinite)
        {
            for (int j = 0; j < N; j++)
            {
                if (comp2[i][j] != infinite)
                    comp2[i][j] = comp2[i][j] - mini;
            }
        }
        if(mini==infinite)
        {
            mini=0;
        }
        reductionCost2=reductionCost2+mini;
    }
    for(int i=0;i<N;i++)
    {
        mini=infinite;
        for(int j=0;j<N;j++)
        {
            if(comp2[j][i]<mini)
            {
                mini=comp2[j][i];
            }
        }
        if(mini!=infinite)
        {
            for (int j = 0; j < N; j++)
            {
                if (comp2[j][i] != infinite)
                {
                    comp2[j][i] = comp2[j][i] - mini;
                }
            }
        }
        if (mini==infinite)
        {
            mini=0;
        }
        reductionCost2=reductionCost2+mini;
    }
    parentCost2=parentCost+reductionCost2;
    return parentCost2;
}
void initialize(int comp[N][N])
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            comp[i][j]=0;
        }
    }
}
void copy1(int cno,int ncno)
{
    for(int i=0;i<N;i++)
    {
        comp1[cno][i]=infinite;
        comp1[i][ncno]=infinite;
    }
    comp1[ncno][0]=infinite;
    //comp1[ncno][cno]=infinite;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(comp1[i][j]==0)
            {
                comp1[i][j]=city[i][j];
            }
        }
    }
    comp1Cost=ReductionMatrix1();
    comp1Cost=comp1Cost+city[cno][ncno];
}
void copy2(int cno,int ncno)
{
    for (int i=0;i<N;i++)
    {
        comp2[cno][i]=infinite;
        comp2[i][ncno]=infinite;
    }
    comp2[ncno][0]=infinite;
    //comp2[ncno][cno]=infinite;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if (comp2[i][j]==0)
            {
                comp2[i][j]=city[i][j];
            }
        }
    }
    comp2Cost=ReductionMatrix2();
    comp2Cost=parentCost2+city[cno][ncno];
}
void copy(int matrix[N][N])
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            city[i][j]=matrix[i][j];
        }
    }
}
void findPath(int cno)
{
    comp1Cost=infinite;
    comp2Cost=infinite;
    chk++;
    path=path+to_string(cno+1);
    visited[cno]=1;
    int i1,i2;
    for(int i=1;i<N;i++)
    {
        if(visited[i]==0)
        {
            if(comp1Cost>comp2Cost)
            {
                copy1(cno,i);
                i1=i;
            }
            else
            {
                copy2(cno,i);
                i2=i;
            }
            if(comp1Cost<comp2Cost)
            {
                initialize(comp2);
            }
            else
            {
                initialize(comp1);
            }
        }
    }
    if(comp1Cost>=0&&comp2Cost>=0)
    {
        parentCost = min(comp1Cost, comp2Cost);
    }
    else{
        parentCost = max(comp1Cost, comp2Cost);
    }
    if(comp1Cost<comp2Cost)
    {
        copy(comp1);
        initialize(comp1);
        initialize(comp2);
    }
    else
    {
        copy(comp2);
        initialize(comp1);
        initialize(comp2);
    }
    
    if(chk!=N)
    {
        display(city);
        cout << "Total Cost = " << totalCost << endl;
        totalCost = totalCost + parentCost;
        path=path+"-->";
        if (comp1Cost<comp2Cost)
        {
            cout<<endl<<"The next selected city : "<<i1+1<<endl;
            findPath(i1);
        }
        else
        {
            cout << endl << "The next selected city : " << i2 + 1 << endl;
            findPath(i2);
        }
    }
}


/*------------------------------------------------M A I N  F U N C T I O N----------------------------------------------------------
--------------------------------------------------M A I N  F U N C T I O N----------------------------------------------------------
--------------------------------------------------M A I N  F U N C T I O N--------------------------------------------------------*/


int main()
{
    SetConsoleTitle("Entroute | JIIT");                       //setting up console
    system("color 0A");

    int i,ch,id,k=0;                                        // making passsword protected
    char c;
    char pas[10];
    string passw="12345",p="";
	gotoxy(42,8);
	cout<<"\t\tLOGIN";
	gotoxy(42,10);
	cout<<"____________";
	gotoxy(42,11);
	cout<<"|\tEnter password :             |";
	gotoxy(42,12);
	cout<<"|____________|";
	cout<<"\n\t\t\t\t\t";
	gotoxy(65,11);
	while( k<5)
	{
	    pas[k]=getch();
	    char s=k;
	    if(s>5)
		 break;
	    else cout<<"*";
	    k++;
	}
	pas[k]='\0';
	p=pas;
	if(p.compare(passw)==0)                                 //verifying password
	{
	    getch();
		system("cls");
		gotoxy(10,3);
		cout<<"<<<< Loading Please Wait >>>>";
		for(i=0; i<5; i++)
        {
            cout<<"\t*";
            Sleep(500);
        }
        //printing the welcome message
        cout<<" \n\n\n\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *";
		cout<<"\n\n\t\t\t\t\t     *                    *";
		cout<<"\n\n\t\t\t\t\t     *       Welcome      *";
		cout<<"\n\n\t\t\t\t\t     *                    *";
		cout<<"\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *";
		cout<<"\n\n\n\n\n\t\t\t\t\tPress any key to continue...... ";
		getch();

    title();

    //printing the team name

    cout<<"\n\n\t\t\t\tLab Evaluation Even Semester 2023";
    cout<<"\n\n\t\t\t   Team :  \n\n\t\t\t\t   ";
    cout<<"\n\n\t\t\t Jaypee Institute of Information Technology\n\t\t\t";
    printChar('=',38);
    cout<<"\n\n\n\t\t\t       Press any key to Enter";
    getch();
    while(1)
    {
        title();
        cout<<"\n\t";
        printChar('*',64);

 /*-----------------------------------------------M E N U----------------------------------------------------------
--------------------------------------------------M E N U----------------------------------------------------------
--------------------------------------------------M E N U--------------------------------------------------------*/

    //menu for user to access the different functions
        cout<<"\n\n\t\t\t\t1. ";
        cout<<"\n\n\t\t\t\t\tWhen start and destination are same";
        cout<<"\n\n\t\t\t\t2. Route ";
        cout<<"\n\n\t\t\t\t\tTo go from A to B in fastest time";
        cout<<"\n\n\t\t\t\t3. for fuel efficient path:";
        cout<<"\n\n\t\t\t\t4.      ";
        cout<<"\n\n\t\t\t\t5.     \n\n\t";
        printChar('*',64);
        int choice;
        cout<<"\n\n\t\t\t\tEnter Your Choice :\t";
        cin>>choice;

    //connecting the program using switch

        switch(choice)
        {
            case 1:
                {

                    break;                              //loop control statement
                }

            case 2:
                {
                    vector<vector<Edge>> adjList(n);
                    adjList[0].push_back({1, 3, 3, 2});
                    adjList[0].push_back({2, 8, 6, 4});
                    adjList[0].push_back({4, 4, 2, 1});
                    adjList[0].push_back({6, 5, 4, 2});
                    adjList[1].push_back({5, 1, 1, 1});
                    adjList[2].push_back({3, 5, 3, 3});
                    adjList[2].push_back({7, 6, 5, 3});
                    adjList[3].push_back({8, 1, 1, 1});
                    adjList[3].push_back({9, 2, 2, 2});
                    adjList[4].push_back({5, 1, 1, 1});
                    adjList[4].push_back({6, 4, 3, 2});
                    adjList[4].push_back({7, 2, 1, 1});
                    adjList[5].push_back({8, 2, 2, 2});
                    adjList[6].push_back({9, 1, 1, 1});
                    adjList[7].push_back({8, 3, 3, 2});
                    adjList[8].push_back({10, 2, 1, 1});
                    adjList[9].push_back({11, 5, 4, 3});
                    adjList[10].push_back({12, 4, 2, 1});
                    adjList[11].push_back({12, 2, 1, 1});
                    adjList[12].push_back({13, 3, 3, 2});
                    adjList[12].push_back({15, 8, 6, 4});
                    adjList[12].push_back({17, 4, 2, 1});
                    adjList[12].push_back({19, 5, 4, 2});
                    adjList[13].push_back({16, 1, 1, 1});
                    adjList[14].push_back({15, 5, 3, 3});
                    adjList[14].push_back({18, 6, 5, 3});
                    adjList[15].push_back({16, 1, 1, 1});
                    adjList[15].push_back({17, 2, 2, 2});
                    adjList[16].push_back({19, 1, 1, 1});
                    adjList[17].push_back({18, 2, 1, 1});
                    adjList[18].push_back({19, 3, 3, 2});
                    cout<<"Enter start: "<<endl<<endl<<endl;
                    cin>>s;
                    cout<<"Enter end: "<<endl<<endl<<endl;
                    cin>>t;

                    dijkstra(s, adjList, dist, parent);

                    if (dist[t] == INF) {
                        cout << "No path found";
                    } else {
                        cout << "Shortest path from " << cityNames[s] << " to " << cityNames[t] << ":\n";
                        printPath(t, parent, cityNames);
                        cout << "\nTotal time required: " << dist[t] << "\nRemaining fuel: " << fuel;
                    }
                    Sleep(5000);
                    break;
                }

            case 3:
                {
                    int noOfCouriers[4];
    int choice;
 
        cout<<endl<<"The input distance matrix:"<<endl;
        display(city);
        cout<<endl<<"The initially reduced distance matrix:"<<endl;
        cout<<endl<<"The starting city will be : "<<1<<endl;
        initialize(comp1);
        initialize(comp2);
         findInitCost();
        cout<<endl<<"The path to be followed"<<endl;
        findPath(0);
        cout<<endl<<"The total cost for this path =  "<<totalCost<<endl;
        cout << endl << "The The fuel efficient path will be:  =  " << path << endl;
     
                     Sleep(10000);
                    break;
                }

            case 4:
                {
                    
                    break;
                }


            case 5:
                return 1;
                break;
            default:
                cout<<"\n\t\tNo Action Detected";
                cout<<"\n\t\tPress Any Key\n\n\n";
                getch();
                system("pause");
        }
    }

	}
    else
    {
        printf("\n\n\n\n\t\t\t\t\t  Wrong Password .Please try again.\n");      //in case password is wrong
        getch();
    }
    cout<<"\n\t";
        printChar('*',64);  //printing design
    return 0;
}
