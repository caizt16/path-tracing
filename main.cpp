// Path tracer main.

using namespace std;
#include <iostream>
#include "stlreader.h"
#include "kdtree.h"

int main(int argc, char** argv) {
	cout << "=== snp's path tracing renderer ===" << endl;

	// Read in the input.
	vector<Triangle>* triangles = read_stl(argv[1]);
	if (triangles == nullptr) {
		cerr << "Couldn't read input file." << endl;
		return 1;
	}
	cout << "Read in " << triangles->size() << " triangles." << endl;

	// Build the kdTree.
	auto tree = new kdTree(triangles);

	int deepest = 0, biggest = 0;
	tree->root->get_stats(deepest, biggest);
	cout << "Depth of: " << deepest << " Size: " << biggest << endl;

	delete tree;
	delete triangles;

	return 0;
}

