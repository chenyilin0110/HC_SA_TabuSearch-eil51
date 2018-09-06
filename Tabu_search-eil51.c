#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
 
double countDistance(int array[51][3],int number);
void tempData(int array[51][3],int randon1,int randon2);
int store(int bestStepList[1000],int bestStepCount,int userStoreStepCount,int a,int b);

int main()
{
	clock_t startclock,endclock;
	startclock = clock();
	FILE *fptr;
	char num[2]={},x[2]={},y[2]={},empty[] = "EOF";
	int startData[51][3] = {0},data[51][3] = {0},read[51][3] = {0},bestStepList[1000]={99999};
	int count = 0,i,chose = 1,co = 1,bestStepCount = 0,userStoreStep=5,temp;
	double bestDistance = 0,startDistance = 0,foreveryzero= 0;
	
//	scanf("%d",&userStoreStep);
	fptr = fopen("eil51-data.txt","r");	
	while(fscanf(fptr,"%s %s %s",&num,&x,&y) != EOF)
	{				
		if(strcmp(num,empty) != 0)
		{	
			read[count][0] = atoi(num);
			read[count][1] = atoi(x);
			read[count][2] = atoi(y);
			count++;
		}
		else
			break;
	}
	fclose(fptr);

	srand(time(NULL));
	for(i=0;i<count;i++)//initial
	{
		chose = rand()%51;
		while(read[chose][0] == -9999)//sample chose
			chose = rand()%51;
		startData[i][0] = read[chose][0];
		startData[i][1] = read[chose][1];
		startData[i][2] = read[chose][2];
		read[chose][0] = -9999;
	}
	bestDistance = countDistance(startData,count);//startDistance
	
	while((co != 500001)&&(bestDistance!=426))
	{
		int change1 = 0,change2 = 0,temp1,temp2,temp3;
		double changeDistance;
		change1 = rand()%51;
		change2 = rand()%51;
		while(change1 == change2)//sample change
			change1 = rand()%51;
		for(i=0;i<bestStepCount;i++)//take a group in bestStepList
		{						
			if(bestStepList[i] == change1)
			{				
				if((i%2) == 0)//the number in left
				{									
					temp = (i+1);
					if(bestStepList[temp] == change2)
						change1 = rand()%51;
				}
				else//the number in right
				{						
					temp = (i-1);
					if(bestStepList[temp] == change2)
						change1 = rand()%51;					
				}
			}
		} 		
		tempData(startData,change1,change2);
		changeDistance = countDistance(startData,count);
		if(changeDistance < bestDistance)
		{
			bestDistance = changeDistance;
			bestStepCount = store(bestStepList,bestStepCount,userStoreStep,change1,change2);
		}
		else
			tempData(startData,change1,change2);
		if(co%10 == 0)		
			printf("%f\n",bestDistance);
		co++;		
	}		
	endclock = clock();	
//	printf("%1f\n",(endclock-startclock)/(double)(CLOCKS_PER_SEC));//total time
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

int store(int bestStepList[1000],int bestStepCount,int userStoreStepCount,int a,int b)
{
	if(bestStepCount == (userStoreStepCount*2))//bestStepList Full
	{		
		int countTwo=2,s;
		for(s=0;s<(userStoreStepCount*2-2);s++)
		{			
			bestStepList[s] = bestStepList[countTwo];
			countTwo++;
		}
		bestStepCount = bestStepCount - 2;
		bestStepList[bestStepCount] = 99999;//empty = 99999
		bestStepList[++bestStepCount] = 99999;////empty = 99999
		bestStepCount--;
	}
	else
	{
		bestStepList[bestStepCount] = a;
		bestStepList[++bestStepCount] = b;
		bestStepCount++;
	} 
	return bestStepCount;
}