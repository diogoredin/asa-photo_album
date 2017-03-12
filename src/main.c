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
	UNVISITED,
	VISITED
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

	Vertex *vertex;
	Vertex *node;
	Vertex *next_node;

	int *vertex_visit;

	Vertex *result;

} Graph;

// Connects two vertices in the Graph
void connect_graph(Graph g, Vertex v1, Vertex v2) {

	int node;

	// Vertex doesn't exist yet
	if ( g.vertex[v1] == 0 ) {

		// Creates node
		g.vertex[v1] = g.edges;
		g.node[g.edges] = v2;
		g.next_node[g.edges] = 0;

	// Vertex already exists
	} else {

		// Finds the first node with an available "next" position
		for ( 
			node = g.next_node[g.vertex[v1]]; 
			node != 0;
			node = g.next_node[node] );

		// Creates a new node and stores it on the node found
		g.node[g.edges] = v2;
		g.next_node[g.edges] = 0;
		g.next_node[node] = g.edges;

	}

}

// Creates a new Graph
Graph new_graph(int num_v, int num_e) {

	// Graph Data
	Graph g;
	g.vertices = num_v;

	// Stores the start, end and next vertex of an edge
	g.vertex = calloc(num_v, sizeof(Vertex));
	g.node = malloc(num_e * sizeof(Vertex));
	g.next_node = malloc(num_e * sizeof(Vertex));

	// Stores the vertex visit state
	g.vertex_visit = malloc(num_e * sizeof(unsigned char));

	// Stores the topological order of the graph
	g.result = malloc( (num_v+1) * sizeof(Vertex) );

	// Creates an edge between the given vertices
	for (g.edges = 0; g.edges < num_e; g.edges++) {
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

		// Goes through the result and displays it
		for (int v = 1; v <= g.vertices; v++) {
			printf("%d ", g.result[v]);
		}

		return "\n";
	}

}

/************************ Algorithm-related functions *************************/

/***************************** Tarjans Algorithm *****************************/

// Tarjans auxiliary function
void tarjans_visit(Graph g, Vertex v) {

	if ( v != g.vertices ) {

		tarjans_visit(g, g.node[g.vertex[v]] );

		if ( g.next_node[v] != 0 && g.vertex_visit[v] == UNVISITED ) {
			tarjans_visit(g, g.node[g.next_node[v]] );
		}

	}

	g.vertex_visit[v] = VISITED;
	g.result[v] = v;

}

// Tarjans Algorithm
void tarjans(Graph g) {

	for (int v = 1; v <= g.vertices; v++) {

		if ( g.vertex[v] != 0 && g.vertex_visit[v] == UNVISITED ) {
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
	//tarjans(g);

	// Writing our result
	printf("%s\n", examine_graph(g));

	return 0;
}