#pragma once

#include <iostream>
#include <set>
#include <vector>

#include <DO/Sara/Core/EigenExtension.hpp>

#include <gtest/gtest.h>


template <typename Matrix1, typename Matrix2>
::testing::AssertionResult assert_matrix_equal(const char *m_expr,
                                               const char *n_expr,
                                               const Matrix1& m,
                                               const Matrix2& n)
{
  if (m == n)
    return ::testing::AssertionSuccess();

  return ::testing::AssertionFailure()
    << "Expected matrix: " << m_expr << ":\n" << m << "\n and \n"
    << "actual matrix: " << n_expr << ":\n" << n << "\n"
    << "are not equal";
}


template <typename Matrix1, typename Matrix2>
::testing::AssertionResult assert_matrix_near(const char *m_expr,
                                              const char *n_expr,
                                              const char *abs_error_expr,
                                              const Matrix1& m,
                                              const Matrix2& n,
                                              double abs_error)
{
  typename Matrix1::Scalar distance = (m-n).norm();
  if (distance < abs_error)
    return ::testing::AssertionSuccess();

  return ::testing::AssertionFailure()
    << "Expected matrix: " << m_expr << ":\n" << m << "\n and \n"
    << "actual matrix: " << n_expr << ":\n" << n << "\n"
    << "have actual Euclidean distance: " << distance << "\n"
    << "but expected Euclidean distance: " << abs_error_expr
    << " = " << abs_error;
}


#define ASSERT_MATRIX_EQ(m, n) ASSERT_PRED_FORMAT2(assert_matrix_equal, m, n)
#define EXPECT_MATRIX_EQ(m, n) EXPECT_PRED_FORMAT2(assert_matrix_equal, m, n)
#define ASSERT_MATRIX_NEAR(m, n, abs_error)\
  ASSERT_PRED_FORMAT3(assert_matrix_near, m, n, abs_error)
#define EXPECT_MATRIX_NEAR(m, n, abs_error)\
  EXPECT_PRED_FORMAT3(assert_matrix_near, m, n, abs_error)


template <typename T>
inline std::set<T> to_std_set(const std::vector<T>& v)
{
  return std::set<T>(v.begin(), v.end());
}

template <typename T, int M, int N, int Opts, int MaxRows, int MaxCols>
inline
std::set<
  Eigen::Matrix<T, M, N, Opts, MaxRows, MaxCols>,
  DO::Sara::LexicographicalOrder
>
to_std_set(const std::vector<Eigen::Matrix<T, M, N, Opts, MaxRows, MaxCols> >& v)
{
  return std::set<
    Eigen::Matrix<T, M, N, Opts, MaxRows, MaxCols>,
    DO::Sara::LexicographicalOrder
  >(v.begin(), v.end());
}

// Define a macro that does something 'self.assertItemsEqual' in Python.
#define EXPECT_ITEMS_EQ(vector1, vector2)                                      \
  EXPECT_EQ(to_std_set(vector1), to_std_set(vector2))
#define ASSERT_ITEMS_EQ(vector1, vector2)                                      \
  ASSERT_EQ(to_std_set(vector1), to_std_set(vector2))


#define BOOST_CHECK_ITEMS_EQUAL(collection1, collection2)                      \
  BOOST_CHECK(to_std_set(collection1) == to_std_set(collection2))

#define BOOST_REQUIRE_ITEMS_EQUAL(collection1, collection2)                    \
  BOOST_REQUIRE(to_std_set(collection1) == to_std_set(collection2))

#define BOOST_CHECK_SMALL_L2_DISTANCE(m1, m2, eps)                             \
  BOOST_CHECK_SMALL((m1 - m2).norm(), eps)

#define BOOST_REQUIRE_SMALL_L2_DISTANCE(m1, m2, eps)                           \
  BOOST_REQUIRE_SMALL((m1 - m2).norm(), eps)

#define BOOST_CHECK_CLOSE_L2_DISTANCE(m1, m2, eps)                             \
  BOOST_CHECK_SMALL((m1 - m2).norm() / m1.norm(), eps)

#define BOOST_REQUIRE_CLOSE_L2_DISTANCE(m1, m2, eps)                           \
  BOOST_REQUIRE_SMALL((m1 - m2).norm() / m1.norm(), eps)


struct CoutRedirect {
  CoutRedirect(std::streambuf * new_buffer)
    : old(std::cout.rdbuf(new_buffer))
  { }

  ~CoutRedirect() {
    std::cout.rdbuf(old);
  }

private:
  std::streambuf * old;
};
