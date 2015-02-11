#ifndef CLUSTER_HH
#define CLUSTER_HH

#include <stdint.h>
#include <vector>
#include <string>
#include <ostream>

struct cluster
{
	uint32_t id;
	std::vector<std::string> genes;
};

std::ostream& operator<<(std::ostream& out, const cluster& clstr);

#endif //CLUSTER_HH
