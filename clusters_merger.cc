/*
 * (C) Copyright 2015 Enterome
 */

#include "clusters_merger.hh"
#include <boost/pending/disjoint_sets.hpp>
#include "cluster_reader.hh"
#include <iostream>

std::vector<Cluster> ClustersMerger::merge()
{
	// Create one set per gene
	size_t num_genes = all_genes_.size();
	std::vector<uint32_t> rank(num_genes);
	std::vector<uint32_t> parent(num_genes);

	boost::disjoint_sets<uint32_t*,uint32_t*> ds(rank.data(), parent.data());

	for (uint32_t i = 0; i < num_genes; ++i)
		ds.make_set(i);

	// Merge genes by single linkage
	for (std::vector<std::string>::const_iterator clusters_it = all_clusters_files_.begin(); clusters_it != all_clusters_files_.end(); ++clusters_it)
	{
		Cluster cluster;
		ClusterReader cluster_reader(*clusters_it);
		while(cluster_reader.next_cluster(cluster))
		{
			// We consider the first gene in the cluster as its representative
			const std::string& gene1  = cluster.genes[0];
			const uint32_t gene1_id = map_gene_id_.at(gene1);

			// Link all the others genes to the cluster representative
			// Because it is recursive, it 'flattens' the clusters in a unique one
			for (size_t i = 1; i < cluster.genes.size(); i++)
			{
				const std::string& gene2  = cluster.genes[i];
				const uint32_t gene2_id = map_gene_id_.at(gene2);

				ds.union_set(gene1_id, gene2_id);
			}
		}
	}


	std::vector<Cluster> merged_clusters = ClusterReader(final_clusters_file_).read_all();

	// Associate each representative to a final cluster
	boost::unordered_map<uint32_t, Cluster*> map_representative_cluster;
	map_representative_cluster.rehash(merged_clusters.size());
	for (std::vector<Cluster>::iterator cluster = merged_clusters.begin(); cluster != merged_clusters.end(); ++cluster)
	{
		const std::string cluster_representative = cluster->genes[0];
		const uint32_t cluster_representative_id = ds.find_set(map_gene_id_.at(cluster_representative));
		map_representative_cluster[cluster_representative_id] = &(*cluster);
		cluster->genes.clear();
	}

	// Place each gene into a cluster thanks to its representative
	for (uint32_t gene_id = 0; gene_id < all_genes_.size(); ++gene_id)
	{
		const std::string& gene = all_genes_[gene_id];
		uint32_t gene_representative_id = ds.find_set(gene_id);

		boost::unordered_map<uint32_t, Cluster*>::const_iterator it = map_representative_cluster.find(gene_representative_id);

		// Gene has to be inserted in a cluster
		if (it != map_representative_cluster.end())
		{
			Cluster* gene_cluster = it->second;
			gene_cluster->genes.push_back(gene);
		}
	}

	return merged_clusters;
}

