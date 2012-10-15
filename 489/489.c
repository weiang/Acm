/*************************************************************************
	> File Name: 489.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: Mon 15 Oct 2012 07:35:44 PM CST
    > Describition: UVA problem 489 "Hangman Judge"
 ************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAXSIZE	1024

int main(void)
{
	int	i, j, k;
	int	flag[MAXSIZE];
	char	answer[MAXSIZE];
	char	guess[MAXSIZE];
	int	tag, err, a_size, g_size;
	int	round;

	while (scanf("%d", &round) && round != -1) {
		scanf("%s", answer);
		scanf("%s", guess);
		a_size = strlen(answer);
		g_size = strlen(guess);

		for (i = 0; i < a_size; i ++)
			flag[i] = 0;
		err = 0;
		for (i = 0; i < g_size; i ++) {
			tag = 0;
			for (j = 0; j < a_size; j ++) {
				if (answer[j] == guess[i]) {
					flag[j] = 1;
					tag = 1;
				}
			}

			if (tag == 0) {
				err ++;
				if (err == 7) {
					printf("Round %d\n", round);
					printf("You lose.\n");
					break;
				}
			}
			else {
				for (k = 0; k < a_size; k ++)
					if (flag[k] != 1)
						break;
				if (k == a_size) {
					printf("Round %d\n", round);
					printf("You win.\n");
					break;
				}
			}
		}
			if (i == g_size) {
				printf("Round %d\n", round);
				printf("You chickened out.\n");
			}
	}
	return 0;
}
	
