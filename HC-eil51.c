#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
 
double countDistance(int array[51][3],int number);
void tempData(int array[51][3],int randon1,int randon2);
int data[51][3] = {0};
int main()
{
	clock_t startclock,endclock;
	startclock = clock();
	FILE *fptr;
	char num[2]={},x[2]={},y[2]={},empty[] = "EOF";
	int startData[51][3] = {0},read[51][3] = {0};
	int count = 0,i,j,w=1,chose = 1,co = 1,iteration = 1;
	double bestDistance = 0,startDistance = 0,foreveryzero= 0;
	
	fptr = fopen("eil51-data.txt","r");	
	while(fscanf(fptr,"%s %s %s",&num,&x,&y) != EOF)
	{				
		if(strcmp(num,empty) != 0)
		{	
			read[count][0] = data[count][0] = atoi(num);
			read[count][1] = data[count][1] = atoi(x);
			read[count][2] = data[count][2] = atoi(y);
			count++;
		}
		else
			break;
	}
	fclose(fptr);
	
	srand(time(NULL));
	for(i=0;i<count;i++)//初始 
	{
		chose = rand()%51;
		while(read[chose][0] == -9999)//取到重複 
			chose = rand()%51;		
		startData[i][0] = read[chose][0];
		startData[i][1] = read[chose][1];
		startData[i][2] = read[chose][2];		
		read[chose][0] = -9999;
	}
	bestDistance = countDistance(startData,count);//初始的距離 
	
	while(co != 500001)
	{
		int change1 = 0,change2 = 0,temp1,temp2,temp3;
		double changeDistance;
		change1 = rand()%51;
		change2 = rand()%51;		
		while(change1 == change2)//取到兩個相同 
			change1 = rand()%51;
		tempData(startData,change1,change2);
		changeDistance = countDistance(startData,count);
		if(changeDistance < bestDistance)		
			bestDistance = changeDistance;			
		else
			tempData(startData,change1,change2);		
		if(co%10 == 0)
			printf("%f\n",bestDistance);
		for(i=0;i<count;i++)
		{
			read[i][0] = data[i][0];
			read[i][1] = data[i][1];
			read[i][2] = data[i][2];
		}
		co++;
	}					
	endclock = clock();
	printf("%1f\n",(endclock-startclock)/(double)(CLOCKS_PER_SEC));//total time	
}

void tempData(int array[51][3],int randon1,int randon2)
{
	int tempDataTemp[3]={0},t;
	for(t=0;t<3;t++)	
	{
		tempDataTemp[t] = array[randon1][t];
		array[randon1][t] = array[randon2][t];
		array[randon2][t] = tempDataTemp[t];
	}	
}

double countDistance(int array[51][3],int number)
{	
	int j;
	double toCountDistance=0;		
	for(j=0;j<number;j++)
	{
		int temp;
		if(j!=(number-1))
		{
			temp = j + 1;		
			toCountDistance += sqrt(pow((array[j][1]-array[temp][1]),2)+pow((array[j][2]-array[temp][2]),2));
		}
		else
		{
			temp = 0;
			toCountDistance += sqrt(pow((array[j][1]-array[temp][1]),2)+pow((array[j][2]-array[temp][2]),2));
		}
	}
	return toCountDistance;
}
