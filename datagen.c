#include"croad.h"

 int main(int argc, char *argv[]){
 int i;
 int gen;
 FILE *fd;
 fd = fopen("croad.data", "w+");
 if(!fd){
   fprintf(stderr, "croad.data not created");
   exit(0);
 }
 for (i=1; i<= NUMHOUSES; i++){

    gen =rand()%MAXDIST;
    fprintf(fd, "%d\t%d\t%d\t%d\n", i, gen, ISHOUSE, ISHOUSE);
   }
  return 0;
   
 }
