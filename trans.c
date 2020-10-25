#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

int judge;
int counter = 0;
int execute = 0;
FILE *out;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
void *mythread(void *enter){
FILE *fp = (FILE*)enter;
int j;
int number[20];
char str[10];
while(!feof(fp)){
  {
    pthread_mutex_lock( &mutex1 );	  
    fscanf(fp,"%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c"
                "%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c",&number[0],str
                ,&number[1],str,&number[2],str,&number[3],str,&number[4],str
                ,&number[5],str,&number[6],str,&number[7],str,&number[8],str
                ,&number[9],str,&number[10],str,&number[11],str
                ,&number[12],str,&number[13],str,&number[14],str
                ,&number[15],str,&number[16],str,&number[17],str
                ,&number[18],str,&number[19],str);
    if(feof(fp))
        pthread_exit(NULL);
    pthread_mutex_unlock( &mutex1 );
    pthread_mutex_lock( &mutex2 );
    if(judge == 0)
      judge = 1;
    else
      fprintf(out,",\n");
    fprintf(out,"  {\n");
    //fprintf(out,"\t\"col_%d\":%d,\n",1,number);
    for(j = 0; j < 20;j++){
      if(j != 19)
        fprintf(out,"\t\"col_%d\":%d,\n",j+1,number[j]);
      else
        fprintf(out,"\t\"col_%d\":%d\n",j+1,number[j]);
    }
    fprintf(out,"  }");
    pthread_mutex_unlock( &mutex2 );
  }
}
pthread_exit(NULL);
}

int main(int argc,char *argv[]){
clock_t start,end;
start = clock();

FILE *in;
int i,j,k;
in = fopen("input.csv","r+");
out = fopen("output.json","w");
int number[20];
int thread_num = atoi(argv[1]);
char str[10];

//int judge = 0;
fprintf(out,"[\n");
/*while(!feof(in)){
  {
    fscanf(in,"%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c"
		"%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c",&number[0],str
		,&number[1],str,&number[2],str,&number[3],str,&number[4],str
		,&number[5],str,&number[6],str,&number[7],str,&number[8],str
		,&number[9],str,&number[10],str,&number[11],str
		,&number[12],str,&number[13],str,&number[14],str
		,&number[15],str,&number[16],str,&number[17],str
		,&number[18],str,&number[19],str);
    if(feof(in))
	break;
    if(judge == 0)
      judge = 1;
    else
      fprintf(out,",\n");    
    fprintf(out,"  {\n");
    //fprintf(out,"\t\"col_%d\":%d,\n",1,number);
    for(j = 0; j < 20;j++){      
      if(j != 19)      
        fprintf(out,"\t\"col_%d\":%d,\n",j+1,number[j]);
      else
	fprintf(out,"\t\"col_%d\":%d\n",j+1,number[j]);      
    }	    
    fprintf(out,"  }");
  }	  
}*/
switch(thread_num){
  case 1:{
    pthread_t t1;
    pthread_create(&t1,NULL,mythread,in);
    pthread_join(t1,NULL);
  }		 
    break;
  case 2:{
    pthread_t t1,t2;
    pthread_create(&t1,NULL,mythread,in);
    pthread_create(&t2,NULL,mythread,in);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
  }
    break;	 
}
/*
pthread_t t1,t2;
pthread_create(&t1,NULL,mythread,in);
pthread_create(&t1,NULL,mythread,in);
pthread_join(t1,NULL);
*/
fprintf(out,"\n]");
fclose(in);
fclose(out);

end = clock();
double speed = end - start;
printf("%f sec\n",speed/CLOCKS_PER_SEC);
return 0;	
}
