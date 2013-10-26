WhiteDB
=======

Ruby wrapper for WhiteDB: http://whitedb.org/. Written fully in C

Requirements:
=============

API:
====

Current features:

    # Create a database
    db_name = "foo"
    db_sier = 2_000_000
    db = WhiteDB::Database.new(db_name, db_size)

    # Create a record
    rec_size = 3
    rec = db.create_record(rec_size)
    # also: rec = WhiteDB::Record.new(db, rec_size)

    # Populate a record
    4.times do |x|
      rec.set_field(x, "Test: #{x}")
    end
