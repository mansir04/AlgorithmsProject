
// GITHUB LINK : https://github.com/mansir04/AlgorithmsProject

// The project was made by a group of 2nd year students as part of college coursework for Even Semester 2023

// This project is entirely made in C++ to demonstrate the real life applications of algorithms learnt throughout the semester. 


/*---------------------------A L G O R I T H M S___A N D___P R O B L E M___S O L V I N G___P R O J E C T-------------------------------*/

/*---------------------------A L G O R I T H M S___A N D___P R O B L E M___S O L V I N G___P R O J E C T-------------------------------*/

/*---------------------------A L G O R I T H M S___A N D___P R O B L E M___S O L V I N G___P R O J E C T-------------------------------*/


//LIBRARIES

#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <limits>
#include <map>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <string>
#include <vector>
#define N 10

using namespace std;

const int INF = numeric_limits<int>::max();   // maximum value of an int

int Fuel=50;     // global variable to store the remaining fuel
int Time=0;     // global variable to store the remaining time


struct Edge {
    int v, w, fuel, time; // v = destination vertex, w = edge weight, fuel = fuel required, time = time required
};

int n = 20, m = 38, s,t;   //n is nodes, m is edges, s is start, t is destination

int infinite=INT_MAX;
int mini=infinite;
int chk=0;
int visited[N]={0};
int initReductionCost=0;    //r cap
int reductionCost1=0;       //r1 cap
int reductionCost2=0;       //r2 cap
int parentCost=0;           //previous parent cost
int parentCost1=0;          //comp1 costing
int parentCost2=0;          //comp2 costing
int totalCost=0;            //final cost
string path;                //path
int comp1Cost,comp2Cost;

int city[N][N] ={
        {infinite, 5, 4, 7, 10, 9, 20, 17, 11, 12},
        {5, infinite, 1, 5, 72, 33, 12, 10, 5, 28},
        {4, 1, infinite, 8, 1, 22, 15, 6, 4, 8},
        {7, 5, 8, infinite, 3, 7, 16, 8, 9, 11},
        {10,72, 1, 3, infinite, 10, 22, 14, 20, 15},
        {9, 33, 22, 7, 10, infinite, 5, 7, 8, 9},
        {20, 12, 15, 16, 22, 5, infinite, 1, 12, 13},
        {17, 10, 6, 8, 14, 7, 1, infinite, 4, 5},
        {11, 5, 4, 9, 20, 8, 12, 4, infinite, 1},
        {12, 28, 8, 11, 15, 9, 13, 5, 1, infinite}
    };
int comp1[N][N],comp2[N][N];


/*------------------------------------------------D I J K S T R A----------------------------------------------------------
--------------------------------------------------D I J K S T R A----------------------------------------------------------
--------------------------------------------------D I J K S T R A----------------------------------------------------------*/

/*------------------------------------------------M A P----------------------------------------------------------*/

// map to link city codes and names

map<int, string> cityNames {
    {1, "Kedarnath"},
    {2, "Badrinath"},
    {3, "Mathura"},
    {4, "Vrindavan"},
    {5, "Dwarka"},
    {6, "Shirdi"},
    {7, "Rameshvaram"},
    {8, "Banaras"},
    {9, "Kolkata"},
    {10, "Panchkula"}

};

//dist stores the updated weights while choosing path, parent keeps track of nodes we are traversing

vector<int> dist, parent;

/*------------------------------------------------D I J K S T R A__ F U N C T I O N----------------------------------------------------------*/

//dijkstra implemented using priority queue method
//adjacecny list declared in main()

void dijkstra(int s, vector<vector<Edge>>& adjList, vector<int>& dist, vector<int>& parent) {

    int n = adjList.size();
    dist.assign(n, INF);        //all distances assigned infinity initially
    parent.assign(n, -1);       //all parents initalised with -1

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    //inserted with 0,start initially
    //priority queue stores distance, node. Weight is distance only.
    pq.emplace(0, s);
    dist[s] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;        //node
        int d = pq.top().first;        //distance
        pq.pop();

        if (d > dist[u]) continue;      //if distance is greater just continue as we dont need this

        for (auto& e : adjList[u]) {
            int v = e.v, w = e.w, f = e.fuel, t = e.time;
            //accessed structure elements

            if(f>Fuel)
                {cout<<" Fuel Too Low ! Need more fuel ! "<<endl;
                break;
            }

            if (f <= Fuel && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;        //update the distances
                parent[v] = u;                //update the parent
                Fuel -= f;                   // update remaining fuel based on fuel required
                Time+=t;                     //compute the time taken
                pq.emplace(dist[v], v);      //insert in priority queue
            }
        }
    }
}

