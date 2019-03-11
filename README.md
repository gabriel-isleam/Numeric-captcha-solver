# Numeric-captcha-solver


   The program is working with bmp files (image files). The first task involves changing the color of all digits from one image to a color specified in the input file.


   To do this, the program copies directly to the final file the file header and the info header, and for the pixel matrix it copies directly the pixels with value 255 for blue, green and red color. For the other pixels, program sets the values for these three colors with the values specified in the input file. When finding the padding in the pixel matrix, it will write 0 in the output file. Padding bytes must be appended to the end of the rows in order to bring up the length of the rows to a multiple of four bytes. So, the number of padding bytes is calculated as follows: for a file width which is a multiple of 4, the number of padding bytes will be 0 and for the other cases, the number is calculated by following formula: 4 - (pixel_matrix_width * 3) % 4.


   Second task involves finding the numeric characters from the captcha file and writing them in an output text file. Digit recognition is made through special functions described in the source file. This is done by going through the pixel matrix on columns from top to bottom, from right to left. Numbers are saved in an array in reverse order, then written to the output file.


   Third task involves removing some digits from the captcha files, digits specified in the input file. To accomplish this, the program uses the second task to save the numbers, their starting position and their color in three different arrays. As long as the program reads number to remove from input file, they will be removed from the number array and from the color array. The starting position array will remain unchanged, as the following digits will be shifted one position to the left (the next digit moved on the position of the removed digit and so on). For the remaining digits, the pixels in the pixel matrix will have a value that corresponds to the position in the array + 1 (an auxiliary matrix which helps writing the output captcha file), so the pixels for the first digit will have the value 2, second digit value 3 and so on. It is written in the output file the corresponding values from color array, when the program finds a value bigger than 2 in the auxiliary pixel matrix.
