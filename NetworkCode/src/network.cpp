#include "network.h"
#include <iostream>
#include "random.h"

void Network::resize(const size_t& n){
	values.clear();
	values.resize(n);	
	for (auto& val : values){
		val = (RNG.normal(0,1));
	}
}

bool Network::add_link(const size_t& a, const size_t& b) {
	bool linked (true);
	if ((a!=b) and (a<values.size()) and (b<values.size())) {
		for (auto link : links){
			if (link.first == a){
				if (link.second == b) linked = false;
			}
		}
		if (linked){
			links.insert({a,b});
			links.insert({b,a});
		}
	}
	else {linked = false;}
	return linked;
}

size_t Network::random_connect(const double& mean){
	links.clear();
	for (size_t i(0); i<values.size(); ++i){
		size_t deg = RNG.poisson(mean);
		bool linked;
		for (size_t j(1); j <= deg; ++j){
			do {
				linked = add_link(i, RNG.uniform_double(0,values.size()));
			} while ((!linked) and (degree(i) < (values.size() - 1)));
		}
	}
	return (links.size() / 2 );
}

size_t Network::set_values(const std::vector<double>& vec){ 
	values.clear();
	values = vec;
	return (values.size());
}

size_t Network::size() const{ 
	return values.size();
}

size_t Network::degree(const size_t &_n) const{ 
	size_t i(0);
	for (auto link : links) {
		if (link.first == _n){i++;}
	}
	return i;
}

double Network::value(const size_t &_n) const{
	return values[_n];
}

std::vector<double> Network::sorted_values() const{ 
	std::vector<double> toSort = values;
	std::sort(toSort.begin(), toSort.end(), std::greater<double>());
	return toSort;
	
}

std::vector<size_t> Network::neighbors(const size_t& n) const{ 
	std::vector<size_t> myNeighbors;
	for (auto link : links) {
		if (link.first == n)  { myNeighbors.push_back(link.second);}
	}
	return myNeighbors;
}

