/*
 * (C) Copyright 2015 Enterome
 */

#include "merge_clusters.hh"
#include <boost/pending/disjoint_sets.hpp>
#include "cluster_reader.hh"
#include <iostream>

std::vector<cluster> merge_clusters(const std::vector<std::string>& all_clusters_files, const std::string& final_clusters_file, const boost::unordered_map<std::string,uint32_t>& map_gene_id, const std::vector<std::string>& all_genes)
{

	// Create one set per gene
	size_t num_genes = all_genes.size();
	std::vector<uint32_t> rank(num_genes);
	std::vector<uint32_t> parent(num_genes);

	boost::disjoint_sets<uint32_t*,uint32_t*> ds(rank.data(), parent.data());

	for (uint32_t i = 0; i < num_genes; i++)
		ds.make_set(i);

	// Merge genes by single linkage
	for (std::vector<std::string>::const_iterator clusters_file = all_clusters_files.begin(); clusters_file != all_clusters_files.end(); clusters_file++)
	{
		cluster clstr;
		cluster_reader reader(*clusters_file);
		while(reader.next_cluster(clstr))
		{
			const std::string& gene1  = clstr.genes[0];
			const uint32_t gene1_id = map_gene_id.at(gene1);

			for (size_t i = 1; i < clstr.genes.size(); i++)
			{
				const std::string& gene2  = clstr.genes[i];
				const uint32_t gene2_id = map_gene_id.at(gene2);

				ds.union_set(gene1_id, gene2_id);
			}
		}
	}


	std::vector<cluster> merged_clusters = cluster_reader(final_clusters_file).read_all();

	// Associate each representative to a final cluster
	boost::unordered_map<uint32_t, cluster*> map_representative_cluster;
	map_representative_cluster.rehash(merged_clusters.size());
	for (std::vector<cluster>::iterator cluster = merged_clusters.begin(); cluster != merged_clusters.end(); cluster++)
	{
		const std::string cluster_representative = cluster->genes[0];
		const uint32_t cluster_representative_id = ds.find_set(map_gene_id.at(cluster_representative));
		map_representative_cluster[cluster_representative_id] = &(*cluster);
		cluster->genes.clear();
	}


	for (uint32_t gene_id = 0; gene_id < all_genes.size(); gene_id++)
	{
		const std::string& gene = all_genes[gene_id];
		uint32_t gene_representative_id = ds.find_set(gene_id);

		boost::unordered_map<uint32_t, cluster*>::const_iterator it = map_representative_cluster.find(gene_representative_id);

		// Gene has to be inserted in a cluster
		if (it != map_representative_cluster.end())
		{
			cluster* gene_cluster = it->second;
			gene_cluster->genes.push_back(gene);
		}
	}

	return merged_clusters;
}

