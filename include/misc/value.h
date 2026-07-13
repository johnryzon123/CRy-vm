#ifndef INCLUDE_MISC_VALUE_H
#define INCLUDE_MISC_VALUE_H

typedef struct CRyValue {
  union {
    double number;

    struct {
      unsigned int length;
      char* start;
    } string;
  };
} CRyValue;

#endif
