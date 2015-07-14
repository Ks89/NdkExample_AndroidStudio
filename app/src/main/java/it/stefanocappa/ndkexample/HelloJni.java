/*
 * Copyright (C) 2009 The Android Open Source Project
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

public class HelloJni extends AppCompatActivity {

    private String instanceField = "Instance Field";
    private static String staticField = "Static Field";


    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        TextView tw = new TextView(this);
        tw.setText(stringFromJNI());
        setContentView(tw);

    }

    /* A native method that is implemented by the
     * native library, which is packaged
     * with this application.
     */
    public native String  stringFromJNI();


    /* This is another native method declaration that is *not*
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


    private String instanceMethod() {
        Log.d("instanceMethod","method called");
        return "Instance Method";
    }

    private static String staticMethod() {
        Log.d("staticMethod", "static method called");
        return "Static Method";
    }

    /* this is used to load the library on application
     * startup.
     */
    static {
        System.loadLibrary("hello-jni");
    }
}
