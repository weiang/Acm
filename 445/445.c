/*************************************************************************
 *  > File Name: 445.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: Mon 15 Oct 2012 05:39:41 PM CST
    > Describition: UVA problem 445 "Marvelous Mazes" 
 ************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAX_SIZE	1024

int main(void)
{
	char	buf[MAX_SIZE];
	unsigned int	i, j , k, t;

	while (gets(buf) != NULL) {
		if (strcmp(buf, "") == 0) {
			printf("\n");
			continue;
		}
		for (i = 0; i < strlen(buf); i ++) {
			if ('1' <= buf[i] && '9' >= buf[i]) {
				j = buf[i] - 48;
				for ( i ++; buf[i] <= '9' && buf[i] >= '1'; i ++)
					j += buf[i] - 48;
				for (k = 0; k < j; k ++)
					printf("%c", buf[i]);
			}
			else if (buf[i] == '!')
				printf("\n");
		}
		printf("\n");
	}
	return 0;
}
				
