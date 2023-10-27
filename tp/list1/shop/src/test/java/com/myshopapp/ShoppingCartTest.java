package com.myshopapp;

import static org.junit.Assert.assertTrue;

import org.junit.Test;

public class ShoppingCartTest 
{
    @Test
    public void shouldEmptyShoppingCartHaveNoProducts()
    {
        ShoppingCart cart = new ShoppingCart(new Customer("Joe", "Smith", 25));
        assertTrue( cart.getProductTypesCount() == 0 );
    }

    @Test
    public void shouldAddToShoppingCart()
    {
        ShoppingCart cart = new ShoppingCart(new Customer("Joe", "Smith", 25));
        Product someProduct = new Product("Blue hat", 15, 24);

        cart.addProduct(someProduct, 10);
        assertTrue( cart.getProductTypesCount() == 1 );
    }

    @Test
    public void shouldRemoveFromShoppingCart()
    {
        ShoppingCart cart = new ShoppingCart(new Customer("Joe", "Smith", 25));
        Product someProduct = new Product("Blue hat", 15, 24);

        cart.addProduct(someProduct, 10);
        cart.removeProduct(someProduct);
        assertTrue( cart.getProductTypesCount() == 0 );
    }
}
