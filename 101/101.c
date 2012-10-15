#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct link_list {
	struct link_list	*next;
	int	block;
} list_node, *list_node_ptr;

typedef struct stack {
	list_node_ptr	base, top;
	int	stack_size;
} stack, *stack_ptr;

/* Block_stacks is a pointer to an array of stack_ptr pointer */
stack	**block_stacks;

void creat_stack(stack_ptr *ppstack)
{
	*ppstack = (stack_ptr)malloc(sizeof(stack));

	(*ppstack) -> top = (list_node_ptr)malloc(sizeof(list_node));
	if ((*ppstack) -> top == NULL) {
		fprintf(stderr, "Malloc error!\n");
		exit(EXIT_FAILURE);
	}
	(*ppstack) -> top -> block = 123;
	(*ppstack) -> stack_size = 0;
	(*ppstack) -> base = (*ppstack) -> top;
	(*ppstack) -> base -> next = NULL;
}

void pop(stack_ptr pstack, list_node_ptr pnode)
{
	if (pstack -> stack_size == 0) {
		fprintf(stderr, "Empty stack!\n");
		exit(EXIT_FAILURE);
	}
	
	pnode = pstack -> top;
	pstack -> top = pnode -> next;
	pstack -> stack_size --;
}

void push(stack_ptr pstack, list_node_ptr pnode)
{
	pnode -> next = pstack -> top;
	pstack -> top = pnode;
	pstack -> stack_size ++;
}

void init_block_world(int nblock, stack_ptr *block_stacks)
{
	int	i;
	list_node_ptr	pnode;

	for (i = 0; i < nblock; i ++) {
		creat_stack(&block_stacks[i]);
		pnode = (list_node_ptr)malloc(sizeof(list_node));
		if (pnode == NULL) {
			fprintf(stderr, "Malloc error!\n");
			exit(EXIT_FAILURE);
		}
		pnode -> next = NULL;
		pnode -> block = i;
		push(block_stacks[i], pnode);
	}
}

void recover(stack_ptr pstack, list_node_ptr pnode)
{	
	list_node_ptr	ptmp;
	
	while (pstack -> top != pnode) {
		pop(pstack, ptmp);
		push(block_stacks[ptmp -> block], ptmp);
	}
}

/* Find block whose block number is block in stack pstack and 
 * Then return its pointer to pnode
 */
int find_block(int block, stack_ptr *ppstack, list_node_ptr *ppnode)
{
	int	i = 0;
	list_node_ptr	ptmp;
	
	while (block_stacks[i] != 0){
		ptmp = block_stacks[i] -> top;
		while (ptmp != NULL) {
			if (ptmp -> block != block)
				ptmp = ptmp -> next;
			else {	*ppnode = ptmp;
				*ppstack = block_stacks[i];
				return 1;
			}
		}
		i ++;
	}
	return 0;
}



void move_onto(int blocka, int blockb)
{
	list_node_ptr	pnode_a, pnode_b;
	stack_ptr	pstack_a, pstack_b;
	
	if (!find_block(blocka,&pstack_a, &pnode_a) || !find_block(blockb, &pstack_b, &pnode_b)) {
		fprintf(stderr, "Block error!\n");
		exit(EXIT_FAILURE);
	}
	
	recover(pstack_a, pnode_a);	 
	recover(pstack_b, pnode_b); 	/* Return bolcks that are stacked on top of block a and b to their initial positions */
	pop(pstack_a, pnode_a);
	push(pstack_b, pnode_a);
}

void move_over(int blocka, int blockb)
{
	list_node_ptr	pnode_a, pnode_b;
	stack_ptr	pstack_a, pstack_b;

	if (!find_block(blocka, &pstack_a, &pnode_a) || !find_block(blockb, &pstack_b, &pnode_b)) {
		fprintf(stderr, "Block error!\n");
		exit(EXIT_FAILURE);
	}
	
	recover(pstack_a, pnode_a);
	pop(pstack_a, pnode_a);
	push(pstack_b, pnode_a);
}

