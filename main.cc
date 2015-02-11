/*
 * (C) Copyright 2015 Enterome
 */

#include <iostream>
#include "parameters.hh"
#include "make_genes_index.hh"
#include "merge_clusters.hh"
#include "print_clusters.hh"

int main(int argc, char* argv[])
{
	const Parameters& pars = Parameters::parse_cmd_line(argc, argv);

	std::cout << "Indexing genes..." << std::endl;
	boost::unordered_map<std::string, uint32_t> map_gene_id;
	std::vector<std::string> all_genes;
	make_genes_index(pars.initial_clusters_files, map_gene_id, all_genes);
	std::cout << "Done. " << all_genes.size() << " genes indexed.\n" <<  std::endl;

	std::cout << "Merging clusters" << std::endl;
	const std::vector<Cluster> merged_clusters = merge_clusters(pars.all_clusters_files, pars.final_clusters_file, map_gene_id, all_genes);
	std::cout << "Done.\n" << std::endl;

	print_clusters(merged_clusters, pars.merged_clusters_file);

	return 0;
}
