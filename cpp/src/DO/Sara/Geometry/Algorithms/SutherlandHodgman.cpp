// ========================================================================== //
// This file is part of Sara, a basic set of libraries in C++ for computer
// vision.
//
// Copyright (C) 2014-2016 David Ok <david.ok8@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.
// ========================================================================== //

#include <DO/Sara/Geometry.hpp>


namespace DO { namespace Sara {

  bool intersection(const P2::Line& l1, const P2::Line& l2, Vector2d& u)
  {
    P2::Point P;
    P = P2::intersection(l1, l2);

    if (fabs(P(2)) < std::numeric_limits<double>::epsilon())
      return false;

    u = P.head(2) / P(2);
    return true;
  }

  static
  P2::Line line(const Point2d& s, const Point2d& e)
  {
    P2::Line l;
    l = P2::line(s, e);
    l /= l.maxCoeff();
    return l;
  }

  // Polygon 'subject' can be a polygon of any type.
  // Polygon 'clip'  must be a convex polygon.
  std::vector<Point2d> sutherland_hodgman(const std::vector<Point2d>& subject,
                                         const std::vector<Point2d>& clip)
  {
    std::vector<Point2d> in, out;
    Point2d inter;
    P2::Line clip_line;
    P2::Line in_line;

    // Initialize
    out = subject;
    const size_t M = clip.size();
    // Loop.
    for (size_t e2 = 0, e1 = M-1; e2 != M; e1 = e2++) // 'e' like edge of the clip polygon.
    {
      in = out;
      out.clear();

      const size_t N = in.size();
      for (size_t v2 = 0, v1 = N-1; v2 != N; v1 = v2++)
      {
        int ccw1 = ccw(clip[e1], clip[e2], in[v1]);
        int ccw2 = ccw(clip[e1], clip[e2], in[v2]);

        if (ccw1 ==  1 && ccw2 ==  1)
          out.push_back(in[v2]);
        else if (ccw1 ==  1 && ccw2 == -1)
        {
          clip_line = line(clip[e1], clip[e2]);
          in_line = line(in[v1], in[v2]);

          if ( intersection(clip_line, in_line, inter) )
            out.push_back(inter);
        }
        else if (ccw1 == -1 && ccw2 ==  1)
        {
          clip_line = line(clip[e1], clip[e2]);
          in_line = line(in[v1], in[v2]);
          if ( intersection(clip_line, in_line, inter) )
            out.push_back(inter);
          out.push_back(in[v2]);
        }
      }
    }

    return out;
  }

} /* namespace Sara */
} /* namespace DO */
