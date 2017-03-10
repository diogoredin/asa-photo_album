/******************************* ASA - Grupo 20 *******************************
** António Sarmento - 77906
** Diogo Redin      - 84711
*******************************************************************************/

/* C Libraries. Only the bare minimum, no need for clutter */
#include <stdio.h>

/******************** Data structures and their "methods" *********************/
#define Vertex int
#define Graph  Vertex*

Graph new_graph(int num_v, int num_e) {
	// TODO: this depends on our implementation
	return NULL;
}

/*************************** Auxiliary functions ******************************/
#define get_numbers(a, b) scanf("%d %d", a, b)

char *get_result(Graph g, int size) {
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
	printf("%s\n", get_result(g, max_v));

	return 0;
}
