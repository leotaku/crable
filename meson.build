project(
  'crable', 'c',
  version : '1.0',
  default_options : [
    # Development settings
    'c_std=c2x',
    'warning_level=3',
    'debug=true',
    'optimization=3',
    'b_lto=true',
    # Sanitize
    'b_lundef=false',
    'b_sanitize=address,undefined',
  ],
)

crable_lib = library(
  'crable', 'crable.c',
  install : true,
)
install_headers('crable.h')

crable_dep = declare_dependency(
  include_directories: include_directories('.'),
  link_with : [ crable_lib ],
)

pkg = import('pkgconfig')
pkg.generate(
  name : 'crable',
  filebase : 'crable',
  description : 'A hash table implementation with various desirable properties',
  subdirs : 'crable',
  libraries : crable_lib,
  version : '1.0',
)