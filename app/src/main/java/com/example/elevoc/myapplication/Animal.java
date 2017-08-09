package com.example.elevoc.myapplication;

/**
 * Created by elevoc on 2017/8/9.
 */

public class Animal {

    protected String name;

    public Animal(String name) {
        this.name = name;
        System.out.println("Animal Construct call");
    }

    public String getName() {
        System.out.println("Animal getName() call");
        return name;
    }

    public void run(){
        System.out.println("Animal run");
    }
}
