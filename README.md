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
    rec_str = db.create_record(rec_size)
    rec_nil = db.create_record(rec_size)
    # alternative:
    rec_num = WhiteDB::Record.new(db, rec_size)
    rec_dbl = WhiteDB::Record.new(db, rec_size)

Populate a record with different types

    4.times do |x|
      rec_str.set_field(x, "#{x}")
      rec_num.set_field(x, x)
      rec_nil.set_field(x, nil)
      rec_dbl.set_field(x, x + 0.5)
     end

You can now check that the data has been properly saved by using the binary `wgdb`

    $ wgdb foo select 20
    ["0","1","2","3","4"]
    [0,1,2,3,4]
    [NULL,NULL,NULL,NULL,NULL]
    [0.500000,1.500000,2.500000,3.500000,4.500000]

Limitations
===========
No date/time for now because date and time are separated in two fields (instead of only one like other types). Maybe later if the API gets rebuilt to accomodate for this.

Next steps
==========

 * Better build process (paths are standard for my box, maybe your headers/libs are somewhere else)

 * Finish the tutorial to have a better view of the API

 * Add blocks to all init methods

 * Check for errors returns, throw some stuff and add a test suite

