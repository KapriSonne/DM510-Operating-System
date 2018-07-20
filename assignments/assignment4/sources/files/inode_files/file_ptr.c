#include "file_ptr.h"

file_ptr * new_file_ptr(FILE * fp, size_t pos, size_t size, const char * data){
  file_ptr * f = malloc(sizeof(*f) + size);
  f->file = fp;
  f->pos = pos;
  f->size = size;
  if(data) memcpy(f->data, (char*)data, size);
  return f;
}

size_t fend(FILE * fp){
  fseek(fp,0,SEEK_END);
  return ftell(fp);
}

file_ptr * buf_read(FILE * fp, size_t pos, size_t size){
  fseek(fp,pos,SEEK_SET);
  file_ptr * f = new_file_ptr(fp,pos,size,NULL);
  int written = fread(f->data, size, 1, fp);
  if(!written) {
    free(f);
    return NULL;
  }
  return f;
}

size_t buf_write(const file_ptr * fp){
  fseek(fp->file,fp->pos,SEEK_SET);
  return fwrite(fp->data,fp->size,1,fp->file);
}

file_ptr * append(FILE *fp, size_t size, const char * data){
  file_ptr *f = new_file_ptr(fp,fend(fp),size,data);
  int written = fwrite(f->data,f->size,1,f->file);
  if(!written) {
    free(f);
    return NULL;
  }
  return f;
}

int append_file_ptr(file_ptr * f){
  f->pos = fend(f->file);
  return fwrite(f->data,f->size,1,f->file);
}
