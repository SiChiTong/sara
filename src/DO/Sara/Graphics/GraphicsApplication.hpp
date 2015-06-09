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

#ifndef DO_SARA_GRAPHICS_GRAPHICSAPPLICATION_HPP
#define DO_SARA_GRAPHICS_GRAPHICSAPPLICATION_HPP


namespace DO { namespace Sara {

  /*!
    \ingroup Graphics
    \defgroup GraphicsInternal Graphics Internals
    \brief This contains the Qt-based internal implementation of the Graphics
    module.
  @{
 */

  //! \brief QApplication-derived class
  //! This graphic application establishes communication between the user
  //! drawing commands and the windows.
  class DO_EXPORT GraphicsApplication
  {
  public:
    class Impl;
    GraphicsApplication(int& argc, char **argv);
    ~GraphicsApplication();
    void register_user_main(int (*userMain)(int, char **));
    int exec();

  private:
    Impl *pimpl_;
  };

  //! @}

} /* namespace Sara */
} /* namespace DO */


/*!
  \addtogroup GraphicsInternal

  @{
 */

// ====================================================================== //
//! \brief Some convenient hacks.
int __main(int, char **);

#define GRAPHICS_MAIN()                     \
int main(int argc, char **argv)             \
{                                           \
  DO::GraphicsApplication app(argc, argv);  \
  app.register_user_main(__main);           \
  return app.exec();                        \
}                                           \
                                            \
int __main(int, char **)


#endif /* DO_SARA_GRAPHICS_GRAPHICSAPPLICATION_HPP */
