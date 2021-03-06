// Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#ifndef _H_TENSOR_COMPUTING_TYPE
#define _H_TENSOR_COMPUTING_TYPE

#include <vector>
#include "type.h"
#ifdef _USE_MALI
#include "gcl.h"
#define ALIGN(len, align_num) ((len + align_num - 1) / align_num * align_num)
#endif

typedef struct {
    U32 top;
    U32 bottom;
    U32 left;
    U32 right;
    F32 constant_value;
    PadMode pad_mode;
} PadDesc;

typedef struct {
    ActivationMode mode;
    float value[4] = {0, 0, 0, 0};
} ActivationDesc;

typedef struct {
    U32 stride_h;
    U32 stride_w;
    U32 padding_top;
    U32 padding_bottom;
    U32 padding_left;
    U32 padding_right;
    U32 dilatedRate_h;
    U32 dilatedRate_w;
} ConvolutionDesc;

typedef enum {
    CONVOLUTION_NO_TMP_MEM,
    CONVOLUTION_FASTEST,
    CONVOLUTION_TUNNING,
    CONVOLUTION_LIBRARY_SEARCH,
} ConvolutionPolicy;

typedef enum {
    CONVOLUTION_ALGORITHM_DIRECT,
    CONVOLUTION_ALGORITHM_GEMM,
    CONVOLUTION_ALGORITHM_GEMM_ICNCHW,
    CONVOLUTION_ALGORITHM_WINOGRAD,
    CONVOLUTION_ALGORITHM_BNN,
    CONVOLUTION_ALGORITHM_DIRECT_SPE_CK,
    CONVOLUTION_ALGORITHM_NULL
} ConvolutionForwardAlgorithm;

typedef struct {
    F32 xmin;
    F32 ymin;
    F32 xmax;
    F32 ymax;
    U32 label;
}BoxRect;

typedef struct {
    U32 num_class;
    F32 nms_threshold;
    U32 nms_top_k;
    U32 keep_top_k;
    F32 confidence_threshold;
}DetectionOutputDesc;

typedef struct {
    PoolingMode pm;
    U32 stride_h;
    U32 stride_w;
    U32 padding_top;
    U32 padding_bottom;
    U32 padding_left;
    U32 padding_right;
    U32 kernelSize_h;
    U32 kernelSize_w;
    RoundMode rm;
} PoolingDesc;

typedef struct {
    std::vector<F32> min_sizes;
    std::vector<F32> max_sizes;
    std::vector<F32> aspect_ratios;
    U32 flip;
    U32 clip;
    F32 variances[4];
    U32 image_h; 
    U32 image_w; 
    F32 step_h;
    F32 step_w;
    F32 offset;
} PriorBoxDesc;

typedef struct {
    bool biDirection;
    U32 numOutput;
    U32 numProjection;
    F32 forgetBias;
    F32 zoneoutCell;
    F32 zoneoutOutput;
    ActivationMode activationMode;
} LSTMDesc;

typedef struct {
    U32 coefficient_len;
    bool has_offset;
    BilateralSliceApplyMode mode;
} BilateralSliceApplyDesc;

typedef enum {
    DEPTHWISE_CONVOLUTION_ALGORITHM_DIRECT,
    DEPTHWISE_POINTWISE_CONVOLUTION_ALGORITHM_DIRECT,
    DEPTHWISE_POINTWISE_CONVOLUTION_ALGORITHM_DIRECT_NO_PADDING,
    DEPTHWISE_POINTWISE_CONVOLUTION_ALGORITHM_3X3S1P1,
    DEPTHWISE_POINTWISE_CONVOLUTION_ALGORITHM_GEMM,
    DEPTHWISE_CONVOLUTION_ALGORITHM_NULL
} DepthwiseConvolutionForwardAlgorithm;

#ifdef _USE_MALI
typedef struct {
    I32  algorithm;
    U32  best_w[2];
    U32  best_c[2];
    U32  best_k[2];
} ForwardRunInfoMali;
typedef ForwardRunInfoMali* ForwardRunInfoMali_t;

typedef struct {
    GCLHandle_t  handle;
    GCLMemDesc_t gclmemInputDesc;
    GCLMemDesc_t gclmemOutputDesc;
    GCLMemDesc_t gclmemFilterDesc;
    ForwardRunInfoMali_t forwardRunInfo;
} MaliInfo;
typedef MaliInfo* MaliInfo_t;
#endif

typedef union{
#ifdef _USE_MALI
    MaliInfo maliInfo;
#endif
} ExtInfo;
typedef ExtInfo* ExtInfo_t;
#endif
