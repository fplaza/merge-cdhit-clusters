#ifndef CLUSTERS_MERGER_HH
#define CLUSTERS_MERGER_HH

/*
 * (C) Copyright 2015 Enterome
 */

#include <string>
#include <vector>
#include <boost/unordered_map.hpp>
#include "cluster.hh"

class ClustersMerger
{
	public:
		ClustersMerger(const std::vector<std::string>& all_clusters_files, const std::string& final_clusters_file, const boost::unordered_map<std::string,uint32_t>& map_gene_id, const std::vector<std::string>& all_genes);
		std::vector<Cluster> merge();

	private:
		const std::vector<std::string> all_clusters_files_;
		const std::string final_clusters_file_;
		const boost::unordered_map<std::string,uint32_t>& map_gene_id_;
		const std::vector<std::string>& all_genes_;
};

inline ClustersMerger::ClustersMerger(const std::vector<std::string>& all_clusters_files, const std::string& final_clusters_file, const boost::unordered_map<std::string,uint32_t>& map_gene_id, const std::vector<std::string>& all_genes):
	all_clusters_files_(all_clusters_files),
	final_clusters_file_(final_clusters_file),
	map_gene_id_(map_gene_id),
	all_genes_(all_genes)
{}

#endif // CLUSTERS_MERGER_HH
