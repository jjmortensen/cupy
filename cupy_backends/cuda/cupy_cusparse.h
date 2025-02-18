#ifndef INCLUDE_GUARD_CUDA_CUPY_CUSPARSE_H
#define INCLUDE_GUARD_CUDA_CUPY_CUSPARSE_H

#include <cuda.h>
#include <cusparse.h>

#if !defined(CUSPARSE_VERSION)
  // CUSPARSE_VERSION introduced in CUDA 10.1 Update 2 (10.1.243).
  #if CUDA_VERSION < 10000
    #define CUSPARSE_VERSION CUDA_VERSION // CUDA_VERSION used instead
  #elif CUDA_VERSION < 10010  // CUDA 10.0.x
    # define CUSPARSE_VERSION 10000
  #elif CUDA_VERSION < 10020  // CUDA 10.1.x
    // CUSPARSE_VER_MAJOR introduced in CUDA 10.1 Update 1 (10.1.168).
    #if !defined(CUSPARSE_VER_MAJOR)
      // CUDA 10.1 (10.1.105) contains cuSPARSE 10.1
      #define CUSPARSE_VERSION 10010
    #else
      // CUDA 10.1 Update 1 (10.1.168) contains cuSPARSE 10.2.0.0
      #define CUSPARSE_VERSION (CUSPARSE_VER_MAJOR * 1000 + \
                                CUSPARSE_VER_MINOR *  100 + \
                                CUSPARSE_VER_PATCH)
    #endif
  #endif
#endif  // #if !defined(CUSPARSE_VERSION)

/*
 * Generic APIs are not suppoted in CUDA 10.1/10.2 on Windows.
 * These APIs are available in headers in CUDA 10.1 and 10.1 Update 1,
 * but hidden in 10.1 Update 2 and 10.2 on Windows.
 */

#if defined(_WIN32) && (CUSPARSE_VERSION < 11000)
  #if 10200 < CUSPARSE_VERSION
    #define WIN32_EXPOSE_SPMM_STUB_DECL 1
  #else
    #define WIN32_EXPOSE_SPMM_STUB_DECL 0
  #endif
  #define WIN32_EXPOSE_SPMM_STUB_IMPL 1
#else
  #define WIN32_EXPOSE_SPMM_STUB_DECL 0
  #define WIN32_EXPOSE_SPMM_STUB_IMPL 0
#endif

#if CUSPARSE_VERSION < 10010
// Added in cuSPARSE 10.1 (CUDA 10.1.105)

// CSR2CSC
typedef enum {} cusparseCsr2CscAlg_t;

#endif  // #if CUSPARSE_VERSION < 10010

#if CUSPARSE_VERSION < 10010 || WIN32_EXPOSE_SPMM_STUB_DECL
// Generic API types added in cuSPARSE 10.1 (CUDA 10.1.105)

typedef void* cusparseSpMatDescr_t;
typedef void* cusparseDnMatDescr_t;
typedef enum {} cusparseIndexType_t;
typedef enum {} cusparseFormat_t;
typedef enum {} cusparseOrder_t;
typedef enum {} cusparseSpMMAlg_t;

#endif  // #if CUSPARSE_VERSION < 10010 || WIN32_EXPOSE_SPMM_STUB_DECL

#if CUSPARSE_VERSION < 10200
// Added in cuSPARSE 10.2 (CUDA 10.1.168)

