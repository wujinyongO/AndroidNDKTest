package com.example.elevoc.myapplication;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    TextView mTestPeople;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private int[] array={9,8,7,6,5,4,3,2,1,0};
    private int[][] array2={{1,2,3,4},{4,5,6,7},{7,8,9,10}};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findView();

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);

        tv.setText("");
//        int a[]=add(array);
//        if(a==null)
//            throw new RuntimeException("a=null");
        transmit2DArray(array2);
        for(int i=0;i<array2.length;i++)
            for(int j=0;j<array2[i].length;j++)
                tv.setText(tv.getText()+String.valueOf(array2[i][j])+" ");

//        transmit1DArray(array);
//        for(int i=0;i<array.length;i++)
//            tv.setText(tv.getText()+String.valueOf(array[i])+" ");

//        tv.setText(connectString("hello ","world!"," I am tom"));

        callJavaStaticMethod();
        callJavaInstanceMethod();

        ClassMethod t=new ClassMethod();
        t.setA2(1);
        accessInstanceField(t);
        accessStaticField();

        tv.setText(""+t.getA2()+" "+ClassMethod.getA1());

        callSuperInstanceMethod();

        // ------------------
        // test People class, people.cpp
        mTestPeople.setText(testPeopleString());
        // ------------------
    }

    private void findView() {
        mTestPeople = (TextView) findViewById(R.id.test_people_class);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native int test(int a,int b);
    public native boolean outputAllData(boolean b,byte by,char c,short s,int i,long l,float f,double d);
    public native String reverseString(String s);//反转字符串
    public native void sort(int a[]);//排序
    public native int[] add(int a[]);//申请一片内存存放相加后的数据

    //jni->java
    public native int[][] getTwoArray(int size);//返回二维数组
    public native int[] getOneArray(int len);//返回一维数组

    //java->jni
    public native void transmit1DArray(int a[]);//传递一维数组
    public native void transmit2DArray(int a[][]);//传递二维数组

    public native String connectString(String... a);//将字符串数组连接成一个字符串,在JNI申请字符串数组内存

    //c c++调用java函数
    public static native void callJavaStaticMethod();//调用java的静态函数
    public static native void callJavaInstanceMethod();//调用java的实例函数

    //c c++调用实例变量和静态变量
    public native static void accessInstanceField(ClassMethod obj);//
    public native static void accessStaticField();//

    public native void callSuperInstanceMethod();

    // ------------------
    // test People class, people.cpp
    private native String testPeopleString();
    // ------------------
}
