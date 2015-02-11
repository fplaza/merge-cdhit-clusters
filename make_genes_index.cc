/*
 * (C) Copyright 2015 Enterome
 */

#include "make_genes_index.hh"
#include "cluster_reader.hh"

void make_genes_index(const std::vector<std::string>& initial_clusters_files, boost::unordered_map<std::string,uint32_t>& map_gene_id, std::vector<std::string>& all_genes)
{
	size_t num_genes = 0;
	for (std::vector<std::string>::const_iterator clusters_file = initial_clusters_files.begin(); clusters_file < initial_clusters_files.end(); clusters_file++)
	{
		Cluster cluster;
		ClusterReader cluster_reader(*clusters_file);
		while(cluster_reader.next_cluster(cluster))
		{
			num_genes += cluster.genes.size();
		}
	}

	map_gene_id.rehash(num_genes);
	all_genes.resize(num_genes);

	uint32_t id =0;
	for (std::vector<std::string>::const_iterator clusters_file = initial_clusters_files.begin(); clusters_file < initial_clusters_files.end(); clusters_file++)
	{
		Cluster cluster;
		ClusterReader cluster_reader(*clusters_file);
		while(cluster_reader.next_cluster(cluster))
		{
			for (std::vector<std::string>::const_iterator gene = cluster.genes.begin(); gene < cluster.genes.end(); gene++)
			{
				all_genes[id] = *gene;
				map_gene_id[*gene] = id;
				id++;
			}
		}
	}
}