// CSR2CSC
cusparseStatus_t cusparseCsr2cscEx2_bufferSize(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCsr2cscEx2(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

#endif  // #if CUSPARSE_VERSION < 10200

#if CUSPARSE_VERSION < 10200 || WIN32_EXPOSE_SPMM_STUB_DECL
// Generic API types added in cuSPARSE 10.2 (CUDA 10.1.168)

typedef void* cusparseSpVecDescr_t;
typedef void* cusparseDnVecDescr_t;
typedef enum {} cusparseSpMVAlg_t;

#endif  // #if CUSPARSE_VERSION < 10200 || WIN32_EXPOSE_SPMM_STUB_DECL

#if CUSPARSE_VERSION < 10200 || WIN32_EXPOSE_SPMM_STUB_IMPL
// Generic APIs added in cuSPARSE 10.2 (CUDA 10.1.168)

/*
 * On Windows, implementations are not exposed from DLL in CUDA 10.1/10.2
 * although it is declared in the header. So we have to provide a stub
 * implementation using the full signature to match with the signature
 * declared in cusparse.h, instead of using (...).
 */

cusparseStatus_t cusparseCreateSpVec(
    cusparseSpVecDescr_t* spVecDescr,
    int64_t               size,
    int64_t               nnz,
    void*                 indices,
    void*                 values,
    cusparseIndexType_t   idxType,
    cusparseIndexBase_t   idxBase,
    cudaDataType          valueType) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDestroySpVec(cusparseSpVecDescr_t spVecDescr) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpVecGet(
    const cusparseSpVecDescr_t spVecDescr,
    int64_t*                   size,
    int64_t*                   nnz,
    void**                     indices,
    void**                     values,
    cusparseIndexType_t*       idxType,
    cusparseIndexBase_t*       idxBase,
    cudaDataType*              valueType) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpVecGetIndexBase(
    const cusparseSpVecDescr_t spVecDescr,
    cusparseIndexBase_t*       idxBase) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpVecGetValues(
    const cusparseSpVecDescr_t spVecDescr,
    void**                     values) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpVecSetValues(
    cusparseSpVecDescr_t spVecDescr,
    void*                values) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCreateCoo(
    cusparseSpMatDescr_t* spMatDescr,
    int64_t               rows,
    int64_t               cols,
    int64_t               nnz,
    void*                 cooRowInd,
    void*                 cooColInd,
    void*                 cooValues,
    cusparseIndexType_t   cooIdxType,
    cusparseIndexBase_t   idxBase,
    cudaDataType          valueType) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCreateCooAoS(
    cusparseSpMatDescr_t* spMatDescr,
    int64_t               rows,
    int64_t               cols,
    int64_t               nnz,
    void*                 cooInd,
    void*                 cooValues,
    cusparseIndexType_t   cooIdxType,
    cusparseIndexBase_t   idxBase,
    cudaDataType          valueType) {
  return CUSPARSE_STATUS_SUCCESS;
}


cusparseStatus_t cusparseCreateCsr(
    cusparseSpMatDescr_t* spMatDescr,
    int64_t               rows,
    int64_t               cols,
    int64_t               nnz,
    void*                 csrRowOffsets,
    void*                 csrColInd,
    void*                 csrValues,
    cusparseIndexType_t   csrRowOffsetsType,
    cusparseIndexType_t   csrColIndType,
    cusparseIndexBase_t   idxBase,
    cudaDataType          valueType) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDestroySpMat(cusparseSpMatDescr_t spMatDescr) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCooGet(
    const cusparseSpMatDescr_t spMatDescr,
    int64_t*                   rows,
    int64_t*                   cols,
    int64_t*                   nnz,
    void**                     cooRowInd,  // COO row indices
    void**                     cooColInd,  // COO column indices
    void**                     cooValues,  // COO values
    cusparseIndexType_t*       idxType,
    cusparseIndexBase_t*       idxBase,
    cudaDataType*              valueType) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCooAoSGet(
    const cusparseSpMatDescr_t spMatDescr,
    int64_t*                   rows,
    int64_t*                   cols,
    int64_t*                   nnz,
    void**                     cooInd,     // COO indices
    void**                     cooValues,  // COO values
    cusparseIndexType_t*       idxType,
    cusparseIndexBase_t*       idxBase,
    cudaDataType*              valueType) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCsrGet(
    const cusparseSpMatDescr_t spMatDescr,
    int64_t*                   rows,
    int64_t*                   cols,
    int64_t*                   nnz,
    void**                     csrRowOffsets,
    void**                     csrColInd,
    void**                     csrValues,
    cusparseIndexType_t*       csrRowOffsetsType,
    cusparseIndexType_t*       csrColIndType,
    cusparseIndexBase_t*       idxBase,
    cudaDataType*              valueType) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpMatGetFormat(
    const cusparseSpMatDescr_t spMatDescr,
    cusparseFormat_t*          format) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpMatGetIndexBase(
    const cusparseSpMatDescr_t spMatDescr,
    cusparseIndexBase_t*       idxBase) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpMatGetValues(
    const cusparseSpMatDescr_t spMatDescr,
    void**                     values) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpMatSetValues(
    cusparseSpMatDescr_t spMatDescr,
    void*                values) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpMatGetStridedBatch(
    const cusparseSpMatDescr_t spMatDescr,
    int*                       batchCount) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpMatSetStridedBatch(
    cusparseSpMatDescr_t spMatDescr,
    int                  batchCount) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCreateDnVec(
    cusparseDnVecDescr_t* dnVecDescr,
    int64_t               size,
    void*                 values,
    cudaDataType          valueType) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDestroyDnVec(cusparseDnVecDescr_t dnVecDescr) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDnVecGet(
    const cusparseDnVecDescr_t dnVecDescr,
    int64_t*                   size,
    void**                     values,
    cudaDataType*              valueType) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDnVecGetValues(
    const cusparseDnVecDescr_t dnVecDescr,
    void**                     values) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDnVecSetValues(
    cusparseDnVecDescr_t dnVecDescr,
    void*                values) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCreateDnMat(
    cusparseDnMatDescr_t* dnMatDescr,
    int64_t               rows,
    int64_t               cols,
    int64_t               ld,
    void*                 values,
    cudaDataType          valueType,
    cusparseOrder_t       order) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDestroyDnMat(cusparseDnMatDescr_t dnMatDescr) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDnMatGet(
    const cusparseDnMatDescr_t dnMatDescr,
    int64_t*                   rows,
    int64_t*                   cols,
    int64_t*                   ld,
    void**                     values,
    cudaDataType*              type,
    cusparseOrder_t*           order) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDnMatGetValues(
    const cusparseDnMatDescr_t dnMatDescr,
    void**                     values) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDnMatSetValues(
    cusparseDnMatDescr_t dnMatDescr,
    void*                values) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDnMatGetStridedBatch(
    const cusparseDnMatDescr_t dnMatDescr,
    int*                       batchCount,
    int64_t*                   batchStride) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDnMatSetStridedBatch(
    cusparseDnMatDescr_t dnMatDescr,
    int                  batchCount,
    int64_t              batchStride) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpVV_bufferSize(
    cusparseHandle_t           handle,
    cusparseOperation_t        opX,
    const cusparseSpVecDescr_t vecX,
    const cusparseDnVecDescr_t vecY,
    const void*                result,
    cudaDataType               computeType,
    size_t*                    bufferSize) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpVV(
    cusparseHandle_t           handle,
    cusparseOperation_t        opX,
    const cusparseSpVecDescr_t vecX,
    const cusparseDnVecDescr_t vecY,
    void*                      result,
    cudaDataType               computeType,
    void*                      externalBuffer) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpMV_bufferSize(
    cusparseHandle_t           handle,
    cusparseOperation_t        opA,
    const void*                alpha,
    const cusparseSpMatDescr_t matA,
    const cusparseDnVecDescr_t vecX,
    const void*                beta,
    const cusparseDnVecDescr_t vecY,
    cudaDataType               computeType,
    cusparseSpMVAlg_t          alg,
    size_t*                    bufferSize) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpMV(
    cusparseHandle_t           handle,
    cusparseOperation_t        opA,
    const void*                alpha,
    const cusparseSpMatDescr_t matA,
    const cusparseDnVecDescr_t vecX,
    const void*                beta,
    const cusparseDnVecDescr_t vecY,
    cudaDataType               computeType,
    cusparseSpMVAlg_t          alg,
    void*                      externalBuffer) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpMM_bufferSize(
    cusparseHandle_t           handle,
    cusparseOperation_t        opA,
    cusparseOperation_t        opB,
    const void*                alpha,
    const cusparseSpMatDescr_t matA,
    const cusparseDnMatDescr_t matB,
    const void*                beta,
    cusparseDnMatDescr_t       matC,
    cudaDataType               computeType,
    cusparseSpMMAlg_t          alg,
    size_t*                    bufferSize) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpMM(
    cusparseHandle_t           handle,
    cusparseOperation_t        opA,
    cusparseOperation_t        opB,
    const void*                alpha,
    const cusparseSpMatDescr_t matA,
    const cusparseDnMatDescr_t matB,
    const void*                beta,
    cusparseDnMatDescr_t       matC,
    cudaDataType               computeType,
    cusparseSpMMAlg_t          alg,
    void*                      externalBuffer) {
  return CUSPARSE_STATUS_SUCCESS;
}

#endif  // #if CUSPARSE_VERSION < 10200 || WIN32_EXPOSE_SPMM_STUB_IMPL

#if CUSPARSE_VERSION < 10300 || WIN32_EXPOSE_SPMM_STUB_IMPL
// Generic APIs added in cuSPARSE 10.3 (CUDA 10.1.243)

cusparseStatus_t cusparseConstrainedGeMM_bufferSize(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseConstrainedGeMM(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

#endif  // #if CUSPARSE_VERSION < 10300 || WIN32_EXPOSE_SPMM_STUB_IMPL

#if CUSPARSE_VERSION >= 11000
// Functions deleted in cuSparse 11.0

// cuSPARSE Level2 Function
cusparseStatus_t cusparseScsrmv(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsrmv(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsrmv(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsrmv(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

// cuSPARSE Level3 Function
cusparseStatus_t cusparseScsrmm(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsrmm(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsrmm(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsrmm(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseScsrmm2(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsrmm2(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsrmm2(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsrmm2(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

// cuSPARSE Extra Function
cusparseStatus_t cusparseXcsrgeamNnz(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseScsrgeam(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsrgeam(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsrgeam(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsrgeam(...) {
  return CUSPARSE_STATUS_SUCCESS;
}


cusparseStatus_t cusparseXcsrgemmNnz(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseScsrgemm(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsrgemm(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsrgemm(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsrgemm(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

// cuSPARSE Format Convrsion
cusparseStatus_t cusparseXcsr2coo(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseScsr2csc(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsr2csc(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsr2csc(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsr2csc(...) {
  return CUSPARSE_STATUS_SUCCESS;
}
#endif // #if CUSPARSE_VERSION >= 11000

#if CUSPARSE_VERSION < 11100
// Functions added in cuSparse 11.1 (CUDA 11.0)

cusparseStatus_t cusparseCsrSetPointers(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpMatGetSize(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

typedef void* cusparseSpGEMMDescr_t;
typedef enum {} cusparseSpGEMMAlg_t;

cusparseStatus_t cusparseSpGEMM_createDescr(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpGEMM_destroyDescr(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpGEMM_workEstimation(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpGEMM_compute(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpGEMM_copy(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

#endif // #if CUSPARSE_VERSION < 11100

#if CUSPARSE_VERSION < 11300
// Types and macros added in cuSparse 11.3 (CUDA 11.1.1)

typedef enum {} cusparseSparseToDenseAlg_t;
typedef enum {} cusparseDenseToSparseAlg_t;

#endif // CUSPARSE_VERSION < 11300

#if CUSPARSE_VERSION < 11500
// API added in cuSparse 11.5 (CUDA 11.3.0)

typedef enum {} cusparseSpMatAttribute_t;

cusparseStatus_t cusparseSpMatSetAttribute(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

#endif // CUSPARSE_VERSION < 11500

#if CUSPARSE_VERSION < 11600
// Generic APIs added in cuSPARSE 11.6 (CUDA 11.3.1)

typedef void* cusparseSpSMDescr_t;
typedef enum {} cusparseSpSMAlg_t;

cusparseStatus_t cusparseSpSM_createDescr(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpSM_destroyDescr(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpSM_bufferSize(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpSM_analysis(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpSM_solve(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

#endif // #if CUSPARSE_VERSION < 11600

// See cusparse.pyx
cusparseStatus_t _cusparseSpSM_solve(cusparseHandle_t     handle,
                                     cusparseOperation_t  opA,
                                     cusparseOperation_t  opB,
                                     const void*          alpha,
                                     cusparseSpMatDescr_t matA,
                                     cusparseDnMatDescr_t matB,
                                     cusparseDnMatDescr_t matC,
                                     cudaDataType         computeType,
                                     cusparseSpSMAlg_t    alg,
                                     cusparseSpSMDescr_t  spsmDescr,
                                     void*                externalBuffer) {
    return cusparseSpSM_solve(handle, opA, opB, alpha, matA, matB, matC, computeType, alg, spsmDescr);
}

#if CUSPARSE_VERSION >= 12000
// Types and functions deleted in cuSPARSE 12.0 (CUDA 12.0)

typedef enum {} cusparseAlgMode_t;
typedef void* csrgemm2Info_t;
typedef void* csrsm2Info_t;
typedef void* csrsv2Info_t;

cusparseStatus_t cusparseCreateCsrsv2Info(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDestroyCsrsv2Info(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCreateCsrsm2Info(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDestroyCsrsm2Info(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCreateCsrgemm2Info(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDestroyCsrgemm2Info(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSgthr(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDgthr(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCgthr(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZgthr(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCsrmvEx_bufferSize(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCsrmvEx(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseScsrsv2_bufferSize(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsrsv2_bufferSize(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsrsv2_bufferSize(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsrsv2_bufferSize(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseScsrsv2_analysis(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsrsv2_analysis(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsrsv2_analysis(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsrsv2_analysis(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseScsrsv2_solve(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsrsv2_solve(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsrsv2_solve(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsrsv2_solve(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseXcsrsv2_zeroPivot(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseScsrsm2_bufferSizeExt(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsrsm2_bufferSizeExt(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsrsm2_bufferSizeExt(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsrsm2_bufferSizeExt(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseScsrsm2_analysis(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsrsm2_analysis(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsrsm2_analysis(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsrsm2_analysis(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseScsrsm2_solve(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsrsm2_solve(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsrsm2_solve(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsrsm2_solve(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseXcsrsm2_zeroPivot(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseScsrgemm2_bufferSizeExt(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsrgemm2_bufferSizeExt(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsrgemm2_bufferSizeExt(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsrgemm2_bufferSizeExt(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseXcsrgemm2Nnz(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseScsrgemm2(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsrgemm2(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsrgemm2(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsrgemm2(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseScsc2dense(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsc2dense(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsc2dense(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsc2dense(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseScsr2dense(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDcsr2dense(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCcsr2dense(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZcsr2dense(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSdense2csc(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDdense2csc(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCdense2csc(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZdense2csc(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSdense2csr(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseDdense2csr(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseCdense2csr(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseZdense2csr(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseSpMatSetStridedBatch(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseConstrainedGeMM(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

cusparseStatus_t cusparseConstrainedGeMM_bufferSize(...) {
  return CUSPARSE_STATUS_SUCCESS;
}

#endif // #if CUSPARSE_VERSION >= 12000

#endif  // INCLUDE_GUARD_CUDA_CUPY_CUSPARSE_H
