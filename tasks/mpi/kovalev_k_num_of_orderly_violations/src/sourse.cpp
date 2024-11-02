// Copyright 2023 Nesterov Alexander
#include "mpi/kovalev_k_num_of_orderly_violations/include/header.hpp"

template <class T>
bool kovalev_k_num_of_orderly_violations_mpi::NumOfOrderlyViolationsPar<T>::count_num_of_orderly_violations_mpi() {
  for (size_t i = 0; i < loc_v.size(); i++) {
    std::cout << loc_v[i] << ' ';
  }
  std::cout << rank << " I am starting to count. loc_v size = " << loc_v.size() << ' ' << bool(1 < loc_v.size())
            << std::endl;
  for (size_t i = 1; i < loc_v.size(); i++) {
    std::cout << "i = " << i;
    if (loc_v[i - 1] > loc_v[i]) {
      l_res++;
    }
  }
  std::cout << ' ' << l_res << std::endl;
  return true;
}

template <class T>
bool kovalev_k_num_of_orderly_violations_mpi::NumOfOrderlyViolationsPar<T>::pre_processing() {
  internal_order_test();
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  size_t scratter_length = n / size;  // minimum length to each process
  loc_v.resize(scratter_length);      // resize the local copy
  if (rank == 0) {
    // Initialization global_vector <T> with input data
    glob_v.resize(n);
    void* ptr_vec = glob_v.data();
    void* ptr_input = taskData->inputs[0];
    memcpy(ptr_vec, ptr_input, sizeof(T) * n);
  }
  MPI_Scatter(glob_v.data(), scratter_length * sizeof(T), MPI_BYTE, loc_v.data(), scratter_length * sizeof(T), MPI_BYTE,
              0, MPI_COMM_WORLD);
  return true;
}

template <class T>
bool kovalev_k_num_of_orderly_violations_mpi::NumOfOrderlyViolationsPar<T>::validation() {
  internal_order_test();
  // input && output counts check
  return (taskData->inputs_count[0] == n && taskData->outputs_count[0] == 1);
}

template <class T>
bool kovalev_k_num_of_orderly_violations_mpi::NumOfOrderlyViolationsPar<T>::run() {
  internal_order_test();
  // counting violations locally
  count_num_of_orderly_violations_mpi();
  // redusing results
  std::cout << rank << " I am starting to reduse. loc = " << l_res << std::endl;
  MPI_Reduce(&l_res, &g_res, 1, MPI_UNSIGNED_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
  std::cout << rank << " I have redused." << std::endl;
  if (rank == 0) {
    for (size_t i = 1; i < size; i++)  // are there any violations between local copies?
      if (glob_v[i * (n / size) - 1] > glob_v[i * (n / size)]) g_res++;
    std::cout << rank << " I have done 1 sycle." << std::endl;
    for (size_t i = n - n % size; i < n; i++)  // are there any violations in the remainder?
      if (glob_v[i - 1] > glob_v[i]) g_res++;
    std::cout << rank << " I have done 2 sycle." << std::endl;
  }
  return true;
}

template <class T>
bool kovalev_k_num_of_orderly_violations_mpi::NumOfOrderlyViolationsPar<T>::post_processing() {
  internal_order_test();
  // Pushing global result to output
  if (rank == 0) {
    reinterpret_cast<size_t*>(taskData->outputs[0])[0] = g_res;
  }
  return true;
}

template class kovalev_k_num_of_orderly_violations_mpi::NumOfOrderlyViolationsPar<int>;
template class kovalev_k_num_of_orderly_violations_mpi::NumOfOrderlyViolationsPar<double>;