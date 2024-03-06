package com.github.kallazz.invoicegenerator;

// GRASP: High Cohesion
public class Element {
    private Product product;
    private int quantity;

    // GRASP: Creator
    public Element(final String productName, final double productPrice, final int quantity) {
        this.product = new Product(productName, productPrice);
        this.quantity = quantity;
    }

    public int getQuantity() {
        return this.quantity;
    }

    public String getProductName() {
        return this.product.getName();
    }

    public double getProductPrice() {
        return this.product.getPrice();
    }

    // GRASP: Information Expert
    public double getProductFullPrice() {
        return this.product.getPrice() * quantity;
    }
}
