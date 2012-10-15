#include <stdio.h>
#include <stdlib.h>


char	*sorted[6] = {"BCG","BGC", "CBG", "CGB", "GBC", "GCB"};

int main(void)
{
	int	i, min, k;
	int	total_move[6];
	int	color[3][3];
	
	while (scanf("%d", &color[0][0]) != EOF) {	
		scanf("%d%d", &color[0][1], &color[0][2]);
		for (i = 1;i < 3;i ++)
			scanf("%d%d%d",&color[i][0], &color[i][1], &color[i][2]);

		total_move[0] = color[1][0] + color[2][0] + color[0][2] + color[2][2] + color[0][1] + color[1][1];
		total_move[1] = color[1][0] + color[2][0] + color[0][1] + color[2][1] + color[0][2] + color[1][2];
		total_move[2] = color[1][2] + color[2][2] + color[0][0] + color[2][0] + color[0][1] + color[1][1];
		total_move[3] = color[1][2] + color[2][2] + color[0][1] + color[2][1] + color[0][0] + color[1][0];
		total_move[4] = color[1][1] + color[2][1] + color[0][0] + color[2][0] + color[0][2] + color[1][2];
		total_move[5] = color[1][1] + color[2][1] + color[0][2] + color[2][2] + color[0][0] + color[1][0];

		min = total_move[0];
		k = 0;
		for (i = 1;i < 6;i ++) {
			if (min > total_move[i]) {
				min = total_move[i];
				k = i;
			}
		}
		printf("%s %d\n", sorted[k], min);
	}
	return 0;
}
