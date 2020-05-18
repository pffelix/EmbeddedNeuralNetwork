/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Sun May 17 11:36:12 2020
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "network.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"

#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 5
#define AI_TOOLS_VERSION_MINOR 0
#define AI_TOOLS_VERSION_MICRO 0


#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 3
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "a2fd5368993dd38fd46aaf936c493ef1"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-5.0.0)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Sun May 17 11:36:12 2020"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array conv2d_2_scratch0_array;   /* Array #0 */
AI_STATIC ai_array conv2d_1_scratch0_array;   /* Array #1 */
AI_STATIC ai_array conv2d_scratch0_array;   /* Array #2 */
AI_STATIC ai_array dense_2_bias_array;   /* Array #3 */
AI_STATIC ai_array dense_2_weights_array;   /* Array #4 */
AI_STATIC ai_array dense_1_bias_array;   /* Array #5 */
AI_STATIC ai_array dense_1_weights_array;   /* Array #6 */
AI_STATIC ai_array dense_bias_array;   /* Array #7 */
AI_STATIC ai_array dense_weights_array;   /* Array #8 */
AI_STATIC ai_array backward_gru_bias_array;   /* Array #9 */
AI_STATIC ai_array backward_gru_recurrent_array;   /* Array #10 */
AI_STATIC ai_array backward_gru_kernel_array;   /* Array #11 */
AI_STATIC ai_array forward_gru_bias_array;   /* Array #12 */
AI_STATIC ai_array forward_gru_recurrent_array;   /* Array #13 */
AI_STATIC ai_array forward_gru_kernel_array;   /* Array #14 */
AI_STATIC ai_array conv2d_2_bias_array;   /* Array #15 */
AI_STATIC ai_array conv2d_2_weights_array;   /* Array #16 */
AI_STATIC ai_array conv2d_1_bias_array;   /* Array #17 */
AI_STATIC ai_array conv2d_1_weights_array;   /* Array #18 */
AI_STATIC ai_array conv2d_bias_array;   /* Array #19 */
AI_STATIC ai_array conv2d_weights_array;   /* Array #20 */
AI_STATIC ai_array input_0_output_array;   /* Array #21 */
AI_STATIC ai_array conv2d_output_array;   /* Array #22 */
AI_STATIC ai_array conv2d_1_output_array;   /* Array #23 */
AI_STATIC ai_array conv2d_2_output_array;   /* Array #24 */
AI_STATIC ai_array backward_gru_output_array;   /* Array #25 */
AI_STATIC ai_array forward_gru_output_array;   /* Array #26 */
AI_STATIC ai_array bidirectional_output_array;   /* Array #27 */
AI_STATIC ai_array dense_output_array;   /* Array #28 */
AI_STATIC ai_array dense_1_output_array;   /* Array #29 */
AI_STATIC ai_array dense_2_output_array;   /* Array #30 */
AI_STATIC ai_array activation_3_output_array;   /* Array #31 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor conv2d_2_scratch0;   /* Tensor #0 */
AI_STATIC ai_tensor conv2d_1_scratch0;   /* Tensor #1 */
AI_STATIC ai_tensor conv2d_scratch0;   /* Tensor #2 */
AI_STATIC ai_tensor dense_2_bias;   /* Tensor #3 */
AI_STATIC ai_tensor dense_2_weights;   /* Tensor #4 */
AI_STATIC ai_tensor dense_1_bias;   /* Tensor #5 */
AI_STATIC ai_tensor dense_1_weights;   /* Tensor #6 */
AI_STATIC ai_tensor dense_bias;   /* Tensor #7 */
AI_STATIC ai_tensor dense_weights;   /* Tensor #8 */
AI_STATIC ai_tensor backward_gru_bias;   /* Tensor #9 */
AI_STATIC ai_tensor backward_gru_recurrent;   /* Tensor #10 */
AI_STATIC ai_tensor backward_gru_kernel;   /* Tensor #11 */
AI_STATIC ai_tensor forward_gru_bias;   /* Tensor #12 */
AI_STATIC ai_tensor forward_gru_recurrent;   /* Tensor #13 */
AI_STATIC ai_tensor forward_gru_kernel;   /* Tensor #14 */
AI_STATIC ai_tensor conv2d_2_bias;   /* Tensor #15 */
AI_STATIC ai_tensor conv2d_2_weights;   /* Tensor #16 */
AI_STATIC ai_tensor conv2d_1_bias;   /* Tensor #17 */
AI_STATIC ai_tensor conv2d_1_weights;   /* Tensor #18 */
AI_STATIC ai_tensor conv2d_bias;   /* Tensor #19 */
AI_STATIC ai_tensor conv2d_weights;   /* Tensor #20 */
AI_STATIC ai_tensor input_0_output;   /* Tensor #21 */
AI_STATIC ai_tensor conv2d_output;   /* Tensor #22 */
AI_STATIC ai_tensor conv2d_1_output;   /* Tensor #23 */
AI_STATIC ai_tensor conv2d_2_output;   /* Tensor #24 */
AI_STATIC ai_tensor conv2d_2_output0;   /* Tensor #25 */
AI_STATIC ai_tensor backward_gru_output;   /* Tensor #26 */
AI_STATIC ai_tensor forward_gru_output;   /* Tensor #27 */
AI_STATIC ai_tensor bidirectional_output;   /* Tensor #28 */
AI_STATIC ai_tensor bidirectional_output0;   /* Tensor #29 */
AI_STATIC ai_tensor dense_output;   /* Tensor #30 */
AI_STATIC ai_tensor dense_1_output;   /* Tensor #31 */
AI_STATIC ai_tensor dense_2_output;   /* Tensor #32 */
AI_STATIC ai_tensor activation_3_output;   /* Tensor #33 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain conv2d_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain conv2d_1_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain conv2d_2_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain backward_gru_chain;   /* Chain #3 */
AI_STATIC_CONST ai_tensor_chain forward_gru_chain;   /* Chain #4 */
AI_STATIC_CONST ai_tensor_chain bidirectional_chain;   /* Chain #5 */
AI_STATIC_CONST ai_tensor_chain dense_chain;   /* Chain #6 */
AI_STATIC_CONST ai_tensor_chain dense_1_chain;   /* Chain #7 */
AI_STATIC_CONST ai_tensor_chain dense_2_chain;   /* Chain #8 */
AI_STATIC_CONST ai_tensor_chain activation_3_chain;   /* Chain #9 */


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_conv2d_nl_pool conv2d_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_1_layer; /* Layer #1 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_2_layer; /* Layer #2 */
AI_STATIC ai_layer_gru backward_gru_layer; /* Layer #3 */
AI_STATIC ai_layer_gru forward_gru_layer; /* Layer #4 */
AI_STATIC ai_layer_eltwise bidirectional_layer; /* Layer #5 */
AI_STATIC ai_layer_dense dense_layer; /* Layer #6 */
AI_STATIC ai_layer_dense dense_1_layer; /* Layer #7 */
AI_STATIC ai_layer_dense dense_2_layer; /* Layer #8 */
AI_STATIC ai_layer_nl activation_3_layer; /* Layer #9 */


