- Use smart pointers (unique pointer will be better for this case).
- Shrink the array if its size is less than 25% of the capacity, this will be an extension for 'resize_array' function.
- Adhere to the open/closed principle (OCP), meaning making the code extensible without modifying the existing functions by allowing new behaviors to be added through function pointers or lamba functions.