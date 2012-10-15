/*************************************************************************
	> File Name: 414.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: Mon 15 Oct 2012 04:10:12 PM CST
    > Describition: UVA problem 414 "Machined Surfaces"
 ************************************************************************/

#include <stdio.h>
#include <string.h>

#define N	25
#define MAX_SIZE	1024

int main(void)
{
	int	lines, i, j, max, blank;
	char	buf[MAX_SIZE];
	int	size[MAX_SIZE];

	while (scanf("%d", &lines) && lines != 0) {
		max = 0;
		for (i = 0; i < lines; i ++)
			size[i] = 0;
		gets(buf);
		for (i = 0; i < lines; i ++) {
			gets(buf);
			for (j = 0; j < strlen(buf); j ++)
				if (buf[j] == 'X')
					size[i] ++;
			if (size[i] > max)
				max = size[i];
		}
		blank = 0;
		for (i = 0; i < lines; i ++)
			blank += max - size[i];
		printf("%d\n", blank);
	}
	return 0;
}
