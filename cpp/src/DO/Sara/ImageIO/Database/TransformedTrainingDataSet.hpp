// ========================================================================== //
// This file is part of Sara, a basic set of libraries in C++ for computer
// vision.
// Copyright (C) 2017 David Ok <david.ok8@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.
// ========================================================================== //

//! @file

#pragma once

#include <tuple>

#include <DO/Sara/Defines.hpp>
#include <DO/Sara/ImageIO/Database/ImageDataSet.hpp>
#include <DO/Sara/ImageProcessing/DataAugmentation.hpp>


namespace DO { namespace Sara {

  template <typename XIterator, typename YIterator, typename TIterator>
  class TransformedTrainingDataSetIterator
  {
  public:
    using x_iterator = XIterator;
    using y_iterator = YIterator;
    using data_transform_iterator = TIterator;

    using x_type = typename XIterator::value_type;
    using y_type = typename YIterator::value_type;
    using data_transform_type = typename TIterator::value_type;
    using self_type = TransformedTrainingDataSetIterator;

    inline TransformedTrainingDataSetIterator() = default;

    inline TransformedTrainingDataSetIterator(x_iterator x, y_iterator y,
                                              data_transform_iterator t)
      : _x{x}
      , _y{y}
      , _t{t}
    {
    }

    inline auto operator++() -> self_type&
    {
      ++_x;
      ++_y;
      ++_t;
      return *this;
    }

    inline auto operator--() -> self_type&
    {
      --_x;
      --_y;
      --_t;
      return *this;
    }

    inline auto operator+=(std::ptrdiff_t n) -> self_type&
    {
      _x += n;
      _y += n;
      _t += n;
      return *this;
    }

    inline auto operator-=(std::ptrdiff_t n) -> self_type&
    {
      _x -= n;
      _y -= n;
      _t -= n;
      return *this;
    }

    inline auto x() const -> x_iterator
    {
      return _x;
    }

    inline auto y() const -> y_iterator
    {
      return _y;
    }

    inline auto t() const -> data_transform_iterator
    {
      return _t;
    }

    inline auto x_ref() const -> const x_type&
    {
      return *_x;
    }

    inline auto y_ref() const -> const y_type&
    {
      return *_y;
    }

    inline auto t_ref() const -> const data_transform_type&
    {
      return *_t;
    }

    inline auto operator==(const self_type& other) const -> bool
    {
      return std::make_tuple(_x, _y, _t) ==
             std::make_tuple(other._x, other._y, other._t);
    }

    inline auto operator!=(const self_type& other) const -> bool
    {
      return !(operator==(other));
    }

  private:
    mutable x_iterator _x;
    mutable y_iterator _y;
    data_transform_iterator _t;
  };


  template <typename XHandle, typename YHandle, typename DataTransform>
  class TransformedTrainingDataSet
  {
  public:
    using x_handle = XHandle;
    using y_handle = YHandle;
    using data_transform_type = DataTransform;

    using x_set_type = std::vector<XHandle>;
    using y_set_type = std::vector<YHandle>;
    using data_transform_set_type = std::vector<DataTransform>;

    inline TransformedTrainingDataSet() = default;

    inline void clear()
    {
      x.clear();
      y.clear();
      t.clear();
    }

    inline bool operator==(const TransformedTrainingDataSet& other) const
    {
      return x == other.x && y == other.y && t == other.t;
    }

    inline bool operator!=(const TransformedTrainingDataSet& other) const
    {
      return !(*this == other);
    }

    x_set_type x;
    y_set_type y;
    data_transform_set_type t;
  };


  class TransformedImageClassificationTrainingDataSet
      : public TransformedTrainingDataSet<std::string, int, ImageDataTransform>
  {
    using base_type =
        TransformedTrainingDataSet<std::string, int, ImageDataTransform>;

  public:
    using x_iterator = ImageDataSetIterator<Image<Rgb8>>;
    using y_iterator = typename y_set_type::const_iterator;
    using data_transform_iterator =
        typename data_transform_set_type::const_iterator;
    using iterator =
        TransformedTrainingDataSetIterator<x_iterator, y_iterator,
                                           data_transform_iterator>;

    inline TransformedImageClassificationTrainingDataSet() = default;

    inline auto begin() const -> iterator
    {
      return iterator{x_begin(), y_begin(), data_transform_begin()};
    }

    inline auto end() const -> iterator
    {
      return iterator{x_end(), y_end(), data_transform_end()};
    }

    auto x_begin() const -> x_iterator
    {
      return x_iterator{x.begin(), x.end()};
    }

    auto x_end() const -> x_iterator
    {
      return x_iterator{x.end(), x.end()};
    }

    auto y_begin() const -> y_iterator
    {
      return y.begin();
    }

    auto y_end() const -> y_iterator
    {
      return y.end();
    }

    auto data_transform_begin() const -> data_transform_iterator
    {
      return t.begin();
    }

    auto data_transform_end() const -> data_transform_iterator
    {
      return t.end();
    }
  };


  class TransformedImageSegmentationTrainingDataSet
      : public TransformedTrainingDataSet<std::string, std::string,
                                          ImageDataTransform>
  {
    using base_type = TransformedTrainingDataSet<std::string, std::string,
                                                 ImageDataTransform>;

  public:
    using x_iterator = ImageDataSetIterator<Image<Rgb8>>;
    using y_iterator = ImageDataSetIterator<Image<int>>;
    using data_transform_iterator =
        typename data_transform_set_type::const_iterator;
    using iterator =
        TransformedTrainingDataSetIterator<x_iterator, y_iterator,
                                           data_transform_iterator>;

    inline TransformedImageSegmentationTrainingDataSet() = default;

    inline auto begin() const -> iterator
    {
      return iterator{x_begin(), y_begin(), data_transform_begin()};
    }

    inline auto end() const -> iterator
    {
      return iterator{x_end(), y_end(), data_transform_end()};
    }

    auto x_begin() const -> x_iterator
    {
      return x_iterator{x.begin(), x.end()};
    }

    auto x_end() const -> x_iterator
    {
      return x_iterator{x.end(), x.end()};
    }

    auto y_begin() const -> y_iterator
    {
      return y_iterator{y.begin(), y.end()};
    }

    auto y_end() const -> y_iterator
    {
      return y_iterator{y.end(), y.end()};
    }

    auto data_transform_begin() const -> data_transform_iterator
    {
      return t.begin();
    }

    auto data_transform_end() const -> data_transform_iterator
    {
      return t.end();
    }
  };

  DO_SARA_EXPORT
  void read_from_csv(TransformedImageClassificationTrainingDataSet& data_set,
                     const std::string& csv_filepath);

  DO_SARA_EXPORT
  void
  write_to_csv(const TransformedImageClassificationTrainingDataSet& data_set,
               const std::string& csv_filepath);

  DO_SARA_EXPORT
  void read_from_csv(TransformedImageSegmentationTrainingDataSet& data_set,
                     const std::string& csv_filepath);

  DO_SARA_EXPORT
  void write_to_csv(const TransformedImageSegmentationTrainingDataSet& data_set,
                    const std::string& csv_filepath);

} /* namespace Sara */
} /* namespace DO */
