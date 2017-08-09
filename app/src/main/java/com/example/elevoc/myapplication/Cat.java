package com.example.elevoc.myapplication;

/**
 * Created by elevoc on 2017/8/9.
 */

public class Cat extends Animal {

    public Cat(String name) {
        super(name);
        System.out.println("Cat Construct call");
    }

    @Override
    public String getName() {
        return "my name is "+this.name;
    }

    @Override
    public void run() {
        System.out.println(this.name+" Cat run");
    }
}
