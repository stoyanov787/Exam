// Function to find longest subseqence
void subseq(int arr[], int n, int dest[], int *new_n){
    dest[0] = arr[0];
    *new_n = 1;
    for(int i = 1; i < n; i++){;
        if(arr[i] < arr[i - 1]){
            dest[(*new_n)] = arr[i];
            (*new_n) = (*new_n) + 1;
        }else{
            break;
        }
    }
}