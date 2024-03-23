
Compilation of wxWidget code
----------------------------

  For a single file project, use g++ with the wx-config tool to provide the correct include and lib configs
  A typical command look like this:

         g++ hello.cpp -o hello `wx-config --cppflags --libs`
