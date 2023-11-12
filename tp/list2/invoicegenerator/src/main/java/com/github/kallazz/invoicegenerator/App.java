package com.github.kallazz.invoicegenerator;

import java.util.Scanner;

public class App {
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_RESET = "\u001B[0m";

    private static void addElement(final Scanner scanner, final Invoice invoice) {
        System.out.println("\nAdding an element to the invoice:");

        System.out.print("Enter product name: ");
        final String productName = scanner.nextLine();

        try {
            System.out.print("Enter product price: ");
            final double productPrice = Double.parseDouble(scanner.nextLine());

            System.out.print("Enter quantity: ");
            final int quantity = Integer.parseInt(scanner.nextLine());

            invoice.addElement(productName, productPrice, quantity);

            System.out.println(ANSI_GREEN + productName + " added to the invoice." + ANSI_RESET);
        }
        catch (final NumberFormatException ex) {
            System.out.println(ANSI_RED + "Please provide a correct number next time." + ANSI_RESET);
            return;
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter buyer's name: ");
        final String buyerName = scanner.nextLine();
        System.out.print("Enter buyer's e-mail address: ");
        final String buyerEmail = scanner.nextLine();

        System.out.print("Enter seller's name: ");
        final String sellerName = scanner.nextLine();
        System.out.print("Enter seller's e-mail address: ");
        final String sellerEmail = scanner.nextLine();

        Invoice invoice = new Invoice(buyerName, buyerEmail, sellerName, sellerEmail);

        while (true) {
            System.out.println("\nChoose an option:");
            System.out.println("1. Add an element to the invoice");
            System.out.println("2. Print the invoice");
            System.out.println("3. End the program");

            try {
                int choice = Integer.parseInt(scanner.nextLine());

                switch (choice) {
                    case 1:
                        addElement(scanner, invoice);
                        break;
                    case 2:
                        System.out.println("\nInvoice:");
                        invoice.printInvoice();
                        break;
                    case 3:
                        System.out.println("Exiting the program.");
                        System.exit(0);
                        break;
                    default:
                        System.out.println("Invalid choice. Please choose a valid option.");
                }
            }
            catch (final NumberFormatException ex) {
                System.out.println(ANSI_RED + "Please provide an integer." + ANSI_RESET);
            }
        }
    }
}
