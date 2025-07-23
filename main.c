#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 #include <time.h>
#define Max_Num_city 1000
#define Max_name_city 50
#define infinty 9999

struct nodeHeap{

    int wight;
    // index of city in arr cityName
    int node;
    int node2;
};
struct Heap{
    int sizeOfHeap;
    int indexOfHeap[Max_Num_city];
    struct nodeHeap *arr[Max_Num_city];


};
int graph[Max_Num_city][Max_Num_city];
char cityName[Max_Num_city][Max_name_city];
int *totelOfK;
int *totelOfP;

int main()
{
       clock_t start, end;
       double timeOfK;
double timeOfP;
    printf("Hello to my project.\n");
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
            start=clock();
            ApplyPrimAlgorithm();
            end=clock();
            timeOfP = (double)(end - start) / CLOCKS_PER_SEC;
            printf("\nexecution time \t\t\t%.3fs\n ",timeOfP);
            break;
            case 3:
             start=clock();
             ApplyKruskalAlgorithm();
             end=clock();
             timeOfK = (double)(end - start) / CLOCKS_PER_SEC;
             printf("\nexecution time \t\t\t%.5fs\n ",timeOfK);
            break;
            case 4:
          Comparethetwoalgorithms(timeOfP,timeOfK);
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
        "\n2. Apply Prim s Algorithm."
        "\n3. Apply Kruskal s Algorithm."
        "\n4. Compare the two algorithms."
        "\n5. Exit. ");
}
// add edge in the matrix
void addedge(int graph[Max_Num_city][Max_Num_city],int i,int j,int w ){
       graph[i][j]=w;
       graph[j][i]=w;

}
// to find the index of city if its exist if its new make new index for it
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

// to fill the matrix
int from=citynumber(name1,&cityCount);
int to=citynumber(name2,&cityCount);
 addedge( graph,from,to,wight );

        edgeCount++;
        }


   if (cityCount < 50 || edgeCount < 200) {
   printf("Error: The graph must have at least 50 cities and 200 connections!\n");
   exit(1);
      }
    else{

       printf("\nThe city was loaded successfully :)\n");
       printf("\n***Graph order (number of cities): %d\n", cityCount);
       printf("\n***Graph size (number of edges): %d\n\n", edgeCount);
}


    fclose(pF);

}

