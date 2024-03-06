package com.github.kallazz.invoicegenerator;

// GRASP: Pure Fabrication
public interface IDatabaseHandler {
    void connectToDatabase(String url, String name, String password);
    void closeConnection();

    void saveInvoice(Invoice invoice);
    Invoice getInvoice(int invoiceId);
}
