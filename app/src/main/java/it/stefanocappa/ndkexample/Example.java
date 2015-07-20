/*
 * Copyright (C) 2015 Stefano Cappa
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package it.stefanocappa.ndkexample;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.util.Log;
import android.widget.TextView;

import java.util.List;

public class Example extends AppCompatActivity {

    private String instanceField = "Instance Field";
    private static String staticField = "Static Field";

    private static final String TAG = "HelloJni";

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        TextView tw = new TextView(this);
        tw.setText(stringFromJNI());
        setContentView(tw);

        testMethodManyParameters();

        Log.d(TAG, "average*average = " + averageTwoNumberFromJni(6, 10));
    }

    /** A native method that is implemented by the
     * native library, which is packaged
     * with this application.
     */
    public native String stringFromJNI();


    /** This is another native method declaration that is *not*
     * implemented by the library. This is simply to show that
     * you can declare as many native methods in your Java code
     * as you want, their implementation is searched in the
     * currently loaded native libraries only the first time
     * you call them.
     *
     * Trying to call this function will result in a
     * java.lang.UnsatisfiedLinkError exception !
     */
    public native String unimplementedStringFromJNI();


    public native int averageTwoNumberFromJni(int a, int b);


    /**
     * I use this method only to call testMethodWithManyParameters(...) from native part.
     * It's useless i know, but it's an example.
     */
    public native void testMethodManyParameters();


    /**
     * Visibility in not important when i want to call this method from c files
     */
    private String testMethodWithManyParameters(int a, String b, int c, float d, int e, String[] f, Object g) {
        Log.d(TAG, a + "," + b + "," + c + "," + d + "," + e + "," + f[0]+f[1] + "," + g.toString());
        return a + "," + b + "," + c + "," + d + "," + e + "," + f[0]+f[1] + "," + g.toString();
    }

    /**
     * Visibility in not important when i want to call this method from c files
     */
    private int power(int a) {
        return a * a;
    }

    /**
     * Visibility in not important when i want to call this method from c files
     */
    private String instanceMethod() {
        Log.d(TAG,"instance method called");
        return "Instance Method";
    }

    /**
     * Visibility in not important when i want to call this method from c files
     */
    private static String staticMethod() {
        Log.d(TAG, "static method called");
        return "Static Method";
    }

    /**
     * This is used to load the library on application
     * startup.
     */
    static {
        System.loadLibrary("example");
    }
}
