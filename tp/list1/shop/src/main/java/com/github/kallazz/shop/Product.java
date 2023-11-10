package com.github.kallazz.shop;

public class Product {
    private String name;
    private int price;
    private int expectedDeliveryTime; // in hours

    public Product(final String name, final int price, final int expectedDeliveryTime) {
        this.name = name;
        this.price = price;
        this.expectedDeliveryTime = expectedDeliveryTime;
    }

    public String getName() {
        return name;
    }

    public int getPrice() {
        return price;
    }

    public int getExpectedDeliveryTime() {
        return expectedDeliveryTime;
    }

    public void changeName(final String name) {
        this.name = name;
    }

    public void changePrice(final int price) {
        this.price = price;
    }

    public void changeExpectedDeliveryTime(final int expectedDeliveryTime) {
        this.expectedDeliveryTime = expectedDeliveryTime;
    }
}
