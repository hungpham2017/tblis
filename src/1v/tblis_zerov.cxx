#include "tblis.hpp"

namespace tblis
{

template <typename T>
void tblis_zerov_ref(ThreadCommunicator& comm, idx_type n, T* A, stride_type inc_A)
{
    if (n == 0) return;

    idx_type n_min, n_max;
    std::tie(n_min, n_max, std::ignore) = comm.distribute_over_threads(n);

    if (inc_A == 1)
    {
        for (idx_type i = n_min;i < n_max;i++)
        {
            A[i] = T();
        }
    }
    else
    {
        A += n_min*inc_A;
        for (idx_type i = n_min;i < n_max;i++)
        {
            (*A) = T();
            A += inc_A;
        }
    }
}

template <typename T>
void tblis_zerov(row_view<T> A)
{
    tblis_zerov(A.length(), A.data(), A.stride());
}

template <typename T>
void tblis_zerov(idx_type n, T* A, stride_type inc_A)
{
    parallelize
    (
        [&](ThreadCommunicator& comm)
        {
            tblis_zerov_ref(comm, n, A, inc_A);
        }
    );
}

#define INSTANTIATE_FOR_TYPE(T) \
template void tblis_zerov_ref(ThreadCommunicator& comm, idx_type n, T* A, stride_type inc_A); \
template void tblis_zerov(idx_type n, T* A, stride_type inc_A); \
template void tblis_zerov(row_view<T> A);
#include "tblis_instantiate_for_types.hpp"

}