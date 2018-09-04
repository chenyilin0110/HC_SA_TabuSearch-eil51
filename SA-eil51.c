#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

double countDistance(int array[51][3],int number);
void tempData(int array[51][3],int randon1,int randon2);
void findNeighbor(int array[51][3]);
void copy(int startData[51][3],int array[51][3],int much);

int main()
{	
	clock_t startclock,endclock;
	startclock = clock();
	FILE *fptr;
	char num[2]={},x[2]={},y[2]={},empty[] = "EOF";
	int startData[51][3] = {0},data[51][3] = {0},read[51][3] = {0},
		temp1[51][3] = {0},temp2[51][3] = {0},temp3[51][3] = {0},temp4[51][3] = {0},temp5[51][3] = {0},
		temp6[51][3] = {0},temp7[51][3] = {0},maxBestData[51][3] = {0};
	int count = 0,i,chose = 1,co = 1,j;
	double bestDistance = 0,startDistance = 0,neighborDistance[7]={0},
		   maxNeighborDistance,temperature = 100.0,randTemperature,rate = 0.9999,expChange,
		   whereMaxNeighborDistance,maxBestDistance;
		
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
	for(i=0;i<count;i++)//初始 
	{
		chose = rand()%51;
		while(read[chose][0] == -9999)//取到重複
			chose = rand()%51;
		
		maxBestData[i][0] = startData[i][0] = read[chose][0];
		maxBestData[i][1] = startData[i][1] = read[chose][1];
		maxBestData[i][2] = startData[i][2] = read[chose][2];		
		read[chose][0] = -9999;
	}		
	maxBestDistance = startDistance = bestDistance = countDistance(startData,count);//初始的距離 
		
	while((temperature > 0)&&(bestDistance!=426)&&(co!=500001))
	{
		for(i=0;i<count;i++)//temp1-7重置 
		{
			for(j=0;j<3;j++)
				temp7[i][j] = temp6[i][j] = temp5[i][j] = temp4[i][j] = temp3[i][j] = temp2[i][j] = temp1[i][j] = startData[i][j];
		}
		findNeighbor(temp1);
		neighborDistance[0] = countDistance(temp1,count);
		findNeighbor(temp2);
		neighborDistance[1] = countDistance(temp2,count);
		findNeighbor(temp3);
		neighborDistance[2] = countDistance(temp3,count);
		findNeighbor(temp4);
		neighborDistance[3] = countDistance(temp4,count);
		findNeighbor(temp5);
		neighborDistance[4] = countDistance(temp5,count);
		findNeighbor(temp6);
		neighborDistance[5] = countDistance(temp6,count);
		findNeighbor(temp7);
		neighborDistance[6] = countDistance(temp7,count);
		maxNeighborDistance = neighborDistance[0];
		whereMaxNeighborDistance = 0;
		for(i=1;i<7;i++)
		{
			if(neighborDistance[i] < maxNeighborDistance)
			{
				maxNeighborDistance = neighborDistance[i];
				whereMaxNeighborDistance = i;
			}
		}
		randTemperature = rand()%1000/1000.0;
		expChange = (-1)*(maxNeighborDistance - bestDistance)/temperature;
		if(maxNeighborDistance < bestDistance)//比原解更好 
		{
			maxBestDistance = bestDistance = maxNeighborDistance;
			//鄰居最優是第幾個temp 把該temp丟到startData
			if(whereMaxNeighborDistance == 0)
				copy(startData,temp1,count);
			else if(whereMaxNeighborDistance == 1)
				copy(startData,temp2,count);
			else if(whereMaxNeighborDistance == 2)
				copy(startData,temp3,count);
			else if(whereMaxNeighborDistance == 3)
				copy(startData,temp4,count);
			else if(whereMaxNeighborDistance == 4)
				copy(startData,temp5,count);
			else if(whereMaxNeighborDistance == 5)
				copy(startData,temp6,count);
			else
				copy(startData,temp7,count);
			copy(maxBestData,startData,count);
		}
		else if(expChange > randTemperature)//一定機率接受 
		{
			bestDistance = maxNeighborDistance;
			//鄰居最優是第幾個temp 把該temp丟到startData
			if(whereMaxNeighborDistance == 0)
				copy(startData,temp1,count);
			else if(whereMaxNeighborDistance == 1)
				copy(startData,temp2,count);
			else if(whereMaxNeighborDistance == 2)
				copy(startData,temp3,count);
			else if(whereMaxNeighborDistance == 3)
				copy(startData,temp4,count);
			else if(whereMaxNeighborDistance == 4)
				copy(startData,temp5,count);
			else if(whereMaxNeighborDistance == 5)
				copy(startData,temp6,count);
			else
				copy(startData,temp7,count);				
		}
		else if(expChange < randTemperature)//不接受，回到最佳解
		{
			bestDistance = maxBestDistance;
			copy(startData,maxBestData,count);
		}
		temperature = rate * temperature;
		co++;
		if(co%10 == 0)
			printf("%f\n",bestDistance);
	}
	endclock = clock();	
//	printf("%1f\n",(endclock-startclock)/(double)(CLOCKS_PER_SEC));//total time
}

void copy(int startData[51][3],int array[51][3],int much)
{
	int ci,cj;
	for(ci=0;ci<much;ci++)
	{
		for(cj=0;cj<3;cj++)		
			startData[ci][cj] = array[ci][cj];		
	}
}

void findNeighbor(int array[51][3])
{
	int a,b;
	a = rand()%51;
	b = rand()%51;	
	tempData(array,a,b);
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
	double toCountDistance = 0;		
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