struct nodeHeap * makeHeapNode(int wight, int node) {
   struct nodeHeap * nod = (struct nodeHeap*)malloc(sizeof(struct nodeHeap));
    nod->wight = wight;
    nod->node = node;
    return nod;
}
// create empty heap
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
// to make min heap
void heapMin(struct Heap* heap, int i)
{
    int min = i;
    int l = 2 * i+1;
    int r = 2 * i + 2;

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
// bulid the min tree
void buildHeap(struct Heap* heap)
{

    int startIdx = (heap->sizeOfHeap / 2)-1 ;
    for (int i = startIdx; i >= 0; i--) {
        heapMin(heap, i);
    }
}
int isEmpty(struct Heap* heap) {
    return heap->sizeOfHeap == 0;
}
// to get the index of the city
int getCityIndex(char name[]) {
    for (int i = 0; i <Max_Num_city; i++) {
        if (strcmp(name, cityName[i]) == 0)
            return i;
    }
    return -1;
}
// to delet the root and make them min heap
void deleteMin(struct Heap* heap) {
    if (heap->sizeOfHeap == 0)
        return;
    heap->arr[0] = heap->arr[heap->sizeOfHeap - 1];
    heap->indexOfHeap[(heap->arr[heap->sizeOfHeap - 1])->node] = 0;
    heap->sizeOfHeap--;
    heapMin(heap, 0);
  // buildHeap(heap);
}

void MST_prim(int graph[Max_Num_city][Max_Num_city],char sro_city [Max_name_city]){
   printf("\n=== Minimum Spanning Tree using Prim s Algorithm ===\n\n");
    int cityNumber=0;
    int total=0;
    // find the number of city
    for(int i=0;i<Max_Num_city;i++){
            if(strlen(cityName[i])!=0)
            cityNumber++;
    }

    int parent[cityNumber];
    int key[cityNumber];
    int Visted[cityNumber];
    struct Heap *heapList=createMinHeap();

    for(int i=0;i<cityNumber;i++)
  {
        key[i]=infinty;
        Visted[i]=0;
        parent[i] = -1;

  }
  // find the index of src city to start with it
  int indexofcity=getCityIndex(sro_city);
  if(indexofcity==-1)
  {
      printf("erorr:the city not found ");
      return 0;
  }
  key[indexofcity]=0;
  parent[indexofcity] = indexofcity;


 for (int i = 0; i <cityNumber; i++) {
    struct nodeHeap* n = makeHeapNode(key[i], i);
    heapList->arr[i] = n;
    heapList->indexOfHeap[i] = i;
}
heapList->sizeOfHeap = cityNumber;

buildHeap(heapList);

  while(!isEmpty(heapList)){
    struct nodeHeap* n = heapList->arr[0];

// delete the node that we visted
deleteMin(heapList) ;
Visted[n->node]=1;
  for (int nextIndex = 0; nextIndex < cityNumber; nextIndex++) {
    if (Visted[nextIndex] == 0 && graph[n->node][nextIndex] && graph[n->node][nextIndex] < key[nextIndex] ) {
        key[nextIndex] = graph[n->node][nextIndex];
        parent[nextIndex] = n->node;
        for (int i = 0; i < heapList->sizeOfHeap; i++) {
            if (heapList->arr[i]->node == nextIndex) {
                heapList->arr[i]->wight = key[nextIndex];
                break;
            }
        }

    }
}

buildHeap(heapList);
  }
 totelOfP=totelprim(parent,key,cityNumber);

 clearHeap(heapList);
}
int totelprim(int parent[], int key[], int cityCount)
{
  int totalWeight = 0;
    for (int i = 0; i < cityCount; i++) {

         if (parent[i] == -1 || i == parent[i])
             continue;
             printf("from %-20s to %-20s %3d km\n", cityName[parent[i]], cityName[i], key[i]);
        totalWeight += key[i];
    }

    printf("\n>> Total cost of MST: %d km\n", totalWeight);
    return totalWeight;
}



void ApplyPrimAlgorithm(){
char nameOfCity[50];
printf("enter the name of source city:");
scanf("%s",nameOfCity);
MST_prim(graph,nameOfCity);

}
void makeSet(int parent[], int rank[], int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}


int findParent(int parent[], int u) {
    if (parent[u] != u)
        parent[u] = findParent(parent, parent[u]);
    return parent[u];
}

void unionSet(int u, int v, int parent[], int rank[]) {
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (u == v)
        return;

    if (rank[u] < rank[v]) {
        parent[u] = v;
    } else if (rank[u] >= rank[v]) {
        parent[v] = u;
    }
    else {
        parent[v] = u;
        rank[u]++;
    }
}
int mst_Kruskal(int citynumber,int edgeCount,int edge[][3]){

    int parent[citynumber];
    int rank[citynumber];
    struct Heap *heapList=createMinHeap();
    for(int i=0;i<edgeCount;i++){
        heapList->arr[i]=makeHeapNode(edge[i][2],i);
       heapList->sizeOfHeap++;
    }
     buildHeap(heapList);
     makeSet(parent,rank, citynumber);
    struct nodeHeap*array[edgeCount];
     int totel=0;
        int i=0;
        int size=0;
     while(!isEmpty(heapList)){
        int u=edge[heapList->arr[0]->node][0];
        int v=edge[heapList->arr[0]->node][1];
        int w=edge[heapList->arr[0]->node][2];

        if(findParent(parent,u)!=findParent(parent,v)){
            unionSet(u, v, parent, rank);
            totel += w;
            array[i] = (struct nodeHeap*)malloc(sizeof(struct nodeHeap));
            array[i]->wight=w;
            array[i]->node=u;
            array[i]->node2=v;
            size++;
            i++;
        }
        deleteMin(heapList);
     }
for(int i=0;i<size;i++)
   {
       if(array[i]!=NULL)
         printf("from:%-20s to:%-15s %-2d km\n", cityName[array[i]->node],cityName[array[i]->node2] , array[i]->wight);
   }
   printf("\nTotal weight of MST (Kruskal): %d km\n", totel);
  for(int i=0;i<size;i++)
   {
       free(array[i]);
   }
  clearHeap(heapList);
  return totel;


}
void ApplyKruskalAlgorithm(){
    int edge[10000][3];
    int edgeCount = 0;

     int cityNumber=0;
for(int i=0;i<Max_Num_city;i++){
    if(strlen(cityName[i])!=0)
        cityNumber++;
}
    for(int i=0;i<Max_Num_city;i++){
        for(int j=i+1;j<Max_Num_city;j++){
            if(graph[i][j]!=0){
                edge[edgeCount][0]=i;
                edge[edgeCount][1]=j;
                edge[edgeCount][2]=graph[i][j];
                edgeCount++;

            }
        }
    }
    totelOfK=mst_Kruskal(cityNumber,edgeCount, edge);



}
void Comparethetwoalgorithms(double timeOfP,double timeOfK){
    printf("\nalgorithms\t\t prim algorithms       Kruskal algorithms\n");
    printf("totel cost \t\t\t%d km\t\t\t%d km\n",totelOfP,totelOfK);
    printf("execution time \t\t\t%.3fs\t\t\t%.3fs\n",timeOfP,timeOfK);

    if(timeOfP> timeOfK)
        printf("the Kruskal algorithms is faster\n");
    else if(timeOfP < timeOfK)
        printf("the prim algorithms is faster\n");

}
void clearHeap(struct Heap* heap) {
    for (int i = 0; i < heap->sizeOfHeap; i++) {
        free(heap->arr[i]);
        heap->arr[i] = NULL;
    }
    heap->sizeOfHeap = 0;
}


