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
		cluster clstr;
		cluster_reader reader(*clusters_file);
		while(reader.next_cluster(clstr))
		{
			num_genes += clstr.genes.size();
		}
	}

	map_gene_id.rehash(num_genes);
	all_genes.resize(num_genes);

	uint32_t id =0;
	for (std::vector<std::string>::const_iterator clusters_file = initial_clusters_files.begin(); clusters_file < initial_clusters_files.end(); clusters_file++)
	{
		cluster clstr;
		cluster_reader reader(*clusters_file);
		while(reader.next_cluster(clstr))
		{
			for (std::vector<std::string>::const_iterator gene = clstr.genes.begin(); gene < clstr.genes.end(); gene++)
			{
				all_genes[id] = *gene;
				map_gene_id[*gene] = id;
				id++;
			}
		}
	}
}
