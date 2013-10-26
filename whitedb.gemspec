Gem::Specification.new do |s|
  s.name        = "whitedb"
  s.version     = "0.0.1"
  s.summary     = "WhiteDB for Ruby"
  s.author      = "Arnaud 'red' Rouyer"
  s.email       = "joshleaves@gmail.com"
  s.description = "Ruby wrapper for WhiteDB: http://whitedb.org/"
  s.homepage    = "http://github.com/joshleaves/whitedb-rb"

  s.files = Dir.glob("ext/**/*.{c,rb}")

  s.extensions << "ext/whitedb/extconf.rb"

  s.add_development_dependency "rake-compiler"
end
