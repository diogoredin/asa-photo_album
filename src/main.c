/******************************* ASA - Grupo 20 *******************************
** António Sarmento - 77906
** Diogo Redin      - 84711
*******************************************************************************/

/* C Libraries. Only the bare minimum, no need for clutter */
#include <stdio.h>

/*************************** Auxiliary functions ******************************/
#define get_numbers(a, b) scanf("%d %d", a, b)

/******************** Data structures and their "methods" *********************/
// FIXME: These "defines" are NOT final.
#define Vertex int
#define Graph  Vertex*

#define new_vertex(a) a

Graph new_graph(int num_v, int num_e) {
	Graph g = malloc(num_v * sizeof(g));

	for (int i = 0; i < num_e; i++) {
		int num1, num2;
		get_numbers(&num1, &num2);

		Vertex vertex1 = new_vertex(num1);
		Vertex vertex2 = new_vertex(num2);

		// TODO: Insert these vertices into our graph
	}

	return g;
}

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
	int max_v, max_e;
	get_numbers(&max_v, &max_e);

	// Initializing our graphs
	Graph g = new_graph(max_v, max_e);

	// Applying algorithm
	// TODO: make function call to algorithm that receives our graph

	// Writing our result
	printf("%s\n", examine_graph(g, max_v));

	return 0;
}
