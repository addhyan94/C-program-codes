//                             Function Overloding
//WAP to input L,B,H for  cubiod and R for sphere calculate volume of cubiod and sphere using function overloding.
#include<stdio.h>
#include<conio.h>
int volume(int,int,int);
int volume(int);
int main()
{
    int l,b,h,r;
    printf("Enter the Length of Cubiod: ");
    scanf("%d",&l);
    printf("Enter the Breadth of Cubiod: ");
    scanf("%d",&b);
    printf("Enter the Height of Cubiod: ");
    scanf("%d",&h);
    printf("Enter the Radius of Sphere: ");
    scanf("%d",&r);
    printf("Volume of Cubiod is : %d",volume(l,b,h));
    printf("\nVolume of Sphere is : %d",volume(r));
}