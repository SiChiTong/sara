// ========================================================================== //
// This file is part of DO-CV, a basic set of libraries in C++ for computer
// vision.
//
// Copyright (C) 2013 David Ok <david.ok8@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.
// ========================================================================== //

//! @file

#ifndef DO_SARA_FEATUREDETECTORS_DEBUG_HPP
#define DO_SARA_FEATUREDETECTORS_DEBUG_HPP

#include <DO/Sara/Defines.hpp>

#include <DO/Sara/Graphics.hpp>

#include <DO/Sara/Geometry/Tools/Utilities.hpp>

#include <DO/Sara/ImageProcessing/ImagePyramid.hpp>


namespace DO { namespace Sara {

  /*!
    \ingroup FeatureDetectors
    \defgroup UtilitiesDebug Utilities for visual inspection of features.
    @{
   */

  //! \brief Visually inspect the image pyramid.
  template <typename T>
  void display_image_pyramid(const ImagePyramid<T>& pyramid,
                             bool rescale = false)
  {
    using namespace std;
    for (int o = 0; o < pyramid.num_octaves(); ++o)
    {
      cout << "Octave " << o << endl;
      cout << "- scaling factor = "
           << pyramid.octave_scaling_factor(o) << endl;
      for (int s = 0; s != int(pyramid(o).size()); ++s)
      {
        cout << "Image " << s << endl;
        cout << "Image relative scale to octave = "
             << pyramid.scale_relative_to_octave(s) << endl;

        display(rescale ? color_rescale(pyramid(s,o)) : pyramid(s,o),
          0, 0, pyramid.octave_scaling_factor(o));
        get_key();
      }
    }
  }

  //! @{
  //! \brief Visually inspect local extrema.
  DO_EXPORT
  void draw_scale_space_extremum(const ImagePyramid<float>& I,
                                 float x, float y, float s,
                                 int o, const Rgb8& c);

  DO_EXPORT
  void draw_extrema(const ImagePyramid<float>& pyramid,
                    const std::vector<OERegion>& extrema,
                    int s, int o, bool rescale_color = true);

  DO_EXPORT
  void highlight_patch(const ImagePyramid<float>& D,
                       float x, float y, float s, int o);

  DO_EXPORT
  void check_patch(const Image<float>& I, int x, int y, int w, int h,
                   double fact = 50.);

  DO_EXPORT
  void check_patch(const Image<float>& I, float x, float y, float s,
                   double fact = 20.);
  //! @}

  //! \brief Visually inspect the descriptor.
  template <typename T, int N>
  void view_histogram(const Array<T, N, 1>& histogram)
  {
    using namespace std;
    set_active_window(create_window(720, 200, "Histogram"));
    auto w = int_round(720. / histogram.size());
    float max = histogram.maxCoeff();
    for (int i = 0; i < histogram.size(); ++i)
    {
      auto h = int_round(histogram(i) / max * 200);
      fill_rect(i*w, 200-h, w, h, Blue8);
    }
    cout << histogram.transpose() << endl;
    get_key();
    close_window();
  }

  //! @}

} /* namespace Sara */
} /* namespace DO */


#endif /* DO_SARA_FEATUREDETECTORS_DEBUG_HPP */
