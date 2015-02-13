/*
 * (C) Copyright 2015 Enterome
 */

#include <iostream>
#include "parameters.hh"
#include "time_profiler.hh"
#include "genes_indexer.hh"
#include "clusters_merger.hh"
#include "clusters_writer.hh"

int main(int argc, char* argv[])
{
	const Parameters& pars = Parameters::parse_cmd_line(argc, argv);

	TimeProfiler time_profiler;
	time_profiler.start_new_timer("Total");

	std::cout << "Indexing genes..." << std::endl;
	time_profiler.start_new_timer("Indexing genes");
	boost::unordered_map<std::string, uint32_t> map_gene_id;
	std::vector<std::string> all_genes;
	GenesIndexer genes_indexer(pars.initial_clusters_files);
	genes_indexer.make_index(map_gene_id, all_genes);
	time_profiler.stop_last_timer();
	std::cout << "Done. " << all_genes.size() << " genes indexed.\n" <<  std::endl;

	std::cout << "Merging clusters..." << std::endl;
	time_profiler.start_new_timer("Merging clusters");
	ClustersMerger clusters_merger(pars.all_clusters_files, pars.final_clusters_file, map_gene_id, all_genes);
	const std::vector<Cluster> merged_clusters = clusters_merger.merge();
	time_profiler.stop_last_timer();
	std::cout << "Done.\n" << std::endl;

	std::cout << "Writing merged clusters..." << std::endl;
	time_profiler.start_new_timer("Writing merged clusters");
	ClustersWriter clusters_writer(merged_clusters, pars.merged_clusters_file);
	clusters_writer.write();
	time_profiler.stop_last_timer();
	std::cout << "Done\n" << std::endl;

	time_profiler.stop_last_timer();
	std::cout << time_profiler;

	std::exit(0);
}
