#  Task1: Creating a small image processing library
## Subtask 2: Accelerating Matrix Multiplication

 By: Rachit Kumar-2017CS10364
       Rahul Choudhary-2017CS10365

## In this, we have implemented four main functions, namely:
- Convolution(with and without input padding, as convolution and as matrix multiplication(multiplication implemented using mkl, openblas, pthreads and iterative formula))
- Non-linear activations(relu and tanh)
- Subsampling(maxpooling and average pooling)
- Converting a vector of random floats to a vector of probabilities(softmax and sigmoid)

## Convolution without input padding:
#### Input format: ./output convolution_withoutpadding matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows
In this function, we find a new matrix of size one more than than the difference of two matrices whose convolution we are calculating. We reverse the kernel matrix and then multiply element of kernel matrix with corresponding element of input matrix and sum them. This will be the element of output matrix.

## Convolution with input padding:
#### Input format: ./output convolution_withpadding padsize matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows
Here, we first convert the input matrix into another matrix, size of whose both column and row is twice of padding size more than the size of column and row of input matrix. Now, element of new matrix will be same as input matrix around the centre and at the corner, elements will be zero(which depends on the padding size). 
Now we do the same procedure as we did in the without padding part with input matrix as the padded matrix.

## Convolution without input padding as matrix multiplication:
#### Input format: ./output convolution_withoutpadding_matrixmult matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows method_of_matrixmult(manual/mkl/openblas/pthread)
In this, we first create a new matrix of size [(a-b+1)*(a-b+1)][b*b] (where a is the size of input matrix and b is the size of kernel matrix). Elements of this matrix will dependent on input matrix. Here size of every row of the created matrix is b*b. 
The elements of this row will be a sub matrix of input matrix of size equal to the kernel matrix (but not in same way because in created matrix there is only one row, so all the row of sub matrix will be in one row. Hence, the size of each row is b*b). 
Now, we reverse the kernel matrix about the centre and then transfer it into a column matrix of size [b*b][1] which now contains every element of reversed kernel matrix. 
Now, if we multiply them (they are multiplicable because column size of created matrix and row size of column matrix is same i.e, b*b), the output matrix will be a column matrix containing all the element of required matrix(final output of convolution). Now we change it into the final matrix of desired dimensions.

## Convolution with input padding as matrix multiplication:
#### Input format: ./output convolution_withpadding_matrixmult padsize matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows method(manual/mkl/openblas/pthread)
In this we first construct the padded matrix(as done in convolution with padding function) and then use the padded matrix as the input matrix for the procedure of finding convolution as matrix multiplication(described above).

## relu function on matrix elements:
#### Input format: ./output activation relu matrix.txt number_of_rows_in_matrix number_of_columns_in_matrix
In this function, we apply relu function(i.e. f(x)=x if x>0, otherwise f(x)=0) on each individual element of the given matrix.

## tanh function on matrix elements:
#### Input format: ./output activation tanh matrix.txt number_of_rows_in_matrix number_of_columns_in_matrix
In this function, we apply tanh function(i.e. f(x)=(exp(x)-exp(-x))/(exp(x)+exp(-x))) on each individual element of the given matrix.

## Maxpooling of square matrices:
#### Input format: ./output subsampling maxpooling matrix.txt number_of_rows_in_input_matrix number_of_rows_in_output_matrix
In this function, we divide the given axa matrix into b*b parts and iterate in each submatrix to find the maximum in each and store the result in the final matrix.
In this and the next function(average pooling), in the case when the size of input matrix is not divisible by the size of the output matrix, we have ignored the extra(remainder) dimensions of the input matrix to display the output.

## Average pooling of square matrices:
#### Input format: ./output subsampling avgpooling matrix.txt number_of_rows_in_input_matrix number_of_rows_in_output_matrix
In this function, we divide the given axa matrix into b*b parts and iterate in each submatrix to find the average in each and store the result in the final matrix.

## Sigmoid:
#### Input format: ./output probability sigmoid vector.txt size_of_vector
In this function, we calculate the sigmoid function of each element(i.e. f(x)=1/(1+exp(-x))) and save the answer in the same vector.

## Softmax:
#### Input format: ./output probability softmax vector.txt size_of_vector
In this function, we calculate the softmax function of each element(i.e. f(x)=exp(x)/(Σexp(x))) and save the answer in the same vector.

### Methods for calculating matrix mutliplication:
- Using Math Kernel Library(MKL)
- Using OpenBLAS Library
- Using pthreads(optimised for dual core systems)
- Using the mathematical iterative formula
The difference in running time of different implementations foe different inputs can be observed from the plots in the file.

#### To observe the time taken for a multiplication to occur, uncomment the lines starting with 'auto' before and after the place where multiplication takes place. 

## LeNet:
#### Input Format: ./output lenet input.txt


### Error Handling:
- In case of incorrect function argument, it displays the valid function arguments which can be given.
- In case of incorrect number of arguments, it displays the whole input format for the respective function.
- Compulsion on the number of rows and columns(or the length of vector) to be always positive.
- In case of convolution, error message is printed if the kernel size is larger than the sixe of the input matrix. 
- In case of invalid file input or invalid data type input for size of arrays, an exception is thrown.

### Inputs and Plots:
We generated 140 input matrices ( 20 each of row size 16,32,64,128,256,512,1024 ) using input_gen.cpp and runnn.sh . Then we generated the output files for each impleentation using runn.sh and then combined them using combine_output.sh . Then we plotted the graphs in gnuplot showing mean, standard deviation, errors and quartiles. All of the files and plots are enclosed in their respective folders.
