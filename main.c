#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET 26

void graph_test(char *graph_name);

typedef struct Edge
{
	int target;
	int weight;
	struct Edge* next;
} Edge;
typedef struct Vertex
{
	char label;
	Edge* edge_list;
} Vertex;
typedef struct Graph
{
	int num_vertices;
	char graph_type; //D is directed, U is undirected
	Vertex* vertices;
	int* label_to_index;
} Graph;

void add_vertex(Graph* graph, char label, int index)
{
	if (index >= graph->num_vertices) return;
	graph->vertices[index].label = label;
	graph->vertices[index].edge_list = NULL;
	graph->label_to_index[label - 'A'] = index;
}

Graph* create_graph(int num_vertices, char graph_type)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->num_vertices = num_vertices;
	graph->graph_type = graph_type;
	graph->vertices = (Vertex*)malloc(num_vertices*sizeof(Vertex));
	graph->label_to_index = (int*)malloc(sizeof(int)*num_vertices);
	for (int i = 0; i < num_vertices; i++)
	{
		graph->label_to_index[i] = -1;
	}
	return graph;
}

void add_edge(Graph* graph, char source_label, char target_label, int weight)
{
	int source_index = graph->label_to_index[source_label - 'A'];
	int target_index = graph->label_to_index[target_label - 'A'];
	
	if (source_index < 0 || target_index < 0) return;

	Edge* newEdge = (Edge*)malloc(sizeof(Edge));
	newEdge->target = target_index;
	newEdge->weight = weight;
	newEdge->next = graph->vertices[source_index].edge_list;
	graph->vertices[source_index].edge_list = newEdge;

	if (graph->graph_type == 'U')
	{
		Edge* undirected_edge = (Edge*)malloc(sizeof(Edge));
		undirected_edge->target = source_index;
		undirected_edge->weight = weight;
		undirected_edge->next = graph->vertices[target_index].edge_list;
		graph->vertices[target_index].edge_list = undirected_edge;
	}
}

void print_graph(Graph* graph)
{
	printf("-----------Here is the graph---------\n");
	for (int i = 0; i < ALPHABET; i++)
	{
		if (graph->label_to_index[i]!=-1)
		{
			Vertex vertex = graph->vertices[i];
			printf("Vertex %c: \n", vertex.label);
			Edge* edge = vertex.edge_list;
			while (edge)
			{
				printf(" ---> %c (Weight: %d)\n", graph->vertices[edge->target].label, edge->weight);
				edge = edge->next;
			}
			printf("\n");
		}
	}
}

//Main method, basically takes in cmd line arguements and runs the code
int main(int argc, char **argv)
{
	//not really sure how to do graphs yet, we shall see
	printf("XDDD\n");
	
	//Running 1 graph through the method, this is my test case until I make a makefile
	if (argc == 2)
	{
		printf("Testing 1 graph: \n");
		
		graph_test(argv[1]);
	}
	
	//This is the actual project program. This else if runs everything and asks if the user
	//wants to try seperate graphs.
	else if (argc == 5)
	{
		printf("Testing 4 (or more) different graphs for the algorithms.\n"
		"Below are the results for the class assignment: \n");
		
		//Running the graph_test file for each graph
		for (int i = 0; i < argc - 1; i++)
		{
			graph_test(argv[i]);
			// cp this to graphtest printf("\n------------------------------------------------------\n");
		}
		
		//asking the user if they want to try another graph they provided, i only provided 4 in my code
		_Bool wouldyouliketogoagain = 1; //True
		while (0)//wouldyouliketogoagain == 1)
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
		printf("Either somehow the make file messed up, you messed up, or i messed up.\n"
		"This error can only occur if 0, 2, or 3 command line arguements are used,\n"
		"which should not be possible given the fact I am having it run using a make file \n"
		"\n"
		"Please do the following commands to run the program so i can pass: \n"
		"gcc -o main main.c \n"
		"./main graph_file1 \n"
		"./main graph_file2 \n" 
		"./main graph_file3 \n"  
		"./main graph_file4 \n" 
		"\n"
		"Or you can email me at ajohn432@charlotte.edu and I can help :D. (I don't want to fail)");
	}
	return 0;
}

void graph_test(char *graph_name)
{
	FILE *f;
	f = fopen(graph_name, "r");
	
	//If file doesn't exist, gracefully exit the method. Should only happen on user inputted files.
	if (f == NULL)
	{
		printf("Somehow, the file %s was not found. This file will be skipped.\n", graph_name);
		perror(graph_name);
	}

	//The below loop creates an adjacency matrix that stores the graph
	//It is represented using a 2d array. Size is V x V (V is # of vertices)
	//
	//First i initialize the array using the given vertices #, and edges aren't important in this.
	//I allocate memory for it, then set everythint to 0, the fill it out using the loop mentioned earlier
	
	printf("test\n");
	//This is var declaration
	char buffer[20];
	char graphinfo[20];

	int num_vertices, num_edges;
	char type_of_graph;
	int index = 0;

	int weight;
	char source_label;
	char target_label;
	

	if (fgets(graphinfo, sizeof(graphinfo), f) == NULL)
	{
		printf("fgets had an error\n");
		return;
	}
	
	sscanf(graphinfo, "%d %d %c", &num_vertices, &num_edges, &type_of_graph);
	
	printf("%d %d %c", num_vertices, num_edges, type_of_graph);
	Graph* graph = create_graph(num_vertices, type_of_graph);

	for (int i = 0; i < num_edges; i++)
	{
		if (fgets(buffer, sizeof(buffer), f) == NULL)
		{
			printf("Why is there numbers adding to over 20 characters bruh i did not design this for that xddd");
			return;
		}
			
		sscanf(buffer, "%c %c %d", &source_label, &target_label, &weight);
			
		//adding new vertices
		if (graph->label_to_index[source_label - 'A'] == -1)
		{
			add_vertex(graph, source_label, index);
			index++;
		}
		if (graph->label_to_index[target_label - 'A'] == -1)
		{
			add_vertex(graph, source_label, index);
			index++;
		}
		//adding edge
		add_edge(graph, source_label, target_label, weight);
	}
	print_graph(graph);
}

