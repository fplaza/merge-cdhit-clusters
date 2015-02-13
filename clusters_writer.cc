/*
 * (C) Copyright 2015 Enterome
 */

#include "clusters_writer.hh"
#include <fstream>

void ClustersWriter::write()
{
	std::ofstream ofs;
	ofs.open(output_file_.c_str());

	for (std::vector<Cluster>::const_iterator cluster_it = clusters_.begin(); cluster_it != clusters_.end(); ++cluster_it)
		ofs << *cluster_it;


	ofs.close();
}