/**  Array declarations section  **********************************************/
AI_ARRAY_OBJ_DECLARE(
    conv2d_2_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 16,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_1_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 64,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 520,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_2_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 8,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_2_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 128,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_1_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 16,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_1_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 512,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 32,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 1024,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    backward_gru_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 24,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    backward_gru_recurrent_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 48,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    backward_gru_kernel_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 1152,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    forward_gru_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 24,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    forward_gru_recurrent_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 48,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    forward_gru_kernel_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 1152,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_2_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 8,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_2_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 576,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_1_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 8,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_1_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 576,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 8,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 144,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    input_0_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
    NULL, NULL, 12480,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 6144,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_1_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 1536,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_2_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 768,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    backward_gru_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 32,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    forward_gru_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 32,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    bidirectional_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 32,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 32,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_1_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 16,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_2_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 8,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    activation_3_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
    NULL, NULL, 8,
     AI_STATIC)




/**  Tensor declarations section  *********************************************/
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_scratch0, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 8, 2, 1), AI_STRIDE_INIT(4, 4, 4, 32, 64),
  1, &conv2d_2_scratch0_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_scratch0, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 8, 8, 1), AI_STRIDE_INIT(4, 4, 4, 32, 256),
  1, &conv2d_1_scratch0_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_scratch0, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 8, 65, 1), AI_STRIDE_INIT(4, 4, 4, 32, 2080),
  1, &conv2d_scratch0_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_2_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &dense_2_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_2_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 16, 8, 1, 1), AI_STRIDE_INIT(4, 4, 64, 512, 512),
  1, &dense_2_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_1_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &dense_1_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_1_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 32, 16, 1, 1), AI_STRIDE_INIT(4, 4, 128, 2048, 2048),
  1, &dense_1_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &dense_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 32, 32, 1, 1), AI_STRIDE_INIT(4, 4, 128, 4096, 4096),
  1, &dense_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  backward_gru_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 4, 4, 96, 96),
  1, &backward_gru_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  backward_gru_recurrent, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 4, 1, 1, 12), AI_STRIDE_INIT(4, 4, 16, 16, 16),
  1, &backward_gru_recurrent_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  backward_gru_kernel, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 96, 1, 1, 12), AI_STRIDE_INIT(4, 4, 384, 384, 384),
  1, &backward_gru_kernel_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  forward_gru_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 4, 4, 96, 96),
  1, &forward_gru_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  forward_gru_recurrent, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 4, 1, 1, 12), AI_STRIDE_INIT(4, 4, 16, 16, 16),
  1, &forward_gru_recurrent_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  forward_gru_kernel, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 96, 1, 1, 12), AI_STRIDE_INIT(4, 4, 384, 384, 384),
  1, &forward_gru_kernel_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &conv2d_2_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 8, 3, 3, 8), AI_STRIDE_INIT(4, 4, 32, 96, 288),
  1, &conv2d_2_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &conv2d_1_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 8, 3, 3, 8), AI_STRIDE_INIT(4, 4, 32, 96, 288),
  1, &conv2d_1_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &conv2d_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 2, 3, 3, 8), AI_STRIDE_INIT(4, 4, 8, 24, 72),
  1, &conv2d_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  input_0_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 2, 65, 96), AI_STRIDE_INIT(4, 4, 4, 8, 520),
  1, &input_0_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 8, 8, 96), AI_STRIDE_INIT(4, 4, 4, 32, 256),
  1, &conv2d_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 8, 2, 96), AI_STRIDE_INIT(4, 4, 4, 32, 64),
  1, &conv2d_1_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 8, 1, 96), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &conv2d_2_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_output0, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 96, 1, 8), AI_STRIDE_INIT(4, 4, 4, 384, 384),
  1, &conv2d_2_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  backward_gru_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 4, 1, 8), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &backward_gru_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  forward_gru_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 4, 1, 8), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &forward_gru_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  bidirectional_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 4, 1, 8), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &bidirectional_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  bidirectional_output0, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &bidirectional_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &dense_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_1_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &dense_1_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_2_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &dense_2_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  activation_3_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &activation_3_output_array, NULL)


