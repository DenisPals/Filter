# Filter - A C program that applies a grayslace, sepia, reflect or blur filter to a bitmap image
## Complexity
This instagram-like filter applies a number of filters to a bitmap image. This is achieved by reading in a given image, iterating over each pixel and changing their RGB values accordingly. To apply an grayscale filter, the average of of all RGB values of a 24 bit pixel (each byte represents a color) is taken and is reapplied to the pixel. This will result in a grayscale version of that pixel. For a sepia filter, a sepia formula is applied to each Pixel of the image:
```
  sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
  sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
  sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
```
To create a reflection effect (horizontaly mirrored image), the pixels must be "rearraged" meaning their respective color values are stored and flipped with the very opposite pixels values.
The blur filter can be applied when iterating of clusters of 3x3 pixels and applying their average color values to the pixel in the middle of the grid. 

The challenge was:
* The implementation of the grayscale function. 
* The implementation of the sepia function. 
* The implementation of the reflect function. 
* The implementation of the blur  function. 


## Files
**helpers.c**
Filter-less.c contains the filtering functions, written in the C programming language. These are then utelized by filter.c in order to perform the filter operation. 

**filter.c**
Filter.c contains the code that reads in a bmp file and creates a new one. The filter functions are called using a switch, which are then applied to the image that is stored in memory. Filter.c also handels the command-line user inputs.

**bmp.h**
Bmp.h contains BMP-related data types based on Microsoft's own. These are provided by Microsoft and can be found in [Microsoft's Documentation](http://msdn.microsoft.com/en-us/library)

## How to run
To run this program, a C compiler must be installed. The best way is to run it is to use a Linux enviroment like WSL for windows (if not using Linux) and to run (after compiling) one of the following: 
Grayscale
> ./filter -g INFILE.bmp OUTFILE.bmp

Sepia
> ./filter -s INFILE.bmp OUTFILE.bmp

Reflect
> ./filter -r INFILE.bmp OUTFILE.bmp

Blur
> ./filter -b INFILE.bmp OUTFILE.bmp

A number of images has been provided in the image folder.

## Output
**The first image is the original one**

![alt text](https://github.com/DenisPals/Filter/blob/main/filterExample.jpg?raw=true)