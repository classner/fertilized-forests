
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


     void * getForest_i_i_uint_fv_fv (

        unsigned int max_tree_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        unsigned int n_trees,
        void * deciders,
        void * leaf_managers,
        void * training
);
     void * getForest_f_f_uint_fv_fv (

        unsigned int max_tree_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        unsigned int n_trees,
        void * deciders,
        void * leaf_managers,
        void * training
);
     void * getForest_d_d_uint_fv_fv (

        unsigned int max_tree_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        unsigned int n_trees,
        void * deciders,
        void * leaf_managers,
        void * training
);
     void * getForest_uint8_uint8_uint_fv_fv (

        unsigned int max_tree_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        unsigned int n_trees,
        void * deciders,
        void * leaf_managers,
        void * training
);
     void * getForest_uint8_int16_int16_hp_vhp (

        unsigned int max_tree_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        unsigned int n_trees,
        void * deciders,
        void * leaf_managers,
        void * training
);
     void * getForest_f_f_f_rpf_vprpff (

        unsigned int max_tree_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        unsigned int n_trees,
        void * deciders,
        void * leaf_managers,
        void * training
);
     void * getForest_d_d_d_rpd_vprpfd (

        unsigned int max_tree_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        unsigned int n_trees,
        void * deciders,
        void * leaf_managers,
        void * training
);


     void * getForestFromTrees_i_i_uint_fv_fv (

        void * trees,
        void * training
);
     void * getForestFromTrees_f_f_uint_fv_fv (

        void * trees,
        void * training
);
     void * getForestFromTrees_d_d_uint_fv_fv (

        void * trees,
        void * training
);
     void * getForestFromTrees_uint8_uint8_uint_fv_fv (

        void * trees,
        void * training
);
     void * getForestFromTrees_uint8_int16_int16_hp_vhp (

        void * trees,
        void * training
);
     void * getForestFromTrees_f_f_f_rpf_vprpff (

        void * trees,
        void * training
);
     void * getForestFromTrees_d_d_d_rpd_vprpfd (

        void * trees,
        void * training
);


     void * getCombineTrees_i_i_uint_fv_fv (

        void * trees
);
     void * getCombineTrees_f_f_uint_fv_fv (

        void * trees
);
     void * getCombineTrees_d_d_uint_fv_fv (

        void * trees
);
     void * getCombineTrees_uint8_uint8_uint_fv_fv (

        void * trees
);
     void * getCombineTrees_uint8_int16_int16_hp_vhp (

        void * trees
);
     void * getCombineTrees_f_f_f_rpf_vprpff (

        void * trees
);
     void * getCombineTrees_d_d_d_rpd_vprpfd (

        void * trees
);


     void * getForestFromFile_i_i_uint_fv_fv (

        char* filename
);
     void * getForestFromFile_f_f_uint_fv_fv (

        char* filename
);
     void * getForestFromFile_d_d_uint_fv_fv (

        char* filename
);
     void * getForestFromFile_uint8_uint8_uint_fv_fv (

        char* filename
);
     void * getForestFromFile_uint8_int16_int16_hp_vhp (

        char* filename
);
     void * getForestFromFile_f_f_f_rpf_vprpff (

        char* filename
);
     void * getForestFromFile_d_d_d_rpd_vprpfd (

        char* filename
);


     void fitForest_i_i_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        unsigned int num_threads
);
     void fitForest_f_f_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        unsigned int num_threads
);
     void fitForest_d_d_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        unsigned int num_threads
);
     void fitForest_uint8_uint8_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        unsigned int num_threads
);
     void fitForest_uint8_int16_int16_hp_vhp (void *__instance,

        mxArray * data,
        mxArray * annotations,
        unsigned int num_threads
);
     void fitForest_f_f_f_rpf_vprpff (void *__instance,

        mxArray * data,
        mxArray * annotations,
        unsigned int num_threads
);
     void fitForest_d_d_d_rpd_vprpfd (void *__instance,

        mxArray * data,
        mxArray * annotations,
        unsigned int num_threads
);


     mxArray * depthsForest_i_i_uint_fv_fv (void *__instance

);
     mxArray * depthsForest_f_f_uint_fv_fv (void *__instance

);
     mxArray * depthsForest_d_d_uint_fv_fv (void *__instance

);
     mxArray * depthsForest_uint8_uint8_uint_fv_fv (void *__instance

);
     mxArray * depthsForest_uint8_int16_int16_hp_vhp (void *__instance

);
     mxArray * depthsForest_f_f_f_rpf_vprpff (void *__instance

);
     mxArray * depthsForest_d_d_d_rpd_vprpfd (void *__instance

);


     void fit_dprovForest_i_i_uint_fv_fv (void *__instance,

        void * fdata_provider,
        void * execution_strategy
);
     void fit_dprovForest_f_f_uint_fv_fv (void *__instance,

        void * fdata_provider,
        void * execution_strategy
);
     void fit_dprovForest_d_d_uint_fv_fv (void *__instance,

        void * fdata_provider,
        void * execution_strategy
);
     void fit_dprovForest_uint8_uint8_uint_fv_fv (void *__instance,

        void * fdata_provider,
        void * execution_strategy
);
     void fit_dprovForest_uint8_int16_int16_hp_vhp (void *__instance,

        void * fdata_provider,
        void * execution_strategy
);
     void fit_dprovForest_f_f_f_rpf_vprpff (void *__instance,

        void * fdata_provider,
        void * execution_strategy
);
     void fit_dprovForest_d_d_d_rpd_vprpfd (void *__instance,

        void * fdata_provider,
        void * execution_strategy
);


     mxArray * predictForest_i_i_uint_fv_fv (void *__instance,

        mxArray * data,
        int num_threads
);
     mxArray * predictForest_f_f_uint_fv_fv (void *__instance,

        mxArray * data,
        int num_threads
);
     mxArray * predictForest_d_d_uint_fv_fv (void *__instance,

        mxArray * data,
        int num_threads
);
     mxArray * predictForest_uint8_uint8_uint_fv_fv (void *__instance,

        mxArray * data,
        int num_threads
);
     mxArray * predictForest_uint8_int16_int16_hp_vhp (void *__instance,

        mxArray * data,
        int num_threads
);
     mxArray * predictForest_f_f_f_rpf_vprpff (void *__instance,

        mxArray * data,
        int num_threads
);
     mxArray * predictForest_d_d_d_rpd_vprpfd (void *__instance,

        mxArray * data,
        int num_threads
);


     mxArray * predict_imageForest_i_i_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
     mxArray * predict_imageForest_f_f_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
     mxArray * predict_imageForest_d_d_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
     mxArray * predict_imageForest_uint8_uint8_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
     mxArray * predict_imageForest_uint8_int16_int16_hp_vhp (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
     mxArray * predict_imageForest_f_f_f_rpf_vprpff (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
     mxArray * predict_imageForest_d_d_d_rpd_vprpfd (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);


     size_t get_input_data_dimensionsForest_i_i_uint_fv_fv (void *__instance

);
     size_t get_input_data_dimensionsForest_f_f_uint_fv_fv (void *__instance

);
     size_t get_input_data_dimensionsForest_d_d_uint_fv_fv (void *__instance

);
     size_t get_input_data_dimensionsForest_uint8_uint8_uint_fv_fv (void *__instance

);
     size_t get_input_data_dimensionsForest_uint8_int16_int16_hp_vhp (void *__instance

);
     size_t get_input_data_dimensionsForest_f_f_f_rpf_vprpff (void *__instance

);
     size_t get_input_data_dimensionsForest_d_d_d_rpd_vprpfd (void *__instance

);


     mxArray * compute_feature_importancesForest_i_i_uint_fv_fv (void *__instance

);
     mxArray * compute_feature_importancesForest_f_f_uint_fv_fv (void *__instance

);
     mxArray * compute_feature_importancesForest_d_d_uint_fv_fv (void *__instance

);
     mxArray * compute_feature_importancesForest_uint8_uint8_uint_fv_fv (void *__instance

);
     mxArray * compute_feature_importancesForest_uint8_int16_int16_hp_vhp (void *__instance

);
     mxArray * compute_feature_importancesForest_f_f_f_rpf_vprpff (void *__instance

);
     mxArray * compute_feature_importancesForest_d_d_d_rpd_vprpfd (void *__instance

);


     mxArray * get_tree_weightsForest_i_i_uint_fv_fv (void *__instance

);
     mxArray * get_tree_weightsForest_f_f_uint_fv_fv (void *__instance

);
     mxArray * get_tree_weightsForest_d_d_uint_fv_fv (void *__instance

);
     mxArray * get_tree_weightsForest_uint8_uint8_uint_fv_fv (void *__instance

);
     mxArray * get_tree_weightsForest_uint8_int16_int16_hp_vhp (void *__instance

);
     mxArray * get_tree_weightsForest_f_f_f_rpf_vprpff (void *__instance

);
     mxArray * get_tree_weightsForest_d_d_d_rpd_vprpfd (void *__instance

);


     int eqForest_i_i_uint_fv_fv (void *__instance,

        void * rhs
);
     int eqForest_f_f_uint_fv_fv (void *__instance,

        void * rhs
);
     int eqForest_d_d_uint_fv_fv (void *__instance,

        void * rhs
);
     int eqForest_uint8_uint8_uint_fv_fv (void *__instance,

        void * rhs
);
     int eqForest_uint8_int16_int16_hp_vhp (void *__instance,

        void * rhs
);
     int eqForest_f_f_f_rpf_vprpff (void *__instance,

        void * rhs
);
     int eqForest_d_d_d_rpd_vprpfd (void *__instance,

        void * rhs
);


     void saveForest_i_i_uint_fv_fv (void *__instance,

        char* filename
);
     void saveForest_f_f_uint_fv_fv (void *__instance,

        char* filename
);
     void saveForest_d_d_uint_fv_fv (void *__instance,

        char* filename
);
     void saveForest_uint8_uint8_uint_fv_fv (void *__instance,

        char* filename
);
     void saveForest_uint8_int16_int16_hp_vhp (void *__instance,

        char* filename
);
     void saveForest_f_f_f_rpf_vprpff (void *__instance,

        char* filename
);
     void saveForest_d_d_d_rpd_vprpfd (void *__instance,

        char* filename
);
     void delete_Forest_i_i_uint_fv_fv(void *ptr);
     void delete_Forest_f_f_uint_fv_fv(void *ptr);
     void delete_Forest_d_d_uint_fv_fv(void *ptr);
     void delete_Forest_uint8_uint8_uint_fv_fv(void *ptr);
     void delete_Forest_uint8_int16_int16_hp_vhp(void *ptr);
     void delete_Forest_f_f_f_rpf_vprpff(void *ptr);
     void delete_Forest_d_d_d_rpd_vprpfd(void *ptr);


     void * getTree_i_i_uint_fv_fv (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);
     void * getTree_f_f_uint_fv_fv (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);
     void * getTree_d_d_uint_fv_fv (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);
     void * getTree_uint8_uint8_uint_fv_fv (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);
     void * getTree_uint8_int16_uint_fv_fv (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);
     void * getTree_uint8_int16_int16_fv_fv (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);
     void * getTree_uint8_int16_int16_hp_vhp (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);
     void * getTree_f_f_f_rpf_vprpff (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);
     void * getTree_d_d_d_rpd_vprpfd (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
);


     void * getTreeFromFile_i_i_uint_fv_fv (

        char* filename
);
     void * getTreeFromFile_f_f_uint_fv_fv (

        char* filename
);
     void * getTreeFromFile_d_d_uint_fv_fv (

        char* filename
);
     void * getTreeFromFile_uint8_uint8_uint_fv_fv (

        char* filename
);
     void * getTreeFromFile_uint8_int16_uint_fv_fv (

        char* filename
);
     void * getTreeFromFile_uint8_int16_int16_fv_fv (

        char* filename
);
     void * getTreeFromFile_uint8_int16_int16_hp_vhp (

        char* filename
);
     void * getTreeFromFile_f_f_f_rpf_vprpff (

        char* filename
);
     void * getTreeFromFile_d_d_d_rpd_vprpfd (

        char* filename
);


     void make_nodeTree_i_i_uint_fv_fv (void *__instance,

        void * data_provider,
        int append_on_different
);
     void make_nodeTree_f_f_uint_fv_fv (void *__instance,

        void * data_provider,
        int append_on_different
);
     void make_nodeTree_d_d_uint_fv_fv (void *__instance,

        void * data_provider,
        int append_on_different
);
     void make_nodeTree_uint8_uint8_uint_fv_fv (void *__instance,

        void * data_provider,
        int append_on_different
);
     void make_nodeTree_uint8_int16_uint_fv_fv (void *__instance,

        void * data_provider,
        int append_on_different
);
     void make_nodeTree_uint8_int16_int16_fv_fv (void *__instance,

        void * data_provider,
        int append_on_different
);
     void make_nodeTree_uint8_int16_int16_hp_vhp (void *__instance,

        void * data_provider,
        int append_on_different
);
     void make_nodeTree_f_f_f_rpf_vprpff (void *__instance,

        void * data_provider,
        int append_on_different
);
     void make_nodeTree_d_d_d_rpd_vprpfd (void *__instance,

        void * data_provider,
        int append_on_different
);


     size_t depthTree_i_i_uint_fv_fv (void *__instance

);
     size_t depthTree_f_f_uint_fv_fv (void *__instance

);
     size_t depthTree_d_d_uint_fv_fv (void *__instance

);
     size_t depthTree_uint8_uint8_uint_fv_fv (void *__instance

);
     size_t depthTree_uint8_int16_uint_fv_fv (void *__instance

);
     size_t depthTree_uint8_int16_int16_fv_fv (void *__instance

);
     size_t depthTree_uint8_int16_int16_hp_vhp (void *__instance

);
     size_t depthTree_f_f_f_rpf_vprpff (void *__instance

);
     size_t depthTree_d_d_d_rpd_vprpfd (void *__instance

);


     void fitTree_i_i_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);
     void fitTree_f_f_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);
     void fitTree_d_d_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);
     void fitTree_uint8_uint8_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);
     void fitTree_uint8_int16_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);
     void fitTree_uint8_int16_int16_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);
     void fitTree_uint8_int16_int16_hp_vhp (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);
     void fitTree_f_f_f_rpf_vprpff (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);
     void fitTree_d_d_d_rpd_vprpfd (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
);


     void fit_dprovTree_i_i_uint_fv_fv (void *__instance,

        void * data_provider,
        int complete_dfs
);
     void fit_dprovTree_f_f_uint_fv_fv (void *__instance,

        void * data_provider,
        int complete_dfs
);
     void fit_dprovTree_d_d_uint_fv_fv (void *__instance,

        void * data_provider,
        int complete_dfs
);
     void fit_dprovTree_uint8_uint8_uint_fv_fv (void *__instance,

        void * data_provider,
        int complete_dfs
);
     void fit_dprovTree_uint8_int16_uint_fv_fv (void *__instance,

        void * data_provider,
        int complete_dfs
);
     void fit_dprovTree_uint8_int16_int16_fv_fv (void *__instance,

        void * data_provider,
        int complete_dfs
);
     void fit_dprovTree_uint8_int16_int16_hp_vhp (void *__instance,

        void * data_provider,
        int complete_dfs
);
     void fit_dprovTree_f_f_f_rpf_vprpff (void *__instance,

        void * data_provider,
        int complete_dfs
);
     void fit_dprovTree_d_d_d_rpd_vprpfd (void *__instance,

        void * data_provider,
        int complete_dfs
);


     mxArray * predictTree_i_i_uint_fv_fv (void *__instance,

        mxArray * data,
        int num_threads
);
     mxArray * predictTree_f_f_uint_fv_fv (void *__instance,

        mxArray * data,
        int num_threads
);
     mxArray * predictTree_d_d_uint_fv_fv (void *__instance,

        mxArray * data,
        int num_threads
);
     mxArray * predictTree_uint8_uint8_uint_fv_fv (void *__instance,

        mxArray * data,
        int num_threads
);
     mxArray * predictTree_uint8_int16_uint_fv_fv (void *__instance,

        mxArray * data,
        int num_threads
);
     mxArray * predictTree_uint8_int16_int16_fv_fv (void *__instance,

        mxArray * data,
        int num_threads
);
     mxArray * predictTree_uint8_int16_int16_hp_vhp (void *__instance,

        mxArray * data,
        int num_threads
);
     mxArray * predictTree_f_f_f_rpf_vprpff (void *__instance,

        mxArray * data,
        int num_threads
);
     mxArray * predictTree_d_d_d_rpd_vprpfd (void *__instance,

        mxArray * data,
        int num_threads
);


     mxArray * predict_imageTree_i_i_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
     mxArray * predict_imageTree_f_f_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
     mxArray * predict_imageTree_d_d_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
     mxArray * predict_imageTree_uint8_uint8_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
     mxArray * predict_imageTree_uint8_int16_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
     mxArray * predict_imageTree_uint8_int16_int16_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
     mxArray * predict_imageTree_uint8_int16_int16_hp_vhp (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
     mxArray * predict_imageTree_f_f_f_rpf_vprpff (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);
     mxArray * predict_imageTree_d_d_d_rpd_vprpfd (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
);


     float get_weightTree_i_i_uint_fv_fv (void *__instance

);
     float get_weightTree_f_f_uint_fv_fv (void *__instance

);
     float get_weightTree_d_d_uint_fv_fv (void *__instance

);
     float get_weightTree_uint8_uint8_uint_fv_fv (void *__instance

);
     float get_weightTree_uint8_int16_uint_fv_fv (void *__instance

);
     float get_weightTree_uint8_int16_int16_fv_fv (void *__instance

);
     float get_weightTree_uint8_int16_int16_hp_vhp (void *__instance

);
     float get_weightTree_f_f_f_rpf_vprpff (void *__instance

);
     float get_weightTree_d_d_d_rpd_vprpfd (void *__instance

);


     size_t get_n_nodesTree_i_i_uint_fv_fv (void *__instance

);
     size_t get_n_nodesTree_f_f_uint_fv_fv (void *__instance

);
     size_t get_n_nodesTree_d_d_uint_fv_fv (void *__instance

);
     size_t get_n_nodesTree_uint8_uint8_uint_fv_fv (void *__instance

);
     size_t get_n_nodesTree_uint8_int16_uint_fv_fv (void *__instance

);
     size_t get_n_nodesTree_uint8_int16_int16_fv_fv (void *__instance

);
     size_t get_n_nodesTree_uint8_int16_int16_hp_vhp (void *__instance

);
     size_t get_n_nodesTree_f_f_f_rpf_vprpff (void *__instance

);
     size_t get_n_nodesTree_d_d_d_rpd_vprpfd (void *__instance

);


     void set_weightTree_i_i_uint_fv_fv (void *__instance,

        float new_weight
);
     void set_weightTree_f_f_uint_fv_fv (void *__instance,

        float new_weight
);
     void set_weightTree_d_d_uint_fv_fv (void *__instance,

        float new_weight
);
     void set_weightTree_uint8_uint8_uint_fv_fv (void *__instance,

        float new_weight
);
     void set_weightTree_uint8_int16_uint_fv_fv (void *__instance,

        float new_weight
);
     void set_weightTree_uint8_int16_int16_fv_fv (void *__instance,

        float new_weight
);
     void set_weightTree_uint8_int16_int16_hp_vhp (void *__instance,

        float new_weight
);
     void set_weightTree_f_f_f_rpf_vprpff (void *__instance,

        float new_weight
);
     void set_weightTree_d_d_d_rpd_vprpfd (void *__instance,

        float new_weight
);


     size_t get_input_data_dimensionsTree_i_i_uint_fv_fv (void *__instance

);
     size_t get_input_data_dimensionsTree_f_f_uint_fv_fv (void *__instance

);
     size_t get_input_data_dimensionsTree_d_d_uint_fv_fv (void *__instance

);
     size_t get_input_data_dimensionsTree_uint8_uint8_uint_fv_fv (void *__instance

);
     size_t get_input_data_dimensionsTree_uint8_int16_uint_fv_fv (void *__instance

);
     size_t get_input_data_dimensionsTree_uint8_int16_int16_fv_fv (void *__instance

);
     size_t get_input_data_dimensionsTree_uint8_int16_int16_hp_vhp (void *__instance

);
     size_t get_input_data_dimensionsTree_f_f_f_rpf_vprpff (void *__instance

);
     size_t get_input_data_dimensionsTree_d_d_d_rpd_vprpfd (void *__instance

);


     mxArray * compute_feature_importancesTree_i_i_uint_fv_fv (void *__instance

);
     mxArray * compute_feature_importancesTree_f_f_uint_fv_fv (void *__instance

);
     mxArray * compute_feature_importancesTree_d_d_uint_fv_fv (void *__instance

);
     mxArray * compute_feature_importancesTree_uint8_uint8_uint_fv_fv (void *__instance

);
     mxArray * compute_feature_importancesTree_uint8_int16_uint_fv_fv (void *__instance

);
     mxArray * compute_feature_importancesTree_uint8_int16_int16_fv_fv (void *__instance

);
     mxArray * compute_feature_importancesTree_uint8_int16_int16_hp_vhp (void *__instance

);
     mxArray * compute_feature_importancesTree_f_f_f_rpf_vprpff (void *__instance

);
     mxArray * compute_feature_importancesTree_d_d_d_rpd_vprpfd (void *__instance

);


     size_t get_samples_storedTree_i_i_uint_fv_fv (void *__instance

);
     size_t get_samples_storedTree_f_f_uint_fv_fv (void *__instance

);
     size_t get_samples_storedTree_d_d_uint_fv_fv (void *__instance

);
     size_t get_samples_storedTree_uint8_uint8_uint_fv_fv (void *__instance

);
     size_t get_samples_storedTree_uint8_int16_uint_fv_fv (void *__instance

);
     size_t get_samples_storedTree_uint8_int16_int16_fv_fv (void *__instance

);
     size_t get_samples_storedTree_uint8_int16_int16_hp_vhp (void *__instance

);
     size_t get_samples_storedTree_f_f_f_rpf_vprpff (void *__instance

);
     size_t get_samples_storedTree_d_d_d_rpd_vprpfd (void *__instance

);


     int eqTree_i_i_uint_fv_fv (void *__instance,

        void * rhs
);
     int eqTree_f_f_uint_fv_fv (void *__instance,

        void * rhs
);
     int eqTree_d_d_uint_fv_fv (void *__instance,

        void * rhs
);
     int eqTree_uint8_uint8_uint_fv_fv (void *__instance,

        void * rhs
);
     int eqTree_uint8_int16_uint_fv_fv (void *__instance,

        void * rhs
);
     int eqTree_uint8_int16_int16_fv_fv (void *__instance,

        void * rhs
);
     int eqTree_uint8_int16_int16_hp_vhp (void *__instance,

        void * rhs
);
     int eqTree_f_f_f_rpf_vprpff (void *__instance,

        void * rhs
);
     int eqTree_d_d_d_rpd_vprpfd (void *__instance,

        void * rhs
);


     void saveTree_i_i_uint_fv_fv (void *__instance,

        char* filename
);
     void saveTree_f_f_uint_fv_fv (void *__instance,

        char* filename
);
     void saveTree_d_d_uint_fv_fv (void *__instance,

        char* filename
);
     void saveTree_uint8_uint8_uint_fv_fv (void *__instance,

        char* filename
);
     void saveTree_uint8_int16_uint_fv_fv (void *__instance,

        char* filename
);
     void saveTree_uint8_int16_int16_fv_fv (void *__instance,

        char* filename
);
     void saveTree_uint8_int16_int16_hp_vhp (void *__instance,

        char* filename
);
     void saveTree_f_f_f_rpf_vprpff (void *__instance,

        char* filename
);
     void saveTree_d_d_d_rpd_vprpfd (void *__instance,

        char* filename
);
     void delete_Tree_i_i_uint_fv_fv(void *ptr);
     void delete_Tree_f_f_uint_fv_fv(void *ptr);
     void delete_Tree_d_d_uint_fv_fv(void *ptr);
     void delete_Tree_uint8_uint8_uint_fv_fv(void *ptr);
     void delete_Tree_uint8_int16_uint_fv_fv(void *ptr);
     void delete_Tree_uint8_int16_int16_fv_fv(void *ptr);
     void delete_Tree_uint8_int16_int16_hp_vhp(void *ptr);
     void delete_Tree_f_f_f_rpf_vprpff(void *ptr);
     void delete_Tree_d_d_d_rpd_vprpfd(void *ptr);


     void * getObjectTemplate_i_i_uint_fv_fv (

        unsigned int example_param
);
     void * getObjectTemplate_f_f_uint_fv_fv (

        unsigned int example_param
);
     void delete_ObjectTemplate_i_i_uint_fv_fv(void *ptr);
     void delete_ObjectTemplate_f_f_uint_fv_fv(void *ptr);
#ifdef __cplusplus
}
#endif 

#endif //#ifndef MATFERTILIZED_MATLAB_HEADERS_ROOTDIR_H_