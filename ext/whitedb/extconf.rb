require "mkmf"

extension_name = 'whitedb'
dir_config(extension_name)
dir_config('tools', '/usr/local/include', '/usr/local/lib')

$CPPFLAGS += " -I/usr/local/include "
$LDFLAGS  += " -lwgdb "

have_library("wgdb")
create_makefile(extension_name)
