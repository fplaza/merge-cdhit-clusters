#ifndef CLUSTER_READER_HH
#define	CLUSTER_READER_HH

/*
 * (C) Copyright 2015 Enterome
 */

#include "cluster.hh"
#include <string>
#include <fstream>
#include <boost/lexical_cast.hpp>

class cluster_reader
{
	private:
		const std::string& cluster_file_;
		std::ifstream stream_;
		std::string line_;

	public:
		cluster_reader(const std::string& cluster_file);
		~cluster_reader();
		void reset();
		bool next_cluster(cluster& clstr);
		std::vector<cluster> read_all();
};


inline cluster_reader::cluster_reader(const std::string& cluster_file)
	: cluster_file_(cluster_file), stream_(cluster_file_.c_str()), line_()
{
	line_.reserve(200);
}

inline cluster_reader::~cluster_reader()
{
	stream_.close();
}

inline void cluster_reader::reset()
{
	stream_.close();
	stream_.open(cluster_file_.c_str());
}

inline bool cluster_reader::next_cluster(cluster& clstr)
{
	if (!stream_.good())
		return false;

	std::getline(stream_, line_);
	if (line_[0] != '>')
	{
		stream_.clear(std::ios_base::failbit);
		return false;
	}
	
	clstr.id = boost::lexical_cast<uint32_t>(line_.substr(9));

	clstr.genes.clear();
	while (stream_.peek() != EOF && stream_.peek() != '>')
	{
		std::getline(stream_, line_);

		const size_t gene_start = line_.find('>')+1;
		const size_t gene_end = line_.find("...", gene_start)-1;
		const std::string& gene = line_.substr(gene_start, gene_end-gene_start+1);
		clstr.genes.push_back(gene);
	}

	return true;
}

#endif // CLUSTER_READER_HH
