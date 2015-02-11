/*
 * (C) Copyright 2015 Enterome
 */

#include "parameters.hh"
#include <iostream>
#include <fstream>
#include <exception>
#include <algorithm>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

Parameters Parameters::parse_cmd_line(int argc, char* argv[])
{
	Parameters pars;

	// Create options decription
	po::options_description opts_desc("");

	opts_desc.add_options()
		("initial-clusters", po::value<std::vector<std::string> >(&pars.initial_clusters_files)->multitoken(), "")
		("intermediate-clusters", po::value<std::vector<std::string> >(&pars.intermediate_clusters_files)->multitoken(), "")
		("final-clusters", po::value<std::string>(&pars.final_clusters_file), "")
		("merged-clusters", po::value<std::string>(&pars.merged_clusters_file), "")
		("help,h", "display this help and exit.")
		;

	// Retrieve and parse command line Parameters
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, opts_desc), vm);

	// Print help
	if (argc == 1 || vm.count("help"))
	{
		std::cout << opts_desc << std::endl;
		std::exit(0);
	}

	po::notify(vm);

	std::for_each(pars.initial_clusters_files.begin(), pars.initial_clusters_files.end(), check_file_is_readable);
	std::for_each(pars.intermediate_clusters_files.begin(), pars.intermediate_clusters_files.end(), check_file_is_readable);
	check_file_is_readable(pars.final_clusters_file);
	check_file_is_writable(pars.merged_clusters_file);

	pars.all_clusters_files.insert(pars.all_clusters_files.end(), pars.initial_clusters_files.begin(), pars.initial_clusters_files.end());
	pars.all_clusters_files.insert(pars.all_clusters_files.end(), pars.intermediate_clusters_files.begin(), pars.intermediate_clusters_files.end());
	pars.all_clusters_files.push_back(pars.final_clusters_file);

	return pars;
}

void Parameters::check_file_is_readable(const std::string& filepath)
{
	std::ifstream ifs;
	ifs.open(filepath.c_str());

	if (ifs.good())
	{
		ifs.close();
	}
	else
	{
		throw (std::invalid_argument("error: " + filepath +
					" cannot be opened. Check that the path is valid and that you have read permissions."));
	}
}

void Parameters::check_file_is_writable(const std::string& filepath)
{
	std::ofstream ofs;
	ofs.open(filepath.c_str());

	if (ofs.good())
	{
		ofs.close();
	}
	else
	{
		throw (std::invalid_argument("error: " + filepath +
					" cannot be created. Check that the path is valid and that you have write permissions."));
	}
}
