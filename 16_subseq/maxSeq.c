#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int *array, size_t n){
	size_t i=0,max_seq=0;
	if (n==0){
		return 0;
	}
	else if (n==1){
		return 1;
	}
	else{

		while(i<n-1){
			int curseq=1;
			while(array[i]<array[i+1]&&i<n-1){
				curseq++;
				i++;
			}
			if (curseq>max_seq){
				max_seq=curseq;
			}
			i++;		
		}
		return 	max_seq;
	}
	/*
}
int main(void) {
  if (maxSeq(NULL, 0)) {
    return EXIT_FAILURE;
  }

  int array1[] = {1, 2, 3, 2};
  int array2[] = {2, -3, 5, 6, 8};
  int array3[] = {5};
  int array4[] = {2, 4, 3, 6, 10, 15, -1, 7, 8, 2};
  int array5[] = {-2};
  int array6[] = {2,2,2,3};
  printf("%ld",maxSeq(array2,5));
  if (maxSeq(array1, 0)) {
    printf("not good!1\n");
    return EXIT_FAILURE;
  }
  if (maxSeq(array1, 4) != 3) {
    printf("not good!2\n");
    return EXIT_FAILURE;
  }
  if (maxSeq(array2, 5) != 4) {
    printf("not good!3\n");
    return EXIT_FAILURE;
  }
  if (maxSeq(array3, 1) != 1) {
    printf("not good!4\n");
    return EXIT_FAILURE;
  }
  if (maxSeq(array4, 10) != 4) {
    printf("not good!\n");
    return EXIT_FAILURE;
  }
  if (maxSeq(array5, 1) != 1) {
    printf("not good!\n");
    return EXIT_FAILURE;
  }
  if (maxSeq(array6, 4) != 2) {
    printf("not good!\n");
    return EXIT_FAILURE;
  }

  printf("good!\n");
  return EXIT_SUCCESS;
  */
}
