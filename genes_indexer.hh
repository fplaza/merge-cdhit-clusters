#ifndef GENES_INDEXER_HH
#define GENES_INDEXER_HH

/*
 * (C) Copyright 2015 Enterome
 */

#include <string>
#include <vector>
#include <stdint.h>
#include <boost/unordered_map.hpp>

class GenesIndexer
{
	public:
		GenesIndexer(const std::vector<std::string>& clusters_files);
		void make_index(boost::unordered_map<std::string,uint32_t>& map_gene_id, std::vector<std::string>& all_genes);

	private:
		const std::vector<std::string>& clusters_files_;

};

inline GenesIndexer::GenesIndexer(const std::vector<std::string>& clusters_files)
	: clusters_files_(clusters_files)
{}

#endif  // GENES_INDEXER_HH 
