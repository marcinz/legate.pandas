/* Copyright 2021 NVIDIA Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include <cuda_runtime.h>
#include <cudf/utilities/error.hpp>

namespace legate {
namespace pandas {

#ifdef DEBUG_PANDAS
#define SYNC_AND_CHECK_STREAM(stream)        \
  do {                                       \
    CUDA_TRY(cudaStreamSynchronize(stream)); \
    CUDA_TRY(cudaPeekAtLastError());         \
  } while (0);
#else
#define SYNC_AND_CHECK_STREAM(stream)        \
  do {                                       \
    CUDA_TRY(cudaStreamSynchronize(stream)); \
  } while (0);
#endif

class AutoStream {
 public:
  AutoStream() { cudaStreamCreate(&stream_); }
  ~AutoStream() { cudaStreamDestroy(stream_); }
  constexpr cudaStream_t stream() const { return stream_; }

 private:
  cudaStream_t stream_;
};

}  // namespace pandas
}  // namespace legate
