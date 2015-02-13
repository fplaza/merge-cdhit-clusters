/*
 * (C) Copyright 2015 Enterome
 */

#include "genes_indexer.hh"
#include "cluster_reader.hh"

void GenesIndexer::make_index(boost::unordered_map<std::string,uint32_t>& map_gene_id, std::vector<std::string>& all_genes)
{
	// Count the total number of genes to avoid rehashing
	size_t num_genes = 0;
	for (std::vector<std::string>::const_iterator clusters_file_it = clusters_files_.begin(); clusters_file_it < clusters_files_.end(); ++clusters_file_it)
	{
		Cluster cluster;
		ClusterReader cluster_reader(*clusters_file_it);
		while(cluster_reader.next_cluster(cluster))
		{
			num_genes += cluster.genes.size();
		}
	}

	map_gene_id.rehash(num_genes);
	all_genes.resize(num_genes);

	// Index all the genes by assigning them a number
	// It is faster to manipulate integers than strings
	uint32_t id =0;
	for (std::vector<std::string>::const_iterator clusters_file_it = clusters_files_.begin(); clusters_file_it < clusters_files_.end(); ++clusters_file_it)
	{
		Cluster cluster;
		ClusterReader cluster_reader(*clusters_file_it);
		while(cluster_reader.next_cluster(cluster))
		{
			for (std::vector<std::string>::const_iterator gene = cluster.genes.begin(); gene < cluster.genes.end(); ++gene)
			{
				all_genes[id] = *gene;
				map_gene_id[*gene] = id;
				++id;
			}
		}
	}
}
