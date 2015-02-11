#include "cluster.hh"

std::ostream& operator<<(std::ostream& out, const cluster& clstr)
{
	out << ">Cluster " << clstr.id+1 << '\n';

	for (size_t i = 0; i < clstr.genes.size(); i++)
		out << clstr.genes[i] << '\n';

	return out;
}

