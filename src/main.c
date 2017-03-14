/******************************* ASA - Grupo 20 *******************************
** António Sarmento - 77906
** Diogo Redin      - 84711
*******************************************************************************/

/* C Libraries. Only the bare minimum, no need for clutter */
#include <stdio.h>
#include <stdlib.h>

/*************************** Auxiliary functions ******************************/
#define get_numbers(a, b) scanf("%d %d", a, b)
#define min(a,b) ((a) < (b) ? a : b)

/*********************** Visit States & Graph Status **************************/
enum visitStates {
	WHITE = 0,
	GREY,
	BLACK
};

enum graphStatus {
	CORRECT = 0,
	INSUFFICIENT,
	INCOHERENT
};

/******************** Data structures and their "methods" *********************/

// Vertex Structure
typedef int Vertex;
#define new_vertex(a) a
#define next_vertex(a) a+1
#define visit(graph, vertex) (graph->vertex_visit[vertex] = BLACK)
#define is_visited(graph, vertex) (graph->vertex_visit[vertex] == BLACK)

// Edge Structure
typedef int Edge;
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

	// Visit States of the Vertices (size: nr. of vertices)
	unsigned char *vertex_visit;

	// Discovery Times of the Vertices (size: nr. of vertices)
	int *vertex_time;

	// First Vertex in the current DFS Link Search (size: nr. of vertices)
	int *vertex_low;

	// Topological Order of the Graph (size: nr. of vertices)
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
	g->vertex_time = calloc(num_v, sizeof(g->vertex_time));
	g->vertex_low = calloc(num_v, sizeof(g->vertex_low));
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
		for (int i = 1; i <= g->vertices; i++) {
			printf("%d ", g->result[i]);
		}

		return "";
	}

}

/***************************** Tarjans Algorithm ******************************/

// Tarjans auxiliary function
void tarjans_visit(Graph *g, Vertex u, int* visited) {

	Edge v;

	// Marks Vertex as part of this Solution
	g->vertex_visit[u] = GREY;
	g->vertex_time[u] = *visited;
	g->vertex_low[u] = *visited;

	// One Vertex Visited
	(*visited)++;

	// Goes through all neighbours of the Vertex
	for (
		v = g->next_edge[g->vertex[u]];
		v != 0;
		v = g->next_edge[v] ) {

			// Neighbour hasn't been visited
			if ( !is_visited(g, v) ) {

				// Pursues Path if neighbour is part of the Solution
				if ( g->vertex_visit[v] == WHITE ) {
					tarjans_visit(g, g->edge[v], visited);
				}
				g->vertex_low[u] = min(	g->vertex_low[v], 
										g->vertex_low[u] );

			}

		}
	
	printf("visited (%d): %d\n time: %d\n low: %d\n", 
	u, *visited, g->vertex_time[u], g->vertex_low[u]);

	// If time of discovery = time of the lowest its SCC
	if ( g->vertex_time[u] == g->vertex_low[u] ) {
		visit(g, u);
		g->result[*visited] = u;
	}

}

// Tarjans Algorithm
void tarjans(Graph *g) {

	int visited = 0;

	for (Vertex v = 1; v <= g->vertices; v = next_vertex(v)) {
		if ( !is_visited(g, v) ) {
			tarjans_visit(g, v, &visited);
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
