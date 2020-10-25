#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
  FILE *fp;
  fp = fopen("input.csv","w");
  srand(time(NULL));
  int i,j,x;

  for(i = 0;i < 2000000;i++){  //5000000
    for(j = 0;j < 20;j++){
      x = (rand() % 2147483647);
      int y = (rand() % 100);
      if((y % 2) == 0)
	x = x * -1;      
      if(j != 19)     
        fprintf(fp,"%d|",x);
      else
	fprintf(fp,"%d\n",x);      
    }    
  }
 
 
  fclose(fp);
return 0;
}	
