#ifndef DM510_FILE_PTR_H
#define DM510_FILE_PTR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  FILE * file;
  size_t pos;
  size_t size;
  char data[]; // <- Allows the expandsion of the struct.
} file_ptr;

// The end of the filestream, returns the size of the filestream.
size_t fend(FILE *);

// Reads a buffer of a size from a postion in a filestream.
file_ptr * buf_read(FILE *, size_t pos, size_t size);

// Writes a file pointer.
size_t buf_write(const file_ptr *);

// Appends a buffer at the end of the filestream.
file_ptr * append(FILE *, size_t size, const char * buf);

// Appends a file_ptr to the end of the filestream. OBS : updates the file pointers position.
int append_file_ptr(file_ptr * fp);

// Creates a new file_ptr, copies the buffer into itself.
file_ptr * new_file_ptr(FILE *fs, size_t pos, size_t size, const char * buf);

#define struct_read(file,pos,value) (typeof(value)*) buf_read(file,pos, sizeof(value) - sizeof(file_ptr))
#define primitiv_read(file,pos,value) ({file_ptr * fs = buf_read(file,pos,sizeof(value)); typeof(value) a ; memcpy(&a,fs->data,sizeof(a)); free(fs);  a ;})
#define struct_write(value) buf_write((file_ptr *) value)
#define struct_append(file,value) (typeof(value)*) append(file, sizeof(value) - sizeof(file_ptr), (const char *)&value + sizeof(file_ptr))

#endif /* end of include guard: DM510_FILE_PTR_H */
