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

// Edge Structure
#define Edge int
#define new_edge(a) a

// Graph Structure
typedef struct graph {

	// Graph Properties
	int vertices;
	int edges;
	int status;

	// Vertex Index -> Is the number of the vertex of origin
	// Vertex[Index] -> Contains the number of the edge
	Vertex *vertex;

	// Edge Index -> Is the number of the edge
	// Edge[Index] -> Contains the number of the vertex of destination
	Edge *edge;

	// Next_Edge Index -> Is the number of the edge
	// Next_Edge[Index] -> Contains the number of another edge that has the same origin
	Edge *next_edge;

	// Stores the Visit States of the Vertices and the Topological Order of the Graph
	int *vertex_visit;
	Vertex *result;

} Graph;

// Connects two vertices in the Graph
void connect_graph(Graph g, Vertex orig, Vertex dest) {

	// Vertex without any Edge
	if ( g.vertex[orig] == 0 ) {

		// Creates Edge (orig -> dest)
		Edge edge = new_edge(dest);

		// Stores it on the Vertex array
		g.vertex[orig] = g.edges;
		g.edge[g.edges] = edge;
		g.next_edge[g.edges] = 0;

	// Vertex with One or More Edges
	} else {

		// Last Edge created for this Vertex
		Edge find_edge;

		// Finds the first Edge with an available "next" edge position
		for (
			find_edge = g.next_edge[g.vertex[orig]]; 
			find_edge != 0;
			find_edge = g.next_edge[find_edge] );

		// Creates Edge (orig -> dest)
		Edge edge = new_edge(dest);
	
		// Stores it on the Edge Found
		g.edge[g.edges] = edge;
		g.next_edge[g.edges] = 0;
		g.next_edge[find_edge] = g.edges;

	}

}

// Creates a new Graph
Graph new_graph(int num_v, int num_e) {

	// Graph Properties
	Graph g;
	g.vertices = num_v;

	// Allocates Space for our Data Structures
	g.vertex = calloc(num_v, sizeof(Vertex));
	g.edge = malloc(num_e * sizeof(Edge));
	g.next_edge = malloc(num_e * sizeof(Edge));
	g.vertex_visit = calloc(num_v, sizeof(int));
	g.result = malloc( (num_v+1) * sizeof(Vertex) );

	// Creates an Edge between the Given Vertices
	for (g.edges = 0; g.edges < num_e; g.edges++) {
		int num1, num2;
		get_numbers(&num1, &num2);

		Vertex orig = new_vertex(num1);
		Vertex dest = new_vertex(num2);
		connect_graph(g, orig, dest);
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
		for (int i = 0; i < g.vertices; i++) {
			printf("%d ", g.result[i]);
		}

		return "\n";
	}

}

/************************ Algorithm-related functions *************************/

/***************************** Tarjans Algorithm *****************************/

// Tarjans auxiliary function
void tarjans_visit(Graph g, Vertex v, int count) {

	Edge neighbour;

	if ( g.vertex_visit[v] == UNVISITED ) {
		
		// Goes through all neighbours of the Vertex
		for (
			neighbour = g.next_edge[g.vertex[v]]; 
			neighbour != 0;
			neighbour = g.next_edge[neighbour] ) {

				// Persues Path
				tarjans_visit(g, g.edge[neighbour], count++);

			}
	
		// Marks as visited
		g.vertex_visit[v] = VISITED;
		g.result[count] = v;
	
	} else {
		g.status = INCOHERENT;
	}

}

// Tarjans Algorithm
void tarjans(Graph g) {

	int count = 0;

	for (int v = 1; v <= g.vertices; v++) {
		tarjans_visit(g, v, count++);
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