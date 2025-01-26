//                             Function Overloding
// WAP to input length of side for a cube and input radius and height for a cylinder calculate volume of cube and cylinder using function overloading
#include<stdio.h>
#include<conio.h>
int volume(int);
int volume(int,int,int);
int main()
{
    int s,r,h;
    printf("Enter the Length of Side of Cube: ");
    scanf("%d",&s);
    printf("Enter the Radius of Cylinder: ");
    scanf("%d",&r);
    printf("Enter the Height of Cylinder: ");
    scanf("%d",&h);
    printf("Volume of Cube is : %d",volume(s));
    printf("\nVolume of Cylinder is : %d",volume(r,h));
}