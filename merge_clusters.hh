#ifndef MERGE_CLUSTERS_HH
#define MERGE_CLUSTERS_HH

/*
 * (C) Copyright 2015 Enterome
 */

#include <string>
#include <vector>
#include <boost/unordered_map.hpp>
#include "cluster.hh"

std::vector<Cluster> merge_clusters(const std::vector<std::string>& all_clusters_files, const std::string& final_clusters_file, const boost::unordered_map<std::string,uint32_t>& map_gene_id, const std::vector<std::string>& all_genes);

#endif // MERGE_CLUSTERS_HH
