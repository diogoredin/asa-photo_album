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
enum graphStatus {
	CORRECT = 0,
	INCOHERENT,
	INSUFFICIENT,
};

/******************** Data structures and their "methods" *********************/

// Global queue
struct queue {
	int *data;
	int front, rear;
} Queue;
#define new_queue(size) Queue.data = malloc(size * sizeof(Queue.data)); Queue.front=0; Queue.rear=0
#define enqueue(a)      Queue.data[Queue.rear++] = a
#define dequeue()       Queue.data[Queue.front++]
#define is_empty()     (Queue.front == Queue.rear)
#define destroy_queue() free(Queue.data = NULL)

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

	Vertex *indegree;
	Vertex *result;

} Graph;

// Connects two Vertices
void connect_graph(Graph *g, Vertex a, Vertex b) {

	Edge edge = new_edge(b);
	g->vertex[g->nr_edges] = edge;
	g->indegree[b]++;

	if ( g->first[a] == 0 ) {
		g->first[a] = g->nr_edges;

	} else {

		Edge find_edge;

		for ( find_edge = g->first[a]; g->next[find_edge] != 0; find_edge = g->next[find_edge] );
		g->next[find_edge] = g->nr_edges;

	}

}

// Creates a new Graph
void init_graph(Graph *g, int num_v, int num_e) {

	g->nr_vertices = num_v;
	g->status      = INCOHERENT;

	g->first  = calloc((num_v+1), sizeof(g->first));
	g->vertex = calloc((num_e+1), sizeof(g->vertex));
	g->next   = calloc((num_e+1), sizeof(g->next));

	g->indegree = calloc((num_v+1), sizeof(g->indegree));
	g->result 	= malloc(num_v    * sizeof(g->result));

	for (g->nr_edges = 1; g->nr_edges <= num_e; g->nr_edges++) {
		int num1, num2;
		get_numbers(&num1, &num2);

		Vertex a = new_vertex(num1);
		Vertex b = new_vertex(num2);
		connect_graph(g, a, b);
	}

	// Adds all orphans to Queue
	new_queue(num_v);
	for (Vertex u = 1; u <= g->nr_vertices; u = next_vertex(u)) {
		if (g->indegree[u] == 0) {
			enqueue(u);
		}
	}

}

void destroy_graph(Graph *g) {
	free(g->first = NULL);
	free(g->vertex = NULL);
	free(g->next = NULL);
	free(g->indegree = NULL);
	free(g->result = NULL);
}

// Examines Graph
const char *examine_graph(Graph *g) {

	switch ( g->status ) {

	case INCOHERENT:
		return "Incoerente";

	case INSUFFICIENT:
		return "Insuficiente";

	default:
		for (int i = 0; i < g->nr_vertices; i++ ) {
			printf("%d", g->result[i]);
			if (i+1 < g->nr_vertices) { printf(" "); }
		}
		return "";
	}

}

/************************* Vertex "Deletion" Algorithm ***************************/
void graph_sort(Graph *g) {

	int count = 0;

	while ( !is_empty() ) {
		Vertex u = dequeue();
		g->result[count++] = u;

		if ( g->indegree[u] == 0 ) {

			Edge find_son;
			int indegree_temp = 0;

			for ( find_son = g->first[u];
				  find_son != 0 && indegree_temp != g->indegree[g->vertex[find_son]];
				  find_son = g->next[find_son] ) {

				Vertex v = g->vertex[find_son];
				indegree_temp = g->indegree[v]--;

				if ( g->indegree[v] == 0 ) {
					enqueue(v);
				}
			}

			if ( indegree_temp == g->indegree[g->vertex[find_son]] ) {
				g->status = INSUFFICIENT;
			}

		}

	}

	if ( ( count == g->nr_vertices ) && ( g->status = INSUFFICIENT ) ) {
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

	destroy_graph(&g);
	destroy_queue();
	return 0;
}
