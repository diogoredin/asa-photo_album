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
enum visitStates {
	WHITE,
	BLACK,
	GREY
};

enum graphStatus {
	INSUFFICIENT,
	INCOHERENT
};

/******************** Data structures and their "methods" *********************/

// Vertex Structure
#define Vertex int
#define new_vertex(a) a

// Graph Structure
typedef struct graph {

    int vertices;
	int edges;
	int status;

	// Stores the start, end and next vertex of an edge
	int *start_vertex;
	int *end_vertex;
	int *next_vertex;

	// Stores the vertex visit state
	int *vertex_visit;

} Graph;

// Connects two vertices in the Graph
void connect_graph(Graph g, Vertex v1, Vertex v2) {

	// Vertex does't exist yet
	if ( g.start_vertex[v1] == 0 ) {
		g.start_vertex[v1] = v1;
		g.end_vertex[v1] = v2;

	// Vertex already exists
	} else {
		g.next_vertex[v1] = v2;
	}

}

// Creates a new Graph
Graph new_graph(int num_v, int num_e) {

	// Graph Data
	Graph g;
	g.vertices = num_v;
	g.edges = num_e;

	// Stores the start, end and next vertex of an edge
	g.start_vertex = calloc(num_v, sizeof(int));
	g.end_vertex = malloc(num_e * sizeof(int));
	g.next_vertex = malloc(num_e * sizeof(int));

	// Stores the vertex visit state
	g.vertex_visit = malloc(num_e * sizeof(unsigned char));

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
	} else {
		// TODO: Loop through our graph and print each of its value in order
		return "";
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