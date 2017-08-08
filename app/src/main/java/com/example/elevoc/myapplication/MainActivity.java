package com.example.elevoc.myapplication;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private int[] array={9,8,7,6,5,4,3,2,1,0};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);

        tv.setText("");
//        int a[]=add(array);
//        if(a==null)
//            throw new RuntimeException("a=null");
////        for(int i=0;i<a.length;i++)
//            for(int j=0;j<a.length;j++)
//                tv.setText(tv.getText()+String.valueOf(a[j])+" ");

        transmit1DArray(array);
        for(int i=0;i<array.length;i++)
            tv.setText(tv.getText()+String.valueOf(array[i])+" ");

//        tv.setText(connectString("hello ","world!"," I am tom"));
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native int test(int a,int b);
    public native boolean outputAllData(boolean b,byte by,char c,short s,int i,long l,float f,double d);
    public native String connectString(String... a);//将字符串数组连接成一个字符串
    public native String reverseString(String s);//反转字符串
    public native void sort(int a[]);
    public native int[] add(int a[]);//申请一片内存存放相加后的数据
    public native int[][] getTwoArray(int size);//返回而且数组
    public native int[] getOneArray(int len);//返回以为数组
    public native void transmit1DArray(int a[]);//传递一维数组
    public native void transmit2DArray(int a[][]);
}
