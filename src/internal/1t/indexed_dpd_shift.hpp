#ifndef _TBLIS_INTERNAL_1T_INDEXED_DPD_SHIFT_HPP_
#define _TBLIS_INTERNAL_1T_INDEXED_DPD_SHIFT_HPP_

#include "util/thread.h"
#include "util/basic_types.h"
#include "configs/configs.hpp"

namespace tblis
{
namespace internal
{

template <typename T>
void indexed_dpd_shift(const communicator& comm, const config& cfg,
                       T alpha, T beta, bool conj_A, const indexed_dpd_varray_view<T>& A,
                       const dim_vector&);

}
}

#endif