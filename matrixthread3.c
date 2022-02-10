// N*N matrix Multimlication using P-threads  Here P = N/2    ....N*N is size of matrix 

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<math.h>
#define N 1024

int not;
int m1[N][N],m2[N][N],res[N][N];
int m,n;

pthread_mutex_t mutex;

void read_matrix(){

	int i,j;
	
	printf("Enter size of matrix");
	scanf("%d %d",&m,&n);

	for(i=0;i<m;i++)    
	{    
		for(j=0;j<n;j++)    
		{    
		m1[i][j]=(rand() % (10-1+1)) +1;
		m2[i][j]=(rand() % (10-1+1)) +1;
		
		}    
	}    
			
}
void print_matrix(int x[N][N]){

	int i,j;
	printf("\n");

	for(i=0;i<m;i++){
	
		printf("\n");
	
		for(j=0;j<n;j++){
		
			printf(" %d\t",x[i][j]);
		}
	}	printf("\n");	

}


void * mult(void *arg){


	long int num = (long int)arg;
	
	
	int t1 = floor(num*sqrt(n));
	int t2 = floor((num+1)*sqrt(n));
	 
	
	 
	int i,j,k;
	
	pthread_mutex_lock(&mutex);
	// Here inner loop executes only one time from num to num+1 
	// So each Thread calculate the result of the row
	for(i=t1;i<t2;i++)
	{
		
		for(j=0;j<n;j++)
		{
		 	
		 	res[i][j] = 0;
		
			for(k=0;k<n;k++)
			{
			
			
				res[i][j] = res[i][j] + m1[i][k]*m2[k][j];
			}
		
		}	
	}
	
	 printf("\nMatrix by thread %ld :", num+1);
	 print_matrix(res);
	  
	 pthread_mutex_unlock(&mutex);
	
	
}

int main(){

	pthread_t tid[N];
	pthread_mutex_init(&mutex,NULL);
	long int i,j;
 	
	read_matrix();
	
	printf("Enter no of threades");
	scanf("%d",&not);
	
	//Creating the threads
	 
	for(i=0;i<not;i++)
		pthread_create(&tid[i], NULL, mult, (void*)i);
 
	for(j=0;j<not;j++)
		pthread_join(tid[j],NULL);
 
		
	 
	
		
	pthread_mutex_destroy(&mutex);
	

	
}
