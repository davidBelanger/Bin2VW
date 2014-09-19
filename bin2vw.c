//Copyright David Belanger, 2014
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
const int max_string_length = 300;
int main(int argc, char **argv)
{
  if (argc < 4) {
    printf("Usage: ./bin2vw <label file> <feature file> <feature dim>\n");
    return 0;
  }
  
  char label_file_name[max_string_length];
  char feature_file_name[max_string_length];
  strcpy(label_file_name, argv[1]);
  strcpy(feature_file_name, argv[2]);
  int feature_dim = atoi(argv[3]);
  
  FILE* label_file = fopen(label_file_name, "rb");
  if (label_file == NULL) {
    printf("Input label file not found\n");
    return -1;
  }

  FILE* feature_file = fopen(feature_file_name, "rb");
  if (feature_file == NULL) {
    printf("Input feature file not found\n");
    return -1;
  }

  float current_label;
  float * current_feats = (float *) malloc(feature_dim*sizeof(float));
  int i;
  int counter = 0;
  while(!feof(label_file)){
    fread(&current_label,sizeof(float),1,label_file);
    fread(current_feats,sizeof(float),feature_dim,feature_file);
    printf("%d | ",(int) current_label);
    for(i = 0; i < feature_dim; i++){
      printf("%d:%f ",i+1,current_feats[i]);
    }
    printf("\n");
    counter++;
  }
  if(!feof(feature_file)){
    printf("ERROR: the number of labels and features read differed\n");
    exit(1);
  }
  fflush(stdout);
  free(current_feats);
  return 0;
}
