#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUMHOUSES 1000  //WARNING! Yoou can't go above 20 000 because of memory allocation issues, Still to fix
#define ISHOUSE 1 //Bool to indicate presence of house in a list
#define MAXDIST 1000  //Max distance from a house  to a phone base station
#define DIAMETER 2*MAXDIST //Max distance between two houses that can potentially share base station
#define MAXTESTDIST 4000 //Used to generate sample distances between houses : rand()%4000
