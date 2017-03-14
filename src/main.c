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
	// first_edge[vertex] -> Contains the number of the edge
	Edge *first_edge;

	// Edge Index -> Is the number of the edge
	// vertex[edge] -> Contains the number of the vertex of destination
	Vertex *vertex;

	// Next_Edge Index -> Is the number of the edge
	// Next_Edge[vertex] -> Contains the number of another edge that has the same origin
	Edge *next_edge;

	// Visit States of the Vertices (size: nr. of vertices)
	unsigned char *vertex_visit;

	// Discovery Times of the Vertices (size: nr. of vertices)
	int *vertex_discover;

	// First Vertex in the current DFS Link Search (size: nr. of vertices)
	int *vertex_finish;

	// An index corresponds to its predecessor
	Vertex *vertex_pi;

	// Topological Order of the Graph (size: nr. of vertices)
	Vertex *result;

} Graph;

// Connects two vertices in the Graph
void connect_graph(Graph *g, Vertex orig, Vertex dest) {
	// Vertex without any Edge
	if ( g->first_edge[orig] == 0 ) {
		// Stores it on the Vertex array
		g->first_edge[orig] = g->edges;
		g->vertex[g->edges] = dest;

	// Vertex with One or More Edges
	} else {
		// Last Edge created for this Vertex
		Edge find_edge = g->first_edge[orig];

		// Finds the vertex Edge with an available "next" edge position
		for (; g->next_edge[find_edge] != 0; find_edge = g->next_edge[find_edge]);

		// Stores it on the Edge Found
		g->vertex[g->edges] = dest;
		g->next_edge[find_edge] = g->edges;
	}
}

// Creates a new Graph
void init_graph(Graph *g, int num_v, int num_e) {
	// Graph Properties
	g->vertices = num_v;

	// Allocates memory for our Data Structures
	g->first_edge      = calloc(num_v+1, sizeof(g->first_edge));
	g->vertex          = malloc(num_e+1 *sizeof(g->vertex));
	g->next_edge       = calloc(num_e+1, sizeof(g->next_edge));
	g->vertex_visit    = calloc(num_v+1, sizeof(g->vertex_visit));
	g->vertex_discover = calloc(num_v+1, sizeof(g->vertex_discover));
	g->vertex_finish   = calloc(num_v+1, sizeof(g->vertex_finish));
	g->vertex_pi       = calloc(num_v+1, sizeof(g->vertex_pi));
	g->result          = malloc(num_v  * sizeof(g->result));

	// Creates an Edge between the given Vertices
	for (g->edges = 1; g->edges <= num_e; g->edges++) {
		int num1, num2;
		get_numbers(&num1, &num2);

		Vertex orig = new_vertex(num1);
		Vertex dest = new_vertex(num2);
		connect_graph(g, orig, dest);
	}
}

// Examines a given graph and either returns an error message, or prints the graph
const char *examine_graph(Graph *g) {

	// Goes through the result and displays it
	for (Vertex u = 1; u <= g->vertices; u = next_vertex(u)) {
		printf("VERTEX = %d;\n DISCOVER TIME = %d;\n FINISH TIME = %d;\n", u, g->vertex_discover[u], g->vertex_finish[u]);
	}

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

/***************************** DFS Algorithm ******************************/
int result_index = 0;

void dfs_visit(Graph *g, Vertex u, int *visited) {
	g->vertex_visit[u] = GREY;
	g->vertex_discover[u] = ++(*visited);

	for (Edge find_edge = g->first_edge[u]; find_edge != 0; find_edge = g->next_edge[find_edge]) {
		Vertex v = g->vertex[find_edge];
		if (g->vertex_visit[v] == WHITE) {
			g->vertex_pi[v] = u;
			dfs_visit(g, v, visited);
		}
	}

	visit(g, u);
	g->vertex_finish[u] = ++(*visited);
	g->result[result_index++] = u;
}

void dfs(Graph *g) {
	int visited = 0;
	for (Vertex u = 1; u <= g->vertices; u = next_vertex(u)) {
		if (g->vertex_visit[u] == WHITE) {
			dfs_visit(g, u, &visited);
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
	dfs(&g);

	// Writing our result
	printf("%s\n", examine_graph(&g));

	return 0;
}
