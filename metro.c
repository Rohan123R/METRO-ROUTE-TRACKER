#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#define MAX_STATIONS 32

typedef struct MetroStation {
    char name[50];  
    int stationId;
} MetroStation;

typedef struct MetroGraph {
    MetroStation stations[MAX_STATIONS];
    int adjacencyMatrixCost[MAX_STATIONS][MAX_STATIONS];
    int adjacencyMatrixDistance[MAX_STATIONS][MAX_STATIONS];
    int numStations;
} MetroGraph;

void initializeMetroGraph(MetroGraph *graph);
void displayMetroGraph(MetroGraph *graph);
void addMetroConnections(MetroGraph *graph, char *from, char *to, int cost, int distance);
int minDistance(int dist[], bool sptSet[]) ;
void printPath(int parent[], int j) ;
void printSolutionCost(int dist[], int parent[], int src, int dest); 
void printSolutionDist(int dist[], int parent[], int src, int dest); 
void dijkstraCost(MetroGraph *graph, int src, int dest) ;
void dijkstraDistance(MetroGraph *graph, int src, int dest); 
void addNodes(MetroGraph *graph) ;
void establishConnections(MetroGraph *graph);
void displayStations(MetroGraph *graph);

int main()
{   
    MetroGraph graph;
    initializeMetroGraph(&graph);
    addNodes(&graph);
    establishConnections(&graph);
    printf("*********************METRO APP*****************************************\n");
    printf("These are the stations available along with thier ids\n");
    displayStations(&graph);
    int choice;
    int from , to;
    printf("Enter your source and destination ids");
    scanf("%d %d",&from,&to);
    printf("Enter : \n 1 - For route with least cost \n 2 for route with least distance\n");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        dijkstraCost(&graph,from,to);
        break;
    case 2:
        dijkstraDistance(&graph,from,to);
        break;
    default:
        break;
    }
    // displayMetroGraph(&graph);
    // establishConnections(&graph);
    // displayMetroGraph(&graph);


    // 
    // // 

    return 0;
}

void initializeMetroGraph(MetroGraph *graph){
    graph->numStations = 0;
    for (int i = 0; i < MAX_STATIONS; i++) {
        for (int j = 0; j < MAX_STATIONS; j++) {
            graph->adjacencyMatrixCost[i][j] = 0;
            graph->adjacencyMatrixDistance[i][j] = 0; 
 
        }
    }
}

void displayMetroGraph(MetroGraph *graph)
{
    printf("Metro Stations:\n");
    for (int i = 0; i < MAX_STATIONS; i++) {
        for (int j = 0; j < MAX_STATIONS; j++) {
            printf("%d\t",graph->adjacencyMatrixDistance[i][j]); 
        }
        printf("\n");
    }
}

void addMetroConnections(MetroGraph *graph,char *from,char *to,int cost,int distance)
{   
    
    int fromId = -1;
    int toId = -1;
    for(int i = 0 ; i<  MAX_STATIONS; i++)
    {
        if(strcmp(graph->stations[i].name,from)==0)
        {
            fromId = i;
            printf("%d",fromId);
        }
        
    }
    for(int i = 0 ; i< MAX_STATIONS; i++)
    {
        if(strcmp(graph->stations[i].name,to)==0)
        {
            toId = i;
            printf("%d",toId);
        }
        
    }
    
    graph->adjacencyMatrixCost[fromId][toId] = cost;
    graph->adjacencyMatrixCost[toId][fromId] = cost;
    graph->adjacencyMatrixDistance[fromId][toId] = distance;
    graph->adjacencyMatrixDistance[toId][fromId] = distance;

    // printf("Connection created between %s and %s with cost %d and distance %d.\n", from, to, cost, distance);

}   

