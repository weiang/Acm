#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int	*a;
	a = (int *)malloc(sizeof(int) * 5);

	memset(a, 0, sizeof(a));
	printf("%lu\n", sizeof(a));
	free(a);
	return 0;
}
