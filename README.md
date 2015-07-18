# NdkExample in AndroidStudio
My example of an AndroidStudio1.3 RC NDK's project.

# What is it intereseting here?

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


Attention this project requires Android Studio RC1 or greater, gradle 2.5  or greater, and gradle build tool experimental 0.1.0 or greater.


#License

Copyright 2015 Stefano Cappa
  
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
