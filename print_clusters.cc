/*
 * (C) Copyright 2015 Enterome
 */

#include "print_clusters.hh"
#include <fstream>

void print_clusters(const std::vector<Cluster>& clusters, const std::string& output_file)
{
	std::ofstream ofs;
	ofs.open(output_file.c_str());

	for (std::vector<Cluster>::const_iterator cluster_it = clusters.begin(); cluster_it != clusters.end(); cluster_it++)
		ofs << *cluster_it;


	ofs.close();
}
