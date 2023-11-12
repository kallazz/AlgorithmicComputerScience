package com.github.kallazz.invoicegenerator;

// GRASP: High Cohesion
public class Product {
    private String name;
    private double price;

    public Product(final String name, final double price) {
        this.name = name;
        this.price = price;
    }

    public String getName() {
        return this.name;
    }

    public double getPrice() {
        return this.price;
    }
}
