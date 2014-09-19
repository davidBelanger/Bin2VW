//Copyright David Belanger, 2014
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
const int max_string_length = 300;
int main(int argc, char **argv)
{
  if (argc < 4) {
    printf("Usage: ./bin2vw <label file> <feature file> <feature dim> <1: convert labels to ints (for multiclass classification), 0: leave labels as floats (default = 1)>\n");
    return 0;
  }
  
  char label_file_name[max_string_length];
  char feature_file_name[max_string_length];
  strcpy(label_file_name, argv[1]);
  strcpy(feature_file_name, argv[2]);
  int feature_dim = atoi(argv[3]);
  int convert_labels = 1;
  if(argc == 5)
    convert_labels = convert_labels && atoi(argv[4]);

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
  while(1){
    fread(&current_label,sizeof(float),1,label_file);
    fread(current_feats,sizeof(float),feature_dim,feature_file);
    if(!feof(label_file)){
      if(convert_labels)
	printf("%d | ",(int) current_label);
      else
	printf("%f | ",current_label);
      
      for(i = 0; i < feature_dim; i++){
	printf("%d:%f ",i+1,current_feats[i]);
      }
      printf("\n");
    }else{
      break;
    }
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
