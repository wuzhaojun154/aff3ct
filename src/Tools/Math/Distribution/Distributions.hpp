#ifndef DISTRIBUTIONS_HPP
#define DISTRIBUTIONS_HPP

#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "Distribution.hpp"

namespace aff3ct
{
namespace tools
{
/*
 * Warning all contained distributions are deleted at destruction time.
 */
template <typename R = float>
class Distributions
{
public:
	static const int saved_noise_precision;

protected:
	std::map<int, Distribution<R>*> distributions; // distributions in function of the noise power
	std::ifstream f_distributions;

	std::vector<R> noise_range;
	std::vector<std::streampos> noise_file_index;

	// the data description
	std::vector<std::string> desc;
	size_t ROP_pos;
	size_t x_pos  ;
	size_t y0_pos ;
	size_t y1_pos ;

public:
	explicit Distributions(const std::string& filename, bool read_all_at_init = false);

	virtual ~Distributions();

	bool has_distribution(R noise) const;
	const Distribution<R>* const get_distribution(R noise) const;
	void read_distribution(R noise);

	std::vector<R> get_noise_range() const;

protected:
	/*
	 * Add a distribution 'new_distribution' associated with the noise power 'noise_power'.
	 */
	void add_distribution(R noise, Distribution<R>* new_distribution);
	void read_noise_range();
	void read_distribution_from_file(unsigned index);

	static int calibrated_noise(R noise);
	void file_go_to_pos(unsigned index = -1);
};

}
}

#endif /* DISTRIBUTIONS_HPP */