void pile_onto(int blocka, int blockb)
{
	int	count = 0;
	
	list_node_ptr   pnode_a, pnode_b, ptmp;
        stack_ptr       pstack_a, pstack_b;

        if (!find_block(blocka, &pstack_a, &pnode_a) || !find_block(blockb, &pstack_b, &pnode_b)) {
                fprintf(stderr, "Block error!\n");
                exit(EXIT_FAILURE);
        }
	
	recover(pstack_b, pnode_b);

	for (ptmp = pstack_a -> top; ptmp != pnode_a; ptmp = ptmp -> next)
		count ++;
	count ++;

	ptmp = pstack_a -> top;
	pstack_a -> top = pnode_a -> next;
	pstack_a -> stack_size -= count;
	
	pnode_a -> next = pstack_b -> top;
	pstack_b -> top = ptmp;
	pstack_b -> stack_size += count;
}

void pile_over(int blocka, int blockb)
{
	int	count = 0;

	list_node_ptr   pnode_a, pnode_b, ptmp;
        stack_ptr       pstack_a, pstack_b;

        if (!find_block(blocka, &pstack_a, &pnode_a) || !find_block(blockb, &pstack_b, &pnode_b)) {
                fprintf(stderr, "Block error!\n");
                exit(EXIT_FAILURE);
        }
	
	for (ptmp = pstack_a -> top; ptmp != pnode_a; ptmp = ptmp -> next)
                count ++;
        count ++;
	
	ptmp = pstack_a -> top;
	pstack_a -> top = pnode_a -> next;
	pstack_a -> stack_size -= count;
	
	pnode_a -> next = pstack_b -> top;
	pstack_b -> top = ptmp;
	pstack_b -> stack_size += count;
}

int main(void)
{
	char	cmd[2][5];
	int	block_a, block_b, nblocks;
	int	i,j;
	list_node_ptr	ptmp;
	int	buf[1024];
	for(i = 0;i < 1024;i ++)
		buf[i] = -1;

	scanf("%d", &nblocks);
	block_stacks = (stack_ptr *)malloc(sizeof(stack) * nblocks);
	init_block_world(nblocks, block_stacks);
/*	while (scanf("%s", cmd[0]) != EOF){ 
*/	while(1) {
		scanf("%s", cmd[0]);
		if (strcmp(cmd[0], "quit") == 0) {
			break;
	/*		for (i = 0; i < nblocks; i ++) {
				ptmp = block_stacks[i] -> top;
				printf("%d: ", i);
				j = 0;
				while(ptmp != block_stacks[i] -> base) {
					buf[j ++] = ptmp -> block;
					ptmp = ptmp -> next;
				}
				for (j = j - 1;j >= 0;j --)
					printf("%d ", buf[j]);
				printf("\n");
			}
			return 0;
	*/	
		}
		else {
			scanf("%d%s%d", &block_a, cmd[1], &block_b);
			if (strcmp(cmd[0], "move") == 0) {	
				if (strcmp(cmd[1], "onto") == 0) {
					move_onto(block_a, block_b);
				}
				else {
					move_over(block_a, block_b);
				}
			}
			else	{
				if (strcmp(cmd[1], "onto") == 0) {
					pile_onto(block_a, block_b);
				}
				else {
					pile_onto(block_a, block_b);
				}	
			}
		}	
	}

	for (i = 0; i < nblocks; i ++) {
		printf("%d: ", i);
		ptmp = block_stacks[i] -> top;
		j = 0;
		while (ptmp != block_stacks[i] -> base) {
			buf[j ++] = ptmp -> block;
			ptmp = ptmp -> next;
		}
		for (j = j - 1;j >= 0;j --)
			printf("%d ", buf[j]);
		printf("\n");
	}
	return 0;
} 
