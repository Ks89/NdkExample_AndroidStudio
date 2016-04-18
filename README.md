# NdkExample in AndroidStudio
My example of an AndroidStudio NDK's project.


# What is it intereseting here?

## A native method to calculate ((6+10)/2)^2

I created an example to calculate the average between 6 and 10 and after that this app calculates the power of previous result.
I mean 6+10/2 = 8 and finally the result will be ((6+10)/2)= 8\*8 = 64.
But 6+10 was made by the native part, and 8\*8 by java.

This means that:<br>
1. Android creates an Activity and inside it calls **averageTwoNumberFromJni(6, 10)**<br>
2. **averageTwoNumberFromJni(6, 10) is a native method** that return an int<br>
3. in the c implementation of averageTwoNumberFromJni, i call the java method (in the original Activity): **private int power(int a) passing to a the result of averageTwoNumberFromJni(6, 10)**, i.e. 8<br>
4. **power(int a) calculate a\*a and returns the result to the caller method averageTwoNumberFromJni**<br>
5. **averageTwoNumberFromJni returns the result of power to the java part**<br>
6. The result appears in Logacat thanks to: Log.d(TAG, "average\*average = " + averageTwoNumberFromJni(6, 10));


## A native method to show JNI signatures and Object creation

I created an example to print a string with a list of variables, for example String, numbers and so on.

This means that:<br>
1. There is a native method **testMethodManyParameters**. Inside of its i call the Java method **testMethodWithManyParameters** from JNI<br>
2. This java method is **private String testMethodWithManyParameters(int a, String b, Integer c, float d, Double e, String[] f, Object g)**<br>
3. To call its, i must pass as parameters all these objects: **int, String, Integer, float, Double, Object and String[]**<br>
4. int and float are simple, because i can use **jint** and **jfloat**, but for Java Object it's more complicated<br>
5. For Integer and Double i created **two functions that receive "env" and a value**<br>
6. For String it's required to call **(*env)->NewStringUTF(env, "STRING")**<br>
7. For String's Array I created a **char array**, a new **jobjectArray** and initialized with **SetObjectArrayElement**<br>
8. Finally i can call the java method with **CallObjectMethod**<br>
9. In fact, i call the java method and the result is **5,Hello,5,3.0,129.58,firstsecond,Hello3**


#Warning

Attention this project requires Android Studio 2 or greater, gradle 2.12  or greater, and gradle build tool experimental 0.7.0-beta1 or greater.


#License

Copyright 2015-2016 Stefano Cappa
  
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
