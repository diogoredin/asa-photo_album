/******************************* ASA - Grupo 20 *******************************
** António Sarmento - 77906
** Diogo Redin      - 84711
*******************************************************************************/

/* C Libraries. Only the bare minimum, no need for clutter */
#include <stdio.h>
#include <stdlib.h>

/*************************** Auxiliary functions ******************************/
#define get_numbers(a, b) scanf("%d %d", a, b)
#define max(a,b) ((a) > (b) ? a : b)
#define min(a,b) ((a) < (b) ? a : b)

/*********************** Visit States & Graph Status **************************/
enum visitStates {
	WHITE = 0,
	GREY,
	BLACK
};

enum graphStatus {
	INSUFFICIENT = 0,
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
	unsigned char *vertex_visit;
	Vertex *result;

} Graph;

// Connects two vertices in the Graph
void connect_graph(Graph *g, Vertex orig, Vertex dest) {

	// Vertex without any Edge
	if ( g->vertex[orig] == 0 ) {

		// Creates Edge (orig -> dest)
		Edge edge = new_edge(dest);

		// Stores it on the Vertex array
		g->vertex[orig] = g->edges;
		g->edge[g->edges] = edge;

	// Vertex with One or More Edges
	} else {

		// Last Edge created for this Vertex
		Edge find_edge;

		// Finds the first Edge with an available "next" edge position
		for (
			find_edge = g->next_edge[g->vertex[orig]];
			find_edge != 0;
			find_edge = g->next_edge[find_edge] );

		// Creates Edge (orig -> dest)
		Edge edge = new_edge(dest);

		// Stores it on the Edge Found
		g->edge[g->edges] = edge;
		g->next_edge[find_edge] = g->edges;

	}

}

// Creates a new Graph
void init_graph(Graph *g, int num_v, int num_e) {

	// Graph Properties
	g->vertices = num_v;

	// Allocates memory for our Data Structures
	g->vertex       = calloc(num_v, sizeof(g->vertex));
	g->edge         = malloc(num_e * sizeof(g->edge));
	g->next_edge    = calloc(num_e, sizeof(g->next_edge));
	g->vertex_visit = calloc(num_v, sizeof(g->vertex_visit));
	g->result       = malloc((num_v+1) * sizeof(g->result));

	// Creates an Edge between the given Vertices
	for (g->edges = 0; g->edges < num_e; g->edges++) {
		int num1, num2;
		get_numbers(&num1, &num2);

		Vertex orig = new_vertex(num1);
		Vertex dest = new_vertex(num2);
		connect_graph(g, orig, dest);
	}
}

// Examines a given graph and either returns an error message, or prints the graph
char *examine_graph(Graph *g) {

	// Checks graph's status and write the appropriate message
	if ( g->status == INCOHERENT ) {
		return "Incoerente";
	} else if ( g->status == INSUFFICIENT ) {
		return "Insuficiente";
	} else {

		// Goes through the result and displays it
		for (int i = 0; i < g->vertices; i++) {
			printf("%d ", g->result[i]);
		}

		return "";
	}

}

/************************ Algorithm-related functions *************************/

/***************************** Tarjans Algorithm *****************************/

// Tarjans auxiliary function
void tarjans_visit(Graph *g, Vertex v, int index) {

	Edge neighbour;

	// Stores the Vertex Index
	int low_index = index;

	// Marks Vertex as part of this Solution
	g->vertex_visit[v] = BLACK;

	// Goes through all neighbours of the Vertex
	for (
		neighbour = g->next_edge[g->vertex[v]];
		neighbour != 0;
		neighbour = g->next_edge[neighbour] ) {

			// Neighbour hasn't been visited
			if ( g->vertex_visit[v] == WHITE ) {

				// Persues Path
				tarjans_visit(g, g->edge[neighbour], index++);
				low_index = min(low_index, index);

			}

			// Neighbour is part of the Solution
			else if ( g->vertex_visit[v] == BLACK ) {

				// Stop!
				low_index = min(low_index, index);

			}

		}

	// Marks as visited
	g->vertex_visit[v] = GREY;
	g->result[index] = v;

}

// Tarjans Algorithm
void tarjans(Graph *g) {

	int index = 0;

	for (int v = 1; v <= g->vertices; v++) {
		if ( g->vertex_visit[v] == WHITE || g->vertex_visit[v] == BLACK ) {
			tarjans_visit(g, v, index++);
		}
	}

}

/***************************** MAIN function **********************************/

int main(void) {

	// Grabbing number of pictures (Vertices) and connections (Edges)
	int num_v, num_e;
	get_numbers(&num_v, &num_e);

	// Initializing our graph
	Graph g;
	init_graph(&g, num_v, num_e);

	// Applying algorithm
	tarjans(&g);

	// Writing our result
	printf("%s\n", examine_graph(&g));

	return 0;
}
