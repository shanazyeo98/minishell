#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	struct	stat	statbuf;
	char	*p1;
	char	*p2;
	char	*p3;
	int		status;
	int		bool;



	p1 = strdup("notadirorexecutable");
	p2 = strdup("tests/bin2");
	p3 = strdup("tests/bin2/permtest");

	status = stat(p1, &statbuf);
	if (status != 0)
		perror("test1");
	status = stat(p2, &statbuf);
	if (status != 0)
		perror("test2");
	else
	{
		printf("p2\n");
		bool = S_ISDIR(statbuf.st_mode);
		printf("Directory?: %d\n", bool);
		bool = S_ISREG(statbuf.st_mode);
		printf("Regular?: %d\n", bool);
	}
	status = stat(p3, &statbuf);
	if (status != 0)
		perror("test3");
	else
	{
		printf("p3\n");
		bool = S_ISDIR(statbuf.st_mode);
		printf("Directory?: %d\n", bool);
		bool = S_ISREG(statbuf.st_mode);
		printf("Regular?: %d\n", bool);
	}



	//logic
	//check if original path exists
		//exists, check if directory
			//if not directory, check executable
				//execuable -> return the original path
				//not executable -> continue
			//directory -> continue
		//not exists -> continue
	//for each path in envp list
		//combine with original path
			//check if combined path exists
				//exists, check if directory
					//not directory, check executable
						//executable -> return combined path
						//not executable -> move on to next path
					//directory -> move on to next path
				//not exists -> move on to next path
	//need to store the latest found status while looping through all paths

}