int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < MAX_STATIONS; v++) {
        if (!sptSet[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);
    printf("Station %d -> ", j);
}

void printSolutionCost(int dist[], int parent[], int src, int dest) {
    printf("Shortest Path from Station %d to Station %d:\n", src, dest);
    printf("Station %d -> ", src);
    printPath(parent, dest);
    printf("Total Cost: %d\n", dist[dest]);
}

void printSolutionDist(int dist[], int parent[], int src, int dest) {
    printf("Shortest Path from Station %d to Station %d:\n", src, dest);
    printf("Station %d -> ", src);
    printPath(parent, dest);
    printf("Total Distance: %d\n", dist[dest]);
}


void dijkstraCost(MetroGraph *graph, int src, int dest) {
    int dist[MAX_STATIONS];
    bool sptSet[MAX_STATIONS];
    int parent[MAX_STATIONS];

    for (int i = 0; i < MAX_STATIONS; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;
    parent[src] = -1;

    for (int count = 0; count < MAX_STATIONS - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < MAX_STATIONS; v++) {
            if (!sptSet[v] && graph->adjacencyMatrixCost[u][v] && dist[u] + graph->adjacencyMatrixCost[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph->adjacencyMatrixCost[u][v];
            }
        }
    }

    printSolutionCost(dist, parent, src, dest);
}

void dijkstraDistance(MetroGraph *graph, int src, int dest) {
    int dist[MAX_STATIONS];
    bool sptSet[MAX_STATIONS];
    int parent[MAX_STATIONS];

    for (int i = 0; i < MAX_STATIONS; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < MAX_STATIONS - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < MAX_STATIONS; v++) {
            if (!sptSet[v] && graph->adjacencyMatrixDistance[u][v] && dist[u] + graph->adjacencyMatrixDistance[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph->adjacencyMatrixDistance[u][v];
            }
        }


    }

    printSolutionDist(dist, parent, src, dest);
}


    

void addNodes(MetroGraph *graph) {
    strcpy(graph->stations[0].name, "Lorem");
    strcpy(graph->stations[1].name, "Mauris");
    strcpy(graph->stations[2].name, "Porta");
    strcpy(graph->stations[3].name, "Potenti");
    strcpy(graph->stations[4].name, "Bdenum");
    strcpy(graph->stations[5].name, "Morbi");
    strcpy(graph->stations[6].name, "Mawris");
    strcpy(graph->stations[7].name, "Ipsum");

    strcpy(graph->stations[8].name, "Adispicing");
    strcpy(graph->stations[9].name, "Tempor");
    strcpy(graph->stations[10].name, "Orci");
    strcpy(graph->stations[11].name, "Ante");
    strcpy(graph->stations[12].name, "Potentin");
    strcpy(graph->stations[13].name, "Tincidunt");
    strcpy(graph->stations[14].name, "Consectetur");


    strcpy(graph->stations[15].name, "Curabitur");
    strcpy(graph->stations[16].name, "Interdum");
    strcpy(graph->stations[17].name, "Ligula");
    strcpy(graph->stations[18].name, "Nisi");
    strcpy(graph->stations[19].name, "Sit");
    strcpy(graph->stations[20].name, "Lobortis");
    strcpy(graph->stations[21].name, "Feuglat");
    strcpy(graph->stations[22].name, "Dolor");


    strcpy(graph->stations[23].name, "Amet");
    strcpy(graph->stations[24].name, "Vestibulum");
    strcpy(graph->stations[25].name, "Suspendisse");
    strcpy(graph->stations[26].name, "Molestie");
    strcpy(graph->stations[27].name, "Lectus");
    strcpy(graph->stations[28].name, "Dictum");
    strcpy(graph->stations[29].name, "Metus");
    strcpy(graph->stations[30].name, "Sollicitudin");
    strcpy(graph->stations[31].name, "Elit");

    for(int i = 0 ; i< MAX_STATIONS; i++)
    {
        graph->stations[i].stationId = i; 

    }

}
void establishConnections(MetroGraph *graph)
{
    addMetroConnections(graph, "Lorem", "Mauris", 10, 20);
    addMetroConnections(graph, "Mauris", "Porta", 10, 20);
    addMetroConnections(graph, "Porta", "Potenti", 10, 20);
    addMetroConnections(graph, "Potenti", "Bdenum", 10, 20);
    addMetroConnections(graph, "Bdenum", "Morbi", 10, 20);
    addMetroConnections(graph, "Morbi", "Mawris", 10, 20);
    addMetroConnections(graph, "Mawris", "Ipsum", 10, 20);

    addMetroConnections(graph, "Adispicing", "Tempor", 15, 20);
    addMetroConnections(graph, "Tempor", "Orci", 15, 20);
    addMetroConnections(graph, "Orci", "Ante", 15, 20);
    addMetroConnections(graph, "Ante", "Potenti", 15, 20);
    addMetroConnections(graph, "Potenti", "Tincidunt", 15, 20);
    addMetroConnections(graph, "Tincidunt", "Consectetur", 15, 20);
    addMetroConnections(graph, "Curabitur", "Interdum", 15, 20);
    addMetroConnections(graph, "Interdum", "Ligula", 15, 20);
    addMetroConnections(graph, "Ligula", "Nisi", 15, 20);  
    addMetroConnections(graph, "Nisi", "Sit", 15, 20);
    addMetroConnections(graph, "Sit", "Lobortis", 15, 3540);
    addMetroConnections(graph, "Lobortis", "Feuglat", 15, 230);
    addMetroConnections(graph, "Feuglat", "Dolor", 15, 30);

    addMetroConnections(graph, "Amet", "Vestibulum", 20, 40);
    addMetroConnections(graph, "Vestibulum", "Suspendisse", 20, 70);
    addMetroConnections(graph, "Suspendisse", "Molestie", 20, 200);
    addMetroConnections(graph, "Molestie", "Lectus", 20, 20);
    addMetroConnections(graph, "Lectus", "Dictum", 20, 20);
    addMetroConnections(graph, "Dictum", "Metus", 20, 20);
    addMetroConnections(graph, "Metus", "Sollicitudin", 20, 20);
    addMetroConnections(graph, "Sollicitudin", "Elit", 20, 20);

    addMetroConnections(graph, "Mauris", "Lectus", 30, 20);
    addMetroConnections(graph, "Mauris", "Molestie", 30, 20);
    addMetroConnections(graph, "Mauris", "Lectus", 30, 20);
    addMetroConnections(graph, "Lobortis", "Potenti", 30, 20);
    addMetroConnections(graph, "Lobortis", "Porta", 30, 20);
    addMetroConnections(graph, "Potenti", "Bibendum", 30, 20);
    addMetroConnections(graph, "Interdum", "Molestie", 30, 20);
    addMetroConnections(graph, "Interdum", "Suspendisse", 30, 20);
    addMetroConnections(graph, "Interdum", "Orci", 30, 20);
    addMetroConnections(graph, "Interdum", "Suspendisse", 30, 20);




}
void displayStations(MetroGraph *graph)
{
    for(int i = 0 ; i < MAX_STATIONS ; i++)
    {
        printf("Station name : %s -> Id : %d \n",graph->stations[i].name,graph->stations[i].stationId);
    }
}
