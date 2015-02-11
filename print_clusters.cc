#include "print_clusters.hh"
#include <fstream>

void print_clusters(const std::vector<cluster>& clusters, const std::string& output_file)
{
	std::ofstream ofs;
	ofs.open(output_file.c_str());

	for (std::vector<cluster>::const_iterator clstr = clusters.begin(); clstr != clusters.end(); clstr++)
		ofs << *clstr;


	ofs.close();
}
