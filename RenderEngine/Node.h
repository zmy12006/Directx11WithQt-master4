#pragma once
#include <vector>
#include "Spatial.h"
class Node : public Spatial
{
public:
	Node();
	~Node();

private:
	std::vector<Spatial*>	mChildren;
};

