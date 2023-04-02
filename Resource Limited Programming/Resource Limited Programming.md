# Resource Limited Programming
###### By: Adelina and Ines

### Introduction
Many of the microcontrollers used in the industry have **limited resources**, especially when it comes to their computing powers. 

The Arduino Uno board, for example, cannot perform floating-point operations natively (computer's natural, basic mode of operation) It doesn’t have a *FPU (Floating Point Unit)*! When you use floats on it, it has to sweat through hundreds of assembly instructions to perform a simple addition or even return the wrong results for comparision between two numbers.

This problem can result in many inaccuracies, slower computations and an overall poor performance.

In order to improve this performance, we had to search for other alternatives to be able to get floating numbers calculations in a faster and more accurate way. Some of the solutions are *fixed-point types*, pre-calculated *lookup tables* and the use of *piece-wise polynomial interpolation*. These terms will be explained further in this tutorial.


### Fixed Point Numbers
**Fixed point numbers** are numbers for which there is a fixed location of the point separating integers from fractional numbers.
We reserve some bits for the integer part and some for the fractional part. This is in contrast to a **floating-point number**, where the "point" is not fixed and can "float" to different positions depending on the value being represented.

We decided to use 40.24 because 24 bits for the decimal part was enough for our application but this ratio can be adjusted depending on the desired outcome. 

To convert a number into a fixed point number we shift the binary representation of the number (which is 2^FIXED_FBITS) and we multiply it with the number we want to convert. To make it back into float in this case we divide instead.
```cpp
#define FIXED_BITS        64
#define FIXED_WBITS       40
#define FIXED_FBITS       24
#define MAKE_FIXED(a)     (int64_t)((a*(1 << FIXED_FBITS)))
#define MAKE_FLOAT(a)     (double )((double)a/(double) (1<< FIXED_FBITS))
```

### Fixed Point Arithmetic 
The benefit of fixed point numbers is that we can perform **fixed point arithmetic** which is faster than float arithmetic when a floating point unit is not available.
Addition and Subtraction are self explanatory, as for multiplication we multiply both numbers then shift to the right which is the equivalent of dividing by the number to scale down the result to suit the fixed point notation. For division we shifted to the left (multiply) the number then we divide and we do it that way because it keeps the accuracy.
```cpp
static int64_t Mul(int64_t a, int64_t b) {
    return (((int64_t) a * (int64_t) b) >> FIXED_FBITS);
}

static int64_t Div(int64_t a, int64_t b) {
    return ((int64_t) a << FIXED_FBITS / (int64_t) b);
}

static int64_t Add(int64_t a, int64_t b) {
    return (((int64_t) a + (int64_t) b));
}

static int64_t Sub(int64_t a, int64_t b) {
    return (((int64_t) a - (int64_t) b));
}
```

### Piecewise Polynomial Interpolation 

**Piecewise interpolation** is a process of determining the unknown values that lie in between the known data points.

This solution is very useful because if we have a **lookup table** (see below) with certain values and we want to determine the values in between, we can use interpolation to find those values.

The corresponding *equation* of this polynomial interpolation is the following:
![](https://i.imgur.com/mGC6gVP.png)

```cpp
static int64_t
newton_poly_interpolation(int64_t x, int64_t x1, int64_t x2, int64_t x3, int64_t f1, int64_t f2, int64_t f3) {
    int64_t b1 = f1;
    int64_t b2 = Div(Sub(f2, f1), Sub(x2, x1));
    int64_t b3 = Div(Sub(Div(Sub(f3, f2), Sub(x3, x2)), Div(Sub(f2, f1), Sub(x2, x1))), Sub(x3, x1));
    int64_t result = Add(b1, Add(Mul(b2, Sub(x, x1)), Mul(b3, Mul(Sub(x, x1), Sub(x, x2)))));
    return result;
}
```

### Lookup Tables 

**Lookup tables** are arrays of data that maps input values to output values.

A lookup table contains **output values** of a certain function corresponding to **input values**. Instead of using a function every time lookup tables offer simple array indexing to find the results of a function.

As an alternative, you can use lookup tables by creating two arrays one for the input values and the other one for their corresponding output values using a specific mathematical function.
This method saves us a lot of time and computation by having *pre-calculated results* of some input values. This means that for specific values wwe do not have to calculate the results using a function, we can just retrieve the result from the output array.

The two arrays below represent the ADC measurement values we got and their corresponding pressure(without adding the unit coefficients) using the following function:

![](https://i.imgur.com/IlfuA2d.png)


```cpp
float ADC_measures[10]={1.96,2.2,3.0,3.8,4.6,5.4,6.2,7.0,7.8,8.6};
float pressure_before_unit[10]={281.83829,562.341325,5623.413252,56234.13252,562341.3252,5623413.252,
                                    56234132.52,562341325.2,5623413252.0,56234132520.0};

```

### IKR 270 Gauge 
We were given the task of reading and converting the signal of the **IKR 270 vacuum gauge**. So firstly, we needed to read a 10-bit ADC value (from 0 to 1023) then convert it to an analogue signal in the range of 0..10V.
Secondly, we had to calculate the corresponding pressure of each signal value. For that, we created intervals for our **polynomial interpolation** function, converted them into *fixed points*, and used interpolation to find the values the user wants to calculate.

```cpp
template <typename T>
T ADC_to_sensor(T sensor_value) {
    auto result= (sensor_value * 10 / 1023);
    return result;
}
```
In our program the user can choose the pressure unit(either Pa or mBar) after that he will be asked to enter an ADC value (between 0 and 1023). The program will then convert this value into an analogue signal value, that will be translated into a fixed-point value and then return the corresponding pressure with the chosen unit.

### Conclusion
Having talked about some of the elements of resource limited programming and our application of it on the *IKR 270 Gauge* I hope that it was clear how these concepts work. You can check our detailed work [here](https://github.com/ababsmuc/Advanced-Programming-Concepts).

Some other areas where this might be useful is in *gaming* when, for example, keeping track of position in 3D space, direction you are facing, how far bones move during a single frame of animation, calculating the distance between two objects, calculating the lighting of a specific pixel, and so on and in *digital signal processing* when using digital signal processor without a FPU makes for better performance, cheaper processor and lower power draw. 

### Main Resources Used
[Fixed Point Numbers in C++](https://www.youtube.com/watch?v=ZMsrZvBmQnU&t=1410s)

[Fixed Point numbers, lookup tables and interpolation](https://www.coranac.com/tonc/text/fixed.htm)

[Piecewise Polynomial Interpolation](https://www.youtube.com/playlist?list=PLYdroRCLMg5NTT00m-7ituVGdtY1X680M)