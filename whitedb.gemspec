Gem::Specification.new do |s|
  s.name    = "whitedb"
  s.version = "0.0.1"
  s.summary = "WhiteDB for Ruby"
  s.author  = "Arnaud 'red' Rouyer <joshleaves@gmail.com>"

  s.files = Dir.glob("ext/**/*.{c,rb}")

  s.extensions << "ext/whitedb/extconf.rb"

  s.add_development_dependency "rake-compiler"
end
