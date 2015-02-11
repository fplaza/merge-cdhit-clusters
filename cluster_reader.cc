/*
 * (C) Copyright 2015 Enterome
 */

#include "cluster_reader.hh"

std::vector<cluster> cluster_reader::read_all()
{
	std::vector<cluster> all_clusters;
	all_clusters.reserve(1000000);

	cluster clstr;
	while(next_cluster(clstr))
		all_clusters.push_back(clstr);

	return all_clusters;
}
