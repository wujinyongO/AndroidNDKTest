package com.example.elevoc.myapplication;

/**
 * Created by elevoc on 2017/8/9.
 */

public class ClassMethod {

    private static int a1=1;
    private int a2=2;

    public static int getA1() {
        return a1;
    }

    public static void setA1(int a1) {
        ClassMethod.a1 = a1;
    }

    public int getA2() {
        return a2;
    }

    public void setA2(int a2) {
        this.a2 = a2;
    }

    private static void callStaticMethod(String str, int i){
        System.out.format("ClassMethod->callStaticMethod()->str=%s,"+" i=%d\n",str,i);
    }

    private void callInstanceMethod(String str,int i){
        System.out.format("ClassMethod->callStaticMethod()->str=%s,"+" i=%d\n",str,i);
    }
}
