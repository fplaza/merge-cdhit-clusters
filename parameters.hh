#ifndef PARAMETERS_HH
#define PARAMETERS_HH

/*
 * (C) Copyright 2015 Enterome
 */

#include <vector>
#include <string>

struct Parameters
{
	std::vector<std::string> initial_clusters_files;
	std::vector<std::string> intermediate_clusters_files;
	std::string final_clusters_file;
	std::vector<std::string> all_clusters_files;
	std::string merged_clusters_file;

	static Parameters parse_cmd_line(int argc, char* argv[]);
	static void check_file_is_readable(const std::string& filepath);
	static void check_file_is_writable(const std::string& filepath);
};

std::ostream& operator<<(std::ostream& os, const Parameters& pars);

#endif // PARAMETERS_HH
