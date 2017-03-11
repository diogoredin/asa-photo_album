/******************************* ASA - Grupo 20 *******************************
** António Sarmento - 77906
** Diogo Redin      - 84711
*******************************************************************************/

/* C Libraries. Only the bare minimum, no need for clutter */
#include <stdio.h>
#include <stdlib.h>

/*************************** Auxiliary functions ******************************/
#define get_numbers(a, b) scanf("%d %d", a, b)

/******************** Data structures and their "methods" *********************/
// FIXME: These data structures (and "methods") are NOT final.
#define Vertex int
#define Graph  Vertex*

// Creates a new vertex and returns it
#define new_vertex(a) a

// Connects two vertices in the graph (and inserts them if they're not there)
void connect_graph(Graph g, Vertex v1, Vertex v2) {
	// TODO: depends on our data structures implementation
}

Graph new_graph(int num_v, int num_e) {
	Graph g = malloc(num_v * sizeof(g));

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
char *examine_graph(Graph g, int size) {
	if (g == NULL) { return "Nulo"; }

	// TODO: check graph's status and write the appropriate message
	if (1) {
		return "Incoerente";
	} else if (2) {
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
	printf("%s\n", examine_graph(g, num_v));

	return 0;
}
