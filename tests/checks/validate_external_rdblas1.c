#include <rblas.h>
#include <IndexedFP.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/test_vec.h"
#include "../common/test_opt.h"
#include "../common/test_file.h"
#include "rdblas1_wrapper.h"

#include "../common/test_file_header.h"

const char* file_name(int argc, char** argv) {
  static char name_buffer[MAX_LINE];
  opt_option func_type;
  opt_option record;

  func_type.header.type       = opt_named;
  func_type.header.short_name = 'w';
  func_type.header.long_name  = "w_type";
  func_type.header.help       = "wrapped function type";
  func_type._named.required   = 1;
  func_type._named.n_names    = wrap_rdblas1_n_names;
  func_type._named.names      = (char**)wrap_rdblas1_names;
  func_type._named.descs      = (char**)wrap_rdblas1_descs;

  record.header.type       = opt_flag;
  record.header.short_name = 'r';
  record.header.long_name  = "record";
  record.header.help       = "record the run insted of testing";

  if(help._flag.exists){
    opt_show_option(func_type);
    opt_show_option(record);
    return "";
  }
  opt_eval_option(argc, argv, &func_type);
  snprintf(name_buffer, MAX_LINE, "Validate %s external", wrap_rdblas1_names[func_type._named.value]);
  return name_buffer;
}

int file_test(int argc, char** argv, char *fname) {
  int i;
  int N;
  char ref_fname[MAX_NAME];
  char Iref_fname[MAX_NAME];
  opt_option func_type;
  opt_option record;

  func_type.header.type       = opt_named;
  func_type.header.short_name = 'w';
  func_type.header.long_name  = "w_type";
  func_type.header.help       = "wrapped function type";
  func_type._named.required   = 1;
  func_type._named.n_names    = wrap_rdblas1_n_names;
  func_type._named.names      = (char**)wrap_rdblas1_names;
  func_type._named.descs      = (char**)wrap_rdblas1_descs;

  record.header.type       = opt_flag;
  record.header.short_name = 'r';
  record.header.long_name  = "record";
  record.header.help       = "record the run insted of testing";

  opt_eval_option(argc, argv, &func_type);
  opt_eval_option(argc, argv, &record);

  double *x;
  double *y;

  double ref;
  I_double Iref;

  double res;
  I_double Ires;

  file_read_vector(fname, &N, (void**)&x, sizeof(double));
  y = dvec_alloc(N, 1);
  //fill y with 1 where necessary
  dvec_fill(N, y, 1, vec_fill_CONSTANT, 1.0, 1.0);

  ((char*)file_ext(fname))[0] = '\0';
  snprintf(ref_fname, MAX_NAME, "%s__%s.dat", fname, wrap_rdblas1_names[func_type._named.value]);
  snprintf(Iref_fname, MAX_NAME, "%s__I%s.dat", fname, wrap_rdblas1_names[func_type._named.value]);

  res = (wrap_rdblas1_func(func_type._named.value))(N, x, 1, y, 1);
  Ires = (wrap_Idblas1_func(func_type._named.value))(N, x, 1, y, 1);

  if(record._flag.exists){
    ref = res;
    Iref = Ires;

    file_write_vector(ref_fname, 1, &ref, sizeof(ref));
    file_write_vector(Iref_fname, 1, &Iref, sizeof(Iref));
  } else {
    void *data;
    int unused0;
    file_read_vector(ref_fname, &unused0, &data, sizeof(ref));
    ref = *(double*)data;
    free(data);
    file_read_vector(Iref_fname, &unused0, &data, sizeof(Iref));
    Iref = *(I_double*)data;
    free(data);
    if(ref != res){
      printf("%s(%s) = %g != %g\n", wrap_rdblas1_names[func_type._named.value], fname, res, ref);
      return 1;
    }
    if(memcmp(&Iref, &Ires, sizeof(Iref)) != 0){
      printf("I%s(%s) = %g != %g\n", wrap_rdblas1_names[func_type._named.value], fname, Iconv2d(Ires), Iconv2d(Iref));
      printf("Ref I_double:\n");
      dIprint(Iref);
      printf("\nRes I_double:\n");
      dIprint(Ires);
      printf("\n");
      return 1;
    }
  }

  free(x);
  free(y);
  return 0;
}
