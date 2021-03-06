/*!
 *  Copyright (c) 2018 by Contributors
 * \file dgl/sampler.h
 * \brief DGL sampler header.
 */
#ifndef DGL_SAMPLER_H_
#define DGL_SAMPLER_H_

#include <string>
#include "graph_interface.h"

namespace dgl {

class ImmutableGraph;

/*!
 * \brief A NodeFlow graph stores the sampling results for a sampler that samples
 * nodes/edges in layers.
 *
 * We store multiple layers of the sampling results in a single graph, which results
 * in a more compact format. We store extra information,
 * such as the node and edge mapping from the NodeFlow graph to the parent graph.
 */
struct NodeFlow {
  /*! \brief The graph. */
  GraphPtr graph;
  /*!
   * \brief the offsets of each layer.
   */
  IdArray layer_offsets;
  /*!
   * \brief the offsets of each flow.
   */
  IdArray flow_offsets;
  /*!
   * \brief The node mapping from the NodeFlow graph to the parent graph.
   */
  IdArray node_mapping;
  /*!
   * \brief The edge mapping from the NodeFlow graph to the parent graph.
   */
  IdArray edge_mapping;
};

class SamplerOp {
 public:
  /*!
   * \brief Sample a graph from the seed vertices with neighbor sampling.
   * The neighbors are sampled with a uniform distribution.
   *
   * \param graphs A graph for sampling.
   * \param seeds the nodes where we should start to sample.
   * \param edge_type the type of edges we should sample neighbors.
   * \param num_hops the number of hops to sample neighbors.
   * \param expand_factor the max number of neighbors to sample.
   * \return a NodeFlow graph.
   */
  static NodeFlow NeighborUniformSample(const ImmutableGraph *graph, IdArray seeds,
                                        const std::string &edge_type,
                                        int num_hops, int expand_factor);

  /*!
   * \brief Batch-generate random walk traces
   * \param seeds The array of starting vertex IDs
   * \param num_traces The number of traces to generate for each seed
   * \param num_hops The number of hops for each trace
   * \return a flat ID array with shape (num_seeds, num_traces, num_hops + 1)
   */
  static IdArray RandomWalk(const GraphInterface *gptr,
                            IdArray seeds,
                            int num_traces,
                            int num_hops);
};

}  // namespace dgl

#endif  // DGL_SAMPLER_H_
