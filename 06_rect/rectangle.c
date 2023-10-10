#include <stdio.h>
#include <stdlib.h>
//I've provided "min" and "max" functions in
//case they are useful to you

typedef struct{
	int x;
	int y;
	int height;
	int width;
}rectangle;
rectangle intersection(rectangle r1, rectangle r2); 
rectangle find_x_max(rectangle r1, rectangle r2);
rectangle find_x_min(rectangle r1, rectangle r2);

rectangle find_y_min(rectangle r1, rectangle r2);
rectangle find_y_max(rectangle r1, rectangle r2);
int min (int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}
int max (int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}
rectangle find_x_max(rectangle r1, rectangle r2){
	if (r1.x>r2.x){
		return r1;
	}
	else{
		return r2;
	}
rectangle find_x_min(rectangle r1, rectangle r2){
	rectangle max=find_x_max(r1,r2);
	if(max.x==r1.x&&max.y==r1.y&&max.height==r1.height&&max.width==r1.width){
		return r2;
	}
	else{
		return r1;
	}

rectangle find_y_max(rectangle r1, rectangle r2){
	if (r1.y>r2.y){
		return r1;
	}
	else{
		return r2;
	}
rectangle find_y_min(rectangle r1, rectangle r2){
	rectangle max=find_y_max(r1,r2);
	if(max.x==r1.x&&max.y==r1.y&&max.height==r1.height&&max.width==r1.width){
		return r2;
	}
	else{
		return r1;
	}
//Declare your rectangle structure here!


rectangle canonicalize(rectangle r) {
  //WRITE THIS FUNCTION
	if(r.height<0){
		r.height=-r.height;
		r.y=r.y-r.height;
	}
	if(r.width<0){
		r.width=-r.width;
		r.x=r.x-r.width;
	}
  return r;
}
rectangle intersection(rectangle r1, rectangle r2) {
  //WRITE THIS FUNCTION
	rectangle x_max=find_x_max(r1,r2);
	rectangle x_min=find_x_min(r1,r2);
	rectangle y_max=find_y_max(r1,r2);
	rectangle y_min=find_y_min(r1,r2);
	//judge if intersection
	if (x_max.x<x_min.x+x_min.w && 
			y_max.y<y_min.y+y_min.h){
		//distinguish x
		if (x_max.x+x_max.w>x_min.x+x_min.w){
			//distinguish y
			if (y_max.y+y_max.h>y_min.y+y_min.h){
			rectangle anw1={x_max.x,y_max.y,y_min.height-y_max.y+y_min.y, x_min.width-x_max.x+x_min.x};
				return anw1;
			}
			else{
				rectangle anw2={x_max.x,y_max.y,y_max.height, x_min.width-x_max.x+x_min.x}
			}
		}
		else{
			if (y_max.y+y_max.h>y_min.y+y_min.h){
				rectangle anw3={x_max.x,y_max.y, y_min.height-y_max.y+y_min.y, x_max.width};
				return anw3;
			}
			else{
				rectangle anw4={x_max.x ,y_max.y, y_max.height, x_max.width};
				return anw4;
			}
		}
	}
	else{
		rectangle zero={0,0,0,0};
		return zero;
	}
}

//You should not need to modify any code below this line
void printRectangle(rectangle r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d,%d) to (%d,%d)\n", r.x, r.y, 
	                           r.x + r.width, r.y + r.height);
  }
}

int main (void) {
  rectangle r1;
  rectangle r2;
  rectangle r3;
  rectangle r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);
  
  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  //test everything with r1
  rectangle i = intersection(r1,r1);
  printf("intersection(r1,r1): ");
  printRectangle(i);

  i = intersection(r1,r2);
  printf("intersection(r1,r2): ");
  printRectangle(i);
  
  i = intersection(r1,r3);
  printf("intersection(r1,r3): ");
  printRectangle(i);

  i = intersection(r1,r4);
  printf("intersection(r1,r4): ");
  printRectangle(i);

  //test everything with r2
  i = intersection(r2,r1);
  printf("intersection(r2,r1): ");
  printRectangle(i);

  i = intersection(r2,r2);
  printf("intersection(r2,r2): ");
  printRectangle(i);
  
  i = intersection(r2,r3);
  printf("intersection(r2,r3): ");
  printRectangle(i);

  i = intersection(r2,r4);
  printf("intersection(r2,r4): ");
  printRectangle(i);

  //test everything with r3
  i = intersection(r3,r1);
  printf("intersection(r3,r1): ");
  printRectangle(i);

  i = intersection(r3,r2);
  printf("intersection(r3,r2): ");
  printRectangle(i);
  
  i = intersection(r3,r3);
  printf("intersection(r3,r3): ");
  printRectangle(i);

  i = intersection(r3,r4);
  printf("intersection(r3,r4): ");
  printRectangle(i);

  //test everything with r4
  i = intersection(r4,r1);
  printf("intersection(r4,r1): ");
  printRectangle(i);

  i = intersection(r4,r2);
  printf("intersection(r4,r2): ");
  printRectangle(i);
  
  i = intersection(r4,r3);
  printf("intersection(r4,r3): ");
  printRectangle(i);

  i = intersection(r4,r4);
  printf("intersection(r4,r4): ");
  printRectangle(i);


  return EXIT_SUCCESS;

}
