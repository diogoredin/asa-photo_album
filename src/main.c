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
enum orphanVertex {
	YES = 0,
	NO
};

enum graphStatus {
	UNINITIALIZED = 0,
	CORRECT,
	INSUFFICIENT,
	INCOHERENT
};

/******************** Data structures and their "methods" *********************/

// Vertex Structure
typedef int Vertex;
#define new_vertex(a) a
#define next_vertex(a) a + 1

// Edge Structure
typedef int Edge;
#define new_edge(a) a

// Graph Structure
typedef struct graph {

	int nr_vertices;
	int nr_edges;
	int status;

	Edge *first;    // first[Vertex] = Edge
	Vertex *vertex; // vertex[Edge]  = Vertex
	Edge *next;     // next[Edge]    = Edge

	Vertex *orphan;
	Vertex *result;

} Graph;

// Connects two Vertices
void connect_graph(Graph *g, Vertex a, Vertex b) {

	Edge edge = new_edge(b);
	g->vertex[g->nr_edges] = edge;

	if ( g->first[a] == 0 ) {
		g->first[a] = g->nr_edges;

	} else {

		Edge find_edge;

		for ( find_edge = g->first[a]; find_edge != 0; find_edge = g->next[find_edge] );
		g->next[find_edge] = g->nr_edges;
		g->orphan[b] = NO;

	}

}

// Creates a new Graph
void init_graph(Graph *g, int num_v, int num_e) {

	g->nr_vertices = num_v;
	g->status      = UNINITIALIZED;

	g->first  = calloc((num_v+1), sizeof(g->first));
	g->vertex = calloc((num_e+1), sizeof(g->vertex));
	g->next   = calloc((num_e+1), sizeof(g->next));

	g->orphan = calloc((num_v+1), sizeof(g->orphan));
	g->result = malloc(num_v    * sizeof(g->result));

	for (g->nr_edges = 1; g->nr_edges <= num_e; g->nr_edges++) {
		int num1, num2;
		get_numbers(&num1, &num2);

		Vertex a = new_vertex(num1);
		Vertex b = new_vertex(num2);
		connect_graph(g, a, b);
	}

}

// Examines Graph
const char *examine_graph(Graph *g) {

	switch ( g->status ) {
	case UNINITIALIZED:
		return "Nulo";

	case INCOHERENT:
		return "Incoerente";

	case INSUFFICIENT:
		return "Insuficiente";

	case CORRECT:
		for (int i = 0; i < g->nr_vertices; i++ ) {
			printf("%d", g->result[i]);
			if (i+1 < g->nr_vertices) { printf(" "); }
		}
		return "";

	default:
		return "Erro";
	}

}

/************************* Vertex "Deletion" Algorithm ***************************/
void graph_sort(Graph *g) {

	int count = 0;

	for ( Vertex v = 1; v <= g->nr_vertices; v++ ) {

		if ( g->orphan[v] == YES ) {
			g->result[count++] = v;

			for ( Edge find_son = g->first[v]; find_son != 0; find_son = g->next[find_son] ) {
				g->orphan[g->vertex[find_son]] = YES;
			}
		}

	}

	// FIXME: THIS IS UTTERLY, COMPLETELY WRONG!!!
	if ( count == g->nr_vertices ) {
		g->status = CORRECT;
	}

}

/***************************** MAIN function **********************************/
int main(void) {

	int num_v, num_e;
	get_numbers(&num_v, &num_e);

	Graph g;
	init_graph(&g, num_v, num_e);

	graph_sort(&g);

	printf("%s\n", examine_graph(&g));

	return 0;
}
