// ========================================================================== //
// This file is part of DO++, a basic set of libraries in C++ for computer 
// vision.
//
// Copyright (C) 2013 David Ok <david.ok8@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public 
// License v. 2.0. If a copy of the MPL was not distributed with this file, 
// you can obtain one at http://mozilla.org/MPL/2.0/.
// ========================================================================== //

#include <gtest/gtest.h>

#include <DO/KDTree.hpp>


using namespace DO;
using namespace std;


void testBatchKnnSearch(const MatrixXd& data, double step)
{
  // Batch query search.
  printStage("Batch query search");
  MatrixXd queries(data);
  queries.array() += 0.5;
  KDTree kdTree(data);
  vector<vector<int> > indices;
  vector<vector<double> > sqDists;
  kdTree.knn_search(queries, 10, indices, sqDists);

  // Check visually.
  printStage("Check out the queries");
  for (int i = 0; i != data.cols(); ++i)
  {
    cout << "p[" << i << "] = " << queries.col(i).transpose() << endl;
    for (size_t j = 0; j != indices[i].size(); ++j)
    {
      size_t indj = indices[i][j];
      cout << "knn["<< j << "]\tp[" << indj << "] = " << data.col(indj).transpose() << endl;
    }
  }
}


void testBatchKnnSearchWithQueryInData(const MatrixXd& data, double step)
{
  // Batch query search.
  printStage("Batch query search");
  vector<size_t> queries(data.cols());
  for (int i = 0; i != data.cols(); ++i)
    queries[i] = i;
  KDTree kdTree(data);
  vector<vector<int> > indices;
  vector<vector<double> > sqDists;
  kdTree.knn_search(queries, 10, indices, sqDists);

  // Check visually.
  printStage("Check out the queries");
  for (int i = 0; i != data.cols(); ++i)
  {
    cout << "p[" << i << "] = " << data.col(queries[i]).transpose() << endl;
    for (size_t j = 0; j != indices[i].size(); ++j)
    {
      size_t indj = indices[i][j];
      cout << "knn["<< j << "]\tp[" << indj << "] = " << data.col(indj).transpose() << endl;
    }
  }
}


int main() 
{
  // Generate grid of points.
  const size_t N = 10;
  MatrixXd data(2,N*N);
  for (size_t i = 0; i != N ; ++i)
    for (size_t j = 0; j != N ; ++j)
      data.col(i+j*N) = Point2d(i, j);

  // View grid of points.
  const double step = 50;
  //testBatchKnnSearch(data, step);
  testBatchKnnSearchWithQueryInData(data, step);


  return 0;
}