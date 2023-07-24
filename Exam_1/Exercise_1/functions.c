#define PI 3.14159265359

// Function to calculate the voulume and the area of a cylinder 
int cylinder(double r, double h, double* V, double* S){
    if(r <= 0 || h <= 0) return -1;

    (*V) = PI * (r * r) * h;
    (*S) = 2 * PI * r * h;

    return 0;
}