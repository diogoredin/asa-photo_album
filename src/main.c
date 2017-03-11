/******************************* ASA - Grupo 20 *******************************
** António Sarmento - 77906
** Diogo Redin      - 84711
*******************************************************************************/

/* C Libraries. Only the bare minimum, no need for clutter */
#include <stdio.h>
#include <stdlib.h>

/*************************** Auxiliary functions ******************************/
#define get_numbers(a, b) scanf("%d %d", a, b)


/*********************** Visit States & Graph Status **************************/
#define WHITE 0
#define BLACK 1
#define GREY 2

#define INSUFFICIENT 0
#define INCOHERENT 1
#define OKAY 2

/******************** Data structures and their "methods" *********************/

// Vertex Structure
#define Vertex int
#define new_vertex(a) a

// Graph Structure
typedef struct graph {

    int vertices;
	int edges;
	int status;

	// Stores the vertices with an edge
	int *vertices_connection_start;

	// Stores the end vertex of the edge
	int *vertices_connection_end;

	// Stores the end vertex of a next extra edge
	int *vertices_next_connection_end;

	// Stores the vertices visit state
	int *vertices_visit;

} Graph;

// Connects two vertices in the Graph
void connect_graph(Graph g, Vertex v1, Vertex v2) {

	// Vertex does't exist yet
	if ( g.vertices_connection_start[v1] == 0 ) {

		// Can't loop to itself
		if ( v1 != v2 ) {
			g.vertices_connection_start[v1] = v1;
			g.vertices_connection_end[v1] = v2;
			g.status = OKAY;
			// debug
			printf("%d to %d (==) %d to %d created\n", v1, v2,
			g.vertices_connection_start[v1], g.vertices_connection_end[v1]);

		} else {
			g.status = INSUFFICIENT;
		}

	// Vertex already exists
	} else {

		// Can't insert B->A if A->B
		if ( g.vertices_connection_start[v1] != v2 ) {
			g.vertices_next_connection_end[v1] = v2;
			g.status = OKAY;
			// debug
			printf("%d to %d (==) %d to %d created\n", v1, v2,
			g.vertices_connection_start[v1], g.vertices_next_connection_end[v1]);

		} else {
			g.status = INCOHERENT;
		}

	}

}

// Creates a new Graph
Graph new_graph(int num_v, int num_e) {

	Graph g;
	g.vertices = num_v;
	g.edges = num_e;
	g.status = INSUFFICIENT;

	// Stores the vertices with an edge and initializes them at 0
	g.vertices_connection_start = calloc(num_v, sizeof(int));

	// Stores the end vertex of the edge
	g.vertices_connection_end = malloc(num_e * sizeof(int));

	// Stores the end vertex of a next extra edge
	g.vertices_next_connection_end = malloc(num_e * sizeof(int));

	// Stores the vertices visit state
	g.vertices_visit = malloc(num_e * sizeof(unsigned char));

	// Connects the given Vertices
	for (int i = 0; i < num_e; i++) {
		int num1, num2;
		get_numbers(&num1, &num2);

		Vertex v1 = new_vertex(num1);
		Vertex v2 = new_vertex(num2);
		connect_graph(g, v1, v2);
	}

	return g;
}

// Examines a given graph and either returns an error message, or prints the graph
char *examine_graph(Graph g) {
	//if (g == NULL) { return "Nulo"; }

	// Checks graph's status and write the appropriate message
	if ( g.status == INCOHERENT ) {
		return "Incoerente";
	} else if ( g.status == INSUFFICIENT ) {
		return "Insuficiente";
	} else if ( g.status ==  OKAY ) {
		return "Okay";
		// TODO: Loop through our graph and print each of its value in order

	} else {
		printf("%d", g.status);
		return "Not Working";
	}
}

/************************ Algorithm-related functions *************************/
// TODO: Implement algorithm

/***************************** MAIN function **********************************/
int main(void) {

	// Grabbing number of pictures (Vertices) and connections (Edges)
	int num_v, num_e;
	get_numbers(&num_v, &num_e);

	// Initializing our graph
	Graph g = new_graph(num_v, num_e);
	
	// Applying algorithm
	// TODO: make function call to algorithm that receives our graph

	// Writing our result
	printf("%s\n", examine_graph(g));

	return 0;
}