// ext/database.c
#include <ruby.h>
#include <whitedb/dbapi.h>

/*
Dev ideas:

-> Database include "Enumerable" ?
-> Insert records to the database class AS ANOTHER CLASS
    - pointer to record
    - record length
    - include enumerable? (haha)
-> Setting fields values on RECORD class
-> Only do encode for a SET
*/

/*****************************
**  Variables declarations  **
*****************************/

VALUE WDB           = Qnil;
VALUE WDB_Database  = Qnil;
VALUE WDB_Record    = Qnil;
VALUE WDB_Pointer   = Qnil;

/*****************************
**  Functions declarations  **
*****************************/

void Init_whitedb();

static VALUE WDB_Database_initialize(VALUE self, VALUE id, VALUE size);
static VALUE WDB_Database_create_record(VALUE self, VALUE length);

static VALUE WDB_Record_initialize(VALUE self, VALUE db, VALUE length);
static VALUE WDB_Record_set_field(VALUE self, VALUE index, VALUE data);

/********************
**  Init function  **
********************/

void Init_whitedb() {
  // Define our module and classes hierarchy
  //
  // module WhiteDB
  //   class Database; end
  //   class Record; end
  // end
  //
  WDB          = rb_define_module("WhiteDB");
  WDB_Database = rb_define_class_under(WDB, "Database", rb_cObject);
  WDB_Record   = rb_define_class_under(WDB, "Record",   rb_cObject);
  WDB_Pointer  = rb_define_class_under(WDB, "Pointer",  rb_cObject);


  // Define our Database methods
  //
  // module WhiteDB
  //   class Database
  //     attr_reader :id, :size
  //
  //     def initialize(id, size); end
  //     def create_record(length); end
  //     def close(); end
  //  end
  // end
  //
  rb_define_method(WDB_Database, "initialize",    WDB_Database_initialize, 2);
  rb_define_method(WDB_Database, "create_record", WDB_Database_create_record, 1);
  rb_define_attr(WDB_Database, "id", 1, 0);
  rb_define_attr(WDB_Database, "size", 1, 0);


  // Define our Record methods
  //
  // module WhiteDB
  //   class Record
  //     attr_reader :length
  //
  //     def initialize(db, length); end
  //     def set_field(index, value); end
  //   end
  // end
  //
  rb_define_method(WDB_Record, "initialize", WDB_Record_initialize, 2);
  rb_define_method(WDB_Record, "set_field",  WDB_Record_set_field, 2);
  rb_define_attr(WDB_Record, "length", 1, 0);
}


/*****************************
**  WDB_Database functions  **
*****************************/

static VALUE WDB_Database_initialize(VALUE self, VALUE id, VALUE size) {
  void *db;

  Check_Type(id,   T_STRING);
  Check_Type(size, T_FIXNUM);

  db = wg_attach_database(RSTRING_PTR(id) , NUM2INT(size));
  rb_iv_set(self, "@id",     id);
  rb_iv_set(self, "@size",   size);
  rb_iv_set(self, "@ptr_db", Data_Wrap_Struct(WDB_Pointer, NULL, NULL, db));
  return self;
}

static VALUE WDB_Database_create_record(VALUE self, VALUE length) {
  Check_Type(length, T_FIXNUM);

  VALUE args[2] = { self, length };
  return rb_class_new_instance(2, args, WDB_Record);
}


/***************************
**  WDB_Record functions  **
***************************/

static VALUE WDB_Record_initialize(VALUE self, VALUE db, VALUE length) {
  void *_db;
  void *rec;

  if (CLASS_OF(db) != WDB_Database) {
    rb_raise(rb_eTypeError, "Wrong argument type %s (expected WhiteDB::Database)", rb_class2name(CLASS_OF(db)));
  }
  Check_Type(length, T_FIXNUM);

  db = rb_iv_get(db, "@ptr_db");
  Data_Get_Struct(db, void *, _db);
  rec = wg_create_record(_db, NUM2INT(length));
  rb_iv_set(self, "@length",  length);
  rb_iv_set(self, "@ptr_db",  db);
  rb_iv_set(self, "@ptr_rec", Data_Wrap_Struct(WDB_Pointer, NULL, NULL, rec));
  return self;
}

static VALUE WDB_Record_set_field(VALUE self, VALUE index, VALUE data) {
  void *_db;
  void *rec;
  wg_int enc;

  Check_Type(index, T_FIXNUM);
  Data_Get_Struct(rb_iv_get(self, "@ptr_db"), void *, _db);
  switch (TYPE(data)) {
    case T_NIL:
      enc = wg_encode_null(_db, 0);
      break;
    case T_STRING:
      enc = wg_encode_str(_db, RSTRING_PTR(data), NULL);
      break;
    case T_FIXNUM:
      enc = wg_encode_int(_db, NUM2INT(data));
      break;
    case T_FLOAT:
      enc =  wg_encode_fixpoint(_db, NUM2DBL(data));
      break;
    default:
      rb_raise(rb_eTypeError, "Wrong argument type %s (expected FixNum, Float, String)", rb_class2name(CLASS_OF(data)));
  }

  Data_Get_Struct(rb_iv_get(self, "@ptr_rec"), void *, rec);
  wg_set_field(_db, rec, NUM2INT(index), enc);
  return self;
}
