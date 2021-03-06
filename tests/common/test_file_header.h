#include <stdio.h>
#include "test_opt.h"

#include "test_header.h"

int file_show_help(void);
const char *file_name(int argc, char** argv);
int file_test(int argc, char** argv, char *fname);

static opt_option input_file;

static void file_options_initialize(void){
  input_file._string.header.type       = opt_string;
  input_file._string.header.short_name = 'i';
  input_file._string.header.long_name  = "input";
  input_file._string.header.help       = "input file name";
  input_file._string.required          = 1;
  input_file._string.value             = "";
}

int show_help(){
  file_options_initialize();

  opt_show_option(input_file);
  return file_show_help();
}

const char* name(int argc, char** argv){
  static char name_buffer[MAX_LINE];

  file_options_initialize();

  opt_eval_option(argc, argv, &input_file);
  snprintf(name_buffer, MAX_LINE, "%s (%s)", file_name(argc, argv), input_file._string.value);
  return name_buffer;
}

int test(int argc, char** argv){
  int rc;

  file_options_initialize();

  opt_eval_option(argc, argv, &input_file);
  rc = file_test(argc, argv, input_file._string.value);
  return rc;
}