/*------------------------------------------------P R I N T__D I J K S T R A__ P A T H----------------------------------------------------------*/

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

/*------------------------------------------------R E D U C T I O N__M A T R I X__M E T H O D----------------------------------------------------------*/


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
    int pathint=0;
    comp1Cost=infinite;
    comp2Cost=infinite;
    chk++;
    path=path+to_string(cno+1);
    pathint=pathint+cno+1;
    if(chk==N)
    {
        path=path+" "+cityNames[pathint]+" ";
    }
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
                i2=i;               //store the visited city with minimum fuel
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
        // cout << "Total Cost = " << totalCost << endl;
        totalCost = totalCost + parentCost;

        path=path+" "+cityNames[pathint]+"-->";

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

/*------------------------------------------------P R I N T__G R A P H__D E T A I L S----------------------------------------------------------*/

void printGraph(const vector<vector<Edge>>& adjList) {

    //Table Headings

    cout << "+--------------+--------------+----------+----------+----------+" << endl;
    cout << "|    Start     | Destination  |  Weight  |   Fuel   |   Time   |" << endl;
    cout << "+--------------+--------------+----------+----------+----------+" <<endl;
    cout << "+--------------+--------------+----------+----------+----------+" <<endl;

    //Traverse Adjacency List and print Details

    for (int i = 0; i < adjList.size(); i++) {
        for (int j = 0; j < adjList[i].size(); j++) {
            int c = adjList[i][j].v;
            cout << "|" << setw(14) << left << cityNames[i] << "|"
                 << setw(14) << left << cityNames[c] << "|"
                 << setw(10) << right << adjList[i][j].w << "|"
                 << setw(10) << right << adjList[i][j].fuel << "|"
                 << setw(10) << right << adjList[i][j].time << "|" << endl;
            cout << "+--------------+--------------+----------+----------+----------+" << endl;
        }
    }
}

/*------------------------------------------------P R I N T__C O D E S__A N D__N A M E S----------------------------------------------------------*/


void city_code( vector<vector<Edge>> adjList , map<int, string> cityNames){
      const int codeWidth = 10;
    const int nameWidth = 20;

    // Print the top border
    cout << setw(codeWidth+3) << setfill('-') << "+" << setw(nameWidth+3) << "+" << endl;

    // Print the table header
    cout << setfill(' ')
         << "| " << setw(codeWidth) << left << "City Code"
         << " | " << setw(nameWidth) << left << "City Name"
         << " |" << endl;

    // Print the middle border
    cout << setw(codeWidth+3) << setfill('-') << "+" << setw(nameWidth+3) << "+" << endl;

    // Print each row of the table
    for (auto const& pair : cityNames) {
        cout << setfill(' ')
   << "| " << setw(codeWidth) << left << pair.first
             << " | " << setw(nameWidth) << left << pair.second
             << " |" << endl;
    }

    // Print the bottom border
    cout << setw(codeWidth+3) << setfill('-') << "+" << setw(nameWidth+3) << "+" << endl;

}


/*------------------------------------------------M A I N  F U N C T I O N----------------------------------------------------------
--------------------------------------------------M A I N  F U N C T I O N----------------------------------------------------------
--------------------------------------------------M A I N  F U N C T I O N--------------------------------------------------------*/


