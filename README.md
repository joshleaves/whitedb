WhiteDB
=======

Ruby wrapper for WhiteDB: http://whitedb.org/. Written fully in C

Requirements
============

 * Install the WhiteDB database: http://whitedb.org/install.html

 * `gem install whitedb`

Current API
===========

Create a database

    db_name = "foo"
    db_sier = 2_000_000
    db = WhiteDB::Database.new(db_name, db_size)

Create a record

    rec_size = 3
    rec = db.create_record(rec_size)
    # alternative:
    # rec = WhiteDB::Record.new(db, rec_size)

Populate a record with strings

    4.times do |x|
      rec.set_field(x, "Test: #{x}")
    end

Next steps
==========

 * Better build process (paths are standard for my box, maybe your headers/libs are somewhere else)

 * Finish the tutorial to have a better view of the API

 * Add blocks to all init methods

 * Check for errors, thow some stuff and add a test suite

