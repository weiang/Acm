/*************************************************************************
	> File Name: 488.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: Mon 15 Oct 2012 07:24:44 PM CST
    > Describition: UVA problem "Triangle Wave"
 ************************************************************************/

#include <stdio.h>

int main(void)
{
	int	heigh, num;
	int i, j, k;

	scanf("%d%d", &heigh, &num);

	for (i = 0; i < num; i ++) {
		for (j = 1; j <= heigh; j ++) {
			for (k = 0; k < j; k ++)
				printf("%d", j);
		printf("\n");
		}

		for (j = heigh - 1; j > 0; j --) {
			for (k = 0; k < j; k ++)
				printf("%d", j);
			printf("\n");
		}
		if (i == num - 1)
			continue;
		printf("\n");
	}
	return 0;
}
