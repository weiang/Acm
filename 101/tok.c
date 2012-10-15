#include <string.h>
#include <stdio.h>

void prase(char *);

int main(void)
{
	int	i = 1;
	char	buf[] = "move 9 onto 1";
	prase(buf);
	return 0;
}

void prase(char *buf)
{
	printf("%s\n", strtok(buf, " "));
	printf("%s\n", strtok(NULL, " "));
}
