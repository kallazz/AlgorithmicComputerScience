package com.myshopapp;

public class Customer {
    private String firstName;
    private String lastName;
    private int age;

    public Customer(final String firstName, final String lastName, final int age) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.age = age;
    }

    public String getFullName() {
        return firstName + " " + lastName;
    }

    public int getAge() {
        return age;
    }
}
