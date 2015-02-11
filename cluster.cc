/*
 * (C) Copyright 2015 Enterome
 */

#include "cluster.hh"

std::ostream& operator<<(std::ostream& out, const Cluster& cluster)
{
	out << ">Cluster " << cluster.id+1 << '\n';

	for (size_t i = 0; i < cluster.genes.size(); i++)
		out << cluster.genes[i] << '\n';

	return out;
}

