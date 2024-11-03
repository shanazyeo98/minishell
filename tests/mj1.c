#include <stdio.h>


void	test(char *type)\
{
	if (type == "in")
		printf("works\n");
	else
		printf("fails\n");
}


int	main(void)
{
	test("in");
}
