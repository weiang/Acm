#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int prase_cmd(char *buf, int *a, int *b)
{
        int     i = 1;
        char    *cmd[4];

        cmd[0] = strtok(buf, " ");
        while ((cmd[i] = strtok(NULL," ")) != NULL)
                i ++;
	if (i > 2) {
		for (i = 0;i < 4;i ++)
			printf("%s\n", cmd[i]);
	        *a = atoi(cmd[1]);
        	*b = atoi(cmd[3]);
		printf("a = %d, b = %d\n", *a, *b);
       	}
	 if (strcmp(cmd[0], "quit") == 0)
                return 0;
        if (strcmp(cmd[0], "move") == 0) {
		printf("Here\n");
                if (strcmp(cmd[2], "onto") == 0)
                        return 1;
                else if (strcmp(cmd[2], "over") == 0)
                        return 2;
                else {  fprintf(stderr, "Cmd error!\n");
                        exit(EXIT_FAILURE);
                }
        }
	if (strcmp(cmd[0], "pile") == 0) {
                if (strcmp(cmd[2], "onto") == 0)
                        return 3;
                else if (strcmp(cmd[2], "over") == 0)
                        return 4;
                else {  fprintf(stderr, "Cmd error!\n");
                        exit(EXIT_FAILURE);
                }
        }
        fprintf(stderr, "Cmd error!\n");
        exit(EXIT_FAILURE);
}

void main(void)
{
	int	a, b, c;
	char	buf[] = "move 2 onto 1 ";
	
	c = prase_cmd("move 2 onto 1", &a, &b);
	printf("c = %d\n", c);
}

