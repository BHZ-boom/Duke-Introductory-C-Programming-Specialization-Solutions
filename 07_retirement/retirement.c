#include<stdio.h>
#include<stdlib.h>

typedef struct {
  int months;
  double contribution;
  double rate_of_return;
}retire_info;

void retirement(int startAge, double initial, retire_info working, retire_info retired);
double computeSaving(double prev, double contribution, double rate);
void Print(int curAge, double saving);

int main(void){
  retire_info working={489,1000,0.045/12};
  retire_info retired={384,-4000,0.01/12};
  int startAge=327;
  double initial=21345;
  retirement(startAge,initial,working,retired);
  return 0;
}

double computeSaving(double prev, double contribution, double rate){
  return prev*(1+rate)+contribution;
}

void Print(int curAge, double saving){
  int year=curAge/12;
  int month=curAge%12;
  printf("Age %3d month %2d you have $%.2lf\n",year,month,saving);
}

void retirement(int startAge, double initial, retire_info working, retire_info retired){
  
  int currentAge=startAge;
  double currentSaving=initial;
  for(int i=working.months;i>0;i--){
    Print(currentAge, currentSaving);
    currentSaving=computeSaving(currentSaving, working.contribution, working.rate_of_return);
    currentAge++;
  }
  for(int j=retired.months;j>0;j--){
    Print(currentAge, currentSaving);
    currentSaving=computeSaving(currentSaving, retired.contribution, retired.rate_of_return);
    currentAge++;
  }
}