/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&input_0_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_weights, &conv2d_bias, NULL),
  AI_TENSOR_LIST_ENTRY(&conv2d_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_layer, 0,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &conv2d_1_layer, AI_STATIC,
  .tensors = &conv2d_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .pool_size = AI_SHAPE_2D_INIT(8, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(8, 1), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&conv2d_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_1_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_1_weights, &conv2d_1_bias, NULL),
  AI_TENSOR_LIST_ENTRY(&conv2d_1_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_1_layer, 5,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &conv2d_2_layer, AI_STATIC,
  .tensors = &conv2d_1_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .pool_size = AI_SHAPE_2D_INIT(4, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(4, 1), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&conv2d_1_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_2_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_2_weights, &conv2d_2_bias, NULL),
  AI_TENSOR_LIST_ENTRY(&conv2d_2_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_2_layer, 10,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &backward_gru_layer, AI_STATIC,
  .tensors = &conv2d_2_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .pool_size = AI_SHAPE_2D_INIT(2, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 1), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  backward_gru_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&conv2d_2_output0),
  AI_TENSOR_LIST_ENTRY(&backward_gru_output),
  AI_TENSOR_LIST_ENTRY(&backward_gru_kernel, &backward_gru_recurrent, &backward_gru_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  backward_gru_layer, 16,
  GRU_TYPE,
  gru, forward_gru,
  &AI_NET_OBJ_INSTANCE, &forward_gru_layer, AI_STATIC,
  .tensors = &backward_gru_chain, 
  .n_units = 4, 
  .activation_nl = ai_math_tanh, 
  .recurrent_nl = ai_math_sigmoid, 
  .go_backwards = true, 
  .reverse_seq = true, 
  .reset_after = true, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  forward_gru_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&conv2d_2_output0),
  AI_TENSOR_LIST_ENTRY(&forward_gru_output),
  AI_TENSOR_LIST_ENTRY(&forward_gru_kernel, &forward_gru_recurrent, &forward_gru_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  forward_gru_layer, 16,
  GRU_TYPE,
  gru, forward_gru,
  &AI_NET_OBJ_INSTANCE, &bidirectional_layer, AI_STATIC,
  .tensors = &forward_gru_chain, 
  .n_units = 4, 
  .activation_nl = ai_math_tanh, 
  .recurrent_nl = ai_math_sigmoid, 
  .go_backwards = false, 
  .reverse_seq = false, 
  .reset_after = true, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  bidirectional_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&forward_gru_output, &backward_gru_output),
  AI_TENSOR_LIST_ENTRY(&bidirectional_output),
  AI_TENSOR_LIST_EMPTY,
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  bidirectional_layer, 16,
  ELTWISE_TYPE,
  eltwise, forward_eltwise,
  &AI_NET_OBJ_INSTANCE, &dense_layer, AI_STATIC,
  .tensors = &bidirectional_chain, 
  .operation = ai_mul, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&bidirectional_output0),
  AI_TENSOR_LIST_ENTRY(&dense_output),
  AI_TENSOR_LIST_ENTRY(&dense_weights, &dense_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_layer, 18,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &dense_1_layer, AI_STATIC,
  .tensors = &dense_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&dense_output),
  AI_TENSOR_LIST_ENTRY(&dense_1_output),
  AI_TENSOR_LIST_ENTRY(&dense_1_weights, &dense_1_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_1_layer, 19,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &dense_2_layer, AI_STATIC,
  .tensors = &dense_1_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&dense_1_output),
  AI_TENSOR_LIST_ENTRY(&dense_2_output),
  AI_TENSOR_LIST_ENTRY(&dense_2_weights, &dense_2_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_2_layer, 20,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &activation_3_layer, AI_STATIC,
  .tensors = &dense_2_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  activation_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&dense_2_output),
  AI_TENSOR_LIST_ENTRY(&activation_3_output),
  AI_TENSOR_LIST_EMPTY,
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  activation_3_layer, 21,
  NL_TYPE,
  nl, forward_sm,
  &AI_NET_OBJ_INSTANCE, &activation_3_layer, AI_STATIC,
  .tensors = &activation_3_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 21952, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 32800, 1,
                     NULL),
  AI_TENSOR_LIST_IO_ENTRY(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_0_output),
  AI_TENSOR_LIST_IO_ENTRY(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &activation_3_output),
  &conv2d_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, 4));
  AI_ASSERT(activations)
  AI_UNUSED(net_ctx)

  {
    /* Updating activations (byte) offsets */
    conv2d_2_scratch0_array.data = AI_PTR(activations + 0);
    conv2d_2_scratch0_array.data_start = AI_PTR(activations + 0);
    conv2d_1_scratch0_array.data = AI_PTR(activations + 0);
    conv2d_1_scratch0_array.data_start = AI_PTR(activations + 0);
    conv2d_scratch0_array.data = AI_PTR(activations + 0);
    conv2d_scratch0_array.data_start = AI_PTR(activations + 0);
    input_0_output_array.data = AI_PTR(NULL);
    input_0_output_array.data_start = AI_PTR(NULL);
    conv2d_output_array.data = AI_PTR(activations + 2080);
    conv2d_output_array.data_start = AI_PTR(activations + 2080);
    conv2d_1_output_array.data = AI_PTR(activations + 26656);
    conv2d_1_output_array.data_start = AI_PTR(activations + 26656);
    conv2d_2_output_array.data = AI_PTR(activations + 64);
    conv2d_2_output_array.data_start = AI_PTR(activations + 64);
    backward_gru_output_array.data = AI_PTR(activations + 3136);
    backward_gru_output_array.data_start = AI_PTR(activations + 3136);
    forward_gru_output_array.data = AI_PTR(activations + 3264);
    forward_gru_output_array.data_start = AI_PTR(activations + 3264);
    bidirectional_output_array.data = AI_PTR(activations + 0);
    bidirectional_output_array.data_start = AI_PTR(activations + 0);
    dense_output_array.data = AI_PTR(activations + 128);
    dense_output_array.data_start = AI_PTR(activations + 128);
    dense_1_output_array.data = AI_PTR(activations + 0);
    dense_1_output_array.data_start = AI_PTR(activations + 0);
    dense_2_output_array.data = AI_PTR(activations + 64);
    dense_2_output_array.data_start = AI_PTR(activations + 64);
    activation_3_output_array.data = AI_PTR(NULL);
    activation_3_output_array.data_start = AI_PTR(NULL);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT(weights)
  AI_UNUSED(net_ctx)

  {
    /* Updating weights (byte) offsets */
    
    dense_2_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_2_bias_array.data = AI_PTR(weights + 21920);
    dense_2_bias_array.data_start = AI_PTR(weights + 21920);
    dense_2_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_2_weights_array.data = AI_PTR(weights + 21408);
    dense_2_weights_array.data_start = AI_PTR(weights + 21408);
    dense_1_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_1_bias_array.data = AI_PTR(weights + 21344);
    dense_1_bias_array.data_start = AI_PTR(weights + 21344);
    dense_1_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_1_weights_array.data = AI_PTR(weights + 19296);
    dense_1_weights_array.data_start = AI_PTR(weights + 19296);
    dense_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_bias_array.data = AI_PTR(weights + 19168);
    dense_bias_array.data_start = AI_PTR(weights + 19168);
    dense_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_weights_array.data = AI_PTR(weights + 15072);
    dense_weights_array.data_start = AI_PTR(weights + 15072);
    backward_gru_bias_array.format |= AI_FMT_FLAG_CONST;
    backward_gru_bias_array.data = AI_PTR(weights + 14976);
    backward_gru_bias_array.data_start = AI_PTR(weights + 14976);
    backward_gru_recurrent_array.format |= AI_FMT_FLAG_CONST;
    backward_gru_recurrent_array.data = AI_PTR(weights + 14784);
    backward_gru_recurrent_array.data_start = AI_PTR(weights + 14784);
    backward_gru_kernel_array.format |= AI_FMT_FLAG_CONST;
    backward_gru_kernel_array.data = AI_PTR(weights + 10176);
    backward_gru_kernel_array.data_start = AI_PTR(weights + 10176);
    forward_gru_bias_array.format |= AI_FMT_FLAG_CONST;
    forward_gru_bias_array.data = AI_PTR(weights + 10080);
    forward_gru_bias_array.data_start = AI_PTR(weights + 10080);
    forward_gru_recurrent_array.format |= AI_FMT_FLAG_CONST;
    forward_gru_recurrent_array.data = AI_PTR(weights + 9888);
    forward_gru_recurrent_array.data_start = AI_PTR(weights + 9888);
    forward_gru_kernel_array.format |= AI_FMT_FLAG_CONST;
    forward_gru_kernel_array.data = AI_PTR(weights + 5280);
    forward_gru_kernel_array.data_start = AI_PTR(weights + 5280);
    conv2d_2_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_2_bias_array.data = AI_PTR(weights + 5248);
    conv2d_2_bias_array.data_start = AI_PTR(weights + 5248);
    conv2d_2_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_2_weights_array.data = AI_PTR(weights + 2944);
    conv2d_2_weights_array.data_start = AI_PTR(weights + 2944);
    conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_bias_array.data = AI_PTR(weights + 2912);
    conv2d_1_bias_array.data_start = AI_PTR(weights + 2912);
    conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_weights_array.data = AI_PTR(weights + 608);
    conv2d_1_weights_array.data_start = AI_PTR(weights + 608);
    conv2d_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_bias_array.data = AI_PTR(weights + 576);
    conv2d_bias_array.data_start = AI_PTR(weights + 576);
    conv2d_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_weights_array.data = AI_PTR(weights + 0);
    conv2d_weights_array.data_start = AI_PTR(weights + 0);
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1587120,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if ( !ai_platform_api_get_network_report(network, &r) ) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= network_configure_weights(net_ctx, &params->params);
  ok &= network_configure_activations(net_ctx, &params->activations);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}

#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

