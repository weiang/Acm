/*************************************************************************
	> File Name: 458.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: Mon 15 Oct 2012 06:58:01 PM CST
    > Describition: 
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(void)
{
	char	buf[1024];
	int	i, j;

	while (gets(buf)) {
		j = strlen(buf);
		for (i = 0; i < j; i ++) {
			buf[i] -= 7;
			printf("%c", buf[i]);
		}
		printf("\n");
	}
}
