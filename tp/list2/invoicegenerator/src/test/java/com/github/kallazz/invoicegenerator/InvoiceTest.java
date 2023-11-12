package com.github.kallazz.invoicegenerator;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class InvoiceTest 
{
    @Test
    public void shouldCreateInvoiceWithBuyerAndSeller()
    {
        Invoice invoice = new Invoice(
            "John Buyer", "john.buyer@example.com",
            "Mike Seller", "mike.seller@example.com"
        );

        assertEquals("John Buyer", invoice.getBuyer().getName());
        assertEquals("john.buyer@example.com", invoice.getBuyer().getEmail());
        assertEquals("Mike Seller", invoice.getSeller().getName());
        assertEquals("mike.seller@example.com", invoice.getSeller().getEmail());
    }

    @Test
    public void shouldHaveNoElementsInNewInvoice()
    {
        Invoice invoice = new Invoice(
            "John Buyer", "john.buyer@example.com",
            "Mike Seller", "mike.seller@example.com"
        );

        assertEquals(0, invoice.getElements().size());
    }

    @Test
    public void shouldAddElementsToInvoice()
    {
        Invoice invoice = new Invoice(
            "John Buyer", "john.buyer@example.com",
            "Mike Seller", "mike.seller@example.com"
        );
        invoice.addElement("Keyboard", 150.0, 2);
        invoice.addElement("Mouse Pad", 29.99, 3);

        assertEquals(2, invoice.getElements().size());
    }

    @Test
    public void shouldHaveZeroFullPriceForEmptyInvoice()
    {
        Invoice invoice = new Invoice(
            "John Buyer", "john.buyer@example.com",
            "Mike Seller", "mike.seller@example.com"
        );

        assertEquals(0.0, invoice.getFullPrice(), 0.001);
    }

    @Test
    public void shouldCalculateCorrectFullPriceForInvoiceElements()
    {
        Invoice invoice = new Invoice(
            "John Buyer", "john.buyer@example.com",
            "Mike Seller", "mike.seller@example.com"
        );
        invoice.addElement("Keyboard", 150.0, 2);
        invoice.addElement("Mouse Pad", 29.99, 3);

        assertEquals(150.0 * 2 + 29.99 * 3, invoice.getFullPrice(), 0.001);
    }
}
