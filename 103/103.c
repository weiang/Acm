#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Error handling function */
static error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

/*
 * Data Structures 
 */
/* Box list node */
typedef struct box_node {
	int	*scale;
	int	num;
	struct box_node	*next;
} box_node;

/* Box link list */
typedef struct {
	int	length;
	box_node	*head;
} box_list;

/*
 * Variables
 */
int	dis = 0;	/* Longest box list length */
int	*vis;
int	*path;
int	dim, boxnum;
box_node	*pmax_box_node;
box_list	box;

void init_box_list(box_list *pboxlist)
{
	pboxlist -> length = 0;
	if (pboxlist -> head != NULL)
		free(pboxlist -> head);
	if ((pboxlist -> head = (box_node *)malloc(sizeof(box_node))) == NULL)
		error("Malloc error");
	if (pboxlist -> head != NULL) {
		pboxlist -> head -> next = NULL;
		pboxlist -> head -> scale = NULL;
		pboxlist -> head -> num = 123;
	}
}

void order_insert(box_list *pboxlist, box_node *pnode,int cmp(int a, int b))
{
	box_node	*ptmp, *preptmp;
	int	result;

	if (pboxlist -> length == 0) {
		pboxlist -> head -> next = pnode;
		pboxlist -> length ++;
		return;
	}
	
	preptmp = pboxlist -> head;
	ptmp = preptmp -> next;
	while (ptmp -> next) {
		result = cmp(pnode -> scale[0], ptmp -> scale[0]);
		if (result >= 0) {
			preptmp = ptmp;
			ptmp = ptmp -> next;
		}
		else {
			pnode -> next = ptmp;
			preptmp -> next = pnode;
			pboxlist -> length ++;
			return;
		}
	}

	result = cmp(pnode -> scale[0], ptmp -> scale[0]);
	if (result >= 0) {
		ptmp -> next = pnode;
	}
	else {
		pnode -> next = ptmp;
		preptmp -> next = pnode;
	}
	pboxlist -> length ++;
}

int cmp(int a, int b)
{
	int i;
	i = a - b;
	if (i > 0)
		return 1;
	if (i = 0)
		return 0;
	if (i < 0)
		return -1;
}

void copy(box_node **pa, box_node **pb, int i)
{
	int	n;
	for (n = 0;n < i;n ++)
		pa[n] = pb[n];
}
/* 
   pa > pb return 1
   pa <= pb return 0
 */
int is(box_node *pa, box_node *pb) 
{
	int	i;
	for (i = 0;i < dim;i ++)
		if (pa -> scale[i] <= pb -> scale[i])
			return 0;
	return 1;
}

void sort(box_node *pnode, int n) 
{
	int	i, j;
	int	*ptmp;
	int	tmp;

	ptmp = pnode -> scale;
	for (i = 0;i < n - 1;i ++)
		for (j = i + 1;j < n;j ++) {
			if (ptmp[i] > ptmp[j]) {
				tmp = ptmp[i];
				ptmp[i] = ptmp[j];
				ptmp[j] = tmp;
			}
		}
}

int dp(box_node *pnode)
{
	int	max, t;
	box_node	*ptmp;

	if (vis[pnode -> num] == 1)
		return path[pnode -> num];
	max = 1;

	vis[pnode -> num] = 1;
	ptmp = box.head -> next;
	while(ptmp) {
		if (ptmp -> num != pnode -> num && is(pnode, ptmp)) {
			t = dp(ptmp) + 1;
			max = max > t ? max : t;
		}
		ptmp = ptmp -> next;
	}
	dis = dis > max ? dis : max;
	pmax_box_node = pnode;
	return path[pnode -> num] = max;
}
	
void print_result(box_node *pnode)
{
	box_node	*ptmp;
	ptmp = box.head -> next;
	
	while (ptmp != NULL) 
		if (path[ptmp -> num] == path[pnode -> num] - 1 && is(pnode, ptmp)) {
		print_result(ptmp);
		break;
		}
		else 
			ptmp = ptmp -> next;
	if (pnode != pmax_box_node)
		printf("%d ", pnode -> num);
	else
		printf("%d", pnode -> num);
}

int main(void)
{
	int	i, j;
	box_node	*ptmp, *p;

	init_box_list(&box);
	
	while(scanf("%d%d", &boxnum, &dim) == 2) {
		dis = 0;
		if ((path = (int *)malloc(sizeof(int) * boxnum)) == NULL)
			error("Malloc error");
		if ((vis = (int *)malloc(sizeof(int) * boxnum)) == NULL)
			error("Malloc error");
		memset(vis, 0, sizeof(int) * boxnum);
		memset(path, 0, sizeof(int) * boxnum);
		
		for (i = 0;i < boxnum;i ++) {
			if ((ptmp = (box_node *)malloc(sizeof(box_node))) == NULL)
			       error("Malloc error");
			ptmp -> next = NULL;
			ptmp -> num = i + 1;
			if ((ptmp -> scale = (int *)malloc(sizeof(int) * dim)) == NULL)
				error("Malloc error");

			for (j = 0;j < dim;j ++)
				scanf("%d", &(ptmp -> scale[j]));
			sort(ptmp, dim);
			order_insert(&box, ptmp, cmp);
		}
		
		ptmp = box.head -> next;
		while (ptmp != NULL) {
			dp(ptmp);
			ptmp = ptmp -> next;
		}
		printf("%d\n", dis);
		print_result(pmax_box_node);
		printf("\n");

		free(vis);
		free(path);

		ptmp = box.head -> next;
		while (ptmp != NULL) {
			p = ptmp -> next;
			free(ptmp);
			ptmp = p;
		}
		free(box.head);
		box.head = NULL;
		init_box_list(&box);
	}
	return 0;
}