int main()
{
  /*------------------------------------------------I N I T I A L__D I S P L A Y----------------------------------------------------------*/

  SetConsoleTitle("Entroute | JIIT");                       //setting up console
  system("color 0A");

  int i,ch,id,k=0;                                        // making passsword protected
  char c;
  char pas[10];
  string passw="12345",p="";                              //password
	gotoxy(42,8);
	cout<<"\t\tLOGIN";
	gotoxy(42,10);
	cout<<"________________________________";
	gotoxy(42,11);
	cout<<"|\tEnter password :          |";              //need to enter password
	gotoxy(42,12);
	cout<<"|_______________________________|";
	cout<<"\n\t\t\t\t\t";
	gotoxy(65,11);


	while( k<5)
	{
	    pas[k]=getch();    //Get the character
	    char s=k;
	    if(s>5)
		 break;
	    else cout<<"*";    //to hide the passwd
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
    cout<<"\n\n\t\t\t   Team : ";
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

        cout<<"\n\n\t\t\t\t1. City Names with Codes ";
        cout<<endl;

        cout<<"\n\n\t\t\t\t2. Find Shortest Route from A to B ";
        cout<<endl;

        cout<<"\n\n\t\t\t\t3. For Fuel Efficient Path ";
        cout<<endl;

        cout<<"\n\n\t\t\t\t4. City Details ";
        cout<<endl;

        cout<<"\n\n\t\t\t\t5. Logout   \n\n\t";
        cout<<endl;

        printChar('*',64);
        int choice;
        cout<<"\n\n\t\t\t\tEnter Your Choice :\t";
        cin>>choice;


        vector<vector<Edge>> adjList(n);

        adjList[1].push_back({2, 3, 3, 2});
        adjList[1].push_back({3, 8, 6, 4});
        adjList[1].push_back({6, 4, 2, 1});
        adjList[2].push_back({1, 5, 4, 2});
        adjList[2].push_back({3, 1, 1, 1});
        adjList[2].push_back({4, 5, 3, 3});
        adjList[2].push_back({5, 6, 5, 3});
        adjList[3].push_back({1, 1, 1, 1});
        adjList[3].push_back({2, 2, 2, 2});
        adjList[3].push_back({5, 1, 1, 1});
        adjList[4].push_back({2, 4, 3, 2});
        adjList[4].push_back({5, 2, 1, 1});
        adjList[5].push_back({2, 2, 2, 2});
        adjList[5].push_back({3, 1, 1, 1});
        adjList[5].push_back({4, 3, 3, 2});
        adjList[5].push_back({6, 2, 1, 1});
        adjList[6].push_back({5, 4, 2, 1});
        adjList[6].push_back({7, 2, 1, 1});
        adjList[7].push_back({6, 5, 4, 2});
        adjList[7].push_back({8, 3, 3, 2});
        adjList[7].push_back({9, 8, 6, 4});
        adjList[7].push_back({10, 4, 2, 1});
        adjList[8].push_back({7, 1, 1, 1});
        adjList[8].push_back({10, 5, 3, 3});
        adjList[9].push_back({7, 6, 5, 3});
        adjList[9].push_back({10, 1, 1, 1});
        adjList[10].push_back({8, 6, 5, 3});
        adjList[10].push_back({9, 1, 1, 1});


    //connecting the program using switch

        switch(choice)
        {
            case 1:
                {
               city_code(adjList ,cityNames);
               cout<<"\n\n\n\n\n\t\t\t\t\tPress any key to continue...... ";
		           getch();
                    break;                              //loop control statement
                }

            case 2:
                {


                    cout<<"Enter start: "<<endl<<endl;
                    cin>>s;
                    cout<<endl;

                    cout<<"Enter end: "<<endl<<endl;
                    cin>>t;
                    cout<<endl;

                    dijkstra(s, adjList, dist, parent);

                    if (dist[t] == INF) {
                        cout << "No path found";
                    } else {
                        cout << "Shortest path from " << cityNames[s] << " to " << cityNames[t] << ":\n";
                        printPath(t, parent, cityNames);
                        cout << "\nTotal distance travelled : " << dist[t] << "\nRemaining fuel: " << Fuel;
                        cout << "\nTotal time required : " << Time;
                    }

                    cout<<"\n\n\n\n\n\t\t\t\t\tPress any key to continue...... ";
		                getch();
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

                    cout<<"\n\n\n\n\n\t\t\t\t\tPress any key to continue...... ";
		getch();

                    break;
                }

            case 4:
                {
                     printGraph(adjList);
                    cout<<"\n\n\n\n\n\t\t\t\t\tPress any key to continue...... ";
		                getch();
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
