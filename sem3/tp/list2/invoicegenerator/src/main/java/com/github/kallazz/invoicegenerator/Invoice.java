package com.github.kallazz.invoicegenerator;

import java.text.DecimalFormat;
import java.util.Vector;

// GRASP: High Cohesion
public class Invoice {
    private Party buyer;
    private Party seller;
    private Vector<Element> elements = new Vector<Element>();

    // GRASP: Creator
    public Invoice(final String buyerName, final String buyerEmail, final String sellerName, final String sellerEmail) {
        this.buyer = new Party(buyerName, buyerEmail);
        this.seller = new Party(sellerName, sellerEmail);
    }

    // GRASP: Creator
    public void addElement(final String productName, final double productPrice, final int quantity) {
        elements.add(new Element(productName, productPrice, quantity));
    }

    // GRASP: Information Expert
    public void printInvoice() {
        DecimalFormat df = new DecimalFormat("0.00");

        System.out.format("+-----------------+-----------------------------------------------------+%n");
        System.out.format("| %-15s | %-51s |%n", "Date", java.time.LocalDate.now());
        System.out.format("+-----------------+-----------------------------------------------------+%n");
        System.out.format("| %-15s | %-51s |%n", "Buyer", this.buyer.getName() + ", " + this.buyer.getEmail());
        System.out.format("+-----------------+-----------------------------------------------------+%n");
        System.out.format("| %-15s | %-51s |%n", "Seller", this.seller.getName() + ", " + this.seller.getEmail());
        System.out.format("+-----------------+-----------------------------------------------------+%n");

        System.out.format("+-----------------+-----------------+-----------------+-----------------+%n");
        System.out.format("| Product Name    | Price           | Quantity        | Full price      |%n");
        System.out.format("+-----------------+-----------------+-----------------+-----------------+%n");

        final String leftAlignFormat = "| %-15s | %-15s | %-15s | %-15s |%n";
        for (Element element : elements) {
            System.out.format(leftAlignFormat, element.getProductName(), df.format(element.getProductPrice()) + "zł",
                element.getQuantity(), df.format(element.getProductFullPrice()) + "zł");
        }
        System.out.format("+-----------------+-----------------+-----------------+-----------------+%n");

        System.out.format("+-----------------+-----------------------------------------------------+%n");
        System.out.format("| %-15s | %-51s |%n", "Total Price", df.format(getFullPrice()) + "zł");
        System.out.format("+-----------------+-----------------------------------------------------+%n");
    }

    public Party getBuyer() {
        return this.buyer;
    }

    public Party getSeller() {
        return this.seller;
    }

    public Vector<Element> getElements() {
        return elements;
    }

    // GRASP: Information Expert
    public double getFullPrice() {
        double fullPrice = 0;
        for (Element element : elements) {
            fullPrice += element.getProductFullPrice();
        }
        return Math.round(fullPrice * 100.0) / 100.0;
    }
}
