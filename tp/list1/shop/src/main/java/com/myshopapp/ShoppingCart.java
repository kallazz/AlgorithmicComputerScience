package com.myshopapp;

import java.util.HashMap;
import java.util.Map;

public class ShoppingCart {
    private final int MIN_DELIVERY_TIME = 24;

    private Customer customer;
    private int totalValue;
    // <Product object, quantity> is held in this map
    private Map<Product, Integer> products = new HashMap<>();

    public ShoppingCart(final Customer customer) {
        this.customer = customer;
        totalValue = 0;
    }

    public void addProduct(final Product product, final int quantity) {
        if (products.containsKey(product)) {
            // update the quantity if the product is already in the cart
            products.put(product, products.get(product) + quantity);
        } else {
            products.put(product, quantity);
        }

        totalValue += product.getPrice() * quantity;
    }

    public void removeProduct(final Product product) {
        if (products.containsKey(product)) {
            products.remove(product);
        }
    }

    public int getProductTypesCount() {
        return products.size();
    }

    public int getTotalValue() {
        return totalValue;
    }

    public void buy() {
        System.out.println("Dear " + customer.getFullName() + ",");
        System.out.println("Thank you for buying: ");
        System.out.print(getProductList());
        System.out.println("Total price: " + getTotalValue() + "zł");
        System.out.println("The order should be delivered in about " + getMaxDeliveryTime() + " hours");
    }

    private String getProductList() {
        String list = "";

        for (Map.Entry<Product, Integer> item : products.entrySet()) {
            list += item.getValue() + " " + item.getKey().getName() + '\n';
        }

        return list;
    }

    private int getMaxDeliveryTime() {
        int maxDeliveryTime = MIN_DELIVERY_TIME;
        for (Map.Entry<Product, Integer> item : products.entrySet()) {
            int itemDeliveryTime = item.getKey().getExpectedDeliveryTime();
            if (itemDeliveryTime > maxDeliveryTime) {
                maxDeliveryTime = itemDeliveryTime;
            }
        }

        return maxDeliveryTime;
    }
}
