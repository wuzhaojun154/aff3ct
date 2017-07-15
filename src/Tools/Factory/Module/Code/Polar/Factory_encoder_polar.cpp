#include "Tools/Exception/exception.hpp"

#include "Module/Encoder/Polar/Encoder_polar.hpp"
#include "Module/Encoder/Polar/Encoder_polar_sys.hpp"

#include "Factory_encoder_polar.hpp"

using namespace aff3ct::module;
using namespace aff3ct::tools;

template <typename B>
Encoder<B>* Factory_encoder_polar
::build(const Factory_encoder::parameters& params, const mipp::vector<B> &frozen_bits)
{
	     if (params.type == "POLAR" && !params.systematic) return new Encoder_polar    <B>(params.K, params.N_cw, frozen_bits, params.n_frames);
	else if (params.type == "POLAR" &&  params.systematic) return new Encoder_polar_sys<B>(params.K, params.N_cw, frozen_bits, params.n_frames);

	throw cannot_allocate(__FILE__, __LINE__, __func__);
}

void Factory_encoder_polar
::build_args(Arguments_reader::arg_map &req_args, Arguments_reader::arg_map &opt_args)
{
	Factory_encoder::build_args(req_args, opt_args);

	opt_args[{"enc-type"}][2] += ", POLAR";

	opt_args[{"enc-no-sys"}] =
		{"",
		 "disable the systematic encoding."};
}

void Factory_encoder_polar
::store_args(const Arguments_reader& ar, Factory_encoder::parameters &params)
{
	params.type = "POLAR";

	Factory_encoder::store_args(ar, params);
}

void Factory_encoder_polar
::group_args(Arguments_reader::arg_grp& ar)
{
	Factory_encoder::group_args(ar);
}

void Factory_encoder_polar
::header(params_list& head_enc, const Factory_encoder::parameters& params)
{
	Factory_encoder::header(head_enc, params);
}

// ==================================================================================== explicit template instantiation
#include "Tools/types.h"
#ifdef MULTI_PREC
template aff3ct::module::Encoder<B_8 >* aff3ct::tools::Factory_encoder_polar::build<B_8 >(const aff3ct::tools::Factory_encoder::parameters&, const mipp::vector<B_8 >&);
template aff3ct::module::Encoder<B_16>* aff3ct::tools::Factory_encoder_polar::build<B_16>(const aff3ct::tools::Factory_encoder::parameters&, const mipp::vector<B_16>&);
template aff3ct::module::Encoder<B_32>* aff3ct::tools::Factory_encoder_polar::build<B_32>(const aff3ct::tools::Factory_encoder::parameters&, const mipp::vector<B_32>&);
template aff3ct::module::Encoder<B_64>* aff3ct::tools::Factory_encoder_polar::build<B_64>(const aff3ct::tools::Factory_encoder::parameters&, const mipp::vector<B_64>&);
#else
template aff3ct::module::Encoder<B>* aff3ct::tools::Factory_encoder_polar::build<B>(const aff3ct::tools::Factory_encoder::parameters&, const mipp::vector<B>&);
#endif
// ==================================================================================== explicit template instantiation
