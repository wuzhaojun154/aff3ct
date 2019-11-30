/*!
 * \file
 * \brief Class module::Subchain.
 */
#ifndef SUBCHAIN_HPP_
#define SUBCHAIN_HPP_

#include <memory>
#include <cstddef>

#include "Tools/Chain/Chain.hpp"
#include "Module/Module.hpp"

namespace aff3ct
{
namespace module
{
	namespace sch
	{
		enum class tsk : size_t { exec, SIZE };
	}

class Subchain : public Module
{
	std::shared_ptr<tools::Chain> chain;

public:
	inline Task& operator[](const sch::tsk t);

	explicit Subchain(const tools::Chain &chain);

	virtual ~Subchain() = default;

	virtual Subchain* clone() const;

	tools::Chain& get_chain();

protected:
	virtual void deep_copy(const Subchain& m);
};
}
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "Module/Subchain/Subchain.hxx"
#endif

#endif /* SUBCHAIN_HPP_ */
