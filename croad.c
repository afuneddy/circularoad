
#include "croad.h"
#include "datagen.c"

 typedef struct{
   int index; //distance index e.g i
   int dist;  //distance(house_i-1 , house_i)
   int hLeft; //Bool 1 or 0
   int hRight;//Bool 1 or 0
 }DAT;

  DAT *LISTLE;
  DAT *LISTGT;
  int MATRIX[NUMHOUSES][NUMHOUSES];

  int bscount,gt,le,t,d,i,j,k;
 
  FILE *fd, *fdw;

 void partitionData();
 void trimList();
 void makeClusters();
 void countHouses();
 void printlist(DAT *list, char *fname);

 int main(int argc, char *argv[]){
    LISTLE = malloc(sizeof(DAT)*(NUMHOUSES+2));
    LISTGT = malloc(sizeof(DAT)*(NUMHOUSES+2));
    bscount =le=gt= t=d=i=j=k=0;

   if(argc<2){
     fprintf(stderr, "USAGE: %s <file name>\n", argv[0]);
     exit(0);
   }
   fd = fopen(argv[1], "r");
   if(!fd){
      fprintf(stderr, "Can't open %s \n", argv[1]);
      exit(0);
   }
   //Generate test data
   datagen();
   //Partition data into two lists;  listGT and  ListLE
   partitionData();
  //Trim LISTGT data 
   trimList();
   //use data in LISTLE to make clusters and store in MATRIX
   makeClusters(); 
   //Count remainiing houses in LISTGT after trim
   countHouses();
   // printf number of Base stations = Matrix length + Numbeer of houses in LISTGT
  fprintf(stdout, "Minimum Number of Base stations: %d\n", bscount);
  fclose(fd);
  return 0;
   
 }
 
 void partitionData(){
   int index, dist, hLeft, hRight;
   while((fscanf(fd, "%d%d%d%d",  &index,&dist, &hLeft, &hRight)==4)&&( le <= NUMHOUSES) && (gt <= NUMHOUSES))
     if(dist <= DIAMETER){
        LISTLE[le].index = index;
        LISTLE[le].dist = dist;
        LISTLE[le].hLeft = hLeft;
        LISTLE[le++].hRight = hRight;
      }
      else
        if(dist > DIAMETER)
        {
           LISTGT[gt].index = index;
           LISTGT[gt].dist = dist;
           LISTGT[gt].hLeft = hLeft;
           LISTGT[gt++].hRight = hRight;
        }
  printlist(LISTLE, "ListLE");
 }

 void trimList(){
  
  for(j=0; j< gt-1; j++)
    if(LISTGT[j+1].index) 
      if(LISTGT[j].index+1 != LISTGT[j+1].index){
         LISTGT[j].hRight = 0;
         LISTGT[j+1].hLeft = 0;
      }
      else
        LISTGT[j].hRight = 0;
   printlist(LISTGT, "ListGT");
  }
 void countHouses(){
   for(i=0; i<gt-1; i++)
      if(LISTGT[i].hRight)
        bscount++;
      if(LISTGT[i].hLeft)
        bscount++;
 }
 void makeClusters(){
   int s, l,z;
   for(k=0; k< le-1; k++){
      if(d == 0){
         if(LISTLE[k].index == 1)
            MATRIX[bscount][t++] = le+gt;
          else
           MATRIX[bscount][t++] = LISTLE[k].index -1;
       }
         if(LISTLE[k+1].index)
            if((LISTLE[k].index+1 == LISTLE[k+1].index) && (d += LISTLE[k].dist+ LISTLE[k+1].dist )){
               if(d <= DIAMETER){
                 MATRIX[bscount][t++] = LISTLE[k+1].index -1;
                 continue;
               }
             }
           else{
              MATRIX[bscount][t++] = LISTLE[k].index;
               }
         
       bscount++;
       d =0;
       t=0;
          
    }
    bscount--;
  FILE *fdw2 = fopen("Clusters.data", "w+");
  if(fdw2){
  for(s=0; s<bscount; s++){
     while(MATRIX[s][z])
       fprintf(fdw2, "%d ", MATRIX[s][z++]);
    z=0;
    fprintf(fdw2, "\n");
   }
  for(l=0;LISTGT[l].index; l++){
      if(LISTGT[l].hLeft)
        if(LISTGT[l].index == 1)
          fprintf(fdw2, "%d\n", le + gt );
          else
         fprintf(fdw2, "%d\n", LISTGT[l].index -1);
      if(LISTGT[l].hRight)
         fprintf(fdw2, "%d\n", LISTGT[l].index);
    }  
    } 
  fclose(fdw2);
  }

 void printlist(DAT *LIST, char *listname){
  int l;
  FILE *fdw2 = fopen(listname, "w+");
  if(fdw2){
    for(l=0;LIST[l].index; l++){
       fprintf(fdw2, "%d\t%d\t%d\t%d\n", LIST[l].index,LIST[l].dist,LIST[l].hLeft, LIST[l].hRight);
    } 
   fclose(fdw2); 
    } 
}
