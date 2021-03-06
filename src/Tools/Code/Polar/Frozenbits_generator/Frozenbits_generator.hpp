/*!
 * \file
 * \brief Determines the frozen bit positions in a frame.
 *
 * \section LICENSE
 * This file is under MIT license (https://opensource.org/licenses/MIT).
 */
#ifndef FROZENBITS_GENERATOR_HPP_
#define FROZENBITS_GENERATOR_HPP_

#include <cstdint>
#include <thread>
#include <vector>
#include <memory>
#include <string>

#include "Tools/Noise/Noise.hpp"

namespace aff3ct
{
namespace tools
{
/*!
 * \class Frozenbits_generator
 * \brief Determines the frozen bit positions in a frame.
 */
class Frozenbits_generator
{
private:
	static std::thread::id master_thread_id;
	const std::string dump_channels_path;
	const bool dump_channels_single_thread;

protected:
	const int K; /*!< Number of information bits in the frame. */
	const int N; /*!< Codeword size (or frame size). */
	std::unique_ptr<tools::Noise<float>> n;

	std::vector<uint32_t> best_channels; /*!< The best channels in a codeword sorted by descending order. */

public:
	/*!
	 * \brief Constructor.
	 *
	 * \param K:     number of information bits in the frame.
	 * \param N:     codeword size (or frame size).
	 */
	Frozenbits_generator(const int K, const int N, const std::string &dump_channels_path = "",
	                                               const bool dump_channels_single_thread = true);

	/*!
	 * \brief Destructor.
	 */
	virtual ~Frozenbits_generator() = default;

	int get_K() const;

	int get_N() const;

	/*!
	 * \brief Sets the current noise to apply to the input signal
	 *
	 * \param sigma: the current noise to apply to the input signal
	 */
	void set_noise(const tools::Noise<float>& noise);

	/*!
	 * \brief Sets the current noise to apply to the input signal
	 *
	 * \param sigma: the current noise to apply to the input signal
	 */
	void set_noise(const tools::Noise<double>& noise);

	/*!
	 * \brief Generates the frozen bits vector.
	 *
	 * \param frozen_bits: output vector of frozen bits.
	 */
	void generate(std::vector<bool> &frozen_bits);

	/*!
	 * \brief Gets the best channels (the most secured bits sorted by descending order).
	 *
	 * \return a vector of the best channels.
	 */
	const std::vector<uint32_t>& get_best_channels() const;

	void dump_best_channels(const std::string& dump_channels_full_path) const;

protected:

	/*!
	 * \brief Evaluates the best channels.
	 *
	 * It is mandatory to compute the best channels to find the position of the frozen bits.
	 * This method fills the internal Frozenbits_generator::best_channels attribute.
	 */
	virtual void evaluate() = 0;

	/*!
	 * \brief Check that the noise has the expected type
	 */
	virtual void check_noise();
};
}
}

#endif /* FROZENBITS_GENERATOR_HPP_ */
