#ifndef MAKE_GENES_INDEX_HH
#define MAKE_GENES_INDEX_HH

#include <string>
#include <vector>
#include <stdint.h>
#include <boost/unordered_map.hpp>

void make_genes_index(const std::vector<std::string>& initial_clusters_files, boost::unordered_map<std::string,uint32_t>& map_gene_id, std::vector<std::string>& all_genes);

#endif  // MAKE_GENES_INDEX_HH
