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
	Vertex *start_vertex;
	Vertex *end_vertex;
	Vertex *next_vertex;

	// Stores the vertex visit state
	int *vertex_visit;

	// Stores the topological order of the graph
	int *result;

} Graph;

// Connects two vertices in the Graph
void connect_graph(Graph g, Vertex v1, Vertex v2) {

	// Vertex doesn't exist yet
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
	g.start_vertex = calloc(num_v, sizeof(Vertex));
	g.end_vertex = malloc(num_e * sizeof(Vertex));
	g.next_vertex = malloc(num_e * sizeof(Vertex));

	// Stores the vertex visit state
	g.vertex_visit = malloc(num_e * sizeof(unsigned char));

	// Stores the topological order of the graph
	g.result = malloc(num_v * sizeof(Vertex));

	// Connects the given vertices
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
		return (char*) g.result;
	}

}

/************************ Algorithm-related functions *************************/

/***************************** Tarjans Algorithm *****************************/

// Tarjans auxiliary function
void tarjans_visit(Graph g, Vertex v) {

	// Apply for
	//tarjans_visit(g, g.end_vertex[g.start_vertex[v]] );
	//tarjans_visit(g, g.start_vertex[g.next_vertex[v]] );

	g.vertex_visit[v] = BLACK;
	g.result[v] = v;

}

// Tarjans Algorithm
void tarjans(Graph g) {

	for (int v = 0; v < g.vertices; v++) {

		if ( g.start_vertex[v] != 0 && g.vertex_visit[v] == WHITE ) {
			tarjans_visit(g, v);
		}

	}

}

/***************************** MAIN function **********************************/

int main(void) {

	// Grabbing number of pictures (Vertices) and connections (Edges)
	int num_v, num_e;
	get_numbers(&num_v, &num_e);

	// Initializing our graph
	Graph g = new_graph(num_v, num_e);

	// Applying algorithm
	tarjans(g);

	// Writing our result
	printf("%s\n", examine_graph(g));

	return 0;
}