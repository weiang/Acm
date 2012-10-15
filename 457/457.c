/*************************************************************************
	> File Name: 457.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: Mon 15 Oct 2012 06:36:59 PM CST
    > Describition: UVA problem 457 "Linear Cellular Automate"
 ************************************************************************/

#include <stdio.h>
#include <string.h>

#define N	10
#define NUM	40
#define DAY 50
int main(void)
{

	int	dna[N];
	int	next_day[NUM], cur_day[NUM];
	int	i, j;

	for ( i = 0; i < N; i ++)
		scanf("%d", &dna[i]);

	for (i = 0; i < NUM; i ++)
		cur_day[i] = 0;
	cur_day[19] = 1;

	for (i = 0; i < NUM; i ++) {
		if (cur_day[i] == 0)
			printf(" ");
		else if (cur_day[i] == 1)
			printf(".");
		else if (cur_day[i] == 2)
			printf("x");
		else 
			printf("W");
	}
	printf("\n");


	for (i = 0; i < DAY - 1; i ++) {
		next_day[0] = dna[cur_day[0] + cur_day[1]];
		for (j = 1; j < NUM - 1; j ++)
			next_day[j] = dna[cur_day[j - 1] + cur_day[j] + cur_day[j + 1]];	
			next_day[NUM - 1] = dna[cur_day[NUM - 1] + cur_day[NUM - 1]];
		for (j = 0; j < NUM; j ++) {
			cur_day[j] = next_day[j];
			if (cur_day[j] == 0)
				printf(" ");
			else if (cur_day[j] == 1)
				printf(".");
			else if (cur_day[j] == 2)
				printf("x");
			else
				printf("W");
		}
		printf("\n");
	}

	return 0;
}


