#ifndef CLUSTERS_PRINTER_HH
#define CLUSTERS_PRINTER_HH

/*
 * (C) Copyright 2015 Enterome
 */

#include <string>
#include <vector>
#include "cluster.hh"

class ClustersWriter
{
	public:
		ClustersWriter(const std::vector<Cluster>& clusters, const std::string& output_file);
		void print();

	private:
		const std::vector<Cluster>& clusters_;
		const std::string output_file_;
}; 

inline ClustersWriter::ClustersWriter(const std::vector<Cluster>& clusters, const std::string& output_file)
	: clusters_(clusters),
	output_file_(output_file)
{}

#endif // CLUSTERS_PRINTER_HH


