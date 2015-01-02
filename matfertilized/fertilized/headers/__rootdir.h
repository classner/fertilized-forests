
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#ifndef MATFERTILIZED_MATLAB_HEADERS_ROOTDIR_H_
#define MATFERTILIZED_MATLAB_HEADERS_ROOTDIR_H_

#include <mex.h>

#include "./global.h"

#ifdef __cplusplus
extern "C"
{
#endif


    DllExport void * getForest_i_i_uint_fv_fv (

        unsigned int max_tree_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        unsigned int n_trees,
        void * deciders,
        void * leaf_managers,
        void * training
);
    DllExport void * getForest_f_f_uint_fv_fv (

        unsigned int max_tree_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        unsigned int n_trees,
        void * deciders,
        void * leaf_managers,
        void * training
);
    DllExport void * getForest_uint8_uint8_uint_fv_fv (

        unsigned int max_tree_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        unsigned int n_trees,
        void * deciders,
        void * leaf_managers,
        void * training
);
    DllExport void * getForest_uint8_int16_int16_hp_vhp (

        unsigned int max_tree_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        unsigned int n_trees,
        void * deciders,
        void * leaf_managers,
        void * training
);
    DllExport void * getForest_f_f_f_rpf_vprpff (

        unsigned int max_tree_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        unsigned int n_trees,
        void * deciders,
        void * leaf_managers,
        void * training
);
    DllExport void * getForest_d_d_d_rpd_vprpfd (

        unsigned int max_tree_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        unsigned int n_trees,
        void * deciders,
        void * leaf_managers,
        void * training
);


    DllExport void * getForestFromTrees_i_i_uint_fv_fv (

        void * trees,
        void * training
);
    DllExport void * getForestFromTrees_f_f_uint_fv_fv (

        void * trees,
        void * training
);
    DllExport void * getForestFromTrees_uint8_uint8_uint_fv_fv (

        void * trees,
        void * training
);
    DllExport void * getForestFromTrees_uint8_int16_int16_hp_vhp (

        void * trees,
        void * training
);
    DllExport void * getForestFromTrees_f_f_f_rpf_vprpff (

        void * trees,
        void * training
);
    DllExport void * getForestFromTrees_d_d_d_rpd_vprpfd (

        void * trees,
        void * training
);


    DllExport void * getCombineTrees_i_i_uint_fv_fv (

        void * trees
);
    DllExport void * getCombineTrees_f_f_uint_fv_fv (

        void * trees
);
    DllExport void * getCombineTrees_uint8_uint8_uint_fv_fv (

        void * trees
);
    DllExport void * getCombineTrees_uint8_int16_int16_hp_vhp (

        void * trees
);
    DllExport void * getCombineTrees_f_f_f_rpf_vprpff (

        void * trees
);
    DllExport void * getCombineTrees_d_d_d_rpd_vprpfd (

        void * trees
);


    DllExport void * getForestFromFile_i_i_uint_fv_fv (

        char* filename
);
    DllExport void * getForestFromFile_f_f_uint_fv_fv (

        char* filename
);
    DllExport void * getForestFromFile_uint8_uint8_uint_fv_fv (

        char* filename
);
    DllExport void * getForestFromFile_uint8_int16_int16_hp_vhp (

        char* filename
);
    DllExport void * getForestFromFile_f_f_f_rpf_vprpff (

        char* filename
);
    DllExport void * getForestFromFile_d_d_d_rpd_vprpfd (

        char* filename
);


    DllExport void fitForest_i_i_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        unsigned int num_threads
);
    DllExport void fitForest_f_f_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        unsigned int num_threads
);
    DllExport void fitForest_uint8_uint8_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        unsigned int num_threads
);
    DllExport void fitForest_uint8_int16_int16_hp_vhp (void *__instance,

        mxArray * data,
        mxArray * annotations,
        unsigned int num_threads
);
    DllExport void fitForest_f_f_f_rpf_vprpff (void *__instance,

        mxArray * data,
        mxArray * annotations,
        unsigned int num_threads
);
    DllExport void fitForest_d_d_d_rpd_vprpfd (void *__instance,

        mxArray * data,
        mxArray * annotations,
        unsigned int num_threads
);


    DllExport void fit_dprovForest_i_i_uint_fv_fv (void *__instance,

        void * fdata_provider,
        void * execution_strategy
);
    DllExport void fit_dprovForest_f_f_uint_fv_fv (void *__instance,

        void * fdata_provider,
        void * execution_strategy
);
    DllExport void fit_dprovForest_uint8_uint8_uint_fv_fv (void *__instance,

        void * fdata_provider,
        void * execution_strategy
);
    DllExport void fit_dprovForest_uint8_int16_int16_hp_vhp (void *__instance,

        void * fdata_provider,
        void * execution_strategy
);
    DllExport void fit_dprovForest_f_f_f_rpf_vprpff (void *__instance,

        void * fdata_provider,
        void * execution_strategy
);
    DllExport void fit_dprovForest_d_d_d_rpd_vprpfd (void *__instance,

        void * fdata_provider,
        void * execution_strategy
);


    DllExport mxArray * predictForest_i_i_uint_fv_fv (void *__instance,

        mxArray * data
);
    DllExport mxArray * predictForest_f_f_uint_fv_fv (void *__instance,

        mxArray * data
);
    DllExport mxArray * predictForest_uint8_uint8_uint_fv_fv (void *__instance,

        mxArray * data
);
    DllExport mxArray * predictForest_uint8_int16_int16_hp_vhp (void *__instance,

        mxArray * data
);
    DllExport mxArray * predictForest_f_f_f_rpf_vprpff (void *__instance,

        mxArray * data
);
    DllExport mxArray * predictForest_d_d_d_rpd_vprpfd (void *__instance,

        mxArray * data
);


    DllExport mxArray * predict_imageForest_i_i_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
    DllExport mxArray * predict_imageForest_f_f_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
    DllExport mxArray * predict_imageForest_uint8_uint8_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
    DllExport mxArray * predict_imageForest_uint8_int16_int16_hp_vhp (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
    DllExport mxArray * predict_imageForest_f_f_f_rpf_vprpff (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
    DllExport mxArray * predict_imageForest_d_d_d_rpd_vprpfd (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);


    DllExport size_t get_input_data_dimensionsForest_i_i_uint_fv_fv (void *__instance

);
    DllExport size_t get_input_data_dimensionsForest_f_f_uint_fv_fv (void *__instance

);
    DllExport size_t get_input_data_dimensionsForest_uint8_uint8_uint_fv_fv (void *__instance

);
    DllExport size_t get_input_data_dimensionsForest_uint8_int16_int16_hp_vhp (void *__instance

);
    DllExport size_t get_input_data_dimensionsForest_f_f_f_rpf_vprpff (void *__instance

);
    DllExport size_t get_input_data_dimensionsForest_d_d_d_rpd_vprpfd (void *__instance

);


    DllExport mxArray * get_tree_weightsForest_i_i_uint_fv_fv (void *__instance

);
    DllExport mxArray * get_tree_weightsForest_f_f_uint_fv_fv (void *__instance

);
    DllExport mxArray * get_tree_weightsForest_uint8_uint8_uint_fv_fv (void *__instance

);
    DllExport mxArray * get_tree_weightsForest_uint8_int16_int16_hp_vhp (void *__instance

);
    DllExport mxArray * get_tree_weightsForest_f_f_f_rpf_vprpff (void *__instance

);
    DllExport mxArray * get_tree_weightsForest_d_d_d_rpd_vprpfd (void *__instance

);


    DllExport int eqForest_i_i_uint_fv_fv (void *__instance,

        void * rhs
);
    DllExport int eqForest_f_f_uint_fv_fv (void *__instance,

        void * rhs
);
    DllExport int eqForest_uint8_uint8_uint_fv_fv (void *__instance,

        void * rhs
);
    DllExport int eqForest_uint8_int16_int16_hp_vhp (void *__instance,

        void * rhs
);
    DllExport int eqForest_f_f_f_rpf_vprpff (void *__instance,

        void * rhs
);
    DllExport int eqForest_d_d_d_rpd_vprpfd (void *__instance,

        void * rhs
);


    DllExport void saveForest_i_i_uint_fv_fv (void *__instance,

        char* filename
);
    DllExport void saveForest_f_f_uint_fv_fv (void *__instance,

        char* filename
);
    DllExport void saveForest_uint8_uint8_uint_fv_fv (void *__instance,

        char* filename
);
    DllExport void saveForest_uint8_int16_int16_hp_vhp (void *__instance,

        char* filename
);
    DllExport void saveForest_f_f_f_rpf_vprpff (void *__instance,

        char* filename
);
    DllExport void saveForest_d_d_d_rpd_vprpfd (void *__instance,

        char* filename
);
    DllExport void delete_Forest_i_i_uint_fv_fv(void *ptr);
    DllExport void delete_Forest_f_f_uint_fv_fv(void *ptr);
    DllExport void delete_Forest_uint8_uint8_uint_fv_fv(void *ptr);
    DllExport void delete_Forest_uint8_int16_int16_hp_vhp(void *ptr);
    DllExport void delete_Forest_f_f_f_rpf_vprpff(void *ptr);
    DllExport void delete_Forest_d_d_d_rpd_vprpfd(void *ptr);


    DllExport void * getTree_i_i_uint_fv_fv (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);
    DllExport void * getTree_f_f_uint_fv_fv (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);
    DllExport void * getTree_uint8_uint8_uint_fv_fv (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);
    DllExport void * getTree_uint8_int16_uint_fv_fv (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);
    DllExport void * getTree_uint8_int16_int16_fv_fv (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);
    DllExport void * getTree_uint8_int16_int16_hp_vhp (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);
    DllExport void * getTree_f_f_f_rpf_vprpff (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);
    DllExport void * getTree_d_d_d_rpd_vprpfd (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);


    DllExport void * getTreeFromFile_i_i_uint_fv_fv (

        char* filename
);
    DllExport void * getTreeFromFile_f_f_uint_fv_fv (

        char* filename
);
    DllExport void * getTreeFromFile_uint8_uint8_uint_fv_fv (

        char* filename
);
    DllExport void * getTreeFromFile_uint8_int16_uint_fv_fv (

        char* filename
);
    DllExport void * getTreeFromFile_uint8_int16_int16_fv_fv (

        char* filename
);
    DllExport void * getTreeFromFile_uint8_int16_int16_hp_vhp (

        char* filename
);
    DllExport void * getTreeFromFile_f_f_f_rpf_vprpff (

        char* filename
);
    DllExport void * getTreeFromFile_d_d_d_rpd_vprpfd (

        char* filename
);


    DllExport void make_nodeTree_i_i_uint_fv_fv (void *__instance,

        void * data_provider,
        int append_on_different
);
    DllExport void make_nodeTree_f_f_uint_fv_fv (void *__instance,

        void * data_provider,
        int append_on_different
);
    DllExport void make_nodeTree_uint8_uint8_uint_fv_fv (void *__instance,

        void * data_provider,
        int append_on_different
);
    DllExport void make_nodeTree_uint8_int16_uint_fv_fv (void *__instance,

        void * data_provider,
        int append_on_different
);
    DllExport void make_nodeTree_uint8_int16_int16_fv_fv (void *__instance,

        void * data_provider,
        int append_on_different
);
    DllExport void make_nodeTree_uint8_int16_int16_hp_vhp (void *__instance,

        void * data_provider,
        int append_on_different
);
    DllExport void make_nodeTree_f_f_f_rpf_vprpff (void *__instance,

        void * data_provider,
        int append_on_different
);
    DllExport void make_nodeTree_d_d_d_rpd_vprpfd (void *__instance,

        void * data_provider,
        int append_on_different
);


    DllExport void fitTree_i_i_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);
    DllExport void fitTree_f_f_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);
    DllExport void fitTree_uint8_uint8_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);
    DllExport void fitTree_uint8_int16_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);
    DllExport void fitTree_uint8_int16_int16_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);
    DllExport void fitTree_uint8_int16_int16_hp_vhp (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);
    DllExport void fitTree_f_f_f_rpf_vprpff (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);
    DllExport void fitTree_d_d_d_rpd_vprpfd (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);


    DllExport void fit_dprovTree_i_i_uint_fv_fv (void *__instance,

        void * data_provider,
        int complete_dfs
);
    DllExport void fit_dprovTree_f_f_uint_fv_fv (void *__instance,

        void * data_provider,
        int complete_dfs
);
    DllExport void fit_dprovTree_uint8_uint8_uint_fv_fv (void *__instance,

        void * data_provider,
        int complete_dfs
);
    DllExport void fit_dprovTree_uint8_int16_uint_fv_fv (void *__instance,

        void * data_provider,
        int complete_dfs
);
    DllExport void fit_dprovTree_uint8_int16_int16_fv_fv (void *__instance,

        void * data_provider,
        int complete_dfs
);
    DllExport void fit_dprovTree_uint8_int16_int16_hp_vhp (void *__instance,

        void * data_provider,
        int complete_dfs
);
    DllExport void fit_dprovTree_f_f_f_rpf_vprpff (void *__instance,

        void * data_provider,
        int complete_dfs
);
    DllExport void fit_dprovTree_d_d_d_rpd_vprpfd (void *__instance,

        void * data_provider,
        int complete_dfs
);


    DllExport mxArray * predictTree_i_i_uint_fv_fv (void *__instance,

        mxArray * data
);
    DllExport mxArray * predictTree_f_f_uint_fv_fv (void *__instance,

        mxArray * data
);
    DllExport mxArray * predictTree_uint8_uint8_uint_fv_fv (void *__instance,

        mxArray * data
);
    DllExport mxArray * predictTree_uint8_int16_uint_fv_fv (void *__instance,

        mxArray * data
);
    DllExport mxArray * predictTree_uint8_int16_int16_fv_fv (void *__instance,

        mxArray * data
);
    DllExport mxArray * predictTree_uint8_int16_int16_hp_vhp (void *__instance,

        mxArray * data
);
    DllExport mxArray * predictTree_f_f_f_rpf_vprpff (void *__instance,

        mxArray * data
);
    DllExport mxArray * predictTree_d_d_d_rpd_vprpfd (void *__instance,

        mxArray * data
);


    DllExport mxArray * predict_imageTree_i_i_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
    DllExport mxArray * predict_imageTree_f_f_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
    DllExport mxArray * predict_imageTree_uint8_uint8_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
    DllExport mxArray * predict_imageTree_uint8_int16_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
    DllExport mxArray * predict_imageTree_uint8_int16_int16_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
    DllExport mxArray * predict_imageTree_uint8_int16_int16_hp_vhp (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
    DllExport mxArray * predict_imageTree_f_f_f_rpf_vprpff (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
    DllExport mxArray * predict_imageTree_d_d_d_rpd_vprpfd (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);


    DllExport float get_weightTree_i_i_uint_fv_fv (void *__instance

);
    DllExport float get_weightTree_f_f_uint_fv_fv (void *__instance

);
    DllExport float get_weightTree_uint8_uint8_uint_fv_fv (void *__instance

);
    DllExport float get_weightTree_uint8_int16_uint_fv_fv (void *__instance

);
    DllExport float get_weightTree_uint8_int16_int16_fv_fv (void *__instance

);
    DllExport float get_weightTree_uint8_int16_int16_hp_vhp (void *__instance

);
    DllExport float get_weightTree_f_f_f_rpf_vprpff (void *__instance

);
    DllExport float get_weightTree_d_d_d_rpd_vprpfd (void *__instance

);


    DllExport size_t get_n_nodesTree_i_i_uint_fv_fv (void *__instance

);
    DllExport size_t get_n_nodesTree_f_f_uint_fv_fv (void *__instance

);
    DllExport size_t get_n_nodesTree_uint8_uint8_uint_fv_fv (void *__instance

);
    DllExport size_t get_n_nodesTree_uint8_int16_uint_fv_fv (void *__instance

);
    DllExport size_t get_n_nodesTree_uint8_int16_int16_fv_fv (void *__instance

);
    DllExport size_t get_n_nodesTree_uint8_int16_int16_hp_vhp (void *__instance

);
    DllExport size_t get_n_nodesTree_f_f_f_rpf_vprpff (void *__instance

);
    DllExport size_t get_n_nodesTree_d_d_d_rpd_vprpfd (void *__instance

);


    DllExport void set_weightTree_i_i_uint_fv_fv (void *__instance,

        float new_weight
);
    DllExport void set_weightTree_f_f_uint_fv_fv (void *__instance,

        float new_weight
);
    DllExport void set_weightTree_uint8_uint8_uint_fv_fv (void *__instance,

        float new_weight
);
    DllExport void set_weightTree_uint8_int16_uint_fv_fv (void *__instance,

        float new_weight
);
    DllExport void set_weightTree_uint8_int16_int16_fv_fv (void *__instance,

        float new_weight
);
    DllExport void set_weightTree_uint8_int16_int16_hp_vhp (void *__instance,

        float new_weight
);
    DllExport void set_weightTree_f_f_f_rpf_vprpff (void *__instance,

        float new_weight
);
    DllExport void set_weightTree_d_d_d_rpd_vprpfd (void *__instance,

        float new_weight
);


    DllExport size_t get_input_data_dimensionsTree_i_i_uint_fv_fv (void *__instance

);
    DllExport size_t get_input_data_dimensionsTree_f_f_uint_fv_fv (void *__instance

);
    DllExport size_t get_input_data_dimensionsTree_uint8_uint8_uint_fv_fv (void *__instance

);
    DllExport size_t get_input_data_dimensionsTree_uint8_int16_uint_fv_fv (void *__instance

);
    DllExport size_t get_input_data_dimensionsTree_uint8_int16_int16_fv_fv (void *__instance

);
    DllExport size_t get_input_data_dimensionsTree_uint8_int16_int16_hp_vhp (void *__instance

);
    DllExport size_t get_input_data_dimensionsTree_f_f_f_rpf_vprpff (void *__instance

);
    DllExport size_t get_input_data_dimensionsTree_d_d_d_rpd_vprpfd (void *__instance

);


    DllExport size_t get_samples_storedTree_i_i_uint_fv_fv (void *__instance

);
    DllExport size_t get_samples_storedTree_f_f_uint_fv_fv (void *__instance

);
    DllExport size_t get_samples_storedTree_uint8_uint8_uint_fv_fv (void *__instance

);
    DllExport size_t get_samples_storedTree_uint8_int16_uint_fv_fv (void *__instance

);
    DllExport size_t get_samples_storedTree_uint8_int16_int16_fv_fv (void *__instance

);
    DllExport size_t get_samples_storedTree_uint8_int16_int16_hp_vhp (void *__instance

);
    DllExport size_t get_samples_storedTree_f_f_f_rpf_vprpff (void *__instance

);
    DllExport size_t get_samples_storedTree_d_d_d_rpd_vprpfd (void *__instance

);


    DllExport int eqTree_i_i_uint_fv_fv (void *__instance,

        void * rhs
);
    DllExport int eqTree_f_f_uint_fv_fv (void *__instance,

        void * rhs
);
    DllExport int eqTree_uint8_uint8_uint_fv_fv (void *__instance,

        void * rhs
);
    DllExport int eqTree_uint8_int16_uint_fv_fv (void *__instance,

        void * rhs
);
    DllExport int eqTree_uint8_int16_int16_fv_fv (void *__instance,

        void * rhs
);
    DllExport int eqTree_uint8_int16_int16_hp_vhp (void *__instance,

        void * rhs
);
    DllExport int eqTree_f_f_f_rpf_vprpff (void *__instance,

        void * rhs
);
    DllExport int eqTree_d_d_d_rpd_vprpfd (void *__instance,

        void * rhs
);


    DllExport void saveTree_i_i_uint_fv_fv (void *__instance,

        char* filename
);
    DllExport void saveTree_f_f_uint_fv_fv (void *__instance,

        char* filename
);
    DllExport void saveTree_uint8_uint8_uint_fv_fv (void *__instance,

        char* filename
);
    DllExport void saveTree_uint8_int16_uint_fv_fv (void *__instance,

        char* filename
);
    DllExport void saveTree_uint8_int16_int16_fv_fv (void *__instance,

        char* filename
);
    DllExport void saveTree_uint8_int16_int16_hp_vhp (void *__instance,

        char* filename
);
    DllExport void saveTree_f_f_f_rpf_vprpff (void *__instance,

        char* filename
);
    DllExport void saveTree_d_d_d_rpd_vprpfd (void *__instance,

        char* filename
);
    DllExport void delete_Tree_i_i_uint_fv_fv(void *ptr);
    DllExport void delete_Tree_f_f_uint_fv_fv(void *ptr);
    DllExport void delete_Tree_uint8_uint8_uint_fv_fv(void *ptr);
    DllExport void delete_Tree_uint8_int16_uint_fv_fv(void *ptr);
    DllExport void delete_Tree_uint8_int16_int16_fv_fv(void *ptr);
    DllExport void delete_Tree_uint8_int16_int16_hp_vhp(void *ptr);
    DllExport void delete_Tree_f_f_f_rpf_vprpff(void *ptr);
    DllExport void delete_Tree_d_d_d_rpd_vprpfd(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_ROOTDIR_H_