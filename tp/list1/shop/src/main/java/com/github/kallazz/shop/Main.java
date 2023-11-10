package com.github.kallazz.shop;

public class Main {
    public static void main(String[] args) {
        Customer customer = new Customer("John", "Smith", 20);
        ShoppingCart cart = new ShoppingCart(customer);

        Product shoes = new Product("Shoes", 100, 24);
        Product tshirt = new Product("T-shirt", 50, 24);
        Product sunglasses = new Product("Sunglasses", 120, 48);

        cart.addProduct(shoes, 1);
        cart.addProduct(sunglasses, 1);
        cart.addProduct(tshirt, 3);

        cart.buy();
    }
}
