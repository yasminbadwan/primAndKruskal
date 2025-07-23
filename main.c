#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Max_Num_city 100
#define Max_name_city 50
#define infinty 999

struct vertice{
       char  city1[Max_name_city];
       char  city2[Max_name_city];
        int wight;
};

struct nodeHeap{

    int wight;
    int node;
    int node2;
};
struct Heap{
    int sizeOfHeap;
    int indexOfHeap[Max_Num_city];
    struct nodeHeap *arr[Max_Num_city];


};
int graph[Max_Num_city][Max_Num_city]={0};
char cityName[Max_Num_city][Max_name_city];

int main()
{
    printf("Hello .\n");
    int x;
    do
    {
        printmenu();
        printf("\n\nplease enter the number from 1 to 5 of your choise:");
        scanf("%d",&x);

        switch (x)
        {
        case 1:
          Loadcities();
            break;
            case 2:
         ApplyPrimAlgorithm();
            break;
            case 3:
          Loadcities();
            break;
            case 4:
          Loadcities();
            break;

        case 5:
            printf("\nyou end the program. good bye :)\n")     ;
            break;
        default:
            printf("\nInvalid!please enter number between 1 to 5\n");

        }

    }
    while(x!=5);

    return 0;
}
void printmenu()
{
     printf("\n================ MENU ================\n");
    printf(
        "\n1. Load cities."
        "\n2. Apply Primís Algorithm."
        "\n3. Apply Kruskalís Algorithm."
        "\n4. Compare the two algorithms."
        "\n5. Exit. ");
}
void addedge(int graph[Max_Num_city][Max_Num_city],int i,int j,int w ){
       graph[i][j]=w;
       graph[j][i]=w;

}

void displayMatrix(int graph[Max_Num_city][Max_Num_city], int cityCount) {
    for (int i = 0; i < cityCount; i++) {
        for (int j = 0; j < cityCount; j++) {
            if (graph[i][j] != 0)
                printf("From %-15s to %-15s: %3d km\n", cityName[i], cityName[j], graph[i][j]);
        }
    }
}
int citynumber(char city[Max_name_city], int *cityCount) {
    for (int i = 0; i < *cityCount; i++) {
        if (strcmp(city, cityName[i]) == 0)
            return i;
    }
    strcpy(cityName[*cityCount], city);
    (*cityCount)++;
    return (*cityCount) - 1;
}

void  Loadcities(){
     FILE *pF = fopen("cities.txt", "r");

    if (pF == NULL)
    {
        printf("Error: Failed to open the file.\n");
        return;
    }


    char temp[500];
    // read the data from a file
    int cityCount=0;
    int edgeCount=0;
    while (fgets(temp, sizeof(temp), pF) != NULL)
    {
        int c=0;
        char  name1[Max_name_city] = "", name2[Max_name_city] = "";
        int wight;
        //this is for Separating the data that read
        char*token=strtok(temp,"#");
        while (token != NULL)
        {
            c++;
            if (c == 1)
            {
                strcpy(name1, token);

            }
            else if (c == 2)
            {
                strcpy(name2, token);
            }
            else if (c == 3)
            {
                wight=atoi(token);
            }

            token = strtok(NULL, "#");
}
if (strlen(name1) == 0 || strlen(name2) == 0 || wight <= 0) {
    continue;
}
int from=citynumber(name1,&cityCount);
int to=citynumber(name2,&cityCount);
 addedge( graph,from,to,wight );

        edgeCount++;
        }


  //  if (cityCount < 50 || edgeCount < 200) {
  //  printf("Error: The graph must have at least 50 cities and 200 connections!\n");
   // exit(1);
    //   }
   // else{

       printf("\nThe task was loaded successfully :)\n");
       printf("\n***Graph order (number of cities): %d\n", cityCount);
       printf("\n***Graph size (number of edges): %d\n\n", edgeCount);



    displayMatrix(graph,cityCount);
  // }


    fclose(pF);

}

