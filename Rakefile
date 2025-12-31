require 'rbconfig'
require 'rubygems'
require 'shellwords'

cc, cflags, coutflag, libext, exeext =
  RbConfig::CONFIG.fetch_values 'CC', 'CFLAGS', 'COUTFLAG', 'LIBEXT', 'EXEEXT'

prism = Gem.loaded_specs.fetch('prism').full_gem_path
include = File.join prism, 'include'
library = File.join prism, 'build'

prism_lib = File.join(library, "libprism.#{libext}") # from `prism/Makefile`
file prism_lib do
  # I’m not bothering with “error while loading shared libraries:
  # libprism.so: cannot open shared object file: No such file or directory”.
  system 'make', '-C', prism, 'static'
end

file prism_h = File.join(include, 'prism.h')
file libprism_example_c = 'libprism_example.c'

libprism_example_exe = "libprism_example#{exeext}"
file libprism_example_exe => [libprism_example_c, prism_h, prism_lib] do
  command_line = [cc,
    "-I#{include.shellescape}",
    cflags,
    [coutflag, libprism_example_exe].join,
    libprism_example_c,
    "-L#{library.shellescape}",
    '-lprism'
  ].join ' '
  puts command_line if verbose
  system command_line
end
task compile: libprism_example_exe

task default: :compile do
  system "./#{libprism_example_exe}"
end

task :clean do
  system 'make', '-C', prism, 'clean'
end
task clobber: :clean do
  puts "rm #{libprism_example_exe}" if verbose
  File.delete libprism_example_exe
rescue Errno::ENOENT
end
