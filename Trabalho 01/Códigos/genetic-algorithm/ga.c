#include <stdio.h>
#include <stdlib.h>
#define ORGS 100
#define GENES 20
#define ALLELES 4
#define MUT 1000

char **curG, **nextG, *mod;
int *f, totF, Eval(), Sel(), Run();
void Mem(), Init(), Gen();

int main(){
  Mem();
  printf("ultima geracao: %d\n", Run());}

void Mem(){
  int o;
  curG=(char**)malloc(sizeof(char*)*ORGS);
  nextG=(char**)malloc(sizeof(char*)*ORGS);
  mod=(char*)malloc(sizeof(char)*GENES);
  f=(int*)malloc(sizeof(int)*ORGS);
  for(o=0; o<ORGS; ++o){
    curG[o]=(char*)malloc(sizeof(char)*GENES);
    nextG[o]=(char*)malloc(sizeof(char)*GENES);}}

int Run(){
  int gen=0;
  Init();
  while(++gen){
    if(Eval()) return gen;;
    Gen();}}

void Init(){
  int o, g;
  for(o=0; o<ORGS; ++o) for(g=0; g<GENES; ++g) curG[o][g]=rand()%ALLELES;
  for(g=0; g<GENES; ++g) mod[g]=rand()%ALLELES;}

int Eval(){
  int o, g, curF;
  for(totF=0, o=0; o<ORGS; ++o){
    for(curF=0, g=0; g<GENES; ++g) if(curG[o][g]==mod[g]) ++curF;
    if(curF==GENES) return 1;
    totF += f[o]=curF;}
  return 0;}

void Gen(){
  int o, g, p1, p2, cp;
  for(o=0;o<ORGS;++o) for(p1=Sel(), p2=Sel(), cp=rand()%GENES,g=0;g<GENES;++g)
      nextG[o][g]=(rand()%MUT)? ((g<cp)? curG[p1][g]: curG[p2][g]): rand()%ALLELES;
  for(o=0; o<ORGS; ++o) for(g=0; g<GENES; ++g) curG[o][g]=nextG[o][g];}

int Sel(){
  int o, tot=0, pt=rand()%(totF+1);
  for(o=0; o<ORGS; ++o) if((tot+=f[o])>=pt) return o;}