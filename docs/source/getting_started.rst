Getting Started
===============

.. _getting_started

Tools Needed
------------
In order to start developing using Kodo you need the following tools installed:

1. A **C++11 compliant compiler:** Kodo is a C++11 library so to use it
   you will need a C++ compiler supporting the new C++11 standard. You
   can see a list of compilers on our buildbot page (`Steinwurf Buildbot`_).

2. **Git:** we use the git version control system for managing our libraries.

If you wish to build the Kodo examples and unit-tests it is recommended
that you also install the following:

3. **Python:** needed by our build scripts. We use the Python based `waf`_
   build system.

.. _waf: https://code.google.com/p/waf/
.. _Steinwurf Buildbot: http://176.28.49.184:12344


In the following we will provide the links for installing the tools on
a number of different platforms.

Download tools (Ubuntu or other Debian based distributions)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Get the dependencies using the following command:

::

  sudo apt-get install g++ python git-core

Download tools (Windows)
~~~~~~~~~~~~~~~~~~~~~~~~

1. **C++11 compliant compiler:** You need a working C++ compiler we have
   tested using `Visual Studio Express 2012`_ compiler which is free of
   charge. Newer versions should also be fine.

2. **Python:** You need a working Python installation. Find the available
   download on the `Python homepage`_. If you are in doubt which version
   to install you may use the `Python 2.7.3 Windows Installer`_.

3. **Git:** There are several ways to get git on Windows. If you plan to use
   the waf build-scripts to build the Kodo examples and unit-tests, you should
   install the msysgit_ tool. If you do not know which version to install you
   may select the latest version from the `msysgit downloads`_ page.

.. _`Visual Studio Express 2012`:
   http://www.microsoft.com/visualstudio/eng/downloads

.. _`Python homepage`:
   http://www.python.org/download/

.. _`Python 2.7.3 Windows Installer`:
   http://www.python.org/ftp/python/2.7.3/python-2.7.3.msi

.. _msysgit:
   http://msysgit.github.com/

.. _`msysgit downloads`:
   https://code.google.com/p/msysgit/downloads/list?q=full+installer+official+git


Download the Kodo source code
-----------------------------

We recommend downloading the library using git, this will allow you to
easily get new updates whenever the library is updated. In addition to
this it is also possible to download the library as either zip or tar.gz
archive. We will describe both approaches in the following:

Recommended: Clone the git repository
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. Create a suitable directory for the projects (optional)

   ::

     mkdir dev
     cd dev

2. Clone and download the Kodo libraries by running:

   ::

     git clone git://github.com/steinwurf/kodo.git

Alternative: Download the source code as archives
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Download the zip or tar.gz archive from the following location and
extract it to a desired location.

* https://github.com/steinwurf/kodo/tags


Waf (build system)
------------------

We use the Waf build system to build all Kodo examples and
unit-tests. Waf is a Python based build-system and supports
a wide variety of use-cases. You may read more about Waf at
the project homepage: http://code.google.com/p/waf/

A Waf project typically contains two types of files:

1. The ``waf`` file this the actual build system executable.
   This file is not meant to be edited.

2. A number of ``wscript`` files, these files contain the
   project build information. You can think of it as a type
   of ``makefile`` written in Python.

.. note:: See the ``waf`` build options by running ``python waf -h``
          in your favorite command-line shell.

In the following we will look at how you can build Kodo's examples, benchmarks
and unit tests using the Waf build system.

Quick Start (building Kodo examples and unit tests)
---------------------------------------------------

.. _quick-start:

If you are primarily interested in quickly trying some Kodo examples
or building the unit-tests, we have tried to make that as easy as possible.
Provided that you have the `Tools Needed`_ installed.

.. note:: We recommend trying to build and run the unit-tests, before
          using Kodo in your own project. However, if you want to skip
          this step you may jump directly to :ref:`using-kodo-in-your-application`


1. Navigate to the directory where you have downloaded the Kodo source code:

   ::

     cd dev/kodo/

2. Invoke ``waf`` to build the Kodo unit-tests and examples.

   ::

     python waf configure --bundle=ALL --bundle-path=~/dev/bundle_dependencies

   The ``waf configure`` ensures that all tools needed by Kodo are
   available and prepares to build Kodo.
   Kodo relies on a number of auxiliary libraries (see :ref:`kodo-dependencies`)
   by specifying the ``--bundle=ALL`` command we instruct ``waf`` to
   automatically download these. The ``--bundle-path`` informs ``waf``
   about where the downloaded libraries should be placed. You may
   omit the ``--bundle-path`` option in that case ``waf`` will create a
   local directory in the Kodo folder called  ``bundle_dependencies`` and
   store the libraries there.

   .. note:: The ``waf configure`` step might take a while, so now would be a
             good time to grap a coffee or similar while it downloads.

3. Invoke ``waf`` to build the unit-tests and examples.

   ::

     python waf build

4. Run the produced executables depending on the host platform.

   a. **Linux**: Run unit-tests from the Kodo directory by running
      ``./build/linux/test/kodo_tests`` in your shell.

   b. **Mac**: Run unit-tests from the Kodo directory by running
      ``./build/darwin/test/kodo_tests`` in your shell.

   c. **Windows**: Run unit-tests from the Kodo directory by running
      ``build/win32/test/kodo_tests.exe`` in your command prompt.

Customize the build
-------------------

You may customize the build process. The list below describes the most
common changes you may want for you build.

* You may change the compiler.

  To change compiler, set the ``CXX`` variable to you preferred compiler.
  In case you want to use clang++, add ``CXX=clang++`` in front of ``waf configure``.

  ::

    CXX=clang++ python waf configure --bundle=ALL --bundle-path=~/dev/bundle_dependencies