struct nodeHeap * makeHeapNode(int wight, int node) {
   struct nodeHeap * nod = (struct nodeHeap*)malloc(sizeof(struct nodeHeap));
    nod->wight = wight;
    nod->node = node;
    return nod;
}
struct Heap* createMinHeap() {
  struct  Heap* heap = (struct Heap*)malloc(sizeof(struct Heap));
    heap->sizeOfHeap = 0;
    for (int i = 0; i < Max_Num_city; i++)
        heap->arr[i] = NULL;
    return heap;
}
void swap(struct nodeHeap *a, struct nodeHeap *b)
{
    struct nodeHeap tmp = *a;
    *a = *b;
    *b = tmp;
}
void heapMin(struct Heap* heap, int i)
{
    int min = i;
    int l = 2 * i;
    int r = 2 * i + 1;

    // If left child is smaller than root
    if (l < heap->sizeOfHeap && heap->arr[l]->wight < heap->arr[min]->wight)
        min = l;

    // If right child is smaller than largest so far
    if (r < heap->sizeOfHeap && heap->arr[r]->wight < heap->arr[min]->wight)
       min = r;

    if (min != i) {
        swap(heap->arr[i],heap->arr[min]);
        heapMin(heap, min);
    }
}
void buildHeap(struct Heap* heap)
{

    int startIdx = (heap->sizeOfHeap / 2) - 1;
    for (int i = startIdx; i >= 0; i--) {
        heapMin(heap, i);
    }
}
int isEmpty(struct Heap* heap) {
    return heap->sizeOfHeap == 0;
}
void printHeap(int arr[], int size)
{
    printf("Array representation of Heap is:\n");

    for (int i = 0; i < size && arr[i]!=NULL; ++i)
        printf("%-2d  km\t\n",arr[i]);
}
int getCityIndex(char name[]) {
    for (int i = 0; i <= Max_Num_city; i++) {
        if (strcmp(name, cityName[i]) == 0)
            return i;
    }
    return -1;
}
void deleteMin(struct Heap* heap) {
    if (heap->sizeOfHeap == 0)
        return;
    heap->arr[0] = heap->arr[heap->sizeOfHeap - 1];
    heap->indexOfHeap[(heap->arr[heap->sizeOfHeap - 1])->node] = 0;
    heap->sizeOfHeap--;
    heapMin(heap, 0);
}
void printprim(int parent[], int key[], int cityCount)
{
    printf("\n*** Minimum Spanning Tree (MST) using Primís Algorithm ***\n\n");
  int totalWeight = 0;
    for (int i = 0; i < cityCount; i++) {

         if (parent[i] == -1 || i == parent[i])
             continue;
        printf("from %-20s to %-20s %3d km\n", cityName[parent[i]], cityName[i], key[i]);
        totalWeight += key[i];
    }

    printf("\n>> Total cost of MST: %d km\n", totalWeight);
}



void ApplyPrimAlgorithm(){
char nameOfCity[50];
printf("enter the name of source city:");
scanf("%s",nameOfCity);
MST_prim(graph,nameOfCity);

}


//  ÂÌ∆… ﬂ· —√” ·ÌﬂÊ‰ ›Ì „Ã„Ê⁄… Œ«’…
void makeSet(int parent[], int rank[], int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// ≈ÌÃ«œ «·Ã–— («·„„À·) ·„Ã„Ê⁄… «·—√”
int findParent(int parent[], int u) {
    if (parent[u] != u)
        parent[u] = findParent(parent, parent[u]);
    return parent[u];
}

//  ÊÕÌœ „Ã„Ê⁄ Ì‰ ≈–« ﬂ«‰ « „Œ ·› Ì‰
void unionSet(int u, int v, int parent[], int rank[]) {
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (u == v) return;

    if (rank[u] < rank[v]) {
        parent[u] = v;
    } else if (rank[u] > rank[v]) {
        parent[v] = u;
    } else {
        parent[v] = u;
        rank[u]++;
    }
}

// ----------- KRUSKAL ALGORITHM ------------

int kruskalUsingHeap(int n, int edgeCount, int edges[][3]) {
    struct Heap* heap = createMinHeap();

    // Ê÷⁄ «·ÕÊ«› ›Ì «·ÂÌ» (Õ”» «·Ê“‰)
    for (int i = 0; i < edgeCount; i++) {
             for (int j = 0; j < edgeCount; j++)
        heap->arr[heap->sizeOfHeap++] = makeHeapNode(edges[i][j], i);
    }
    buildHeap(heap);

    int parent[MAX_VERTICES], rank[MAX_VERTICES];
    makeSet(parent, rank, n);

    int minCost = 0, edgesUsed = 0;

    while (!isEmpty(heap) && edgesUsed < n - 1) {
        struct nodeHeap* minEdge = heap->arr[0];
        int edgeIndex = minEdge->node;

        int u = edges[edgeIndex][0];
        int v = edges[edgeIndex][1];
        int w = edges[edgeIndex][2];

        // ≈–« ·„ Ì‘ﬂ· œÊ—…
        if (findParent(parent, u) != findParent(parent, v)) {
            unionSet(u, v, parent, rank);
            minCost += w;
            edgesUsed++;
            printf("Edge included: %d -- %d (weight = %d)\n", u, v, w);
        }

        deleteMin(heap);
    }

    return minCost;
}
