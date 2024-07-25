#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char **argv)
{
	//not really sure how to do graphs yet, we shall see
	printf("XDDD\n");
	
	//Running 1 graph through the method, this is my test case until I make a makefile
	if (argc == 2)
	{
		printf("Testing 1 graph: \n");
		
		graph_test(argv[1];
	}
	
	//This is the actual project program. This else if runs everything and asks if the user
	//wants to try seperate graphs.
	else if (argc == 5)
	{
		printf("Testing 4 (or more) different graphs for the algorithms.\n
		Below are the results for the class assignment:\n");
		
		//Running the graph_test file for each graph
		for (int i = 0; i < argc; i++)
		{
			graph_test(argv[i]);
			// cp this to graphtest printf("\n------------------------------------------------------\n");
		}
		
		//asking the user if they want to try another graph they provided, i only provided 4 in my code
		bool wouldyouliketogoagain = true;
		while (wouldyouliketogoagain == true)
		{
			//printf("Would you like to test another graph?\n");
			//wouldyouliketogoagain = false;
			// if (user says yes)
			// {
			// 	wouldyouliketogoagain = true;
			// 	printf("Please provide another filename to test");
			// 	userinput xddd forgor
			// 	graph_test("%s", userinput);
			// }
			//
		}

	}
	else 
	{
		printf("Either somehow the make file messed up, you messed up, or i messed up.\n
		This error can only occur if 0, 2, or 3 command line arguements are used,\n
		which should not be possible given the fact I am having it run using a make file\n
		\n
		Please do the following commands to run the program so i can pass:\n
		gcc -o main main.c\n
		./main graph_file1\n
		./main graph_file2\n  
		./main graph_file3\n  
		./main graph_file4\n  
		\n
		Or you can email me at ajohn432@charlotte.edu and I can help :D. (I don't want to fail)"	);
	}
}
